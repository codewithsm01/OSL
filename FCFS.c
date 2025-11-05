#include <stdio.h>

int main() {
    int no_of_frames, no_of_pages, frames[10], pages[30];
    int i, j, k, flag, faults = 0, next = 0;

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
        flag = 0;

        // Check if page is already in frame
        for (j = 0; j < no_of_frames; j++) {
            if (frames[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        // Page fault occurs
        if (flag == 0) {
            frames[next] = pages[i];
            next = (next + 1) % no_of_frames; // Circular queue replacement
            faults++;
        }

        // Print current frame status
        printf("After page %d: ", pages[i]);
        for (k = 0; k < no_of_frames; k++) {
            if (frames[k] != -1)
                printf("%d ", frames[k]);
            else
                printf("- ");
        }
        if (flag == 0)
            printf(" (Page Fault)");
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);
    printf("Page Fault Rate = %.2f%%\n", (float)faults / no_of_pages * 100);

    return 0;
}
