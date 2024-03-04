#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

static pthread_t thing1, thing2, thing3;

void *start_thread(void *message) {
    for (int i = 0; i < 10; i++) {
        printf("%s\n", (const char *)message);
        sleep(1);
    }
    return NULL;
}

void *cancelador(void *message) {
    sleep(5);
    pthread_cancel(thing1);
    sleep(2);
    pthread_cancel(thing2);
    return NULL;
}

int main(void) {
    const char *message1 = "Thing 1";
    const char *message2 = "Thing 2";

    pthread_create(&thing1, NULL, start_thread, (void *)message1);
    pthread_create(&thing2, NULL, start_thread, (void *)message2);
    pthread_create(&thing3, NULL, cancelador, NULL);

    printf("Espero fin de threads...\n");

    void *ret;
    pthread_join(thing1, &ret);
    if (ret == PTHREAD_CANCELED)
        printf("Se cancelo t1\n");
    else
        printf("Termino t1\n");

    pthread_join(thing2, &ret);
    if (ret == PTHREAD_CANCELED)
        printf("Se cancelo t2\n");
    else
        printf("Termino t2\n");

    printf("Fin main\n");
    return 0;
}
