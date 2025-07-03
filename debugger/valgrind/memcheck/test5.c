#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char* buffer = malloc(100);
    int i;

    for(i = 0; i < 100; i++)
    {
        buffer[i] = i;
    }

    memcpy(buffer + 10, buffer, 50); // src and dst overlap!
    free(buffer);
    return 0;
}
