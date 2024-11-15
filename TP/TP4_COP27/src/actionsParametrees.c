#include <stdio.h>

#include "IHM_Setup.h"
#include "actionsParametrees.h"


bool lirePoints(char *fichier, int *valeurs, int *temps, int *nbValLues)
{
    // Fichier
    FILE *fp;
    // variables pour le temps et la valeur
    int t,v; 
    // nombre de champs lus à chaque ligne
    int nbChamp;
    
    // ouverture fichier
    fp = fopen(fichier, "r");
    // Si le fichier n'est pas ouvrable
    if (!fp)
    {
        printf("Impossible d'ouvrir le fichier!");
    }
    else
    {
        do
        {
            // On lit les deux champs année / valeur
            nbChamp = fscanf(fp, "%d;%d", &t, &v);
            if (nbChamp == 2)
            {
                // ... à compléter !
                printf("valeurs lues : %d %d \n",t,v);
            }
        } while (!feof(fp));
        // Fermeture du fichier
        fclose(fp);
        printf(" Nb points = %d\n", *nbValLues);
    }
    return false; // ou true ? completer...
}

void afficheCadre(int x, int y) {
    int w,h;
    getWindowSize(&w, &h);
    dessineRectanglePlein(0, 0, h, w, IHM_Window_couleur(255,255,255));
    dessineRectanglePlein(((w - y) / 2), ((h - x) / 2), y, x, IHM_Window_couleur(0,0,0));
    dessineRectanglePlein(((w - (y-2)) / 2), ((h - (x-2)) / 2), y-2, x -2, IHM_Window_couleur(255,255,255));
}