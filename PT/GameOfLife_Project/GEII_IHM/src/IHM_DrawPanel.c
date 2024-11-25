#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include <SDL2/SDL.h>

#include "IHM_DrawPanel.h"
#include "IHM_Window.h"

void IHM_DrawPanel_init(IHM_DrawPanel_t *self, struct IHM_Window *parent){
    self->parent = parent;
    self->listeFigures = NULL;
    self->texture = SDL_CreateTexture(self->parent->sdlRenderer, 
        SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,100,100);
    self->maxX = 0;
    self->maxY = 0;
    self->xScale = 1.0;
    self->yScale = 1.0;
    self->scalable = 0;
    self->reverseY = 0;
}

void IHM_DrawPanel_destroy(IHM_DrawPanel_t *self){
    SDL_DestroyTexture(self->texture);
    IHM_DrawPanel_listeFigures_t *tmpPtr = self->listeFigures;
    IHM_DrawPanel_listeFigures_t *tmpPrec;
    while(tmpPtr != NULL){
        tmpPrec = tmpPtr;
        tmpPtr = tmpPtr->next;
        free(tmpPrec);
    }
        self->listeFigures=NULL;
}

void IHM_DrawPanel_setBoundaries(IHM_DrawPanel_t *self, int top, int left, int width, int height){
    if(left>=0) self->boundingRect.x = left;
    if(top>=0) self->boundingRect.y = top;
    if(width>=0) self->boundingRect.w = width;
    if(height>=0) self->boundingRect.h = height;
    SDL_DestroyTexture(self->texture);
    self->texture = SDL_CreateTexture(self->parent->sdlRenderer, 
        SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,width,height);
}

void IHM_DrawPanel_scale(IHM_DrawPanel_t *self, int x, int y){
    //si nécessaire ajuste le facteur x
    if(self->scalable){
        if(x>self->maxX) self->maxX = x;
        if(self->maxX > self->boundingRect.w)
            self->xScale = (float)(self->boundingRect.w) / (float)(self->maxX);
        else self->xScale = 1.0;
    }
    //si nécessaire ajuste le facteur y
    if(self->scalable){
        if(y>self->maxY) self->maxY = y;
        if(self->maxY>self->boundingRect.h)
            self->yScale = (float)(self->boundingRect.h) / (float)(self->maxY);
        else self->yScale = 1.0;
    }
}

void IHM_DrawPanel_addPoint(IHM_DrawPanel_t *self, int x1, int y1, unsigned long int couleur){
    IHM_DrawPanel_figure_t *new = (IHM_DrawPanel_figure_t*)malloc(sizeof(IHM_DrawPanel_figure_t));
    new->type = POINT_T;
    new->point.x = x1;
    new->point.y = y1;
    new->next = NULL;
    new->couleur = couleur;
    IHM_DrawPanel_listeFigures_t *tmpPtr = self->listeFigures;
    if(tmpPtr == NULL) self->listeFigures = new;
    else{
        while(tmpPtr->next != NULL) tmpPtr = tmpPtr->next;
        tmpPtr->next = new;
    }

    IHM_DrawPanel_scale(self, x1,y1);
    
}

void IHM_DrawPanel_addLine(IHM_DrawPanel_t *self, int x1, int y1, int x2, int y2, unsigned long int couleur){
    IHM_DrawPanel_figure_t *new = (IHM_DrawPanel_figure_t*)malloc(sizeof(IHM_DrawPanel_figure_t));
    new->type = LINE_T;
    new->line.p1.x = x1;
    new->line.p1.y = y1;
    new->line.p2.x = x2;
    new->line.p2.y = y2;
    new->couleur = couleur;
    new->next = NULL;
    IHM_DrawPanel_listeFigures_t *tmpPtr = self->listeFigures;
    if(tmpPtr == NULL) self->listeFigures = new;
    else{
        while(tmpPtr->next != NULL) tmpPtr = tmpPtr->next;
        tmpPtr->next = new;
    }
    IHM_DrawPanel_scale(self, x1,y1);
    IHM_DrawPanel_scale(self, x2,y2);

}

void IHM_DrawPanel_addRect(IHM_DrawPanel_t *self, int top, int left, int width, int height, unsigned long int couleur){
    IHM_DrawPanel_figure_t *new = (IHM_DrawPanel_figure_t*)malloc(sizeof(IHM_DrawPanel_figure_t));
    new->type = RECT_T;
    new->rect.x = left;
    new->rect.y = top;
    new->rect.w = width;
    new->rect.h = height;
    new->couleur = couleur;
    new->next = NULL;
    IHM_DrawPanel_listeFigures_t *tmpPtr = self->listeFigures;
    if(tmpPtr == NULL) self->listeFigures = new;
    else{
        while(tmpPtr->next != NULL) tmpPtr = tmpPtr->next;
        tmpPtr->next = new;
    }
}

