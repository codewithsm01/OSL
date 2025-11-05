#include <stdio.h>

int findLRU(int time[], int n) {
    int i, minimum = time[0], pos = 0;
    for (i = 1; i < n; i++) {
        if (time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int no_of_frames, no_of_pages, frames[10], pages[30];
    int counter = 0, time[10];
    int flag1, flag2, i, j, pos, faults = 0;

    printf("Enter number of frames (minimum 3): ");
    scanf("%d", &no_of_frames);
    if (no_of_frames < 3) {
        printf("Frame size must be at least 3.\n");
        return 0;
    }

    printf("Enter number of pages: ");
    scanf("%d", &no_of_pages);

    printf("Enter the page reference string:\n");
    for (i = 0; i < no_of_pages; i++) {
        scanf("%d", &pages[i]);
    }

    // Initialize frames
    for (i = 0; i < no_of_frames; i++) {
        frames[i] = -1;
    }

    printf("\nPage Reference String: ");
    for (i = 0; i < no_of_pages; i++)
        printf("%d ", pages[i]);
    printf("\n\nPage Replacement Process:\n");

    for (i = 0; i < no_of_pages; i++) {
        flag1 = flag2 = 0;

        // Check if page already exists in frames
        for (j = 0; j < no_of_frames; j++) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }

        // If page not found (page fault)
        if (flag1 == 0) {
            for (j = 0; j < no_of_frames; j++) {
                if (frames[j] == -1) {
                    counter++;
                    faults++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }

        // If no empty frame, replace LRU page
        if (flag2 == 0) {
            pos = findLRU(time, no_of_frames);
            counter++;
            faults++;
            frames[pos] = pages[i];
            time[pos] = counter;
        }

        // Print current frame status
        printf("After page %d: ", pages[i]);
        for (j = 0; j < no_of_frames; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);
    printf("Page Fault Rate = %.2f%%\n", (float)faults / no_of_pages * 100);

    return 0;
}
