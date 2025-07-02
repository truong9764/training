#include <stdio.h>

int main() {
    int x;           // ❌ uninitialized
    printf("%d\n", x);  // using undefined value
    return 0;
}
