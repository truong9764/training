#include <cstdlib>

int main() {
    int* x = (int*)malloc(sizeof(int));
    delete x;  // ❌ should use free(x)
    return 0;
}