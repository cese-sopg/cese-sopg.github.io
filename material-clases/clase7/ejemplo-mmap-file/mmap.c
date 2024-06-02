#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
  if(argc < 2){
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(1);
  }

  int fd = open(argv[1], O_RDWR);
  if (fd == -1) {
    perror("open");
    exit(2);
  }

  struct stat sb;
  if (fstat(fd, &sb) == -1) {
    perror("fstat");
    exit(3);
  }

  char *data = mmap(NULL, sb.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
  if (data == MAP_FAILED) {
    perror("mmap");
    exit(4);
  }

  for (int i = 0; i < sb.st_size; i++) {
      data[i] = toupper(data[i]);
  }

  // write changes to file system
  if (msync(data, sb.st_size, MS_SYNC) == -1) {
    perror("msync");
    exit(5);
  }

  if (munmap(data, sb.st_size) == -1) {
    perror("munmap");
    exit(6);
  }
  close(fd);

  return 0;
}
