#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#define STORAGE_ID "/SHM_TEST"
#define STORAGE_SIZE 32

int main(int argc, char *argv[]) {
    // get shared memory file descriptor (NOT a file)
    int fd = shm_open(STORAGE_ID, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        return 10;
    }

    // extend shared memory object as by default it's initialized with size 0
    int res = ftruncate(fd, STORAGE_SIZE);
    if (res == -1) {
        perror("ftruncate");
        return 20;
    }

    // map shared memory to process address space
    void *addr = mmap(NULL, STORAGE_SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        return 30;
    }

    // place data into memory
    char data[STORAGE_SIZE];
    sprintf(data, "Hello, World! From PID %d", getpid());
    int len = strlen(data) + 1;
    memcpy(addr, data, len);

    // wait for someone to read it
    sleep(2);

    // mmap cleanup
    res = munmap(addr, STORAGE_SIZE);
    if (res == -1) {
        perror("munmap");
        return 40;
    }

    // shm_open cleanup
    fd = shm_unlink(STORAGE_ID);
    if (fd == -1) {
        perror("unlink");
        return 100;
    }

    return 0;
}
