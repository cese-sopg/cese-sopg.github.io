/*
 * Fuente: https://www.softprayog.in/programming/interprocess-communication-using-posix-message-queues-in-linux
 *
 * The example below demonstrates interprocess communication between a server
 * and clients using POSIX message queues in Linux. The server manages token
 * numbers, which could be seat numbers for a flight, or something similar. It
 * is server’s job to give a token number to a client on request. In a typical
 * scenario, there might be multiple clients requesting the server for token
 * numbers. The server’s message queue name is known to clients. Each client has
 * its own message queue, in which server posts responses. When a client sends a
 * request, it sends its message queue name. The server opens client’s message
 * queue and sends its response. The client picks up the response from its
 * message queue and reads the token number in it.
 *
 * server.c: Server program
 *           to demonstrate interprocess commnuication
 *           with POSIX message queues
 */

#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SERVER_QUEUE_NAME "/sp-example-server"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

int main(int argc, char **argv) {
    mqd_t qd_server, qd_client; // queue descriptors
    long token_number = 1;      // next token to be given to client

    printf("Server: Hello, World!\n");

    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    if ((qd_server = mq_open(SERVER_QUEUE_NAME, O_RDONLY | O_CREAT,
                             QUEUE_PERMISSIONS, &attr)) == -1) {
        perror("Server: mq_open (server)");
        exit(1);
    }
    char in_buffer[MSG_BUFFER_SIZE];
    char out_buffer[MSG_BUFFER_SIZE];

    while (1) {
        // get the oldest message with highest priority
        if (mq_receive(qd_server, in_buffer, MSG_BUFFER_SIZE, NULL) == -1) {
            perror("Server: mq_receive");
            exit(1);
        }

        printf("Server: message received.\n");

        // send reply message to client

        if ((qd_client = mq_open(in_buffer, O_WRONLY)) == 1) {
            perror("Server: Not able to open client queue");
            continue;
        }

        sprintf(out_buffer, "%ld", token_number);

        if (mq_send(qd_client, out_buffer, strlen(out_buffer) + 1, 0) == -1) {
            perror("Server: Not able to send message to client");
            continue;
        }

        printf("Server: response sent to client.\n");
        token_number++;
    }
}
