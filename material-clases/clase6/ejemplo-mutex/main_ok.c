#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
    int a;
    int b;
} data_t;

data_t data;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *start_thread(void *message) {
    while (1) {
        pthread_mutex_lock(&mutex);
        data.a++;
        data.b++;
        pthread_mutex_unlock(&mutex);
        usleep(100);
    }
    return NULL;
}

int main(void) {

    pthread_t t1, t2;
    pthread_create(&t1, NULL, start_thread, NULL);
    pthread_create(&t2, NULL, start_thread, NULL);

    while (1) {
        pthread_mutex_lock(&mutex);
        int a = data.a;
        int b = data.b;
        pthread_mutex_unlock(&mutex);
        printf("%d %d\r\n", a, b);
        sleep(1);
    }

    return 0;
}
