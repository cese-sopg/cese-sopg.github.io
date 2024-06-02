#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#define STORAGE_ID "/SHM_TEST"
#define STORAGE_SIZE 32

int main(int argc, char *argv[]) {
    // get shared memory file descriptor (NOT a regular file)
    int fd = shm_open(STORAGE_ID, O_RDONLY, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        return 10;
    }

    // map shared memory to process address space
    void *addr = mmap(NULL, STORAGE_SIZE, PROT_READ, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        return 30;
    }

    char *message = addr;
    printf("PID %d: Read from shared memory: \"%s\"\n", getpid(), message);

    return 0;
}
