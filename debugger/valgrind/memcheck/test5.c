#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = malloc(10);
    if (!buf) return 1;

    strcpy(buf, "abcdef");

    // Overlapping memcpy — source and dest overlap incorrectly
    memcpy(buf + 1, buf, 6);  // ❌ copy "abcdef\0" to buf+1

    printf("%s\n", buf);

    free(buf);
    return 0;
}
