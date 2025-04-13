#include <stdio.h>
#include <string.h>

int q[100], front = -1, rear = -1;

struct process {
    char name[20];
    int at, bt, wt, tt, ct, left, status;
} p[20];

struct done {
    char name[20];
    int st, ct;
} d[100];

void enqueue(int j) {
    if (front == -1 && rear == -1)
        front = 0;
    q[++rear] = j;
}

int dequeue() {
    int item = q[front];
    if (front == rear)
        front = rear = -1;
    else
        front++;
    return item;
}

int main() {
    int n, t, i, j, k, time = 0, num = 0, ls = 0, idle = 0;
    float avwt = 0, avtt = 0;

    printf("ENTER THE NUMBER OF PROCESSES: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nENTER DETAILS OF PROCESS %d", i + 1);
        printf("\nPROCESS NAME: ");
        scanf(" %s", p[i].name);
        printf("ARRIVAL TIME: ");
        scanf("%d", &p[i].at);
        printf("BURST TIME: ");
        scanf("%d", &p[i].bt);
        p[i].left = p[i].bt;
        p[i].status = 0;
    }

    printf("\nENTER THE TIME QUANTUM: ");
    scanf("%d", &t);

    for (time = 0; ls < n;) {
        for (j = 0; j < n; j++) {
            if (p[j].status == 0 && p[j].at <= time) {
                enqueue(j);
                p[j].status = 1;
            }
        }

        if (front == -1) {
            if (idle == 0) {
                strcpy(d[num].name, "Idle");
                d[num].st = time;
                idle = 1;
            }
            time++;
        } else {
            if (idle == 1) {
                d[num].ct = time;
                num++;
                idle = 0;
            }

            k = dequeue();
            d[num].st = time;
            strcpy(d[num].name, p[k].name);

            if (p[k].left <= t) {
                time += p[k].left;
                d[num].ct = time;
                p[k].ct = time;
                p[k].tt = p[k].ct - p[k].at;
                p[k].wt = p[k].tt - p[k].bt;
                p[k].status = 2;
                ls++;
            } else {
                time += t;
                d[num].ct = time;
                p[k].left -= t;

                // Check for newly arrived processes during this time slice
                for (j = 0; j < n; j++) {
                    if (p[j].status == 0 && p[j].at > d[num].st && p[j].at <= time) {
                        enqueue(j);
                        p[j].status = 1;
                    }
                }

                enqueue(k);
            }
            num++;
        }
    }

    if (idle == 1) num++; // Close last idle block

    printf("\n\nPROCESS NAME\tCT\tWT\tTT\n\n");
    for (i = 0; i < n; i++) {
        printf("%s\t\t%d\t%d\t%d\n", p[i].name, p[i].ct, p[i].wt, p[i].tt);
        avwt += p[i].wt;
        avtt += p[i].tt;
    }

    printf("\n\nGANTT CHART\n");
    printf("----------------------------------------------------------------------------\n|");
    for (i = 0; i < num; i++) {
        printf(" %s\t|", d[i].name);
    }
    printf("\n----------------------------------------------------------------------------\n");

    for (i = 0; i < num; i++) {
        printf("%d\t", d[i].st);
    }
    printf("%d\n", d[num - 1].ct);

    printf("\nAVERAGE WAITING TIME: %.2f", avwt / n);
    printf("\nAVERAGE TURNAROUND TIME: %.2f\n", avtt / n);

    return 0;
}