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
    int userNumber;     /* Integer given by user*/
    int sum;            /* Sum of all inferior numbers*/
    int i;
    int typeOfSum;
    do {
        printf("Value of the N integer:\n");
        scanf("%d", &userNumber);
    } while(userNumber  <= 0);
    do {
        printf("\n1 : sum of all integers\n2 : sum of peer integer\n3 : sum of odd integer\nType of sum :");
        scanf("%d", &typeOfSum); /* 1 : All Integers */      /* 2 : Peer */       /* 3 : Odd */
    } while(typeOfSum < 1 || typeOfSum > 3);
    
    if(typeOfSum == 1){
        printf("\nLa somme des %d entiers vaut : %d\n",userNumber, allIntegersSum(userNumber));
    } else if(typeOfSum == 2) {
        printf("\nLa somme des %d entiers pair vaut : %d\n",userNumber, peerSum(userNumber));
    } else if(typeOfSum == 3) {
        printf("\nLa somme des %d entiers impair vaut : %d\n",userNumber, oddSum(userNumber));
    };
    
    return 0;
}
