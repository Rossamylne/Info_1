
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jeu.h"

etat_t getPresent(terrain_t *monTerrain, int x, int y) {
    int xCorrected = (x + LARGEUR_TERRAIN) % LARGEUR_TERRAIN;
    int yCorrected = (y + HAUTEUR_TERRAIN) % HAUTEUR_TERRAIN;
    return monTerrain->etatPresent[xCorrected + yCorrected * LARGEUR_TERRAIN];
}

void setPresent(terrain_t *monTerrain, int x, int y, etat_t etat){
    monTerrain->etatPresent[(x)+(y)*(LARGEUR_TERRAIN)] = etat;
}

etat_t getFutur(terrain_t *monTerrain, int x, int y){
    int xCorrected = (x + LARGEUR_TERRAIN) % LARGEUR_TERRAIN;
    int yCorrected = (y + HAUTEUR_TERRAIN) % HAUTEUR_TERRAIN;
    return monTerrain->etatPresent[xCorrected + yCorrected * LARGEUR_TERRAIN];
}

void setFutur(terrain_t *monTerrain, int x, int y, etat_t etat){
    monTerrain->etatFutur[(x)+(y)*(LARGEUR_TERRAIN)] = etat;
}

int nbVoisins(terrain_t *monTerrain, int x, int y){
    int nbVoisinsVivants = 0;
    for(int y=0; y<HAUTEUR_TERRAIN; y++){
        for(int x=0; x<LARGEUR_TERRAIN; x++){
            if(getPresent(monTerrain,x-1,y-1)) nbVoisinsVivants = nbVoisinsVivants + 1;
            if(getPresent(monTerrain,x,y-1)) nbVoisinsVivants = nbVoisinsVivants + 1;
            if(getPresent(monTerrain,x+1,y-1)) nbVoisinsVivants = nbVoisinsVivants + 1;
            if(getPresent(monTerrain,x+1,y)) nbVoisinsVivants = nbVoisinsVivants + 1;
            if(getPresent(monTerrain,x+1,y+1)) nbVoisinsVivants = nbVoisinsVivants + 1;
            if(getPresent(monTerrain,x-1,y)) nbVoisinsVivants = nbVoisinsVivants + 1;
            if(getPresent(monTerrain,x-1,y+1)) nbVoisinsVivants = nbVoisinsVivants + 1;
            if(getPresent(monTerrain,x,y+1)) nbVoisinsVivants = nbVoisinsVivants + 1;
        }
    }
    return nbVoisinsVivants; //A modifier. Doit retourner le nombre de voisins de la case x y
}


void calculFutur(terrain_t *monTerrain) {
    for (int y = 0; y < HAUTEUR_TERRAIN; y++) {
        for (int x = 0; x < LARGEUR_TERRAIN; x++) {
            int nbVoisinsVivants = nbVoisins(monTerrain, x, y);

            if (getPresent(monTerrain, x, y)) {                     /*CELLULE VIVANTE*/
                if (nbVoisinsVivants < 2 || nbVoisinsVivants > 3) {
                    setFutur(monTerrain, x, y, 0);                  //mort par sous population ou surpopulation
                } else {
                    setFutur(monTerrain, x, y, 1);                  //survie
                }
            } else {                                                /*CELLULE MORTE*/
                if (nbVoisinsVivants == 3) {
                    setFutur(monTerrain, x, y, 1);                  //reproduction
                } else {
                    setFutur(monTerrain, x, y, 0);                  //reste morte
                }
            }
        }
    }
}

int getPopulation(terrain_t *monTerrain){
    return 0;
}


void avanceTemps(terrain_t *monTerrain) {
    for (int y = 0; y < HAUTEUR_TERRAIN; y++) {
        for (int x = 0; x < LARGEUR_TERRAIN; x++) {
            setPresent(monTerrain, x, y, getFutur(monTerrain, x, y));
        }
    }
}

void razTerrain(terrain_t *monTerrain) {
    for (int i = 0; i < LARGEUR_TERRAIN * HAUTEUR_TERRAIN; i++) {
        monTerrain->etatPresent[i] = 0;
    }
    
    for (int i = 0; i < LARGEUR_TERRAIN * HAUTEUR_TERRAIN; i++) {
        monTerrain->etatFutur[i] = 0;
    }
}


void initMotif(int motif, terrain_t *monTerrain, int x, int y){

    switch(motif){
        case GLIDER:
            setPresent(monTerrain,x,y,1);
            setPresent(monTerrain,x+1,y,1);
            setPresent(monTerrain,x+2,y,1);
            setPresent(monTerrain,x,y+1,1);
            setPresent(monTerrain,x+1,y+2,1);
        break;
    }
}


void initAleatoire(terrain_t *monTerrain){
    int randVal;
    srand( time( NULL ) );

    for(int y=0; y<HAUTEUR_TERRAIN; y++){
        for(int x=0; x<LARGEUR_TERRAIN; x++){
            randVal = rand() % 2;
            setPresent(monTerrain,x,y,randVal);
        }
    }
}

void printConsole(terrain_t *monTerrain){

    printf("\n Etat Present:\n");
    for(int y=0; y<HAUTEUR_TERRAIN; y++){
        for(int x=0; x<LARGEUR_TERRAIN; x++){
            if(getPresent(monTerrain,x,y)) printf("X"); else printf("0");
        }
        printf("\n");
    }
    

    printf("\n");
    printf("\n Etat Futur:\n");
    for(int y=0; y<HAUTEUR_TERRAIN; y++){
        for(int x=0; x<LARGEUR_TERRAIN; x++){
            if(getFutur(monTerrain,x,y)) printf("X"); else printf("0");
        }
        printf("\n");
    }
    
}