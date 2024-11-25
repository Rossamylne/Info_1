#ifndef FONCTIONSGRAPHIQUES_H_
#define FONCTIONSGRAPHIQUES_H_

#include "IHM_Window.h"
#include "jeu.h"
#include <stdbool.h>

/* Constantes */

/* Prototypes des actions paramétrées utilisées */

/* Mettre les commentaires doxigen */

void dessineGrille(void);
void placePoint(int x, int y);
void placeCellules(terrain_t *monTerrain);

#endif //FONCTIONSGRAPHIQUES_H_
