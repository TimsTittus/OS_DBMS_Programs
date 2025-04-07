#include <stdio.h>
#include <string.h>

struct Process {
    char name[20];
    int arrival, burst, completion, waiting, turnaround, done;
} p[10];

int main() {
    int n, time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Get process details
    for (int i = 0; i < n; i++) {
        printf("\nEnter name of process %d: ", i + 1);
        scanf("%s", p[i].name);
        printf("Enter arrival time: ");
        scanf("%d", &p[i].arrival);
        printf("Enter burst time: ");
        scanf("%d", &p[i].burst);
        p[i].done = 0;
    }

    // Process scheduling
    while (completed < n) {
        int shortest = -1;

        // Find the process with the shortest burst time that's arrived
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].arrival <= time) {
                if (shortest == -1 || p[i].burst < p[shortest].burst) {
                    shortest = i;
                }
            }
        }

        // If no process is found, just move time forward (CPU is idle)
        if (shortest == -1) {
            time++;
            continue;
        }

        // Execute the shortest process
        p[shortest].completion = time + p[shortest].burst;
        p[shortest].turnaround = p[shortest].completion - p[shortest].arrival;
        p[shortest].waiting = p[shortest].turnaround - p[shortest].burst;
        p[shortest].done = 1;
        time = p[shortest].completion;
        completed++;

        total_wt += p[shortest].waiting;
        total_tat += p[shortest].turnaround;
    }

    // Print result
    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
            p[i].name, p[i].arrival, p[i].burst,
            p[i].completion, p[i].waiting, p[i].turnaround);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
