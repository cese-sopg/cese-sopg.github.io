#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig) {
    write(1, "se presiono ctrl+c!!\n", 21);
}

int main(void) {
    struct sigaction sa;

    sa.sa_handler = handler;
    sa.sa_flags = 0; // SA_RESTART;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGINT, &sa, NULL);

    char s[200];
    if (fgets(s, sizeof(s), stdin) == NULL) {
        perror("error en fgets");
    } else {
        printf("ingresaste: %s\n", s);
    }

    /*
    while (1) {
        printf("inicio\n");
        unsigned int r = sleep(30);
        printf("fin. %u\n",r);
    }
    */

    return 0;
}
