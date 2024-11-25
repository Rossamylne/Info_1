#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include "IHM_Application.h"

void IHM_Application_init(IHM_Application_t *self){
    self->nbFenetres = 0;
    self->quitter = 0;
    self->listeFenetres = NULL;
    self->mainWindowID = 0;
}

void IHM_Application_destroy(IHM_Application_t *self){
    //detruire chaque fenetre
    IHM_Application_listeFenetres_t *tmpPtr = self->listeFenetres;
    IHM_Application_listeFenetres_t *tmpPrec;
    while(tmpPtr != NULL){
        IHM_Window_destroy(tmpPtr->fenetre);
        tmpPrec = tmpPtr;
        tmpPtr = tmpPtr->suivante;
        free(tmpPrec);
    }

}

void IHM_Application_addWindow(IHM_Application_t *self, IHM_Window_t* fenetre){
    IHM_Application_listeFenetres_t *nouvelle = (IHM_Application_listeFenetres_t*)malloc(sizeof(IHM_Application_listeFenetres_t));
    nouvelle->fenetre = fenetre;
    nouvelle->ID = SDL_GetWindowID(fenetre->sdlWindow);
    nouvelle->suivante = NULL;
    IHM_Application_listeFenetres_t *tmpPtr = self->listeFenetres;
    if(tmpPtr == NULL) self->listeFenetres = nouvelle;
    else{
        while(tmpPtr->suivante != NULL) tmpPtr = tmpPtr->suivante;
        tmpPtr->suivante = nouvelle;
    }
    self->nbFenetres++;
    printf("IHM Application nbFenetres=%d\n", self->nbFenetres);
}

void IHM_Application_removeWindow(IHM_Application_t *self, IHM_Window_t* fenetre){
    IHM_Application_listeFenetres_t *tmpPtr = self->listeFenetres->suivante;
    IHM_Application_listeFenetres_t *tmpPtrPrec = self->listeFenetres;
    if(self->listeFenetres->fenetre == fenetre){
        self->listeFenetres = self->listeFenetres->suivante;
        free(tmpPtrPrec);
        
    }
    else{
        while(tmpPtr->fenetre != fenetre){
            tmpPtrPrec = tmpPtr;
            tmpPtr = tmpPtr->suivante;
        }
        tmpPtrPrec->suivante = NULL;
        free(tmpPtr);
    }
    self->nbFenetres--;
        printf("IHM Application nbFenetres=%d\n", self->nbFenetres);

}

void IHM_Application_setWindowAsMain(IHM_Application_t *self, IHM_Window_t* fenetre){
    self->mainWindowID = fenetre->windowID;
}

void IHM_Application_clearWindows(IHM_Application_t *self){
    IHM_Application_listeFenetres_t *tmpPtr = self->listeFenetres;

    while(tmpPtr!=NULL){
        IHM_Window_clear(tmpPtr->fenetre);
        tmpPtr = tmpPtr->suivante;
    }
}

void IHM_Application_drawWindows(IHM_Application_t *self){
    IHM_Application_listeFenetres_t *tmpPtr = self->listeFenetres;

    while(tmpPtr!=NULL){
        IHM_Window_draw(tmpPtr->fenetre);
        tmpPtr = tmpPtr->suivante;
    }
}

IHM_Window_t* IHM_Application_fenetreParID(IHM_Application_t *self, Uint32 ID){
    IHM_Application_listeFenetres_t *tmpPtr = self->listeFenetres;

    while(tmpPtr!=NULL)
        if(tmpPtr->ID == ID) return tmpPtr->fenetre;
        else tmpPtr = tmpPtr->suivante;
    return NULL;
}

void IHM_Application_processEvent(IHM_Application_t *self){
    // message processing loop
    SDL_Event event;
    IHM_Window_t* window;
    while (SDL_PollEvent(&event))
    {
        // check for messages
        switch (event.type)
        {
        //window events
        case SDL_WINDOWEVENT:
            window = IHM_Application_fenetreParID(self, event.window.windowID);
            if(event.window.event == SDL_WINDOWEVENT_RESIZED){  
                IHM_Window_resized(window, event.window.data1, event.window.data2);
            }
            if(event.window.event == SDL_WINDOWEVENT_CLOSE){  
                if(window->onClose != NULL) window->onClose(window);
                if(window->windowID == self->mainWindowID) {
                    self->quitter = 1;
                    IHM_Application_removeWindow(self, window);
                    IHM_Window_destroy(window);
                }
                else{
                    
                }
                //if(self->nbFenetres == 0) self->quitter = 1; 
            }
            break;

        // check for keypresses
        case SDL_KEYDOWN:
        {
            window = IHM_Application_fenetreParID(self, event.key.windowID);
            // exit if ESCAPE is pressed
            if (event.key.keysym.sym == SDLK_ESCAPE){
                self->quitter = 1;
            }
            else if (event.key.keysym.sym > SDLK_SPACE && event.key.keysym.sym <= SDLK_z)
            {
                if(window->onKeyPressed != NULL) window->onKeyPressed(window, event.key.keysym.sym);
            }
            break;
        }

        case SDL_MOUSEMOTION:
        {
            window = IHM_Application_fenetreParID(self, event.motion.windowID);
            if(window->onMouseMove != NULL) window->onMouseMove(window, event.motion.x, event.motion.y);
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            window = IHM_Application_fenetreParID(self, event.button.windowID);
            IHM_Window_mouseButtonDown(window ,event.button.x,event.button.y,event.button.button);
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            window = IHM_Application_fenetreParID(self, event.button.windowID);
            IHM_Window_mouseButtonUp(window ,event.button.x,event.button.y,event.button.button);
            break;
        }
        } // end switch
    }     // end of message processing
}