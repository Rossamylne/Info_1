#include "IHM_Component.h"
//#include "IHM_Window.h"

void IHM_Component_init(IHM_Component_t *self, struct IHM_Window *parent, IHMComposantType_t type){
    self->type = type;
    self->parent = parent;
    self->onMouseButtonDown = NULL;
    self->onMouseButtonUp = NULL;
    self->gridPanel = NULL;
    self->drawPanel = NULL;
    self->bouton = NULL;
    self->textLabel =NULL;

    switch(self->type){
        case GRIDPANEL_T:
            self->gridPanel = (IHM_GridPanel_t*)malloc(sizeof(IHM_GridPanel_t));
            IHM_GridPanel_init(self->gridPanel, parent);
            break;
        case DRAWPANEL_T:
            self->drawPanel = (IHM_DrawPanel_t*)malloc(sizeof(IHM_DrawPanel_t));
            IHM_DrawPanel_init(self->drawPanel, parent);
            break;
        case BUTTON_T:
            self->bouton = (IHM_Button_t*)malloc(sizeof(IHM_Button_t));
            IHM_Button_init(self->bouton, parent);
            break;
        case TEXTLABEL_T:
            self->textLabel = (IHM_TextLabel_t*)malloc(sizeof(IHM_TextLabel_t));
            IHM_TextLabel_init(self->textLabel, parent);
            break;
    }
}

void IHM_Component_destroy(IHM_Component_t *self){
    switch(self->type){
        case GRIDPANEL_T:
            free(self->gridPanel);
            break;
        case DRAWPANEL_T:
            free(self->drawPanel);
            break;
        case BUTTON_T:
            free(self->bouton);
            break;
        case TEXTLABEL_T:
            free(self->textLabel);
            break;
    }
}

void IHM_Component_draw(IHM_Component_t *self){
    switch(self->type){
        case GRIDPANEL_T:
            IHM_GridPanel_draw(self->gridPanel);
            break;
        case DRAWPANEL_T:
            IHM_DrawPanel_draw(self->drawPanel);
            break;
        case BUTTON_T:
            IHM_Button_draw(self->bouton);
            break;
        case TEXTLABEL_T:
            IHM_TextLabel_draw(self->textLabel);
            break;
    }
}



void IHM_Component_setBoundaries(IHM_Component_t *self, int top, int left, int width, int height){
    if(left>=0) self->boundingRect.x = left;
    if(top>=0) self->boundingRect.y = top;
    if(width>=0) self->boundingRect.w = width;
    if(height>=0) self->boundingRect.h = height;
    switch(self->type){
        case GRIDPANEL_T:
            IHM_GridPanel_setBoundaries(self->gridPanel, top,left,width,height);
            break;
        case DRAWPANEL_T:
            IHM_DrawPanel_setBoundaries(self->drawPanel, top,left,width,height);
            break;
        case BUTTON_T:
            IHM_Button_setBoundaries(self->bouton, top,left,width,height);
            break;
        case TEXTLABEL_T:
            IHM_TextLabel_setBoundaries(self->textLabel, top,left,width,height);
            break;
    }
}

int IHM_Component_mouseDown(IHM_Component_t *self, int parentX, int parentY){
    
    //si le point appartient a ce composant on traite et retourne 0, sinon retourne -1
    if( parentX >= self->boundingRect.x && 
        parentX <= self->boundingRect.x+self->boundingRect.w &&
        parentY >= self->boundingRect.y && 
        parentY <= self->boundingRect.y+self->boundingRect.h){
        if(self->onMouseButtonDown != NULL) self->onMouseButtonDown(self, parentX-self->boundingRect.x, parentY-self->boundingRect.y);
        return 0;
    }
    return -1;

}

int IHM_Component_mouseUp(IHM_Component_t *self, int parentX, int parentY){
    
    //si le point appartient a ce composant on traite et retourne 0, sinon retourne -1
    if( parentX >= self->boundingRect.x && 
        parentX <= self->boundingRect.x+self->boundingRect.w &&
        parentY >= self->boundingRect.y && 
        parentY <= self->boundingRect.y+self->boundingRect.h){
        if(self->onMouseButtonUp != NULL) self->onMouseButtonUp(self, parentX-self->boundingRect.x, parentY-self->boundingRect.y);
        return 0;
    }
    return -1;

}