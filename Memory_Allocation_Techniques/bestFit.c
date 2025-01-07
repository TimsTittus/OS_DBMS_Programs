#include<stdio.h>
#include<stdlib.h>

int main() {
    int m, n;
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    int *blockSizes = malloc(m * sizeof(int));
    printf("Enter sizes of memory blocks: ");
    for (int i = 0; i < m; i++) scanf("%d", &blockSizes[i]);

    printf("Enter number of processes: ");
    scanf("%d", &n);
    int *processSizes = malloc(n * sizeof(int));
    printf("Enter sizes of processes: ");
    for (int i = 0; i < n; i++) scanf("%d", &processSizes[i]);

    for (int i = 0; i < n; i++) {
        int bestIndex = -1;
        for (int j = 0; j < m; j++) {
            if (blockSizes[j] >= processSizes[i] && (bestIndex == -1 || blockSizes[j] < blockSizes[bestIndex]))
                bestIndex = j;
        }
        if (bestIndex != -1) {
            printf("Process %d -> Block %d\n", i + 1, bestIndex + 1);
            blockSizes[bestIndex] -= processSizes[i];
        } else {
            printf("Process %d -> Not allocated\n", i + 1);
        }
    }

    free(blockSizes);
    free(processSizes);
    return 0;
}
