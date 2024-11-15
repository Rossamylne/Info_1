#ifndef IHM_BUTTON_H_
#define IHM_BUTTON_H_

#include <SDL2/SDL.h>

struct IHM_Window;


typedef struct IHM_Button{
    char* caption;
    int state;
    SDL_Rect boundingRect;


    struct IHM_Window *parent;

    SDL_Texture *imagePressed;
    SDL_Texture *imageReleased;

    void (*onClick)(struct IHM_Button *self);
} IHM_Button_t;

void IHM_Button_init(IHM_Button_t *self, struct IHM_Window *parent);

void IHM_Button_destroy(IHM_Button_t *self);

void IHM_Button_setBoundaries(IHM_Button_t *self, int top, int left, int width, int height);

void IHM_Button_setCaption(IHM_Button_t *self, char *caption);

void IHM_Button_setImages(IHM_Button_t *self, char* pathToReleasedBmp, char* pathToPressedBmp);

void IHM_Button_draw(IHM_Button_t *self);

#endif //IHM_BUTTON_H_