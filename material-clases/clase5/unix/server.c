#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/mysocket"

int main() {
    int s = socket(AF_UNIX, SOCK_STREAM, 0);
    if (s == -1) {
        perror("socket");
        return 1;
    }

    unlink(SOCKET_PATH); // avoid "address already in use"

    struct sockaddr_un local = {0};
    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, SOCKET_PATH);
    int addrlen = offsetof(struct sockaddr_un, sun_path) + strlen(local.sun_path) + 1;
    if (bind(s, (struct sockaddr *)&local, addrlen) != 0) {
        perror("bind");
        return 1;
    }

    if (listen(s, 10) != 0) {
        perror("listen");
        return 1;
    }

    while (true) {
        printf("waiting for connection....\n");

        unsigned int sock_len;
        struct sockaddr_un remote;
        int conn = accept(s, (struct sockaddr *)&remote, &sock_len);
        if (conn  == -1) {
            perror("accept");
            return 1;
        }

        printf("server connected\n");

        while (true) {
            char buf[100] = {0};
            int n = recv(conn, buf, 100, 0);
            if (n < 0) {
                perror("recv");
                return 1;
            }
            if (n == 0) { // EOF
                break;
            }
            buf[n] = '\0';
            printf("received %d bytes: %s\n", n, buf);

            // echo to client
            if (send(conn, buf, strlen(buf), 0) == -1) {
                perror("send");
                return 1;
            }
        }

        close(conn);
    }

    return 0;
}
