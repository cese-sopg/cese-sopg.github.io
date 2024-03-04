#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    // Creamos socket
    int s = socket(PF_INET, SOCK_STREAM, 0);

    // Cargamos datos de direccion de server
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       // ipv4
    hints.ai_socktype = SOCK_STREAM; // tcp
    hints.ai_flags = AI_PASSIVE;     /* For wildcard IP address */

    struct addrinfo *result;
    int r = getaddrinfo("localhost", "4096", &hints,
                        &result); // NULL para localhost
    if (r != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(r));
        exit(EXIT_FAILURE);
    }
    // result es una lista enlazada!. En este ejemplo usamos el primer resultado

    // Ejecutamos connect()
    if (connect(s, (const struct sockaddr *)result->ai_addr,
                result->ai_addrlen) < 0) {
        fprintf(stderr, "ERROR connecting\r\n");
        close(s);
        exit(EXIT_FAILURE);
    }

    // Enviamos mensaje a server
    printf("Ingrese un mensaje:\r\n");
    char buf[128];
    fgets(buf, sizeof(buf), stdin);
    printf("envio:%s", buf);

    int n = write(s, buf, strlen(buf));
    if (n <= 0) {
        fprintf(stderr, "ERROR sending command\r\n");
        close(s);
        exit(EXIT_FAILURE);
    }

    // Leemos respuesta de server
    n = read(s, buf, sizeof(buf));
    if (n > 0) {
        printf("Recibi:'%s'\r\n", buf);
    }

    freeaddrinfo(result);
    close(s);

    return 0;
}
