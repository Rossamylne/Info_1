#include "IHM_Button.h"
#include "IHM_Window.h"

void IHM_Button_init(IHM_Button_t *self, IHM_Window_t *parent){
    self->parent = parent;
    self->imageReleased = NULL;
    self->imagePressed = NULL;
    
    self->caption = NULL;
    self->state = 0;
}

void IHM_Button_destroy(IHM_Button_t *self){
    SDL_DestroyTexture(self->imagePressed);
    SDL_DestroyTexture(self->imageReleased);
    free(self->caption);
}

void IHM_Button_setBoundaries(IHM_Button_t *self, int top, int left, int width, int height){
    if(left>=0) self->boundingRect.x = left;
    if(top>=0) self->boundingRect.y = top;
    if(width>=0) self->boundingRect.w = width;
    if(height>=0) self->boundingRect.h = height;
}

void IHM_Button_setCaption(IHM_Button_t *self, char *caption){
    self->caption=(char*)realloc(self->caption, strlen(caption)+1);
    strcpy(self->caption, caption);
}

void IHM_Button_setImages(IHM_Button_t *self, char* pathToReleasedBmp, char* pathToPressedBmp){

    SDL_Surface *surfaceReleased = SDL_LoadBMP(pathToReleasedBmp);
    if(surfaceReleased==NULL) printf("Fichier %s non trouve\n", pathToReleasedBmp);
    else{
        self->imageReleased = SDL_CreateTextureFromSurface(self->parent->sdlRenderer, surfaceReleased);
        SDL_FreeSurface(surfaceReleased);
    }

    SDL_Surface *surfacePressed = SDL_LoadBMP(pathToPressedBmp);
    if(surfacePressed==NULL) printf("Fichier %s non trouve\n", pathToPressedBmp);
    else{
        self->imagePressed = SDL_CreateTextureFromSurface(self->parent->sdlRenderer, surfacePressed);
        SDL_FreeSurface(surfacePressed);
    }
}

void IHM_Button_draw(IHM_Button_t *self){
    if(self->state == 0){ 
        IHM_Window_drawFillRect(self->parent,
                            self->boundingRect.x,
                            self->boundingRect.y,
                            self->boundingRect.h,
                            self->boundingRect.w,
                            IHM_Window_couleur(100,255,100));
        IHM_Window_texte(self->parent,
                            self->boundingRect.x+1,
                            self->boundingRect.y+1,
                            self->caption,
                            0);
        if(self->imageReleased !=NULL){
            SDL_RenderCopy(self->parent->sdlRenderer, self->imageReleased, NULL, &self->boundingRect);
        }
    }
    else if(self->state != 0){ 
        IHM_Window_drawFillRect(self->parent,
                            self->boundingRect.x,
                            self->boundingRect.y,
                            self->boundingRect.h,
                            self->boundingRect.w,
                            IHM_Window_couleur(255,100,100));
        IHM_Window_texte(self->parent,
                            self->boundingRect.x+1,
                            self->boundingRect.y+1,
                            self->caption,
                            0);
        if(self->imagePressed !=NULL){
            SDL_RenderCopy(self->parent->sdlRenderer, self->imagePressed, NULL, &self->boundingRect);
        }
    }
}