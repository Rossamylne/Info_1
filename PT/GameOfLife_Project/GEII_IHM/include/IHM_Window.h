#ifndef IHM_WINDOW_H
#define IHM_WINDOW_H

#include "SDL_ttf.h"
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <freetype2/ft2build.h>
#include "IHM_Component.h"

// type pour les couleurs
typedef struct
{
    unsigned char R;
    unsigned char V;
    unsigned char B;
    unsigned char A;
} TYPE_IHM_RVB;

typedef union
{
    TYPE_IHM_RVB rvb;
    unsigned long int val;
} TYPE_IHM_COUL;

/**
 * @brief énumération des zones de placement des composants.
 */
typedef enum {WINDOW_TOP, WINDOW_CENTER, WINDOW_BOTTOM} windowZone_t;
/**
 * @brief Enumération des alignements des composants dans les zones haut ou bas.
 */
typedef enum {ZONEALIGN_LEFT, ZONEALIGN_RIGHT} windowZoneAlign_t;

typedef struct IHM_Window_listeComposants{
    IHM_Component_t* composant;
    windowZone_t zone;
    windowZoneAlign_t align;
    struct IHM_Window_listeComposants *suivant;
}IHM_Window_listeComposants_t;

// Fenetre d'application
typedef struct IHM_Window
{
    char title[50];

    struct IHM_Window *self;
    Uint32 windowID;
    int width,height;
    int borderWidth;
    int topLayoutHeight;
    int bottomLayoutHeight;
    int visible;

    SDL_Window *sdlWindow;
    SDL_Renderer *sdlRenderer;
    TTF_Font *activeFont;

    IHM_Window_listeComposants_t *listeComposants;

    // gestion des evenements

    //Callbacks
    void (*onMouseMove)(struct IHM_Window *window, int x, int y);
    void (*onMouseButtonDown)(struct IHM_Window *window, int x, int y, int bouton);
    void (*onMouseButtonUp)(struct IHM_Window *window, int x, int y, int bouton);
    void (*onKeyPressed)(struct IHM_Window *window, char caractere);
    void (*onClose)(struct IHM_Window *window);
    void (*onResize)(struct IHM_Window *window, int width, int height);

} IHM_Window_t;

/**
 * @brief Initialise la structure IHM_Window_t
 * @param self Pointeur d'autoréférence sur la structure de fenêtre à initialiser.
 * @param width Largeur initiale de la fenêtre.
 * @param height Hauteur initiale de la fenêtre.
 * @param visible Booléen déterminant l'état visible ou caché initial de la fenêtre.
 */
void IHM_Window_init(IHM_Window_t *self, int width, int height, int visible);

/**
 * @brief Fixe la position de la fenêtre dans les coordonnées écran
 * @param self Pointeur d'autoréférence sur la structure de fenêtre.
 * @param top Ordonnée du coin supérieur gauche de la fenêtre.
 * @param left Abscisse du coin supérieur gauche de la fenêtre.
 */
void IHM_Window_setPosition(IHM_Window_t *self, int top, int left);

/**
 * @brief Détermine les dimensions des zones d'agencement de composants graphiques dans la fenêtre.
 * Une fenêtre possède 3 zones d'agencement pour déposer des composants graphiques:
 * Zones WINDOW_TOP ou WINDOW_BOTTOM : bandeau supérieur pouvant contenir plusieurs composants,
 * eux même pouvant s'aligner à gauche ou à droite dans cette zone.
 * Zone WINDOW_CENTER : partie centrale pouvant contenir un seul composant remplissant cet espace.
 * @param self Pointeur d'autoréférence sur la structure de fenêtre concernée.
 * @param topHeight Hauteur en pixels de la zone WINDOW_TOP;
 * @param bottomHeight Hauteur en pixels de la zone WINDOW_BOTTOM;
 */
void IHM_Window_setLayout(IHM_Window_t *self, int topHeight, int bottomHeight);

