#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, j, head, total = 0;
    
    printf("Enter number of disk requests: ");
    scanf("%d", &n);
    
    int request[n];
    printf("Enter the disk requests (track numbers):\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }
    
    printf("Enter initial head position: ");
    scanf("%d", &head);
    
    // Sort the requests
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (request[i] > request[j]) {
                int temp = request[i];
                request[i] = request[j];
                request[j] = temp;
            }
        }
    }

    int index;
    for (i = 0; i < n; i++) {
        if (head < request[i]) {
            index = i;
            break;
        }
    }

    printf("\nInitial head position: %d\n", head);
    printf("Head moving away from spindle (towards higher tracks)\n");
    printf("\nSeek Sequence: %d", head);

    // Move towards higher track numbers
    for (i = index; i < n; i++) {
        total += abs(request[i] - head);
        head = request[i];
        printf(" -> %d", head);
    }

    // Jump to the lowest request (C-LOOK circular jump)
    if (index != 0) {
        total += abs(request[n - 1] - request[0]); // Jump not counted as movement in real C-LOOK
        head = request[0];
        printf(" -> %d", head);
    }

    // Continue servicing remaining requests
    for (i = 0; i < index; i++) {
        total += abs(request[i] - head);
        head = request[i];
        printf(" -> %d", head);
    }

    printf("\n\nTotal Head Movement = %d tracks\n", total);
    printf("Average Seek Length = %.2f\n", (float) total / n);

    return 0;
}
