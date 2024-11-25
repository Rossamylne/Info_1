#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif
#include <stdio.h>
#include <string.h>
#include "conio.h"

// Mettre dans tests.h les prototypes des actions parametrees des tests
#include "tests.h"
#include "jeu.h"

/**
 * @brief fonction principale
 * @return int compte-rendu d'exécution
 */
int main()
{
    char choix;

    printf("\nTests des fonctionnalités du jeu en mode texte\n");

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
        int generations = 0;

    terrain_t monTerrain;


    //RAZ Terrain
    
    //Initialisation terrain

    //affichage etat de départ
    initAleatoire(&monTerrain);    
    printConsole(&monTerrain);

    while(getche() != 'q'){
        printf("\n%d\n",generations++);
        printf("rendSpherique \n");

        //Votre code ici

        printConsole(&monTerrain);
    }
}
