#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif
#include <stdio.h>
#include <string.h>
#include "conio.h"

// Mettre dans main.h les prototypes des actions parametrees
#include "main.h"
#include "actionsParametrees.h"

/**
 * @brief fonction principale
 * @return int compte-rendu d'exécution
 */
int main()
{
    char unCar;          // caractère courant
    char unCarChiffre;   // caractère courant chiffré
    char unCarDechiffre; // caractère courant déchiffré
    int laCle;           // clé de chiffrement
    int nbCar;           // nombre de caractères lus

    laCle = acquerirCle(0, 25);

    printf("\nFournir les caracteres a chiffrer...\n");
    printf("\n\nCar \t| Car \t| Car");
    printf("\nInit \t| Code \t| Decode");
    nbCar = 0;
    do
    {
        unCar = getch();
        if (unCar != '.' && unCar != '\n' && unCar != '\r')
        {
            nbCar++;
            unCarChiffre = chiffrerCar(unCar, laCle);
            unCarDechiffre = dechiffrerCar(unCarChiffre, laCle);
            printf("\n%c \t| %c \t| %c", unCar, unCarChiffre, unCarDechiffre);
            printf("%d", nbCar);
        }
    } while((unCar != '.') && (nbCar < MAX_NB_CAR));

    printf("\nAppuyer sur une touche pour terminer...");
    getch();
    return 0;
}
