#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, j, head, total = 0, min, pos;
    int completed[100] = {0};
    int direction = 1; // 1 = moving away from spindle (higher tracks)

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int request[n];
    printf("Enter the disk requests (track numbers):\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("\nInitial head position: %d\n", head);
    printf("Head moving away from spindle (towards higher tracks)\n");
    printf("\nSeek Sequence: %d", head);

    for (i = 0; i < n; i++) {
        min = 9999;
        pos = -1;

        // Find the nearest request that is not yet completed
        for (j = 0; j < n; j++) {
            if (!completed[j]) {
                int diff = abs(request[j] - head);
                if (diff < min) {
                    min = diff;
                    pos = j;
                }
            }
        }

        // Move head to that position
        total += abs(request[pos] - head);
        head = request[pos];
        completed[pos] = 1;
        printf(" -> %d", head);
    }

    printf("\n\nTotal Head Movement = %d tracks\n", total);
    printf("Average Seek Length = %.2f\n", (float)total / n);

    return 0;
}
