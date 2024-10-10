#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    int s = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in serveraddr;
    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(4096);
    if (inet_pton(AF_INET, "127.0.0.1", &(serveraddr.sin_addr)) <= 0) {
        fprintf(stderr, "ERROR invalid server IP\r\n");
        return 1;
    }

    int numBytes = sendto(s, "hola", 5, 0,
                          (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    printf("Se enviaron %d bytes\n", numBytes);

    close(s);

    return 0;
}
