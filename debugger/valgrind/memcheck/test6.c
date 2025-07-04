#include <stdlib.h>
/*Fishy argument values*/
int main() {
    int size = -100;
    char *buf = malloc(size);  // ❌ size is negative (wrapped as large unsigned)
    free(buf);
    return 0;
}