void IHM_DrawPanel_addFilledRect(IHM_DrawPanel_t *self, int top, int left, int width, int height, unsigned long int couleur){
    IHM_DrawPanel_figure_t *new = (IHM_DrawPanel_figure_t*)malloc(sizeof(IHM_DrawPanel_figure_t));
    new->type = FILLRECT_T;
    new->rect.x = left;
    new->rect.y = top;
    new->rect.w = width;
    new->rect.h = height;
    new->couleur = couleur;
    new->next = NULL;
    IHM_DrawPanel_listeFigures_t *tmpPtr = self->listeFigures;
    if(tmpPtr == NULL) self->listeFigures = new;
    else{
        while(tmpPtr->next != NULL) tmpPtr = tmpPtr->next;
        tmpPtr->next = new;
    }
}

void IHM_DrawPanel_addText(IHM_DrawPanel_t *self, int x, int y, char* text, unsigned long int couleur){
    IHM_DrawPanel_figure_t *new = (IHM_DrawPanel_figure_t*)malloc(sizeof(IHM_DrawPanel_figure_t));
    new->type = TEXT_T;
    strcpy(new->text.string,text);
    new->text.coords.x = x;
    new->text.coords.y = y;
    new->next = NULL;
    new->couleur = couleur;
    IHM_DrawPanel_listeFigures_t *tmpPtr = self->listeFigures;
    if(tmpPtr == NULL) self->listeFigures = new;
    else{
        while(tmpPtr->next != NULL) tmpPtr = tmpPtr->next;
        tmpPtr->next = new;
    }
}

void IHM_DrawPanel_clear(IHM_DrawPanel_t *self){
    IHM_DrawPanel_listeFigures_t *tmpPtr = self->listeFigures;
    IHM_DrawPanel_listeFigures_t *tmpPrec;
    while(tmpPtr != NULL){
        tmpPrec = tmpPtr;
        tmpPtr = tmpPtr->next;
        free(tmpPrec);
    }
    self->listeFigures=NULL;
}

void IHM_DrawPanel_draw(IHM_DrawPanel_t *self){

    SDL_SetRenderTarget(self->parent->sdlRenderer, self->texture);

    IHM_Window_drawFillRect(self->parent,
                            0,
                            0,
                            self->boundingRect.h,
                            self->boundingRect.w,
                            IHM_Window_couleur(255,255,255));

    IHM_DrawPanel_listeFigures_t *tmpPtr = self->listeFigures;
        while(tmpPtr != NULL){
            int Y1,Y2;
            switch(tmpPtr->type){
                case POINT_T :
                if(!self->reverseY){
                    Y1 = tmpPtr->point.y*self->yScale;
                }
                else{
                    Y1 = self->boundingRect.h - tmpPtr->point.y*self->yScale;
                }
                IHM_Window_drawPoint(self->parent,
                    tmpPtr->point.x*self->xScale, Y1,
                    tmpPtr->couleur);
                break;

                case LINE_T :
                if(!self->reverseY){
                    Y1 = tmpPtr->line.p1.y*self->yScale;
                    Y2 = tmpPtr->line.p2.y*self->yScale;
                }
                else{
                    Y1 = self->boundingRect.h - tmpPtr->line.p1.y*self->yScale;
                    Y2 = self->boundingRect.h - tmpPtr->line.p2.y*self->yScale;
                }
                IHM_Window_drawLine(self->parent,
                    tmpPtr->line.p1.x*self->xScale, Y1,
                    tmpPtr->line.p2.x*self->xScale, Y2,
                    tmpPtr->couleur);
                break;

                case RECT_T :
                IHM_Window_drawRect(self->parent,
                    tmpPtr->rect.x*self->xScale, tmpPtr->rect.y*self->yScale, 
                    tmpPtr->rect.h, tmpPtr->rect.w,
                    tmpPtr->couleur);
                break;

                case FILLRECT_T:
                IHM_Window_drawFillRect(self->parent,
                    tmpPtr->rect.x*self->xScale, tmpPtr->rect.y*self->yScale, 
                    tmpPtr->rect.h, tmpPtr->rect.w,
                    tmpPtr->couleur);
                break;

                case TEXT_T :
                IHM_Window_texte(self->parent,
                    tmpPtr->text.coords.x*self->xScale, tmpPtr->text.coords.y*self->yScale,
                    tmpPtr->text.string,
                    tmpPtr->couleur);
                break;
            }

            tmpPtr = tmpPtr->next;
    }

    SDL_SetRenderTarget(self->parent->sdlRenderer, NULL);
    SDL_RenderCopy(self->parent->sdlRenderer, self->texture, NULL, &self->boundingRect);

}