/**
 * @brief Donne un titre à la fenêtre
 * @param self Pointeur d'autoréférence sur la structure de fenêtre concernée.
 * @param titre chaine de caractère contenant le titre à donner.
 */
void IHM_Window_setTitle(IHM_Window_t *self, char* titre);

/**
 * @brief Met en avant et donne le focus pointeur à la fenêtre.
 * @param self Pointeur d'autoréférence sur la structure de fenêtre à mettre en avant.
 */
void IHM_Window_setFocus(IHM_Window_t *self);

/**
 * @brief Masque ou montre la fenêtre
 * @param self Pointeur d'autoréférence sur la structure de fenêtre concernée.
 * @param visible Entier booléen déterminant si la fenêtre doit être montrée ou masquée
 */
void IHM_Window_setVisible(IHM_Window_t *self, int visible);

/**
 * @brief Destructeur de la fenêtre.
 * Doit obligatoirement être invoqué lorsque la fenêtre doit cesser d'exister.
 * Responsable de la libération des variables internes allouées dynamiquement en mémoire.
 * @param self Pointeur d'autoréférence sur la structure de fenêtre concernée.
 */
void IHM_Window_destroy(IHM_Window_t *self);


/**
 * @brief Ajoute un composant graphique à la fenêtre.
 * @param self Pointeur d'autoréférence sur la structure de fenêtre concernée.
 * @param composant Pointeur vers la structure de composant à ajouter.
 * @param zone Zone d'agencement où le composant doit être placé.
 * Choix entre haut, centre et bas (voir énumération windowZone_t).
 * @param align alignement dans la zone choisie. Gauche ou droite (voir énulération windowZoneAlign_t).
 * sans effet dans la zone centrale.
 */
void IHM_Window_addComponent(IHM_Window_t *self, IHM_Component_t* composant, windowZone_t zone, windowZoneAlign_t align);

/**
 * @brief Efface la fenêtre
 * @param self Pointeur d'autoréférence sur la structure de fenêtre concernée.
 */
void IHM_Window_clear(IHM_Window_t *self);

/**
 * @brief Dessine le contenu de la fenêtre la fenêtre
 * Parcours la liste de tous les composants graphiques et force leur dessin.
 * @param self Pointeur d'autoréférence sur la structure de fenêtre concernée.
 */
void IHM_Window_draw(IHM_Window_t *self);

/**
 * @brief Fonction exécutée automatiquement lorsqu'un appui de bouton de souris est détecté dans la fenêtre.
 * @param self Pointeur d'autoréférence sur la structure de fenêtre concernée.
 * @param x Abscisse du click relative au coin supérieur gauche de la surface interne de la fenêtre.
 * @param y Ordonnée du click relative au coin supérieur gauche de la surface interne de la fenêtre.
 * @param bouton numéro de bouton de la souris qui a été cliqué.
 */
void IHM_Window_mouseButtonDown(IHM_Window_t* self, int x, int y, int bouton);

/**
 * @brief Fonction exécutée automatiquement lorsqu'un appui de bouton de souris est détecté dans la fenêtre.
 * @param self Pointeur d'autoréférence sur la structure de fenêtre concernée.
 * @param x Abscisse du click relative au coin supérieur gauche de la surface interne de la fenêtre.
 * @param y Ordonnée du click relative au coin supérieur gauche de la surface interne de la fenêtre.
 * @param bouton numéro de bouton de la souris qui a été cliqué.
 */
void IHM_Window_mouseButtonUp(IHM_Window_t* self, int x, int y, int bouton);

/**
 * @brief Fonction exécutée automatiquement lorsque la fenêtre est redimensionnée.
 * @param self Pointeur d'autoréférence sur la structure de fenêtre concernée.
 * @param width Nouvelle largeur de la fenêtre.
 * @param height Nouvelle hauteur de la fenêtre.
 */
