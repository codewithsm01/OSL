#include <stdio.h>

int findOptimal(int pages[], int frame[], int n, int index, int fsize) {
    int pos = -1, farthest = index;
    for (int i = 0; i < fsize; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == n)
            return i; // This page is never used again
    }
    return (pos == -1) ? 0 : pos;
}

int main() {
    int n, fsize;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames (minimum 3): ");
    scanf("%d", &fsize);
    if (fsize < 3) {
        printf("Frame size must be at least 3!\n");
        return 0;
    }

    int frame[fsize];
    for (int i = 0; i < fsize; i++)
        frame[i] = -1;

    int pageFaults = 0;

    printf("\nPage Replacement Process (Optimal Algorithm):\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < fsize; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            pageFaults++;
            int empty = -1;
            for (int j = 0; j < fsize; j++) {
                if (frame[j] == -1) {
                    empty = j;
                    break;
                }
            }

            if (empty != -1)
                frame[empty] = pages[i];
            else {
                int pos = findOptimal(pages, frame, n, i + 1, fsize);
                frame[pos] = pages[i];
            }
        }

        printf("After page %d: ", pages[i]);
        for (int j = 0; j < fsize; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);

    return 0;
}
