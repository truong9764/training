#include <stdlib.h>
#include <stdio.h>
/*Illegal read / illegal write error*/
int main() {
    int *arr = malloc(5 * sizeof(int));
    arr[5] = 42;  // ❌ out-of-bounds (index 0-4 valid)
    free(arr);
    return 0;
}
