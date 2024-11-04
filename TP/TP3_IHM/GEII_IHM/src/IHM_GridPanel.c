#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include "IHM_GridPanel.h"
#include "IHM_Window.h"

void IHM_GridPanel_init(IHM_GridPanel_t *self, struct IHM_Window *parent){
    self->parent = parent;
    self->grille = NULL;
}

void IHM_GridPanel_destroy(IHM_GridPanel_t *self){
    free(self->grille);
}

void IHM_GridPanel_setBoundaries(IHM_GridPanel_t *self, int top, int left, int width, int height){
    if(left>=0) self->boundingRect.x = left;
    if(top>=0) self->boundingRect.y = top;
    if(width>=0) self->boundingRect.w = width;
    if(height>=0) self->boundingRect.h = height;
}

void IHM_GridPanel_setGrid(IHM_GridPanel_t *self, int nbLignes, int nbColonnes){
    self->nbLignes = nbLignes;
    self->nbColonnes = nbColonnes;
    self->grille = (int*)malloc(nbLignes*nbColonnes*sizeof(int));
    if(self->grille != 0)
    for(int i =0; i< nbColonnes; i++)
        for(int j=0; j< nbLignes; j++){
            self->grille[i+j*nbColonnes] = 0;
        }
}

void IHM_GridPanel_setCell(IHM_GridPanel_t *self, int x, int y, int val){
    if(x>=0 && x<self->nbColonnes && y >=0 && y<self->nbLignes)
        self->grille[x+y*self->nbColonnes] = val;
}


void IHM_GridPanel_draw(IHM_GridPanel_t *self){

    IHM_Window_drawFillRect(self->parent,
                            self->boundingRect.x,
                            self->boundingRect.y,
                            self->boundingRect.h,
                            self->boundingRect.w,
                            IHM_Window_couleur(255,255,255));

    //colonnes
    float colW = (float)(self->boundingRect.w) / self->nbColonnes;
    for(int i=0; i<=self->nbColonnes; i++){
        int tmpX = i*colW+self->boundingRect.x;
        IHM_Window_drawLine(   self->parent,
                                tmpX,
                                self->boundingRect.y,
                                tmpX,
                                self->boundingRect.y+self->boundingRect.h,
                                IHM_Window_couleur(0,0,0)
                                );
    }

    //lignes
    float ligneH = (float)(self->boundingRect.h) / self->nbLignes;
    for(int i=0; i<=self->nbLignes; i++)
        IHM_Window_drawLine(self->parent,
                                self->boundingRect.x,
                                self->boundingRect.y+i*ligneH,
                                self->boundingRect.x+self->boundingRect.w,
                                self->boundingRect.y+i*ligneH,
                                IHM_Window_couleur(0,0,0)
                                );

    //Cases

    if(self->grille != 0)
    for(int i =0; i< self->nbColonnes; i++)
        for(int j=0; j< self->nbLignes; j++){
            if(self->grille[i+j*self->nbColonnes] != 0)
                IHM_Window_drawFillRect(self->parent, 
                            self->boundingRect.x+i*colW+1, 
                            self->boundingRect.y+j*ligneH+1, 
                            ligneH-1, colW-1,
                            IHM_Window_couleur(255,0,0));
        }
    
}

void IHMgridPanelCoordVersCase(IHM_GridPanel_t *self, int localX, int localY, int* caseX, int* caseY){
    float colW = (float)(self->boundingRect.w) / self->nbColonnes;
    float ligneH = (float)(self->boundingRect.h) / self->nbLignes;
    *caseX = localX / colW;
    *caseY = localY / ligneH;
}
