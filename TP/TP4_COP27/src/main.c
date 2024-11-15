#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif
#include <stdio.h>
#include <string.h>

#include "IHM_Application.h"
#include "IHM_Window.h"
#include "IHM_Setup.h"
#include "actionsParametrees.h"
#include "main.h"

void afficheCadre(int x, int y);
int main(int argc, char **argv)
{
    //////////////////////////////////////////////////////////////////////////////////////////////
    // Inits partie graphique de l'application.
    ///////////////////////////////////////////////

    IHM_DataModel_t dataModel;
    IHM_Application_t application;
    IHM_Window_t mainWindow;
    IHM_Setup(&application, &dataModel, &mainWindow);

    // environnement ////////////////////////////

    int xSouris = 0;
    int ySouris = 0;
    int carreVisible = 0;
    char keyPressed = 0;

     // Variables liées aux paramètres des fichiers
    int tabCO2[NB_MAX_LECTURE];
    int tabAnnee[NB_MAX_LECTURE];
    int tabAff[LONGUEUR_ABSCISSE];
    // nombre de valeurs lues
    int nbValLues;
    // début et fin de l'interval affiché
    int i_deb;
    int i_fin;


    do
    {
        // Effacement de l'interface
        IHM_Application_clearWindows(&application);
        // Récupération de tous les événements ayant eu lieu sur l'OS
        IHM_Application_processEvent(&application);

        //Mon Code Ici /////////////////////////////////////////////
        
        // Extraction des événements utiles
        keyPressed = getKeyPressed();
        getMousePosition(&xSouris, &ySouris);

        // Gestion des événements
        if (keyPressed == 'c') carreVisible = !carreVisible;
        
        // Création des objets graphiques dans l'application
        if (carreVisible == 1) dessineRectanglePlein(xSouris,ySouris,40,40, IHM_Window_couleur(255,0,0));

        afficheCadre(HAUTEUR_ORDONNEE, LONGUEUR_ABSCISSE);

        //Fin de mon code ////////////////////////////////////////
        // Affichage des objets dans la fenêtre de l'IHM
        IHM_Application_drawWindows(&application);
 

    } while (!application.quitter); //On quitte soit par la touche ESC, soit par la fermeture de la fenêtre
    // fin de la boucle principale
    IHM_Application_destroy(&application);
    return 0;
}
