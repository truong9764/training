#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



void* case1() {
    // Case 1: RRR --> BBB 
    void *BBB = malloc(10);
    return BBB;
}

void* case2() {
    // Case 2: RRR --> AAA --> BBB
    void *AAA = malloc(10);
    void *BBB = malloc(10);
    *((void **)AAA) = BBB;
    return AAA;
}

void case3() {
    // Case 3: RRR disconnected, BBB unreferenced 
    void *BBB = malloc(10);
    (void)BBB;
}

void case4() {
    // Case 4: AAA --> BBB, but not referenced by RRR → AAA: DL, BBB: IL
    void *AAA = malloc(10);
    void *BBB = malloc(10);
    *((void **)AAA) = BBB;
}

void* case5() {
    // Case 5: RRR holds interior pointer to BBB → (y)DR, (n)DL
    void *BBB = malloc(10);
    return (uintptr_t)BBB + 1;
}

void* case6() {
    // Case 6: RRR --> AAA -?-> BBB → AAA: DR, BBB: (y)IR, (n)DL
    void *AAA = malloc(sizeof(void *));
    void *BBB = malloc(10);
    uintptr_t iptr = (uintptr_t)BBB + 1;
    *((void **)AAA) = (void *)iptr;
    void *RRR = AAA;
    (void)RRR;
    return NULL;
}

void* case7() {
    // Case 7: RRR -?-> AAA --> BBB → (y)DR/IR or (n)DL/IL
    void *AAA = malloc(sizeof(void *));
    void *BBB = malloc(10);
    *((void **)AAA) = BBB;
    uintptr_t iptr = (uintptr_t)AAA + 1;
    void *RRR = (void *)iptr;
    (void)RRR;
    return NULL;
}

void* case8() {
    // Case 8: RRR -?-> AAA -?-> BBB → many combinations
    void *AAA = malloc(sizeof(void *));
    void *BBB = malloc(10);
    uintptr_t iptrBBB = (uintptr_t)BBB + 1;
    *((void **)AAA) = (void *)iptrBBB;
    uintptr_t iptrAAA = (uintptr_t)AAA + 1;
    void *RRR = (void *)iptrAAA;
    (void)RRR;
    return NULL;
}

void* case9() {
    // Case 9: AAA -?-> BBB, no root → AAA: DL, BBB: (y)IL, (n)DL
    void *AAA = malloc(sizeof(void *));
    void *BBB = malloc(10);
    uintptr_t iptrBBB = (uintptr_t)BBB + 1;
    *((void **)AAA) = (void *)iptrBBB;
    return NULL;
}



int main() {
    printf("Running all leak cases...\n");
    static void* RRR = NULL;
    int option;

    printf("Enter option: ");
    scanf("%d", &option);

    switch (option)
    {
        case 1:
            RRR = case1();
            break;
        case 2:
            RRR = case2();
            break;
        case 3:
            case3();
            break;
        case 4:
            case4();
            break;
        case 5:
            RRR = case5();
            break;
        case 6:
            RRR = case6();
            break;
        case 7:
            RRR = case7();
            break;
        case 8:
            RRR = case8();
            break;
        case 9:
            RRR = case9();
            break;
    }

    printf("Done. Run under Valgrind for analysis.\n");
    return 0;
}
