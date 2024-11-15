#ifndef IHM_SETUP_H_
#define IHM_SETUP_H_

#include "IHM_Application.h"
#include "IHM_Window.h"

typedef struct{
    IHM_Window_t *windowPtr;
    int windowWidth, windowHeight;
    int xClicked, yClicked;
    int xMouse, yMouse;
    int btnClicked;
    int clicked;
    char keyPressed;
} IHM_DataModel_t;



/**
 * @brief Initialise les objets de l'application graphique
 * @param application 
 * @param dataModel 
 * @param window 
 */
void IHM_Setup(IHM_Application_t* application, IHM_DataModel_t* dataModel, IHM_Window_t* window);

void onMainWindowClick(IHM_Window_t* window, int x, int y, int bouton);
void onMainWindowResize(IHM_Window_t* window, int width, int height);
void onMainWindowKeyPressed(struct IHM_Window *window, char caractere);
void onMainWindowMouseMove(struct IHM_Window *window, int x, int y);

/**
 * @brief remplit les paramètres donnés en argument avec la largeur et la hauteur courante
 * de la fenêtre de l'application.
 * @param width [S] pointeur vers la variable recevant la largeur.
 * @param height [S] pointeur vers la variable recevant la hauteur.
 */
void getWindowSize(int* width, int* height);

/**
 * @brief récupère la dernière touche pressée au clavier
 * @return renvoie le caractère de la touche pressée.
 * Renvoie le caractère nul ('\0' de valeur 0) si aucune touche n'a été pressée.
 */
char getKeyPressed();

/**
 * @brief Remplit les paramètres donnés en argument avec les dernières coordonnées 
 * connues de la souris dans l'espace de la fenêtre.
 * @param x [S] abscisse de la souris dans les coordonnées fenêtre.
 * @param y [S] ordonnée de la souris dans les coordonnées fenêtre.
 */
void getMousePosition(int* x, int* y);

/**
 * @brief Remplit les paramètres donnés en argument avec les coordonnées 
 * du dernier click de la souris dans l'espace de la fenêtre.
 * @param x [S] abscisse du click de souris dans les coordonnées fenêtre.
 * @param y [S] ordonnée du click de souris dans les coordonnées fenêtre.
 * @return renvoie le numéro du bouton de souris. Renvoie 0 si aucun click.
 */
int getMouseClick(int* x, int* y);

/**
 * @brief Dessine un rectangle vide.
 * @param x Abscisse du coin supérieur gauche.
 * @param y Ordonnée du coin supérieur gauche.
 * @param h Hauteur en pixels.
 * @param l Largeur en pixels
 * @param couleur Couleur du dessin.
 */
void dessineRectangle(int x, int y, int h, int l, unsigned long couleur);

/**
 * @brief Dessine un rectangle plein.
 * @param x Abscisse du coin supérieur gauche.
 * @param y Ordonnée du coin supérieur gauche.
 * @param h Hauteur en pixels.
 * @param l Largeur en pixels
 * @param couleur Couleur du dessin.
 */
void dessineRectanglePlein(int x, int y, int h, int l, unsigned long couleur);


/**
 * @brief Trace une ligne entre les points (x1,y1) et (x2,y2)
 * @param couleur Couleur du dessin.
 */
void dessineLigne(int x1, int y1, int x2, int y2, unsigned long couleur);

#endif //IHM_SETUP_H_