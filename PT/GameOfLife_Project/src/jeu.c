
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jeu.h"

etat_t getPresent(terrain_t *monTerrain, int x, int y){
    //Votre code ici
    return 0; //A modifier. Doit retourner l'etat d'une case de tableau
}

void setPresent(terrain_t *monTerrain, int x, int y, etat_t etat){
    //Votre code ici
}

etat_t getFutur(terrain_t *monTerrain, int x, int y){
    //Votre code ici
    return 0; //A modifier. Doit retourner l'etat d'une case de tableau
}

void setFutur(terrain_t *monTerrain, int x, int y, etat_t etat){
    //Votre code ici
}

int nbVoisins(terrain_t *monTerrain, int x, int y){
    //Votre code ici
    return 0; //A modifier. Doit retourner le nombre de voisins de la case x y
}


void calculFutur(terrain_t *monTerrain){
    //Votre code ici
}

int getPopulation(terrain_t *monTerrain){
    return 0;
}


void avanceTemps(terrain_t *monTerrain){
    //Votre code ici
}

void razTerrain(terrain_t *monTerrain){
    //Votre code ici
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