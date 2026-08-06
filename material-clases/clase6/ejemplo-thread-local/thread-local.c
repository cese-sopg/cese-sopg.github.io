#include <pthread.h>
#include <stdio.h>

// C11: _Thread_local
// C23: thread_local
thread_local int id = 0;

void *f(void *arg)
{
    id = (long)arg;

    for (int i = 0; i < 3; i++)
        printf("thread %d\n", id);

    return NULL;
}

int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, f, (void *)1);
    pthread_create(&t2, NULL, f, (void *)2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}
