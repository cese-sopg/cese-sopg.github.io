#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "myfifo"

int main(void) {
    char s[300];
    int num, fd;

    mknod(FIFO_NAME, S_IFIFO | 0666, 0);

    printf("waiting for readers...\n");
    fd = open(FIFO_NAME, O_WRONLY);
    printf("got a reader--type some stuff\n");

    while (1) {
        fgets(s, 300, stdin);
        if ((num = write(fd, s, strlen(s))) == -1)
            perror("write");
        else
            printf("writer: wrote %d bytes\n", num);
    }
    return 0;
}
