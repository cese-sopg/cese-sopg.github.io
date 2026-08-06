// compilar con -fsanitize=undefined
#include <limits.h>

int main(void) {
    int x = INT_MAX;
    x += 1;  // Signed integer overflow (undefined behavior)
    return x;
}
