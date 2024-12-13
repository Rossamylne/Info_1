#ifndef FONCTIONSGRAPHIQUES_H_
#define FONCTIONSGRAPHIQUES_H_

#include "IHM_Window.h"
#include "jeu.h"
#include <stdbool.h>

/* Constantes */

/* Prototypes des actions paramétrées utilisées */

/* Mettre les commentaires doxigen */

void placeCellules(terrain_t *monTerrain);
void placePoint(int pos_y, int pos_x, int case_h, int case_w);
void dessineGrille(int h, int w, int case_height, int case_width);

#endif //FONCTIONSGRAPHIQUES_H_
