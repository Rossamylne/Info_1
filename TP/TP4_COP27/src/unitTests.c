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
        printf("\n1 Test Témoin");

        printf("\nChoix? ('q' pour quitter)");
        if((choix = getche()) == '\n') choix = getche();

        if(choix == '1') testTemoin();
    }while(choix!='q');
    printf("\n");
}

void testTemoin()
{
    int resultat = 0;
    printf("\nTest témoin toujours OK\n");
    //Mettre en oeuvre la fonction ici
    if (resultat == 0)
        printf("test OK\n");
    else
        printf("test KO\n");
}
