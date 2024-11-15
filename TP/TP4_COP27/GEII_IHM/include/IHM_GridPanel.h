#ifndef IHM_GRIDPANEL_H
#define IHM_GRIDPANEL_H

#include <SDL2/SDL.h>

struct IHM_Window;

typedef struct {
    SDL_Rect boundingRect;

    int nbLignes, nbColonnes;
    int* grille;

    struct IHM_Window *parent;

} IHM_GridPanel_t;

void IHM_GridPanel_init(IHM_GridPanel_t *self, struct IHM_Window *parent);

void IHM_GridPanel_destroy(IHM_GridPanel_t *self);

void IHM_GridPanel_setBoundaries(IHM_GridPanel_t *self, int top, int left, int width, int height);

void IHM_GridPanel_setGrid(IHM_GridPanel_t *self, int nbLignes, int nbColonnes);

void IHM_GridPanel_draw(IHM_GridPanel_t *self);

void IHM_GridPanel_setCell(IHM_GridPanel_t *self, int x, int y, int val);

void IHMgridPanelCoordVersCase(IHM_GridPanel_t *self, int localX, int localY, int* caseX, int* caseY);

#endif //IHM_GRIDPANEL_H