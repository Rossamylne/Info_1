#ifndef IHM_TEXTLABEL_H_
#define IHM_TEXTLABEL_H_

#include <SDL2/SDL.h>

struct IHM_Window;


typedef struct IHM_TextLabel{
    SDL_Rect boundingRect;


    struct IHM_Window *parent;

    char *text;

    void (*onClick)(struct IHM_TextLabel *self);
} IHM_TextLabel_t;

void IHM_TextLabel_init(IHM_TextLabel_t *self, struct IHM_Window *parent);

void IHM_TextLabel_destroy(IHM_TextLabel_t *self);

void IHM_TextLabel_setBoundaries(IHM_TextLabel_t *self, int top, int left, int width, int height);

void IHM_TextLabel_setText(IHM_TextLabel_t *self, char* text);

void IHM_TextLabel_draw(IHM_TextLabel_t *self);

#endif //IHM_TEXTLABEL_H_