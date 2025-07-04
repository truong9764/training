#include <stdio.h>
/*Use of uninitialised values*/
int main() {
    int x;           // ❌ uninitialized
    printf("%d\n", x);  // using undefined value
    return 0;
}
