#include <stdlib.h>

int main() {
    void *ptr;
    posix_memalign(&ptr, 5, 100);  // ❌ 3 is not a power of two
    return 0;
}
