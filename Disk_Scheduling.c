#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void sort(int *arr, int size, int ascending);
void seektimeFinder(int *arr, int size);

void fcfs(int requests[], int req, int head) {
    int queue[50];
    queue[0] = head;
    for (int i = 0; i < req; i++) {
        queue[i + 1] = requests[i];
    }
    printf("\n--- FCFS ---\n");
    seektimeFinder(queue, req + 1);
}

void scan(int requests[], int req, int head, int range) {
    int left[50], right[50], l = 0, r = 0;
    for (int i = 0; i < req; i++) {
        if (requests[i] < head)
            left[l++] = requests[i];
        else
            right[r++] = requests[i];
    }

    sort(left, l, 0);  // descending
    sort(right, r, 1); // ascending

    int queue[100], idx = 0;
    queue[idx++] = head;
    for (int i = 0; i < r; i++) queue[idx++] = right[i];
    queue[idx++] = range; // go to end
    for (int i = 0; i < l; i++) queue[idx++] = left[i];

    printf("\n--- SCAN ---\n");
    seektimeFinder(queue, idx);
}

void cscan(int requests[], int req, int head, int range) {
    int left[50], right[50], l = 0, r = 0;
    for (int i = 0; i < req; i++) {
        if (requests[i] < head)
            left[l++] = requests[i];
        else
            right[r++] = requests[i];
    }

    sort(left, l, 1);  // ascending
    sort(right, r, 1); // ascending

    int queue[100], idx = 0;
    queue[idx++] = head;
    for (int i = 0; i < r; i++) queue[idx++] = right[i];
    queue[idx++] = range;
    queue[idx++] = 0;
    for (int i = 0; i < l; i++) queue[idx++] = left[i];

    printf("\n--- C-SCAN ---\n");
    seektimeFinder(queue, idx);
}

void seektimeFinder(int *arr, int size) {
    int seek = 0;
    for (int i = 0; i < size - 1; i++) {
        int diff = abs(arr[i + 1] - arr[i]);
        seek += diff;
        printf("Head moves from %d to %d — Seek = %d\n", arr[i], arr[i + 1], diff);
    }
    printf("Total Seek Time = %d\n", seek);
}

void sort(int *arr, int size, int ascending) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if ((ascending && arr[j] > arr[j + 1]) || (!ascending && arr[j] < arr[j + 1])) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int range, req, requests[50], head, choice;

    printf("Enter max range of the disk: ");
    scanf("%d", &range);

    printf("Enter number of requests: ");
    scanf("%d", &req);

    printf("Enter the disk requests:\n");
    for (int i = 0; i < req; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    do {
        printf("\nMenu:\n1. FCFS\n2. SCAN\n3. C-SCAN\n4. Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: fcfs(requests, req, head); break;
            case 2: scan(requests, req, head, range); break;
            case 3: cscan(requests, req, head, range); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    return 0;
}