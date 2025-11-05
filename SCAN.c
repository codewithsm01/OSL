#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, j, temp;
    int disk_size, head, total = 0;
    int direction; // 1 = moving away from spindle (towards higher tracks)
    
    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int request[n + 1];

    printf("Enter the disk requests (track numbers):\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter total disk size (number of tracks): ");
    scanf("%d", &disk_size);

    direction = 1; // 1 means moving away from spindle (increasing track numbers)

    // Add head position into request array
    request[n] = head;
    n++;

    // Sort all requests
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (request[j] > request[j + 1]) {
                temp = request[j];
                request[j] = request[j + 1];
                request[j + 1] = temp;
            }
        }
    }

    // Find position of head in sorted array
    int pos;
    for (i = 0; i < n; i++) {
        if (request[i] == head) {
            pos = i;
            break;
        }
    }

    printf("\nSCAN Disk Scheduling (Head moving away from spindle):\n");
    printf("Seek Sequence: %d", head);

    if (direction == 1) {
        // Move toward higher track numbers first
        for (i = pos + 1; i < n; i++) {
            printf(" -> %d", request[i]);
            total += abs(request[i] - head);
            head = request[i];
        }

        // Then go to the end (maximum track)
        if (head != disk_size - 1) {
            printf(" -> %d", disk_size - 1);
            total += abs((disk_size - 1) - head);
            head = disk_size - 1;
        }

        // Reverse direction and service remaining lower tracks
        for (i = pos - 1; i >= 0; i--) {
            printf(" -> %d", request[i]);
            total += abs(request[i] - head);
            head = request[i];
        }
    }

    printf("\n\nTotal Head Movement = %d tracks\n", total);
    printf("Average Seek Length = %.2f\n", (float)total / (n - 1));

    return 0;
}
