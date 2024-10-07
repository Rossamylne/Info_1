#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"
#include "main.h"

int main(int argc, char **argv)
{
    printf("\nBase de projet BUT GEII - Module Info1\n\n");
        /* environnement */ /* rôle des objets */
    int vA, vB, vC;
    vA = getUserValue("A");
    vB = getUserValue("B");
    vC = getUserValue("C");
    printf("The biggest value is %d\n", testBiggestValue(vA, vB, vC));
    return 0;
}