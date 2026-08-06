// compilar con -fsanitize=leak
#include <stdlib.h>

int main(void) {
    void *p = malloc(1024);
    (void)p;
    return 0;  // Memory is leaked
}
