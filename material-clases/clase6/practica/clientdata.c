#include "clientdata.h"

void cd_init(clientdata *clients, int len) {
    for (int i = 0; i < len; i++) {
        clients[i].free = true;
    }
}

int cd_getFreeIndex(clientdata *clients, int len) {
    for (int i = 0; i < len; i++) {
        if (clients[i].free)
            return i;
    }
    return -1;
}
