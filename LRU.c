#include <stdio.h>

int findLRU(int time[], int f) {
    int i, min = time[0], pos = 0;
    for (i = 1; i < f; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int pages[50], frames[10], time[10];
    int n, f, i, j, pos, faults = 0, counter = 0, found;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++) {
        frames[i] = -1;
    }

    printf("\nLRU Page Replacement:\n");

    for (i = 0; i < n; i++) {
        found = 0;

        // Check if page is already in frame
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        // If page not found (Page Fault)
        if (!found) {
            faults++;
            if (i < f) {
                frames[i] = pages[i];
                time[i] = ++counter;
            } else {
                pos = findLRU(time, f);
                frames[pos] = pages[i];
                time[pos] = ++counter;
            }
        }

        // Print current state of frames
        for (j = 0; j < f; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);
    return 0;
}