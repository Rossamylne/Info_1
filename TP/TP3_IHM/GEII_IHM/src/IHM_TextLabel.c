#include "IHM_TextLabel.h"
#include "IHM_Window.h"

void IHM_TextLabel_init(IHM_TextLabel_t *self, struct IHM_Window *parent){
    self->parent = parent;
    self->text = NULL;
    self->onClick = NULL;
    IHM_TextLabel_setText(self, "Text"); //default text;
}

void IHM_TextLabel_destroy(IHM_TextLabel_t *self){
    free(self->text);
}

void IHM_TextLabel_setBoundaries(IHM_TextLabel_t *self, int top, int left, int width, int height){
    if(left>=0) self->boundingRect.x = left;
    if(top>=0) self->boundingRect.y = top;
    if(width>=0) self->boundingRect.w = width;
    if(height>=0) self->boundingRect.h = height;
}

void IHM_TextLabel_setText(IHM_TextLabel_t *self, char* text){
    if(self->text != NULL)  free(self->text);   
    self->text = (char*)malloc((strlen(text)+1)*sizeof(char));
    strcpy(self->text, text);
}

void IHM_TextLabel_draw(IHM_TextLabel_t *self){
    IHM_Window_texte(self->parent,self->boundingRect.x,self->boundingRect.y,self->text,0);
}