#include "IHM_Window.h"

/**
 * @brief Initialise la fenêtre
 *
 */
void IHM_Window_init(IHM_Window_t *self, int width, int height, int visible)
{
    self->self = self;
    self->width = width;
    self->height = height;
    self->borderWidth = 5;
    self->topLayoutHeight = 0;
    self->bottomLayoutHeight = 0;
    self->visible = visible;

    // init des callbacks
    self->onClick = NULL;
    self->onKeyPressed = NULL;
    self->onResize = NULL;
    self->onMouseMove = NULL;
    self->onClose = NULL;

    // self->nbComposants=0;
    self->listeComposants = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        // std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
        // return -1;
    }

    SDL_CreateWindowAndRenderer(width, height, (visible ? SDL_WINDOW_SHOWN : SDL_WINDOW_HIDDEN) | SDL_WINDOW_RESIZABLE,
                                &(self->sdlWindow), &(self->sdlRenderer));

    self->windowID = SDL_GetWindowID(self->sdlWindow);

    IHM_Window_clear(self);

    if (TTF_Init() != 0)
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "TTF init error", TTF_GetError(), self->sdlWindow);
    else
    {
        self->activeFont = TTF_OpenFont("build/clacon2.ttf", 10);
        if (self->activeFont == NULL)
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Font Open error at init", TTF_GetError(), self->sdlWindow);
    }
}

void IHM_Window_setPosition(IHM_Window_t *self, int top, int left)
{
    SDL_SetWindowPosition(self->sdlWindow, left, top);
}

void IHM_Window_setLayout(IHM_Window_t *self, int topHeight, int bottomHeight)
{
    /*     self->leftLayoutWidth = leftWidth;
        self->rightLayoutWidth = rightWidth; */
    self->topLayoutHeight = topHeight;
    self->bottomLayoutHeight = bottomHeight;
    /*     self->centerLayoutWidth = self->width - 2*self->borderWidth - self->leftLayoutWidth - self->rightLayoutWidth;
        self->centerLayoutHeight = self->height - 2*self->borderWidth - self->topLayoutHeight - self->bottomLayoutHeight; */
}

void IHM_Window_setTitle(IHM_Window_t *self, char *titre)
{
    strcpy(self->title, titre);
    SDL_SetWindowTitle(self->sdlWindow, titre);
}

void IHM_Window_setFocus(IHM_Window_t *self)
{
    SDL_SetWindowInputFocus(self->sdlWindow);
}

void IHM_Window_setVisible(IHM_Window_t *self, int visible)
{
    self->visible = visible;
    if (visible)
        SDL_ShowWindow(self->sdlWindow);
    else
        SDL_HideWindow(self->sdlWindow);
}

void IHM_Window_destroy(IHM_Window_t *self)
{

    // detruit les composants
    /*     for(int i=0; i<self->nbComposants; i++)
            IHM_Component_destroy(self->tabComposants[i]); */
    IHM_Window_listeComposants_t *tmpPtr = self->listeComposants;
    IHM_Window_listeComposants_t *tmpPrec;
    while (tmpPtr != NULL)
    {
        IHM_Component_destroy(tmpPtr->composant);
        tmpPrec = tmpPtr;
        tmpPtr = tmpPtr->suivant;
        free(tmpPrec);
    }
    // libere les pointeurs de fenêtre
    SDL_DestroyRenderer(self->sdlRenderer);
    SDL_DestroyWindow(self->sdlWindow);

    TTF_CloseFont(self->activeFont);
}

void IHM_Window_addComponent(IHM_Window_t *self, IHM_Component_t *composant, windowZone_t zone, windowZoneAlign_t align)
{
    /*     self->tabComposants[self->nbComposants] = composant;
        self->nbComposants++; */

    IHM_Window_listeComposants_t *nouveau = (IHM_Window_listeComposants_t *)malloc(sizeof(IHM_Window_listeComposants_t));
    nouveau->composant = composant;
    nouveau->zone = zone;
    nouveau->align = align;
    nouveau->suivant = NULL;
    IHM_Window_listeComposants_t *tmpPtr = self->listeComposants;
    if (tmpPtr == NULL)
        self->listeComposants = nouveau;
    else
    {
        while (tmpPtr->suivant != NULL)
            tmpPtr = tmpPtr->suivant;
        tmpPtr->suivant = nouveau;
    }
}

