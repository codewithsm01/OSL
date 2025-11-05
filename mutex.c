#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

pthread_mutex_t mutex;      // To protect read_count
pthread_mutex_t wrt;        // To ensure mutual exclusion for writers
int read_count = 0;         // Number of readers currently reading
int data = 0;               // Shared resource

// Function declarations
void *reader(void *arg);
void *writer(void *arg);

int main() {
    pthread_t rtid[5], wtid[3];
    int i;

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&wrt, NULL);

    // Create reader threads
    for (i = 0; i < 5; i++) {
        pthread_create(&rtid[i], NULL, reader, (void *)(long)i);
    }

    // Create writer threads
    for (i = 0; i < 3; i++) {
        pthread_create(&wtid[i], NULL, writer, (void *)(long)i);
    }

    // Join all threads
    for (i = 0; i < 5; i++) {
        pthread_join(rtid[i], NULL);
    }
    for (i = 0; i < 3; i++) {
        pthread_join(wtid[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&wrt);

    return 0;
}

void *reader(void *arg) {
    int id = (long)arg;

    while (1) {
        pthread_mutex_lock(&mutex);
        read_count++;
        if (read_count == 1)
            pthread_mutex_lock(&wrt); // First reader locks writer
        pthread_mutex_unlock(&mutex);

        // Critical section (reading)
        printf("Reader %d is reading data = %d\n", id, data);
        sleep(1); // Simulate reading time

        pthread_mutex_lock(&mutex);
        read_count--;
        if (read_count == 0)
            pthread_mutex_unlock(&wrt); // Last reader unlocks writer
        pthread_mutex_unlock(&mutex);

        sleep(1); // Allow other threads chance to run
    }
}

void *writer(void *arg) {
    int id = (long)arg;

    while (1) {
        pthread_mutex_lock(&wrt); // Lock for writing

        // Critical section (writing)
        data++;
        printf("\tWriter %d wrote data = %d\n", id, data);
        sleep(1); // Simulate writing time

        pthread_mutex_unlock(&wrt); // Unlock for others
        sleep(1);
    }
}
