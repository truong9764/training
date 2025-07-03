#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *buffer = malloc(10);
    if (!buffer) return 1;

    strcpy(buffer, "ABC");
    strcpy(buffer, buffer + 1); 

    printf("%s\n", buffer);

    free(buffer);
    return 0;
}
