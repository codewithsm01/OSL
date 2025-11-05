#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void sortArray(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main() {
    int n, i;
    pid_t pid;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Sort the array in parent
    sortArray(arr, n);

    printf("\nParent Process (PID: %d)\n", getpid());
    printf("Sorted Array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        // Child process
        char *args[n + 2];  // +2 for program name and NULL terminator
        char numStr[10];

        // Program to execute (child.c executable)
        args[0] = "./child";

        // Pass sorted array elements as string arguments
        for (i = 0; i < n; i++) {
            sprintf(numStr, "%d", arr[i]);
            args[i + 1] = strdup(numStr);
        }

        args[n + 1] = NULL;

        printf("\nChild Process (PID: %d): Executing child program...\n", getpid());
        execve("./child", args, NULL);

        // If execve fails
        perror("execve failed");
        exit(1);
    } 
    else {
        wait(NULL);
        printf("\nParent Process: Child finished execution.\n");
    }

    return 0;
}
