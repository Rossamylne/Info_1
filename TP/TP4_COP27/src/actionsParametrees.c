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
    int i = 0;
    
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
                temps[i]=t;
                valeurs[i]=v;
                i=i+1;
                printf("valeurs lues : %d %d \n",t,v);
            }
        } while (!feof(fp));
        // Fermeture du fichier
        fclose(fp);
        *nbValLues=i;
        printf(" Nb points = %d\n", *nbValLues);
    }
    return false; // ou true ? completer...
}

void afficheCadre(int x, int y) {
    // Dessine le fond (le grand rectangle blanc)
    dessineRectanglePlein(0, 0, y, x, IHM_Window_couleur(255, 255, 255));

    // Dimensions du cadre noir (au centre)
    int largeurCadre = HAUTEUR_ORDONNEE;
    int hauteurCadre = LONGUEUR_ABSCISSE;

    // Calcul des positions du rectangle noir centré
    int xNoir = (x - largeurCadre) / 2;
    int yNoir = (y - hauteurCadre) / 2;

    // Dessine le rectangle noir (le cadre)
    dessineRectanglePlein(xNoir, yNoir, largeurCadre, hauteurCadre, IHM_Window_couleur(0, 0, 0));

    // Dessine le rectangle blanc à l'intérieur du cadre noir (l'intérieur du cadre)
    dessineRectanglePlein(xNoir + 1, yNoir + 1, largeurCadre - 2, hauteurCadre - 2, IHM_Window_couleur(255, 255, 255));
}