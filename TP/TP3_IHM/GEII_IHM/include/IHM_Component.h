#ifndef IHM_COMPONENT_H_
#define IHM_COMPONENT_H_

#include <SDL2/SDL.h>
#include "IHM_Button.h"
#include "IHM_GridPanel.h"
#include "IHM_DrawPanel.h"
#include "IHM_TextLabel.h"


struct IHM_Window;

/**
 * @enum IHMComposantType_t
 * @brief Enumeration des types de composants graphiques supportés.
 * 
 * BUTTON_T    Bouton d'action
 * GRIDPANEL_T,    Panneau de cases sur grille de taille paramétrable
 * DRAWPANEL_T,    Panneau dédié à du dessin de formes
 * TEXTLABEL_T     Champ de texte sur une ligne
 */
typedef enum {  BUTTON_T,      
                GRIDPANEL_T,  
                DRAWPANEL_T,    
                TEXTLABEL_T     
} IHMComposantType_t;

/**
 * @struct IHM_Component_t
 * @brief Abstraction d'un composant graphique.
 * Il contient le type à réaliser et la réalisation elle-même.
 */
typedef struct IHM_Component {
    SDL_Rect boundingRect;          
    struct IHM_Window *parent;
    IHMComposantType_t type;

    IHM_GridPanel_t *gridPanel;
    IHM_DrawPanel_t *drawPanel;
    IHM_Button_t *bouton;
    IHM_TextLabel_t *textLabel;

    void (*onClick)(struct IHM_Component *self, int localX, int localY);


} IHM_Component_t;

/**
 * @fn void IHM_Component_init(IHM_Component_t *self, struct IHM_Window *parent, IHMComposantType_t type)
 * @brief Initialise le composant et réalise son type désiré.
 * @param self Pointeur d'auto-référence du composant concerné.
 * @param parent Fenêtre devant contenir ce composant.
 * @param type Type effectif désiré du composant.
 */
void IHM_Component_init(IHM_Component_t *self, struct IHM_Window *parent, IHMComposantType_t type);

/**
 * @fn void IHM_Component_destroy(IHM_Component_t *self)
 * @brief Détruit le composant en libère les allocations mémoire dont il est responsable.
 * @param self Pointeur d'auto-référence du composant concerné.
 */
void IHM_Component_destroy(IHM_Component_t *self);

/**
 * @brief Force le composant à se redessiner dans sa fenêtre mère.
 * @param self Pointeur d'auto-référence du composant concerné.
 */
void IHM_Component_draw(IHM_Component_t *self);

/**
 * @brief Fixe dimesions et position du composant dans sa fenêtre mère.
 * @param self Pointeur d'auto-référence du composant concerné.
 * @param top Ordonnée du coin supérieur gauche du composant dans le système de coordonnées 
 * de sa fenêtre mère
 * @param left Abcisse du coin supérieur gauche du composant dans le système de coordonnées 
 * de sa fenêtre mère
 * @param width Largeur du composant.
 * @param height Hauteur du composant.
 */
void IHM_Component_setBoundaries(IHM_Component_t *self, int top, int left, int width, int height);

/**
 * @brief Fonction automatiquement appelée pour vérifier si les coordonnées de click
 * appartiennent à ce composant.
 * Si c'est le cas et que le pointeur de fonction onClick est valide, la fonction onClick() est invoquée.
 * @param self Pointeur d'auto-référence du composant concerné.
 * @param parentX Abcisse du click sur le composant dans le système de coordonnées 
 * de sa fenêtre mère.
 * @param parentY Abcisse du click sur le composant dans le système de coordonnées 
 * de sa fenêtre mère.
 * @return Renvoie 0 si ce composant était bien cliqué. -1 sinon.
 */
int IHM_Component_click(IHM_Component_t *self, int parentX, int parentY);


#endif //IHM_COMPONENT_H_