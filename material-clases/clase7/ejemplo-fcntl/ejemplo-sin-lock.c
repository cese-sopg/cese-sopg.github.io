#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

const char* FILENAME = "counter.dat";
const int NUM_INCREMENTS = 10;

void incrementar_contador(int pid) {
    int fd = open(FILENAME, O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_INCREMENTS; ++i) {
        char buffer[32];
        lseek(fd, 0, SEEK_SET); // Ir al inicio del archivo
        read(fd, buffer, sizeof(buffer)); // Leer el contador
        int counter = atoi(buffer);

        counter++; // Incrementar el contador

        usleep(10000);

        // Escribir el contador
        snprintf(buffer, sizeof(buffer), "%d", counter);
        lseek(fd, 0, SEEK_SET); // Ir al inicio
        write(fd, buffer, strlen(buffer)); // Escribir
        ftruncate(fd, strlen(buffer)); // Truncar el archivo

        printf("PID %d: El nuevo valor del contador es %d\n", pid, counter);

        usleep(5000);
    }

    close(fd);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <cant_procesos>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int cant_procesos = atoi(argv[1]);

    // Inicializar el archivo con "0"
    int fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }
    write(fd, "0", 1);
    close(fd);

    // Crear procesos hijos
    for (int i = 0; i < cant_procesos; ++i) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            return EXIT_FAILURE;
        }
        if (pid == 0) { // soy el hijo
            incrementar_contador(getpid());
            exit(EXIT_SUCCESS);
        }
    }

    // Padre: esperar a que terminen todos los hijos
    for (int i = 0; i < cant_procesos; ++i) {
        wait(NULL);
    }

    return EXIT_SUCCESS;
}
