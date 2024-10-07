#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"

int main(int argc, char **argv)
{
    printf("\nBase de projet BUT GEII - Module Info1\n\n");
    int NB_MAX = 40;
    char CAR_FIN = '\n';
    int i, nbCar = 0;
    char word[NB_MAX], reverseWord[NB_MAX], car;
    bool areCharSame = true;

    /* Algorithm */
    printf("\nType chain of characters (press Enter to finish): ");
    do {
        car = getchar();
        if((car != CAR_FIN) && (car != ' ') && (nbCar < NB_MAX)) {
            word[nbCar] = car;
            nbCar = nbCar + 1;
        }
    }while(car != CAR_FIN);
    for(i = 0; i < nbCar; i++) {
        reverseWord[i] = word[i];
    }
    /*
    printf("\nCharacters in reverse order: ");
    for(i = 0; i < nbCar; i++) {
        printf("%c", reverseWord[i]);
    }
    printf("\nIndexes of characters: ");
    for(i = 0; i < nbCar; i++) {
        printf("%d ", i);
    }
    */
    for(i = 0; i < nbCar; i++) {
        if (word[i] != reverseWord[i]) {
            areCharSame = false;
            break;
        }
    }
    switch(areCharSame) {
        case true:
            printf("\nThe word \"%s\" is a palindrome\n", word);
            break;

        case false:
            printf("\nThe word \"%s\" is not a palindrome\n", word);
            break;

        default:
            printf("\nError\n");
            break;
    }

    return 0;
}