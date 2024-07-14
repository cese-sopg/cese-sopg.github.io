#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/mysocket"

int main() {
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket");
        return 1;
    }

    struct sockaddr_un remote = {0};
    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, SOCKET_PATH);
    int addrlen = offsetof(struct sockaddr_un, sun_path) + strlen(remote.sun_path) + 1;

    printf("connecting...\n");
    if (connect(sock, (struct sockaddr *)&remote, addrlen) == -1) {
        perror("connect");
        return 1;
    }

    printf("connected\n");

    while (true) {
        printf("> ");
        char send_buf[100] = {0};
        char *r = fgets(send_buf, 100, stdin);
        if (r == NULL) {
            if (feof(stdin)) {
                break;
            } else {
                perror("fgets");
                return 1;
            }
        }
        if (send(sock, send_buf, strlen(send_buf), 0) == -1) {
            perror("send");
            return 1;
        }

        char recv_buf[100] = {0};
        int n = recv(sock, recv_buf, 100, 0);
        if (n < 0) {
            perror("recv");
            return 1;
        }
        if (n == 0) { // EOF
            break;
        }
        recv_buf[n] = '\0';
        printf("received %d bytes from server: %s\n", n, recv_buf);
    }

    close(sock);
    printf("Client: bye! \n");

    return 0;
}
