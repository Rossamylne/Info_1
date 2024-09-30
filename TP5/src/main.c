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
        /* environnement */ /* rôle des objets */
    int NB_MAX = 40;
    const CAR_FIN = "\r";
    int i, nbCar;
    char word[NB_MAX];
    char car;
    /* Algorithm*//* condition */
    printf("\nType chain of caracter : ");
    do {
        car = getchar();
        if((car != CAR_FIN) && (car != " ") && (nbCar < NB_MAX)) {
            word[nbCar] = car;
            nbCar = nbCar + 1;
            printf("\n table --> %c\n", word);
        }
    } while((car != CAR_FIN) || (nbCar == 0));
    for(i = 0;i <= nbCar-1;i++) {
        printf("%d", i);
    }
    return 0;
}