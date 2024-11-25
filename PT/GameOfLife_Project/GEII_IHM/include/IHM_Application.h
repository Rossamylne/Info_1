#ifndef IHM_APPLICATION_H
#define IHM_APPLICATION_H


#include "SDL_ttf.h"
#include <SDL2/SDL.h>
#include "IHM_Window.h"


typedef struct IHM_Application_listeFenetres{
    IHM_Window_t* fenetre;
    Uint32 ID;
    struct IHM_Application_listeFenetres *suivante;
}IHM_Application_listeFenetres_t;

/**
 * \struct IHM_Application_t
 * \brief Objet conteneur de la partie graphique de l'application.
 *
 * l'objet IHM_Application_t doit obligatoirement être déclaré et initialisé 
 * pour toute utilisation d'une application graphique. 
 * Il est responsable de la gestion des fenêtres et de la boucle événementielle.
 */
typedef struct IHM_Application{
    IHM_Application_listeFenetres_t* listeFenetres; /*!< Liste chainée référençant les fenêtres. */
    int nbFenetres; /*!< Nombre de fenêtres de l'application */
    Uint32 mainWindowID; /*!< identifiant SDL de la fenêtre principale */

    int quitter; /*!< booléen signifiant que la fermeture de l'application est demandée */

} IHM_Application_t;

/**
 * \fn IHM_Application_init(IHM_Application_t *self)
 * \brief Fonction d'initialisation de l'objet IHM_Application_t.
 *
 * \param self Adresse de l'objet IHM_Application_t à initialiser.
 */
void IHM_Application_init(IHM_Application_t *self);

/**
 * \fn IHM_Application_destroy(IHM_Application_t *self)
 * \brief Fonction de destruction de l'objet IHM_Application_t.
 *
 * \param self Adresse de l'objet IHM_Application_t à détruire.
 */
void IHM_Application_destroy(IHM_Application_t *self);

/**
 * \fn IHM_Application_addWindow(IHM_Application_t *self, IHM_Window_t* fenetre)
 * \brief Ajoute une fenêtre à l'application
 *
 * \param self Adresse de l'objet IHM_Application_t.
 * \param fenetre Adresse de la fenêtre à ajouter.
 */
void IHM_Application_addWindow(IHM_Application_t *self, IHM_Window_t* fenetre);

/**
 * \fn IHM_Application_removeWindow(IHM_Application_t *self, IHM_Window_t* fenetre)
 * \brief Retire une fenêtre à l'application
 *
 * \param self Adresse de l'objet IHM_Application_t.
 * \param fenetre Adresse de la fenêtre à retirer.
 */
void IHM_Application_removeWindow(IHM_Application_t *self, IHM_Window_t* fenetre);

/**
 * \fn IHM_Application_setWindowAsMain(IHM_Application_t *self, IHM_Window_t* fenetre)
 * \brief Désigne une fenêtre comme fenêtre principale de l'application.
 * Le click sur la croix de fermeture d'une fenêtre la masque.
 * Dans le cas de la fenêtre principale, la fin de l'application est aussi requise.
 *
 * \param self Adresse de l'objet IHM_Application_t.
 * \param fenetre Adresse de la fenêtre choisie comme principale.
 */
void IHM_Application_setWindowAsMain(IHM_Application_t *self, IHM_Window_t* fenetre);

/**
 * \fn IHM_Application_clearWindows(IHM_Application_t *self)
 * \brief Demande à chaque fenêtre d'effacer son contenu.
 *
 * \param self Adresse de l'objet IHM_Application_t.
 */
void IHM_Application_clearWindows(IHM_Application_t *self);

/**
 * \fn IHM_Application_drawWindows(IHM_Application_t *self)
 * \brief Demande à chaque fenêtre de redessiner son contenu.
 *
 * \param self Adresse de l'objet IHM_Application_t.
 */
void IHM_Application_drawWindows(IHM_Application_t *self);

/**
 * \fn IHM_Application_fenetreParID(IHM_Application_t *self, Uint32 ID)
 * \brief Récupère le pointeur d'objet fenêtre à partir de son ID SDL.
 *
 * \param self Adresse de l'objet IHM_Application_t.
 * \param ID Identifiant SDL de la fenêtre.
 */
IHM_Window_t* IHM_Application_fenetreParID(IHM_Application_t *self, Uint32 ID);

/**
 * \fn IHM_Application_processEvent(IHM_Application_t *self)
 * \brief Boucle événementielle de l'application.
 *
 * \param self Adresse de l'objet IHM_Application_t.
 */
void IHM_Application_processEvent(IHM_Application_t *self);


#endif //IHM_APPLICATION_H