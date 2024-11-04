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
#define NB_COUL = 5;
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

    int xTrain, Ytrain;             /* Position du train */
    int xClic, yClic, btnClick;     /* Position du dernier clic */
    long unsigned int mapalette[5];               /* Palette de couleur */
    char keyPressed;                /* Dernier caractère tapé */
    int railsVisibles = 0;          /* Si vrai afficher les rails */
    int trainVisible = 0;           /* Si vrai afficher le train */
    int xSouris = 0;
    int ySouris = 0;
    int carreVisible = 0;

    do
    {
        mapalette[0] = IHM_Window_couleur(142, 202, 230);
        mapalette[1] = IHM_Window_couleur(33, 158, 188);
        mapalette[2] = IHM_Window_couleur(2, 48, 71);
        mapalette[3] = IHM_Window_couleur(255, 183, 3);
        mapalette[4] = IHM_Window_couleur(251, 133, 0);
        IHM_Application_clearWindows(&application);
        IHM_Application_processEvent(&application);

        //Mon Code Ici /////////////////////////////////////////////
        getMouseClick(&xClic, &yClic);
        keyPressed = getKeyPressed();
        if(keyPressed == 'r')  railsVisibles = !railsVisibles;
        if(keyPressed == 't')  trainVisible = !trainVisible;
        getMousePosition(&xSouris, &ySouris);
        if(carreVisible == 1) dessineRectanglePlein(xSouris,ySouris,40,40, IHM_Window_couleur(255,0,0));
        if(railsVisibles) afficheRails(xSouris,ySouris);
        if(trainVisible) afficheTrain(xSouris,ySouris, mapalette[getIndiceCouleur(xClic, 5)]);
        printf("%d", mapalette[getIndiceCouleur(xClic, 5)]);
        affichePalette(mapalette, 5);
        //Fin de mon code ////////////////////////////////////////

        IHM_Application_drawWindows(&application);
 

    } while (!application.quitter); //On quitte soif(railsVisibles == true) it par la touche ESC, soit par la fermeture de la fenêtre
    // fin de la boucle principale
    IHM_Application_destroy(&application);
    return 0;
}
 