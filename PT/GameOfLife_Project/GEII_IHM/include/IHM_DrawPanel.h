#ifndef IHM_DRAWPANEL_H
#define IHM_DRAWPANEL_H

#include <SDL2/SDL.h>

struct IHM_Window;

typedef enum{POINT_T, LINE_T, RECT_T, FILLRECT_T, TEXT_T} IHM_DrawPanel_typeFigure_t;

typedef SDL_Point IHM_DrawPanel_point;

typedef struct{
    IHM_DrawPanel_point p1, p2;
} IHM_DrawPanel_line;

typedef SDL_Rect IHM_DrawPanel_rect;

typedef struct{
    char string[50];
    SDL_Point coords;
} IHM_DrawPanel_text;

typedef struct IHM_DrawPanel_listeFigures{
    IHM_DrawPanel_typeFigure_t type;
    IHM_DrawPanel_point point;
    IHM_DrawPanel_line line;
    IHM_DrawPanel_rect rect;
    IHM_DrawPanel_text text;
    unsigned long int couleur;

    struct IHM_DrawPanel_listeFigures *next;
}IHM_DrawPanel_listeFigures_t;

typedef struct IHM_DrawPanel_listeFigures IHM_DrawPanel_figure_t;

typedef struct {
    SDL_Rect boundingRect;
    float xScale,yScale;
    int maxX, maxY;
    int scalable;
    int reverseY;

    IHM_DrawPanel_listeFigures_t *listeFigures;

    SDL_Texture *texture;
    struct IHM_Window *parent;

} IHM_DrawPanel_t;

/**
 * @brief Initialise le panneau de dessin
 * @param self Pointeur d'auto-référence vers le panneau.
 * @param parent Pointeur vers la fenêtre mêre.
 */
void IHM_DrawPanel_init(IHM_DrawPanel_t *self, struct IHM_Window *parent);

/**
 * @brief Détruit le panneau en libérant la mémoire allouée
 * @param self Pointeur d'auto-référence vers le panneau.
 */
void IHM_DrawPanel_destroy(IHM_DrawPanel_t *self);

/**
 * @brief Fixe dimesions et position du panneau dans sa fenêtre mère.
 * @param self Pointeur d'auto-référence vers le panneau.
 * @param top Ordonnée du coin supérieur gauche du composant dans le système de coordonnées 
 * de sa fenêtre mère
 * @param left Abcisse du coin supérieur gauche du composant dans le système de coordonnées 
 * de sa fenêtre mère
 * @param width Largeur du composant.
 * @param height Hauteur du composant.
 */
void IHM_DrawPanel_setBoundaries(IHM_DrawPanel_t *self, int top, int left, int width, int height);

/**
 * @brief Si le point (x,y) est en dehors de l'espace de représentation du panneau,
 * les facteur d'échelle de largeur et hauteur sont recalculés.
 * @param self Pointeur d'auto-référence vers le panneau.
 * @param x Abcisse du point de référence.
 * @param y Ordonnée du point de référence.
 */
void IHM_DrawPanel_scale(IHM_DrawPanel_t *self, int x, int y);

/**
 * @brief Ajoute un point de coordonnées (x1,y1) dans la liste des figures à dessiner.
 * @param self Pointeur d'auto-référence vers le panneau.
 * @param couleur Couleur désirée pour le point.
 */
void IHM_DrawPanel_addPoint(IHM_DrawPanel_t *self, int x1, int y1, unsigned long int couleur);

/**
 * @brief Ajoute une ligne entre les points (x1,y1) et (x2,y2) dans la liste des figures à dessiner.
 * @param self Pointeur d'auto-référence vers le panneau.
 * @param couleur Couleur désirée pour la ligne.
 */
void IHM_DrawPanel_addLine(IHM_DrawPanel_t *self, int x1, int y1, int x2, int y2, unsigned long int couleur);

void IHM_DrawPanel_addRect(IHM_DrawPanel_t *self, int top, int left, int width, int height, unsigned long int couleur);

void IHM_DrawPanel_addFilledRect(IHM_DrawPanel_t *self, int top, int left, int width, int height, unsigned long int couleur);

void IHM_DrawPanel_addText(IHM_DrawPanel_t *self, int x, int y, char* text, unsigned long int couleur);

void IHM_DrawPanel_clear(IHM_DrawPanel_t *self);

void IHM_DrawPanel_draw(IHM_DrawPanel_t *self);

#endif //IHM_DRAWPANEL_H