void IHM_Window_resized(IHM_Window_t* self, int width, int height);


/**
 * @brief Convertit une couleur R V B (entre 0 et 255) en entier non signé
 *
 * @param R Composante rouge de 0 à 255
 * @param V Composante verte de 0 à 255
 * @param B Composante bleue de 0 à 255
 * @return unsigned long int Couleur RVB sur 32 bits
 */
unsigned long int IHM_Window_couleur(unsigned char R, unsigned char V, unsigned char B);

/**
 * @brief Dessine un pixel à la position (x,y) de la couleur donnée
 *
 * @param self Pointeur d'autoréférence sur la structure de fenêtre concernée.
 * @param x Abscisse (axe orienté de gauche à droite)
 * @param y Ordonnée (axe orienté du haut vers le bas)
 * @param couleur Couleur au format RVB sur 32 bits
 */
void IHM_Window_drawPoint(IHM_Window_t *self, int x, int y, unsigned long int couleur);

/**
 * @brief Dessine un rectangle de HxL pixels dont le coin en haut à gauche est en (x,y) de la couleur donnée
 *
 * @param self Pointeur d'autoréférence sur la structure de fenêtre concernée.
 * @param x Abscisse du coin supérieur gauche
 * @param y Ordonnée du coin supérieur gauche
 * @param H Hauteur du rectangle
 * @param L Largeur du rectangle
 * @param Couleur couleur du rectangle au format RVB 32 bits
 */
void IHM_Window_drawRect(IHM_Window_t *self, int x, int y, int H, int L, unsigned long int couleur);

/**
 * @brief Dessine un rectangle plein de HxL pixels dont le coin en haut à gauche est en (x,y) de la couleur donnée
 *
 * @param self Pointeur d'autoréférence sur la structure de fenêtre concernée.
 * @param x Abscisse du coin supérieur gauche
 * @param y Ordonnée du coin supérieur gauche
 * @param H Hauteur du rectangle
 * @param L Largeur du rectangle
 * @param Couleur couleur du rectangle au format RVB 32 bits
 */
void IHM_Window_drawFillRect(IHM_Window_t *self, int x, int y, int H, int L, unsigned long int couleur);

/**
 * @brief Dessine une ligne entre (x1,y1) et (x2,y2)
 *
 * @param self Pointeur d'autoréférence sur la structure de fenêtre concernée.
 * @param x1 Abscisse du premier point
 * @param y1 Ordonnée du premier point
 * @param x2 Abscisse du second point
 * @param y2 Ordonnée du second point
 * @param Couleur couleur de ligne au format RVB 32 bits
 */
void IHM_Window_drawLine(IHM_Window_t *self, int x1, int y1, int x2, int y2, unsigned long int couleur);


/**
 * @brief Renvoie le dernier caractère tapé au clavier
 *
 * @return char Caractère saisi
 */
char IHM_Window_getChar();

/**
 * @brief Renvoie la position x courante de la souris
 *
 * @return int Position x de la souris
 */
int IHM_Window_souris_x();

/**
 * @brief Renvoie la position y courante de la souris
 *
 * @return int Position y de la souris
 */
int IHM_Window_souris_y();

/**
 * @brief Renvoie vrai si le bouton gauche de la souris a été cliqué
 *
 * @return char Etat du bouton gauche de la souris
 */
char IHM_Window_souris_boutonG();


/**
 * @brief Dessine du texte
 * @param self Pointeur d'autoréférence sur la structure de fenêtre concernée.
 * @param x Abcisse du coin supérieur gauche du rectangle contenant le texte.
 * @param y Ordonnée du coin supérieur gauche du rectangle contenant le texte.
 * @param string Texte à dessiner.
 * @param couleur Couleur du texte.
 */
void IHM_Window_texte(IHM_Window_t *self, int x, int y, char *string, unsigned long int couleur);

#endif