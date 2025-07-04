#include <stdlib.h>
/*Realloc size zero*/
int main() {
    int *p = malloc(10 * sizeof(int));
    p = realloc(p, 0);  // ❌ returns NULL or frees memory depending on implementation
    return 0;
}
