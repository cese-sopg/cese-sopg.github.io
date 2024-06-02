/*
 * Fuente: https://www.softprayog.in/programming/posix-semaphores
 *   posix-semaphore-example.c: Program to demonstrate POSIX semaphores
 *                        in C under Linux (Producer - Consumer problem)
 */

#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define SEM_MUTEX_NAME "/sem-mutex"
#define SEM_BUFFER_COUNT_NAME "/sem-buffer-count"
#define SEM_SPOOL_SIGNAL_NAME "/sem-spool-signal"

// Buffer data structures
#define MAX_BUFFERS 10
char buf[MAX_BUFFERS][100];

int buffer_print_index;

int buffer_produce_index;
sem_t *mutex_sem; // protects buffer_produce_index

sem_t *buffer_count_sem; // spooler -> producer (number of available buffers) - initial value: MAX_BUFFERS
sem_t *spool_signal_sem; // producer -> spooler (number of strings ready to be printed)

void *producer(void *arg);
void *spooler(void *arg);

int main(int argc, char **argv) {
    pthread_t tid_producer[10], tid_spooler;
    int i, r;

    // initialization
    buffer_produce_index = buffer_print_index = 0;

    //  mutual exclusion semaphore, mutex_sem with an initial value 1.
    if ((mutex_sem = sem_open(SEM_MUTEX_NAME, O_CREAT, 0660, 1)) ==
        SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    // counting semaphore, indicating the number of available buffers. Initial
    // value = MAX_BUFFERS
    if ((buffer_count_sem = sem_open(SEM_BUFFER_COUNT_NAME, O_CREAT, 0660,
                                     MAX_BUFFERS)) == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    // counting semaphore, indicating the number of strings to be printed.
    // Initial value = 0
    if ((spool_signal_sem =
             sem_open(SEM_SPOOL_SIGNAL_NAME, O_CREAT, 0660, 0)) == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    // Create spooler
    if ((r = pthread_create(&tid_spooler, NULL, spooler, NULL)) != 0) {
        fprintf(stderr, "Error = %d (%s)\n", r, strerror(r));
        exit(1);
    }

    // Create 10 producer threads
    int thread_no[10];
    for (i = 0; i < 10; i++) {
        thread_no[i] = i;
        if ((r = pthread_create(&tid_producer[i], NULL, producer,
                                (void *)&thread_no[i])) != 0) {
            fprintf(stderr, "Error = %d (%s)\n", r, strerror(r));
            exit(1);
        }
    }
    // Wait for producers to terminate
    for (i = 0; i < 10; i++)
        if ((r = pthread_join(tid_producer[i], NULL)) == -1) {
            fprintf(stderr, "Error = %d (%s)\n", r, strerror(r));
            exit(1);
        }

    // No more strings to print? Wait for spool_signal_sem to become 0
    int semval;
    while (1) {
        if (sem_getvalue(spool_signal_sem, &semval) == -1)
            perror("sem_getvalue");
        if (!semval)
            break;
        sleep(1);
    }
    // terminate spooler
    if ((r = pthread_cancel(tid_spooler)) != 0) {
        fprintf(stderr, "Error = %d (%s)\n", r, strerror(r));
        exit(1);
    }

    // Remove semaphores

    if (sem_unlink(SEM_MUTEX_NAME) == -1) {
        perror("sem_unlink");
        exit(1);
    }

    if (sem_unlink(SEM_BUFFER_COUNT_NAME) == -1) {
        perror("sem_unlink");
        exit(1);
    }

    if (sem_unlink(SEM_SPOOL_SIGNAL_NAME) == -1) {
        perror("sem_unlink");
        exit(1);
    }

    exit(0);
}

// producer: produce strings for printing
// There might be multiple producer threads
void *producer(void *arg) {
    // Create 10 strings and terminate
    int my_id = *((int *)arg);

    int count = 0;
    for (int i = 0; i < 10; i++) {
        // get a buffer
        if (sem_wait(buffer_count_sem) == -1) {
            perror("sem_wait: buffer_count_sem");
            exit(1);
        }

        /* There might be multiple producers. We must ensure that
            only one producer uses buffer_produce_index at a time.  */
        if (sem_wait(mutex_sem) == -1) {
            perror("sem_wait: mutex_sem");
            exit(1);
        }

        // Critical section
        int j = buffer_produce_index;
        buffer_produce_index++;
        if (buffer_produce_index == MAX_BUFFERS)
            buffer_produce_index = 0;

        // Release mutex sem
        if (sem_post(mutex_sem) == -1) {
            perror("sem_post: mutex_sem");
            exit(1);
        }

        // Produce a string
        sprintf(buf[j], "Producer %d: %d\n", my_id, ++count);
        usleep(rand() % 100000); // simulate that this took a lot of effort

        // Tell spooler that there is a string to print
        if (sem_post(spool_signal_sem) == -1) {
            perror("sem_post: spool_signal_sem");
            exit(1);
        }
    }

    return NULL;
}

// There is only one spooler thread
void *spooler(void *arg) {
    while (1) { // forever
        // Is there a string to print?
        if (sem_wait(spool_signal_sem) == -1) {
            perror("sem_wait: spool_signal_sem");
            exit(1);
        }

        printf("%s", buf[buffer_print_index]);
        usleep(rand() % 100000); // simulate that this took a lot of effort

        /* Since there is only one thread (spooler) using the
           buffer_print_index, mutex is not necessary */
        buffer_print_index++;
        if (buffer_print_index == MAX_BUFFERS)
            buffer_print_index = 0;

        /* Contents of one buffer has been printed.
           One more buffer is available for use by producers.
           Release buffer */
        if (sem_post(buffer_count_sem) == -1) {
            perror("sem_post: buffer_count_sem");
            exit(1);
        }
    }
}
