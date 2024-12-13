#include <stdio.h>

#include "IHM_Helper.h"
#include "fonctionsGraphiques.h"


void dessineGrille(void)
{
    int w,h;
    getWindowSize(&w, &h);
    dessineRectanglePlein(5, 60, h-90, w-10, IHM_Window_couleur(255,255,255));

    int case_width = (w-10) / 80;
    dessineLigne(w-5, 60, w-5, h-90, IHM_Window_couleur(0, 0, 0)); 
    
    for (int i = 0; i <= w-5; i+=case_width) {
        int x = i + 5; 
        dessineLigne(x, 60, x, h-30, IHM_Window_couleur(0, 0, 0)); 
    }

    int case_height = (h - 90) / 80;
    dessineLigne(5, h-90, w-5, h-30, IHM_Window_couleur(0, 0, 0));

    for (int j = 0; j <= h-90; j+=case_height) {
        int y = 60 + j;
        dessineLigne(5, y, w-5, y, IHM_Window_couleur(0, 0, 0));
    }
}

void placePoint(int x, int y)
{

}

void placeCellules(terrain_t *monTerrain)
{

}