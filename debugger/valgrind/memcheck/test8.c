#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 
/*Alignment errors*/
int main() {
    void *ptr_memalign = NULL;
    void *ptr_posix_memalign = NULL;
    void *ptr_aligned_alloc = NULL;

    ptr_memalign = memalign(15, 64); 

    posix_memalign(&ptr_posix_memalign, 63, 64);

    ptr_aligned_alloc = aligned_alloc(0, 64);  

    free(ptr_memalign);
    free(ptr_posix_memalign);
    free(ptr_aligned_alloc);

    return 0;
}
