/*
  En este ejemplo demostramos como es necesario cerrar los FD que no se usan en
  los procesos padre e hijo para que cuando (en este ejemplo) el proceso hijo
  termine y cierre su FD de escritura, la funcion read que se ejecuta en el
  padre, devuelva 0 (EOF). De lo contrario, si el padre no cierra el FD de
  escritura cuando el proceso hijo termina, todavia queda un FD de escritura
  abierto, y la funcion read no devuelve EOF.
*/
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void handlerHijo(int sig) {
    printf("handler.termino hijo, ejecuto wait\n");
    int rv;
    wait(&rv);
    printf("fin handler\n");
}

int main(void) {
    struct sigaction sa;
    int pipes[2];

    sa.sa_handler = handlerHijo;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    pipe(pipes);

    int pid = fork();
    if (pid == 0) {
        printf("CHILD: inicio\n");
        close(pipes[0]); // cierro el de lectura
        sleep(5);

        write(pipes[1], "hola1", 6);
        sleep(10);
        printf("CHILD: fin\n");
    } else {
        printf("PARENT: inicio\n");
        sigaction(SIGCHLD, &sa, NULL);

        // comentar este close para probar
        close(pipes[1]); // cierro el de escritura. Sino, no me
                         // llega EOF cuando el child cierra el fd
        //________________________________

        while (1) {
            char buff[30];
            printf("PARENT: llamo a read\n");
            int ret = read(pipes[0], buff, 6);
            if (ret > 0) {
                printf("PARENT: llego de hijo:%s\n", buff);
            } else if (ret == 0) {
                printf("PARENT: hay EOF!\n");
                break;
            } else {
                perror("PARENT: read error");
            }
        }
    }

    return 0;
}