/**
 * @brief Efface la fenêtre
 *
 */
void IHM_Window_clear(IHM_Window_t *self)
{
    SDL_SetRenderDrawColor(self->sdlRenderer, 100, 100, 100, 255);
    SDL_RenderClear(self->sdlRenderer);
}

void IHM_Window_clicked(IHM_Window_t *self, int x, int y, int bouton)
{
    // On parcourt les composants pour chercher celui qui est cliqué
    IHM_Window_listeComposants_t *tmpPtr = self->listeComposants;
    while (tmpPtr != NULL)
    {
        if (!IHM_Component_click(tmpPtr->composant, x, y))
            break;
        tmpPtr = tmpPtr->suivant;
    }
    if (self->onClick != NULL)
        self->onClick(self, x, y, bouton);
}

void IHM_Window_resized(IHM_Window_t *self, int width, int height)
{
    int minimumWidth=self->borderWidth;

    //Taille minimale pour les composants TOP
    IHM_Window_listeComposants_t *tmpPtr = self->listeComposants;
    while(tmpPtr!=NULL) 
    {
        if(tmpPtr->zone == WINDOW_TOP){
            minimumWidth += tmpPtr->composant->boundingRect.w + self->borderWidth;
        }
        tmpPtr = tmpPtr->suivant;
    }

    self->width = (width>=minimumWidth) ? width : minimumWidth;
    self->height = height;

    if(width<minimumWidth) {
        SDL_SetWindowSize(self->sdlWindow,self->width,self->height);
    }

    if (self->onResize != NULL)
        self->onResize(self, width, height);
}

void IHM_Window_draw(IHM_Window_t *self)
{
    /*     for(int i=0; i<self->nbComposants; i++)
            IHM_Component_draw(self->tabComposants[i]); */

    IHM_Window_listeComposants_t *tmpPtr = self->listeComposants;
    int topLeftMargin = self->borderWidth; // pour placer les composants alignes a gauche
    int topRightMargin = self->borderWidth;// pour placer les composants alignes a droite
    int bottomLeftMargin = self->borderWidth; // pour placer les composants alignes a gauche
    int bottomRightMargin = self->borderWidth;// pour placer les composants alignes a droite

    while (tmpPtr != NULL)
    {
        if (tmpPtr->zone == WINDOW_CENTER)
        {
            // redimensionnement du composant central
            IHM_Component_setBoundaries(tmpPtr->composant,
                                        self->topLayoutHeight + self->borderWidth,
                                        self->borderWidth,
                                        self->width - 2 * self->borderWidth,
                                        self->height - self->topLayoutHeight - self->bottomLayoutHeight - 2 * self->borderWidth);
            IHM_Component_draw(tmpPtr->composant);
        }
        else if (tmpPtr->zone == WINDOW_TOP)
        {
            if (tmpPtr->align == ZONEALIGN_LEFT)
            {
                IHM_Component_setBoundaries(tmpPtr->composant,
                                            self->borderWidth, topLeftMargin, -1, -1);
                topLeftMargin += tmpPtr->composant->boundingRect.w + self->borderWidth;
                IHM_Component_draw(tmpPtr->composant);
            }
            else if (tmpPtr->align == ZONEALIGN_RIGHT){
                IHM_Component_setBoundaries(tmpPtr->composant,
                                            self->borderWidth, 
                                            self->width - self->borderWidth - tmpPtr->composant->boundingRect.w,
                                            -1, -1);
                topRightMargin -= (tmpPtr->composant->boundingRect.w + self->borderWidth);
                IHM_Component_draw(tmpPtr->composant);
            }
        }
        else if (tmpPtr->zone == WINDOW_BOTTOM)
        {
            if (tmpPtr->align == ZONEALIGN_LEFT)
            {
                IHM_Component_setBoundaries(tmpPtr->composant,
                                            self->height - self->bottomLayoutHeight, bottomLeftMargin, -1, -1);
                bottomLeftMargin += tmpPtr->composant->boundingRect.w + self->borderWidth;
                IHM_Component_draw(tmpPtr->composant);
            }
            else if (tmpPtr->align == ZONEALIGN_RIGHT){
                IHM_Component_setBoundaries(tmpPtr->composant,
                                            self->height - self->bottomLayoutHeight, 
                                            self->width - self->borderWidth - tmpPtr->composant->boundingRect.w,
                                            -1, -1);
                bottomRightMargin -= (tmpPtr->composant->boundingRect.w + self->borderWidth);
                IHM_Component_draw(tmpPtr->composant);
            }
        }
        tmpPtr = tmpPtr->suivant;
    }

    // on affiche tout ce qui a �t� dessin�
    SDL_RenderPresent(self->sdlRenderer);
}

