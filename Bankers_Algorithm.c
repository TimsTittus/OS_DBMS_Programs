#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX], avail[MAX];
bool finished[MAX];
int n, m;

bool canRun(int p) {
    for (int j = 0; j < m; j++)
        if (need[p][j] > avail[j]) return false;
    return true;
}

int main() {
    printf("Enter number of processes and resources: ");
    scanf("%d %d", &n, &m);

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Max Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Calculate Need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    int safeSeq[MAX], count = 0;

    while (count < n) {
        bool progress = false;

        for (int i = 0; i < n; i++) {
            if (!finished[i] && canRun(i)) {
                for (int j = 0; j < m; j++)
                    avail[j] += alloc[i][j];
                safeSeq[count++] = i;
                finished[i] = true;
                progress = true;
            }
        }

        if (!progress) break;
    }

    if (count == n) {
        printf("\nSystem is Safe.\nSafe Sequence: ");
        for (int i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);
        printf("\nFinal Available: ");
        for (int i = 0; i < m; i++)
            printf("%d ", avail[i]);
        printf("\n");
    } else {
        printf("\nSystem is Unsafe.\n");
    }

    return 0;
}
