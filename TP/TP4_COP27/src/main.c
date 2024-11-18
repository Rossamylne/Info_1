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
void affichePoint(int x_0, int y_0, int val[200]);
void zoom(int valeursSource[], int nbSource, int valeursZoom[], int longueurDest, int i_deb, int i_fin);
void afficheFrise(int x_0, int y_0, int largeur, int nbPeriodes, int datesDebut[], int datesFin[], int minDate, int maxDate);
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
    int valeursZoom[LONGUEUR_ABSCISSE];
    // Initialisation des périodes de test pour la frise
    /*
    short datesDebut[]
    short datesFin[]
    int nbPeriodes = sizeof(datesDebut) / sizeof(datesDebut[0]);
    int minDate = 1800, maxDate = 2020; // Dates réelles
    */
    // nombre de valeurs lues
    int nbValLues = 0;
    // début et fin de l'interval affiché
    int i_deb = 50, i_fin = 100;
    int w,h;
    int fPressed = 0;
    lirePoints("CO2_france.csv", tabCO2, tabAnnee, &nbValLues);
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
        if(keyPressed == 'f') fPressed = 1;
        
        // Création des objets graphiques dans l'application
        getWindowSize(&w, &h);
        afficheCadre(w, h);
        if(fPressed) {
            zoom(tabCO2, 200, valeursZoom, LONGUEUR_ABSCISSE, i_deb, i_fin);
            affichePoint((w-LONGUEUR_ABSCISSE)/2,(h-HAUTEUR_ORDONNEE)/2, tabCO2);
        }
        
        //afficheFrise(50, h - 50, w-100, nbPeriodes, datesDebut, datesFin, minDate, maxDate);
        //Fin de mon code ////////////////////////////////////////
        // Affichage des objets dans la fenêtre de l'IHM
        IHM_Application_drawWindows(&application);


    } while (!application.quitter); //On quitte soit par la touche ESC, soit par la fermeture de la fenêtre
    // fin de la boucle principale
    IHM_Application_destroy(&application);
    return 0;
}
