#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*Memory leak detection*/
void* case1() {
    // Case 1: RRR --> BBB 
    void *BBB = malloc(10 * sizeof(int));
    int i = 0;

    for(i = 0; i < 10; i++)
    {
        *((int*)BBB + i) = i;
    }

    return BBB;
}

void* case2() {
    // Case 2: RRR --> AAA --> BBB
    int i;
    void *AAA = malloc(10 * sizeof(int));
    void *BBB = malloc(10 * sizeof(int));

    for(i = 0; i < 10; i++)
    {
        *((int*)AAA + i) = i;
    }

    for(i = 0; i < 10; i++)
    {
        *((int*)BBB + i) = i;
    }

    *((void **)AAA) = BBB;
    return AAA;
}

void case3() {
    // Case 3: RRR disconnected, BBB unreferenced 
    int i;
    void *BBB = malloc(10 * sizeof(int));

    for(i = 0; i < 10; i++)
    {
        *((int*)BBB + i) = i;
    }

    (void)BBB;
}

void case4() {
    // Case 4: AAA --> BBB, but not referenced by RRR → AAA
    int i;
    void *AAA = malloc(10 * sizeof(int));
    void *BBB = malloc(10 * sizeof(int));

    for(i = 0; i < 10; i++)
    {
        *((int*)AAA + i) = i;
    }

    for(i = 0; i < 10; i++)
    {
        *((int*)BBB + i) = i;
    }

    *((void **)AAA) = BBB;
}

void* case5() {
    // Case 5: RRR -?-> BBB 
    int i;
    void *BBB = malloc(10 * sizeof(int));

    for(i = 0; i < 10; i++)
    {
        *((int*)BBB + i) = i;
    }

    return (void*)(BBB + 1);    /*y(DR) real pointer*/
    //return (void*)(BBB - 1); /*n(DL) not real pointer*/
}

void* case6() {
    // Case 6: RRR --> AAA -?-> BBB 
    int i;
    void *AAA = malloc(10 * sizeof(int));
    void *BBB = malloc(10 * sizeof(int));

    for(i = 0; i < 10; i++)
    {
        *((int*)AAA + i) = i;
    }

    for(i = 0; i < 10; i++)
    {
        *((int*)BBB + i) = i;
    }

    uintptr_t iptr = (uintptr_t)BBB + 1;    /*y(IR) real pointer*/
    //uintptr_t iptr = (uintptr_t)BBB - 1; /*n(DL) not a real pointer */
    *((void **)AAA) = (void *)iptr;

    return AAA;
}

void* case7() {
    // Case 7: RRR -?-> AAA --> BBB 
    int i;
    void *AAA = malloc(10 * sizeof(int));
    void *BBB = malloc(10 * sizeof(int));

    for(i = 0; i < 10; i++)
    {
        *((int*)AAA + i) = i;
    }

    for(i = 0; i < 10; i++)
    {
        *((int*)BBB + i) = i;
    }

    *((void **)AAA) = BBB;

    return AAA - 1;   /*(n)DL, (n)IL not real pointer*/
    //return AAA + 1; /*(y)DR, y(IR) real pointer*/
}

void* case8() {
    // Case 8: RRR -?-> AAA -?-> BBB 
    int i;
    void *AAA = malloc(10 * sizeof(int));
    void *BBB = malloc(10 * sizeof(int));

    for(i = 0; i < 10; i++)
    {
        *((int*)AAA + i) = i;
    }

    for(i = 0; i < 10; i++)
    {
        *((int*)BBB + i) = i;
    }

    uintptr_t iptr = (uintptr_t)BBB + 1;    /*y(IR) real pointer*/
    //uintptr_t iptr = (uintptr_t)BBB - 1; /*n(DL) not a real pointer */
    *((void **)AAA) = (void *)iptr;

    //return AAA - 1;   /*(n)DL, (n)IL not real pointer*/
    return AAA + 1; /*(y)DR, y(IR) real pointer*/
}

void* case9() {
    // Case 9: AAA -?-> BBB, but not referenced by RRR → AAA
    int i;
    void *AAA = malloc(10 * sizeof(int));
    void *BBB = malloc(10 * sizeof(int));

    for(i = 0; i < 10; i++)
    {
        *((int*)AAA + i) = i;
    }

    for(i = 0; i < 10; i++)
    {
        *((int*)BBB + i) = i;
    }

    uintptr_t iptr = (uintptr_t)BBB + 1;    /*y(IR) real pointer*/
    //uintptr_t iptr = (uintptr_t)BBB - 1; /*n(DL) not a real pointer */
    *((void **)AAA) = (void *)iptr;

    //return AAA - 1;   /*(n)DL, (n)IL not real pointer*/
    return AAA + 1; /*(y)DR, y(IR) real pointer*/
}

void case10()
{
    void* ptr = NULL;
    int i;

    for(i = 0; i < 100; i++)
    {
        ptr = malloc(10 * sizeof(int));
    }
}

static void* RRR = NULL;

void printRRR()
{
    int i;
    for(i = 0; i < 10; i++)
    {
        printf("%d ", *((int*)RRR + i));
    }
    printf("\n");
}

int main() {
    printf("Running all leak cases...\n");
    
    int option;

    printf("Enter option: ");
    scanf("%d", &option);

    switch (option)
    {
        case 1:
            printf("case 1\n");
            RRR = case1();
            printRRR();
            break;
        case 2:
            printf("case 2\n");
            RRR = case2();
            printRRR();
            break;
        case 3:
            printf("case 3\n");
            case3();
            break;
        case 4: 
            printf("case 4\n");
            case4();
            break;
        case 5:
            printf("case 5\n");
            RRR = case5();  /*is a real pointer*/
            // case5(); /*not a real pointer*/
            break;
        case 6:
            printf("case 6\n");
            RRR = case6();
            printRRR();
            break;
        case 7:
            printf("case 7\n");
            RRR = case7();
            printRRR();
            break;
        case 8:
            printf("case 8\n");
            RRR = case8();
            printRRR();
            break;
        case 9:
            printf("case 9\n");
            case9();
            break;
        case 10:
            printf("case 10\n");
            case10();
            break;
    }

    free(RRR);

    printf("Done. Run under Valgrind for analysis.\n");
    return 0;
}
