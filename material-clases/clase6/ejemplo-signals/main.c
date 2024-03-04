#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void bloquear_sigint(void) {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    pthread_sigmask(SIG_BLOCK, &set, NULL);
}

void desbloquear_sigint(void) {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    pthread_sigmask(SIG_UNBLOCK, &set, NULL);
}

void sigint_handler(int sig) {
    write(0, "Ahhh! SIGINT!\n", 14);
}

int main(void) {
    printf("Asigno handler\n");

    // signal ctrl+c
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("Bloqueo signal\n");
    bloquear_sigint();

    printf("Espero. Presionar ctrl+c para probar\n");
    int c = 0;
    while (c < 10) {
        sleep(1);
        printf("%d \n", c);
        c++;
    }
    printf("Desbloqueo signal\n");

    desbloquear_sigint();

    printf("Espero.\n");
    sleep(1);
    printf("Fin proceso.\n");
    return 0;
}
