#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void) {
    // Creamos socket
    int s = socket(AF_INET, SOCK_STREAM, 0);

    // Cargamos datos de IP:PORT del server
    struct sockaddr_in serveraddr;
    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(4096);
    if (inet_pton(AF_INET, "127.0.0.1", &(serveraddr.sin_addr)) <= 0) {
        fprintf(stderr, "ERROR invalid server IP\n");
        exit(EXIT_FAILURE);
    }

    // Abrimos puerto con bind()
    if (bind(s, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Seteamos socket en modo Listening
    if (listen(s, 1) == -1) { // backlog=10
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Ejecutamos accept() para recibir conexiones entrantes
        socklen_t addr_len = sizeof(struct sockaddr_in);
        struct sockaddr_in clientaddr;
        int newfd;
        printf("server: esperando una conexion...\n");
        if ((newfd = accept(s, (struct sockaddr *)&clientaddr, &addr_len)) == -1) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        char ipClient[32];
        inet_ntop(AF_INET, &(clientaddr.sin_addr), ipClient, sizeof(ipClient));
        printf("server: conexion desde:  %s\n", ipClient);

        // prueba cierre de conexion. El cliente recibira SIGPIPE.
        /*
        printf("presionar enter para salir\n");
        getchar();
        close(newfd);
        close(s);
        exit(EXIT_FAILURE);
        */

        // Leemos mensaje de cliente
        char buffer[128];
        int n;
        if ((n = read(newfd, buffer, 128)) == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        buffer[n] = 0x00;
        printf("server: recibi %d bytes:%s\n", n, buffer);

        // Enviamos mensaje a cliente
        if ((n = write(newfd, "chau", 5)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        printf("server: envie %d bytes\n", n);

        // Esperamos a que el cliente cierre
        printf("server: esperando a que el cliente cierre la conexion...\n");
        if ((n = read(newfd, buffer, 128)) == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        if (n != 0) {
            // No deberia ocurrir ya que si el cliente cerro la conexion, read devuelve 0
            buffer[n] = 0x00;
            printf("server: recibi %d bytes:%s\n", n, buffer);
        }

        // Cerramos conexion con cliente
        close(newfd);
    }

    return EXIT_SUCCESS;
}
