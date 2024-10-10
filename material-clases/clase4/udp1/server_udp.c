#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    // Creamos socket
    int s = socket(AF_INET, SOCK_DGRAM, 0);

    // Cargamos datos de IP:PORT del server
    struct sockaddr_in serveraddr;
    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(4096);
    serveraddr.sin_addr.s_addr =
        INADDR_ANY; // if(inet_pton(AF_INET, "127.0.0.1",
                    // &(serveraddr.sin_addr))<=0)

    // Abrimos puerto con bind()
    if (bind(s, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1) {
        close(s);
        perror("listener: bind");
    }

    // Escuchamos datagram con recvfrom()
    struct sockaddr_in clientaddr;
    bzero((char *)&clientaddr, sizeof(clientaddr));
    socklen_t addr_len = sizeof(clientaddr);

    char buffer[128];
    int numBytes = recvfrom(s, buffer, 127, 0,
                            (struct sockaddr *)&clientaddr, &addr_len);
    printf("Se recibieron %d bytes", numBytes);

    char ipClient[32];
    inet_ntop(AF_INET, &(clientaddr.sin_addr), ipClient, sizeof(ipClient));
    int port = ntohs(clientaddr.sin_port);
    printf(" desde ip:%s port:%d", ipClient, port);

    buffer[numBytes] = 0;
    printf("\nMSG:%s\n", buffer);

    close(s);

    return 0;
}
