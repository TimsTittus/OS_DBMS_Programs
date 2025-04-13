#include <stdio.h>

int fifo(int p[], int n, int f);
int lru(int p[], int n, int f);
int lfu(int p[], int n, int f);

int main() {
    int n, f;
    int p[50];

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &f);

    int pf1 = fifo(p, n, f);
    int pf2 = lru(p, n, f);
    int pf3 = lfu(p, n, f);

    printf("\nPage Fault Summary:");
    printf("\nFIFO = %d", pf1);
    printf("\nLRU  = %d", pf2);
    printf("\nLFU  = %d\n", pf3);

    return 0;
}

// FIFO Algorithm
int fifo(int p[], int n, int f) {
    int q[10], front = 0, rear = 0, count = 0;
    for (int i = 0; i < f; i++) q[i] = -1;

    printf("\n\n--- First In First Out ---\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < f; j++) {
            if (q[j] == p[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            q[rear] = p[i];
            rear = (rear + 1) % f;
            count++;
        }

        for (int j = 0; j < f; j++)
            (q[j] == -1) ? printf("-\t") : printf("%d\t", q[j]);
        printf("\n");
    }
    return count;
}

// LRU Algorithm
int lru(int p[], int n, int f) {
    int q[20], time[20], count = 0;
    for (int i = 0; i < f; i++) {
        q[i] = -1;
        time[i] = 0;
    }

    printf("\n--- Least Recently Used ---\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < f; j++) {
            if (q[j] == p[i]) {
                found = 1;
                time[j] = i;
                break;
            }
        }

        if (!found) {
            int lru_index = 0;
            for (int j = 1; j < f; j++)
                if (time[j] < time[lru_index]) lru_index = j;

            q[lru_index] = p[i];
            time[lru_index] = i;
            count++;
        }

        for (int j = 0; j < f; j++)
            (q[j] == -1) ? printf("-\t") : printf("%d\t", q[j]);
        printf("\n");
    }
    return count;
}

// LFU Algorithm
int lfu(int p[], int n, int f) {
    int q[50], freq[50], time[50], count = 0;
    for (int i = 0; i < f; i++) {
        q[i] = -1;
        freq[i] = 0;
        time[i] = -1;
    }

    printf("\n--- Least Frequently Used ---\n");
    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < f; j++) {
            if (q[j] == p[i]) {
                freq[j]++;
                found = 1;
                break;
            }
        }

        if (!found) {
            int replace = 0;
            for (int j = 1; j < f; j++) {
                if ((freq[j] < freq[replace]) || 
                    (freq[j] == freq[replace] && time[j] < time[replace])) {
                    replace = j;
                }
            }

            q[replace] = p[i];
            freq[replace] = 1;
            time[replace] = i;
            count++;
        }

        for (int j = 0; j < f; j++)
            (q[j] == -1) ? printf("-\t") : printf("%d\t", q[j]);
        printf("\n");
    }
    return count;
}