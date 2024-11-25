#ifndef IHM_SETUP_H_
#define IHM_SETUP_H_


#include "IHM_Application.h"
#include "IHM_Window.h"
#include "IHM_Component.h"

typedef struct{
    IHM_Window_t *windowPtr;
    IHM_Component_t *textLabelGenerationsPtr;
    int windowWidth, windowHeight;
    int xClicked, yClicked;
    int xMouse, yMouse;
    int btnClicked;
    int clicked;
    int mouseState;
    char keyPressed;
    int btnPlayState;
    int btnResetClicked;
    int btnClearClicked;
} IHM_DataModel_t;



/**
 * @brief Initialise les objets de l'application graphique
 * @param application 
 * @param dataModel 
 * @param window 
 */
void IHM_Setup(IHM_Application_t* application, IHM_DataModel_t* dataModel, IHM_Window_t* window);

void onMainWindowMouseDown(IHM_Window_t* window, int x, int y, int bouton);
void onMainWindowMouseUp(IHM_Window_t* window, int x, int y, int bouton);
void onMainWindowResize(IHM_Window_t* window, int width, int height);
void onMainWindowKeyPressed(struct IHM_Window *window, char caractere);
void onMainWindowMouseMove(struct IHM_Window *window, int x, int y);
void onBoutonPlayMouseDown(IHM_Component_t *self, int localX, int localY);
void onBoutonResetMouseDown(IHM_Component_t *self, int localX, int localY);
void onBoutonClearMouseDown(IHM_Component_t *self, int localX, int localY);


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
 * @param state [S] etat pressé (1) ou relaché (0) du bouton.
 * @return renvoie le numéro du bouton de souris. Renvoie 0 si aucun click.
 */
int getMouseClick(int *x, int *y, int *state);

/**
 * @brief teste si le bouton Play est actif ou non
 * @return renvoie 1 si presse, 0 si relache
 */
int getBoutonPlayState();

/**
 * @brief Teste si le bouton de reset a ete clique
 * @return 1 si il a ete clique, 0 sinon
 */
int getBoutonResetClicked();

/**
 * @brief Teste si le bouton d'effacement a ete clique
 * @return 1 si il a ete clique, 0 sinon
 */
int getBoutonClearClicked();


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

/**
 * @brief Met a jour le texte de la barre de statut en bas de la fenêtre
 * @param generation numero de generation du jeu.
 * @param population population presente sur le terrain
 */
void setStatustext(int generation, int population);

/**
 * @brief teste si un ecart de temps s'est écoulé
 * @param timeStep ecart de temps en microsecondes
 * @return 0 tant que le temps ne s'est pas écoulé, 1 sinon.
 */
int timeLapse(double timeStep);

#endif //IHM_SETUP_H_