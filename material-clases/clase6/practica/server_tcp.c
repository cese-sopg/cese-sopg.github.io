#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    // Creamos socket
    int s = socket(PF_INET, SOCK_STREAM, 0);

    // Cargamos datos de IP:PORT del server
    struct sockaddr_in serveraddr;
    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(4096);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (serveraddr.sin_addr.s_addr == INADDR_NONE) {
        fprintf(stderr, "ERROR invalid server IP\n");
        return 1;
    }

    // Abrimos puerto con bind()
    if (bind(s, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1) {
        close(s);
        perror("listener: bind");
        return 1;
    }

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
        if ((newfd = accept(s, (struct sockaddr *)&clientaddr, &addr_len)) == -1) {
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
