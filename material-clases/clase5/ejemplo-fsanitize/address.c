// compilar con -fsanitize=address
#include <stdlib.h>

int main(void) {
    int *p = malloc(4 * sizeof(int));
    p[4] = 42;  // Out-of-bounds write
    free(p);
    return 0;
}
