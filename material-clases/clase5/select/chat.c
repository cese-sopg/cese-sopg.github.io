// select_chat.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>

#define BACKLOG 2
#define BUF_SIZE 4096

static int create_listener(int port)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        exit(1);
    }

    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(1);
    }

    if (listen(fd, BACKLOG) < 0) {
        perror("listen");
        exit(1);
    }

    return fd;
}

static int accept_one(int listen_fd)
{
    int fd = accept(listen_fd, NULL, NULL);
    if (fd < 0) {
        perror("accept");
        exit(1);
    }

    printf("client connected (fd=%d)\n", fd);
    return fd;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return 1;
    }

    int port = atoi(argv[1]);
    int listen_fd = create_listener(port);

    printf("waiting for 2 clients on port %d...\n", port);
    int client[2];
    client[0] = accept_one(listen_fd);
    client[1] = accept_one(listen_fd);
    printf("2 clients connected, relaying messages...\n");

    char buf[BUF_SIZE];
    while (1) {
        fd_set readfds;
        FD_ZERO(&readfds);

        FD_SET(client[0], &readfds);
        FD_SET(client[1], &readfds);

        int maxfd = client[0] > client[1] ? client[0] : client[1];
        int ready = select(maxfd + 1, &readfds, NULL, NULL, NULL);
        if (ready < 0) {
            if (errno == EINTR)
                continue;
            perror("select");
            break;
        }

        for (int i = 0; i < 2; i++) {

            if (FD_ISSET(client[i], &readfds)) {

                ssize_t n = recv(client[i], buf, sizeof(buf), 0);

                if (n <= 0) {
                    printf("client %d disconnected\n", i);
                    goto cleanup;
                }

                int other = 1 - i;

                ssize_t sent = send(client[other], buf, n, 0);

                if (sent < 0) {
                    perror("send");
                    goto cleanup;
                }
            }
        }
    }

cleanup:

    close(client[0]);
    close(client[1]);
    close(listen_fd);

    return 0;
}
