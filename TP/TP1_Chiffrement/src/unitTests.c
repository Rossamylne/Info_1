#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif
#include <stdio.h>
#include <string.h>
#include "conio.h"

// Mettre dans main.h les prototypes des actions parametrees
#include "unitTests.h"
#include "actionsParametrees.h"

/**
 * @brief fonction principale
 * @return int compte-rendu d'exécution
 */
int main()
{
    char choix;

    printf("\nTests unitaires des fonctions\n");

    do
    {
        printf("\n1 Test acquerirCle(min,max)\n");
        printf("\n2 Test ChiffrerMin(char car,int cle)\n");

        printf("\nChoix? ('q' pour quitter)");
        if((choix = getche()) == '\n') choix = getche();

        if(choix == '1') testAcquerirCle();
        if(choix == '2') testChiffrerMin();
    }while(choix!='q');
    printf("\n");
}

void testAcquerirCle()
{
    int cle;
    int min = 0, max = 12;
    printf("\nSaisie en boucle jusqu'a ce qu'une valeur entre min et max soit rentree\n");
    cle = acquerirCle(min, max);
    if (cle >= min && cle <= max)
        printf("test OK\n");
    else
        printf("test KO\n");
}

void testChiffrerMin()
{
    char resultat;

    printf("\nChiffrage sans repliement - car='g', cle=10 \n");
    resultat = chiffrerMin('g', 10);
    if (resultat == 'p')
        printf("Resultat %c - test OK\n", resultat);
    else
        printf("Resultat %c - test KO\n", resultat);

    printf("\nChiffrage avec repliement - car='o', cle=15 \n");
    resultat = chiffrerMin('o', 15);
    if (resultat == 'd')
        printf("Resultat %c - test OK\n", resultat);
    else
        printf("Resultat %c - test KO\n", resultat);
}