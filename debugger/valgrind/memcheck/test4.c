#include <stdlib.h>

void leak() {
    for (int i = 0; i < 123; i++) {
        int *p = malloc(10);
    // Forgot to free(p)
    }
}

int main() {
    leak();
    return 0;
}