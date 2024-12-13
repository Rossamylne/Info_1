#include <stdio.h>

#include "IHM_Helper.h"
#include "fonctionsGraphiques.h"


void dessineGrille(int height, int width, int case_h, int case_w)
{
    /**int width,h;
    getWindowSize(&w, &h);
    **/
    dessineRectanglePlein(5, 60, height-90, width-10, IHM_Window_couleur(255,255,255));

//Lignes verticales

    //int case_w = (w-10) / 80;
    dessineLigne(width-5, 60, width-5, height-30, IHM_Window_couleur(0, 0, 0)); 
    
    for (int i = 0; i <= width-5; i+=case_w) {
        int x = i + 5; 
        dessineLigne(x, 60, x, height-30, IHM_Window_couleur(0, 0, 0)); 
    }

//Lignes heightorizontales

    //int case_h = (h - 90) / 80;
    dessineLigne(5, height-30, width-5, height-30, IHM_Window_couleur(0, 0, 0));

    for (int j = 0; j <= height-90; j+=case_h) {
        int y = 60 + j;
        dessineLigne(5, y, width-5, y, IHM_Window_couleur(0, 0, 0));
    }
}

void placePoint(int pos_y, int pos_x, int case_h, int case_w)
{
    dessineRectanglePlein(pos_x, pos_y, case_h, case_w, IHM_Window_couleur(255,0,0));
}

void placeCellules(terrain_t *monTerrain)
{

}