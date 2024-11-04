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
    int carreVisible = 0;
    char keyPressed = 0;

    do
    {

        IHM_Application_clearWindows(&application);
        IHM_Application_processEvent(&application);

        //Mon Code Ici /////////////////////////////////////////////

        keyPressed = getKeyPressed();
        if (keyPressed == 'c') carreVisible = !carreVisible;

        getMousePosition(&xSouris, &ySouris);
        if (carreVisible == 1) dessineRectanglePlein(xSouris,ySouris,40,40, IHM_Window_couleur(255,0,0));

        //Fin de mon code ////////////////////////////////////////

        IHM_Application_drawWindows(&application);
 

    } while (!application.quitter); //On quitte soit par la touche ESC, soit par la fermeture de la fenêtre
    // fin de la boucle principale
    IHM_Application_destroy(&application);
    return 0;
}
