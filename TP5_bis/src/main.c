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
#define TAILLE_MAX 64


int main(int argc, char **argv)
{
    printf("\nBase de projet BUT GEII - Module Info1\n\n");
    int NB_MAX = 40;
    char CAR_FIN = '\n';
    int i, nbCar = 0;
    char word[NB_MAX], reverseWord[NB_MAX], car;
    bool areCharSame = true;


    /*OPEN FILE*/
    FILE* monFichier = NULL;
    char phrase[TAILLE_MAX];
    monFichier = fopen("./build/dictionnaire.txt","r");
    if (monFichier != NULL) {
        while ( fgets(phrase, TAILLE_MAX, monFichier) != NULL ) {
        printf("phrase : %s \n", phrase);               /* UNFUNCTIONNAL*/
        for(i=0;i<phrase;i++) {
            word[i] = phrase[i];
        }
        for(i = 0; i < nbCar; i++) {
        reverseWord[i] = word[i];
        }
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
        } 
        fclose(monFichier);
    }
    else // message d'erreur
    {
    printf("Impossible d'ouvrir le fichier entree.txt \n");
    }


    /* Algorithm */
    for(i = 0; i < nbCar; i++) {
        reverseWord[i] = word[i];
    }
    printf("\nCharacters in reverse order: ");
    for(i = 0; i < nbCar; i++) {
        printf("%c", reverseWord[i]);
    }
    printf("\nIndexes of characters: ");
    for(i = 0; i < nbCar; i++) {
        printf("%d ", i);
    }
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