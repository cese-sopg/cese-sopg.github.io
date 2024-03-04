#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    // Creamos socket
    int s = socket(PF_INET, SOCK_STREAM, 0);

    // Cargamos datos de IP:PORT del server
    struct addrinfo hints;
    struct addrinfo *result;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       // ipv4
    hints.ai_socktype = SOCK_STREAM; // tcp
    hints.ai_flags = AI_PASSIVE;     /* For wildcard IP address */

    int r = getaddrinfo(NULL, "4096", &hints, &result); // NULL para localhost
    if (r != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(r));
        exit(EXIT_FAILURE);
    }
    // result es lista enlazada!. En este ejemplo usamos la primera

    // Abrimos puerto con bind()
    if (bind(s, (struct sockaddr *)result->ai_addr, result->ai_addrlen) == -1) {
        close(s);
        perror("listener: bind");
    }

    freeaddrinfo(result);

    // Seteamos socket en modo Listening
    if (listen(s, 10) == -1) // backlog=10
    {
        perror("error en listen");
        exit(1);
    }

    while (1) {
        // Ejecutamos accept() para recibir conexiones entrantes
        socklen_t addr_len = sizeof(struct sockaddr_in);
        struct sockaddr_in clientaddr;
        int newfd;
        if ((newfd = accept(s, (struct sockaddr *)&clientaddr, &addr_len)) ==
            -1) {
            perror("error en accept");
            exit(1);
        }
        printf("server:  conexion desde:  %s\n",
               inet_ntoa(clientaddr.sin_addr));

        // Leemos mensaje de cliente
        char buffer[128];
        int n;
        if ((n = read(newfd, buffer, 128)) == -1) {
            perror("Error leyendo mensaje en socket");
            exit(1);
        }
        buffer[n] = 0;
        printf("Recibi %d bytes.:%s\n", n, buffer);

        // Enviamos mensaje a cliente
        if (write(newfd, "hola", 5) == -1) {
            perror("Error escribiendo mensaje en socket");
            exit(1);
        }

        // Cerramos conexion con cliente
        close(newfd);
    }

    return 0;
}
