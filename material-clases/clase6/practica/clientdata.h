#include <pthread.h>
#include <stdbool.h>

typedef struct {
	int fd;
	pthread_t thread;
	bool free;
} clientdata;

void cd_init(clientdata* clients, int len);
int cd_getFreeIndex(clientdata* clients, int len);
