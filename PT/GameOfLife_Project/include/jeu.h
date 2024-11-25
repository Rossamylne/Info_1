#ifndef JEU_H
#define JEU_H

#define LARGEUR_TERRAIN 80
#define HAUTEUR_TERRAIN 80

#define GLIDER 1
#define FLECHE 2
#define FUSEE 3

typedef unsigned char etat_t;

typedef struct {
    etat_t etatPresent[LARGEUR_TERRAIN*HAUTEUR_TERRAIN];
    etat_t etatFutur[LARGEUR_TERRAIN*HAUTEUR_TERRAIN];
} terrain_t;

etat_t getPresent(terrain_t *monTerrain, int x, int y);
void setPresent(terrain_t *monTerrain, int x, int y, etat_t etat);
etat_t getFutur(terrain_t *monTerrain, int x, int y);
void setFutur(terrain_t *monTerrain, int x, int y, etat_t etat);
int getPopulation(terrain_t *monTerrain);

int nbVoisins(terrain_t *monTerrain, int x, int y);
void calculFutur(terrain_t *monTerrain);
void avanceTemps(terrain_t *monTerrain);
void razTerrain(terrain_t *monTerrain);
void initMotif(int motif, terrain_t *monTerrain, int x, int y);
void initAleatoire(terrain_t *monTerrain);

void printConsole(terrain_t *monTerrain);

#endif // JEU_H