unsigned long int IHM_Window_couleur(unsigned char R, unsigned char V, unsigned char B)
{
    TYPE_IHM_COUL coul;
    coul.rvb.R = R;
    coul.rvb.V = V;
    coul.rvb.B = B;
    coul.rvb.A = 255;
    return coul.val;
}

void IHM_Window_drawPoint(IHM_Window_t *self, int x, int y, unsigned long int couleur)
{
    TYPE_IHM_COUL coul;
    coul.val = couleur;
    SDL_SetRenderDrawColor(self->sdlRenderer, coul.rvb.R, coul.rvb.V, coul.rvb.B, coul.rvb.A);
    SDL_Rect rectangle;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = 1;
    rectangle.h = 1;
    SDL_RenderFillRect(self->sdlRenderer, &rectangle);
}

void IHM_Window_drawRect(IHM_Window_t *self, int x, int y, int H, int L, unsigned long int couleur)
{
    TYPE_IHM_COUL coul;
    coul.val = couleur;
    SDL_SetRenderDrawColor(self->sdlRenderer, coul.rvb.R, coul.rvb.V, coul.rvb.B, coul.rvb.A);
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.h = H;
    rect.w = L;
    SDL_RenderDrawRect(self->sdlRenderer, &rect);
}

void IHM_Window_drawFillRect(IHM_Window_t *self, int x, int y, int H, int L, unsigned long int couleur)
{
    TYPE_IHM_COUL coul;
    coul.val = couleur;
    SDL_SetRenderDrawColor(self->sdlRenderer, coul.rvb.R, coul.rvb.V, coul.rvb.B, coul.rvb.A);
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.h = H;
    rect.w = L;
    SDL_RenderFillRect(self->sdlRenderer, &rect);
}

void IHM_Window_drawLine(IHM_Window_t *self, int x1, int y1, int x2, int y2, unsigned long int couleur)
{
    TYPE_IHM_COUL coul;
    coul.val = couleur;
    SDL_SetRenderDrawColor(self->sdlRenderer, coul.rvb.R, coul.rvb.V, coul.rvb.B, coul.rvb.A);
    SDL_RenderDrawLine(self->sdlRenderer, x1, y1, x2, y2);
}

void IHM_Window_texte(IHM_Window_t *self, int x, int y, char *string, unsigned long int couleur)
{
    SDL_Color color = {0, 0, 0};
    // SDL_GetRGBA(couleur, SDL_PIXELFORMAT_RGBA8888, &(color.r), &(color.g), &(color.b), &(color.a));

    SDL_Surface *surfaceMessage = TTF_RenderUTF8_Blended(self->activeFont, string, color);
    SDL_Texture *Message = SDL_CreateTextureFromSurface(self->sdlRenderer, surfaceMessage);

    int textureW, textureH;
    SDL_QueryTexture(Message, NULL, NULL, &textureW, &textureH);

    SDL_Rect Message_rect;     // create a rect
    Message_rect.x = x;        // controls the rect's x coordinate
    Message_rect.y = y;        // controls the rect's y coordinate
    Message_rect.w = textureW; // controls the width of the rect
    Message_rect.h = textureH; // controls the height of the rect

    SDL_RenderCopy(self->sdlRenderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}