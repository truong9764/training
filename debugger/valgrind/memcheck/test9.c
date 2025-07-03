#include <stdlib.h>
#include <unistd.h>

int main( void )
{
    char* arr  = malloc(10);
    int*  arr2 = malloc(sizeof(int));
    write(1, arr, 10 ); /*write 10 elements in arr to stdout*/
    exit(arr2[0]); /*exit program and return status*/
}