#include <stdlib.h>
/*Illegal frees*/
int main() {
    int *p = malloc(10 * sizeof(int));
    free(p);
    free(p);  // ❌ double free
    return 0;
}
