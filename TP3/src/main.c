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
    
    /* environnement */ /* rôle des objets */
    char car;           // variable contenant le caractère courant
    int nbGE;           // Nombre de GE déjà lu
    bool G_lu;          // variable logique vraie si le dernier
                        // caractère lu a été un ‘G’
    /* algorithme */
    nbGE = 0;
    G_lu = false;
    do
    {
        car = getchar();
        if (G_lu && car == 'E')
        {
            nbGE = nbGE + 1;
            G_lu = false;
        }
        else
        {
            if (car != 'G')
            {
                G_lu = false;
            }
            else
            {
                G_lu = true;
            }
        }
    } while (car != '.');
    printf("Nombre de 'GE' = %d \n", nbGE);
    return 0;
}
