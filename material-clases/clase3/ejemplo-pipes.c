#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int pipesChild2Parent[2];
    int pipesParent2Child[2];

    char buff[30];

    pipe(pipesChild2Parent);
    pipe(pipesParent2Child);

    int pid = fork();
    if (pid == 0) {
        printf("CHILD: inicio\n");

        close(pipesParent2Child[1]); // este lo cierro porque lo escribe el padre
        close(pipesChild2Parent[0]); // este lo cierro porque lo lee el padre

        sleep(2);
        printf("CHILD: Escribo hola\n");
        write(pipesChild2Parent[1], "hola", 5);
        sleep(2);
        printf("CHILD: Leo\n");
        read(pipesParent2Child[0], buff, 5);
        printf("CHILD: Lei %s\n", buff);
        sleep(2);
        printf("\nCHILD: fin\n");
    } else {
        printf("PARENT: inicio\n");
        close(pipesChild2Parent[1]); // este lo cierro porque lo escribe el hijo
        close(pipesParent2Child[0]); // este lo cierro porque lo lee el hijo

        sleep(10);
        printf("PARENT: Leo\n");
        read(pipesChild2Parent[0], buff, 5);
        printf("PARENT: Lei %s\n", buff);
        sleep(10);
        printf("\nPARENT: Escribo chau\n");
        write(pipesParent2Child[1], "chau", 5);
        sleep(10);
        printf("PARENT: espero hijo\n");
        wait(NULL);
        printf("PARENT: fin\n");
    }

    return 0;
}
