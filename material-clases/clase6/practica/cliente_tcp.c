#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    // Creamos socket
    int s = socket(PF_INET, SOCK_STREAM, 0);

    // Cargamos datos de direccion de server
    struct sockaddr_in serveraddr;
    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(4096);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (serveraddr.sin_addr.s_addr == INADDR_NONE) {
        fprintf(stderr, "ERROR invalid server IP\n");
        return 1;
    }

    // Ejecutamos connect()
    if (connect(s, (const struct sockaddr *)&serveraddr, sizeof(serveraddr)) <
        0) {
        fprintf(stderr, "ERROR connecting\n");
        close(s);
        exit(EXIT_FAILURE);
    }

    // Enviamos mensaje a server
    printf("Ingrese un mensaje:\n");
    char buf[128];
    fgets(buf, sizeof(buf), stdin);
    printf("envio:%s", buf);

    int n = write(s, buf, strlen(buf));
    if (n <= 0) {
        fprintf(stderr, "ERROR sending command\n");
        close(s);
        exit(EXIT_FAILURE);
    }

    // Leemos respuesta de server
    n = read(s, buf, sizeof(buf));
    if (n > 0) {
        printf("Recibi:'%s'\n", buf);
    }

    close(s);

    return 0;
}
