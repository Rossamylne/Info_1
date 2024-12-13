#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif
#include <stdio.h>
#include <string.h>

#include "IHM_Application.h"
#include "IHM_Window.h"
#include "IHM_Helper.h"
#include "jeu.h"
#include "fonctionsGraphiques.h"
#include "main.h"


int main(int argc, char **argv)
{
    //////////////////////////////////////////////////////////////////////////////////////////////
    // Inits partie graphique de l'application.
    ///////////////////////////////////////////////

    IHM_DataModel_t dataModel;
    IHM_Application_t application;
    IHM_Window_t mainWindow;
    IHM_Setup(&application, &dataModel, &mainWindow);

    // Mon environnement ici ////////////////////////////

    int xSouris = 0;
    int ySouris = 0;
    char keyPressed = 0;

    terrain_t monTerrain;
    int generation = 0;
    int population = 0;
    int run = 0;
    double pasTemporel = TIMESTEP;

    int w,h;
    getWindowSize(&w, &h);
    int case_width = (w-10) / 80;
    int case_height = (h - 90) / 80;

    razTerrain(&monTerrain);

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

        // Gestion des événements boutons
        run = getBoutonPlayState();
        if(getBoutonResetClicked()) printf("Reset aléatoire demandé\n");
        if(getBoutonClearClicked()) printf("Effacement demandé\n");
 
        //Evolution du monde
        if(timeLapse(pasTemporel)){
            if(run){
                generation++;
                population = getPopulation(&monTerrain);
                calculFutur(&monTerrain);       
                avanceTemps(&monTerrain);
                printf("\n Generation %d - Population %d", generation, population);
                setStatustext(generation, population);
            }
        }

        // Création des objets graphiques dans l'application (grille, points ...)
        dessineGrille(h, w, case_height, case_width);
        placeCellules(&monTerrain);
        //Fin de mon code ////////////////////////////////////////
        // Affichage des objets dans la fenêtre de l'IHM
        IHM_Application_drawWindows(&application);
 

    } while (!application.quitter); //On quitte soit par la touche ESC, soit par la fermeture de la fenêtre
    // fin de la boucle principale


    IHM_Application_destroy(&application);
    return 0;
}
