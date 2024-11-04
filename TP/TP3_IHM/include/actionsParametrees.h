#ifndef ACTIONSPARAMETREES_H_
#define ACTIONSPARAMETREES_H_

#include "IHM_Window.h"

#define LARGEUR_TRAIN 40
#define HAUTEUR_PALETTE 20


void afficheTrain(int x, int y, unsigned long coul);
void afficheRails(int x, int y);
void affichePalette(unsigned long palette[], int nbCouleurs);
int getIndiceCouleur(int x, int nbCouleurs);

/* Prototypes des actions paramétrées utilisées */


#endif //ACTIONSPARAMETREES_H_