#include <stdio.h>

#include "IHM_Setup.h"
#include "actionsParametrees.h"


void afficheTrain(int x, int y, unsigned long couleur)
{
    dessineRectanglePlein(x+20, y-47, 54, 10, IHM_Window_couleur(0,0,0));
    dessineRectanglePlein(x+60, y-47, 54, 10, IHM_Window_couleur(0,0,0));
    dessineRectanglePlein(x, y-LARGEUR_TRAIN, LARGEUR_TRAIN, LARGEUR_TRAIN*2, couleur);
    for(int i=0; i<20; i++){
        dessineLigne(x+80, y-LARGEUR_TRAIN,  x+80+i, y-i, couleur);
    }
}

void afficheRails(int x, int y){
    int w,h;
    int i;
    getWindowSize(&w, &h);
    dessineLigne(0, y+2, w, y+2, IHM_Window_couleur(0,0,255));
    dessineLigne(0, y-42, w, y-42, IHM_Window_couleur(0,0,255));
    for(i=0;i<w;i++) {
        dessineRectanglePlein(i*20, y-42, 44, 3, IHM_Window_couleur(0,0,255));
    }
}

void affichePalette(unsigned long palette[], int nbCouleurs){
    int w, h;
    getWindowSize(&w, &h);
    for(int i=0;i<nbCouleurs;i++) {
        dessineRectanglePlein(i*(w/5),h-10, (i+1)*((w/5)-1),h, palette[i]);
    }
}

int getIndiceCouleur(int x, int nbCouleurs){
    int coul, w, h;
    getWindowSize(&w, &h);
    if(h-10){
        coul = x % (w/nbCouleurs);
    }
    return coul;
}