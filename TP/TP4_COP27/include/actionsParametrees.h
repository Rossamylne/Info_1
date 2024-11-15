#ifndef ACTIONSPARAMETREES_H_
#define ACTIONSPARAMETREES_H_

#include "IHM_Window.h"
#include <stdbool.h>

/* Constantes */

#define EPAISSEUR_CADRE 2
#define HAUTEUR_ORDONNEE 300
#define LONGUEUR_ABSCISSE 400
#define NB_MAX_LECTURE 300

#define ROUGE IHM_Window_couleur(255, 0, 0)
#define VERT IHM_Window_couleur(0, 255, 0)
#define BLEU IHM_Window_couleur(0, 0 , 255)

/* Prototypes des actions paramétrées utilisées */

/* Mettre les commentaires doxigen */

/**
 * @brief ... à compléter !
 * 
 * @param fichier 
 * @param valeurs 
 * @param temps 
 * @param nbValLues 
 * @return 
 */
bool lirePoints(char *fichier, int *valeurs, int *temps, int *nbValLues);

#endif //ACTIONSPARAMETREES_H_
