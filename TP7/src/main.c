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

/**
 * @file Main.c
 * @brief Get biggest number
 * @author Loris
 * @date 07/10/2024
 */



int main(int argc, char **argv)
{
        /* environnement */
    /*int vA, vB, vC;*/
    int valueList[10];
    int i;
    /*Algorithm*/


    for(i=0;i<10;i++) {
        valueList[i] = getArraySize(i);
    }
    printf("Biggest value is %d\n", getBiggestValueInArray(valueList));
    /*
    vA = getUserValue("A");
    vB = getUserValue("B");
    vC = getUserValue("C");
    printf("The biggest value is %d\n", testBiggestValue(vA, vB, vC));
    */
    return 0;
}