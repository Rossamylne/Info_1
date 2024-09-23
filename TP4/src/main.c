#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "main.h"

/* Function prototype */
int allIntegersSum(int n) ;
int peerSum(int n) ;
int oddSum(int n) ;

int main(int argc, char **argv)
{
    printf("\nBase de projet BUT GEII - Module Info1\n\n");
    
    /* environnement */ /* rôle des objets */
    int userNumber;     /* Integer given by user*/
    int sum;            /* Sum of all inferior numbers*/
    int i;
    int typeOfSum;
    do {
        printf("Value of the N integer:\n");
        scanf("%d", &userNumber);
    } while(userNumber  <= 0);
    printf("\n1 : sum of all integers\n2 : sum of peer integer\n3 : sum of odd integer\nType of sum :");
    sum = 0;
    for(i = 1; i <= userNumber; i++){
        sum = sum + i;
    }
    printf("\nLa somme des %d entiers vaut : %d\n",userNumber,sum);
    return 0;
}
