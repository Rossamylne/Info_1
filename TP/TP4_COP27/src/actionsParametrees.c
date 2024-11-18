#include <stdio.h>

#include "IHM_Setup.h"
#include "actionsParametrees.h"

/**
 * @fn bool lirePoints
 * @brief Fonction qui charge les données depuis un fichier texte, rend faux si le fichier n’existe pas ou s’il est vide
 * @param [in] fichier récupère le nom du fichier à ouvrir
 * @param [in] valeurs
 * @param [in] temps
 * @param [in] nbValLues
 */
bool lirePoints(char *fichier, int *valeurs, int *temps, int *nbValLues)
{
    /* Fonctionnement :
     * 1. Ouvre le fichier en mode lecture.
     * 2. Vérifie si le fichier est ouvrable. Si ce n'est pas le cas, affiche un message d'erreur.
     * 3. Lit chaque ligne du fichier jusqu'à la fin (`feof`) en utilisant `fscanf`.
     *    - Si deux champs sont lus avec succès (un temps et une valeur), les ajoute aux tableaux.
     *    - Incrémente l'indice pour suivre la position actuelle dans les tableaux.
     *    - Met à jour le compteur du nombre de valeurs lues via `nbValLues`.
     *    - Affiche les valeurs lues dans la console.
     * 4. Ferme le fichier une fois la lecture terminée.
     * 5. Affiche le nombre total de points lus dans la console.
     * 6. Retourne `false` (note : ce retour n'est pas utilisé dans l'état actuel du code).
     */
    // Fichier
    FILE *fp;
    // variables pour le temps et la valeur
    int t, v;
    // nombre de champs lus à chaque ligne
    int nbChamp;
    int indice = 0;
    int finishValue = 0;
    *nbValLues = 0;
    // ouverture fichier
    fp = fopen(fichier, "r");
    // Si le fichier n'est pas ouvrable
    if (!fp)
    {
        printf("Impossible d'ouvrir le fichier!");
    }
    else
    {
        do
        {
            nbChamp = fscanf(fp, "%d;%d", &t, &v);
            if (nbChamp == 2)
            {
                indice++;
                temps[indice] = t;
                valeurs[indice] = v;
                (*nbValLues)++;
                printf("valeurs lues : %d %d \n", t, v);
                finishValue = 1;
            }
        } while (!feof(fp));
        fclose(fp);
        printf(" Nb points = %d\n", *nbValLues);
    }
    return false;
}

/**
 * @fn void afficheCadre
 * @brief Procédure qui affiche le cadre où l’origine est à la coordonnée (x,y) de la fenêtre
 * @param [in] x Coordonnée d'affichage du cadre
 * @param [in] y Deuxième coordonnée d'affichage du cadre
 * @param [in] coul Couleur du cadre
 */
void afficheCadre(int x, int y)
{
    /* Fonctionnement :
     * 1. Dessine un rectangle blanc en fond pour remplir toute la zone de dimensions (x, y).
     * 2. Calcule les dimensions du rectangle noir central à afficher, basé sur des constantes (`LONGUEUR_ABSCISSE` et `HAUTEUR_ORDONNEE`).
     * 3. Positionne le rectangle noir de manière à ce qu'il soit centré dans la zone.
     * 4. Dessine un second rectangle blanc à l'intérieur du rectangle noir, en laissant une bordure noire visible.
     *
     * Résultat : Le cadre final est un rectangle blanc (zone de fond), avec un rectangle noir centré
     * et un deuxième rectangle blanc légèrement plus petit au centre du rectangle noir.
     */
    dessineRectanglePlein(0, 0, y, x, IHM_Window_couleur(255, 255, 255));

    int largeurCadre = HAUTEUR_ORDONNEE;
    int hauteurCadre = LONGUEUR_ABSCISSE;


    dessineRectanglePlein((x - LONGUEUR_ABSCISSE) / 2, (y - HAUTEUR_ORDONNEE) / 2, largeurCadre, hauteurCadre, IHM_Window_couleur(0, 0, 0));

    dessineRectanglePlein((x - LONGUEUR_ABSCISSE) / 2 + 2, (y - HAUTEUR_ORDONNEE) / 2 + 2, HAUTEUR_ORDONNEE - 4, LONGUEUR_ABSCISSE - 4, IHM_Window_couleur(255, 255, 255));
}

/**
 * @fn void affichePoints
 * @brief Procédure qui affiche les 200 points de données dans le cadre, en faisant la mise à l’échelle verticale des valeurs
 * @param [in] x_0 Coordonnée d'origine pour l'affichage, tient compte des dimensions de la fenêtre
 * @param [in] y_0 Deuxième coordonnée d'origine pour l'affichage, tient compte des dimensions de la fenêtre
 * @param [in] tableau Stockage des valeurs
 * @param [in] coul Couleur de l'affichage
 */
void affichePoint(int x_0, int y_0, int valeurs[200])
{
    /* Fonctionnement :
     * 1. Trouve la valeur maximale dans le tableau des valeurs.
     *    - Cela permet de normaliser les hauteurs des points en fonction de la hauteur du cadre (`HAUTEUR_ORDONNEE`).
     * 2. Calcule un facteur d'échelle pour adapter les valeurs à la hauteur du cadre.
     * 3. Parcourt chaque valeur du tableau et calcule la hauteur correspondante dans le cadre.
     *    - La hauteur est déterminée en divisant chaque valeur par le facteur d'échelle.
     * 4. Dessine un rectangle rouge pour chaque point, en utilisant :
     *    - Une largeur fixe (1 pixel).
     *    - Une hauteur fixe (2 pixels).
     *    - Une position horizontale incrémentée de 2 pixels pour chaque point, créant une frise régulière.
     *    - Une position verticale adaptée à la hauteur calculée.
     */
    float maxValeur = 0;
    int hauteurCadre = HAUTEUR_ORDONNEE;

    for (int i = 0; i < 200; i++)
    {
        if (valeurs[i] > maxValeur)
        {
            maxValeur = valeurs[i];
        }
    }

    float facteurEchelle = maxValeur / hauteurCadre;

    for (int i = 0; i < 200; i++)
    {
        int hauteurPoint = valeurs[i] / facteurEchelle;
        dessineRectangle(x_0 + i * 2, y_0 + hauteurCadre - hauteurPoint, 1, 2, IHM_Window_couleur(255, 0, 0));
    }
}

/**
 * @fn void zoom
 * @brief Procédure qui sélectionne ou interpole 200 points dans l’intervalle [i_deb,i_fin] du tableau valIn (en vu de son affichage)
 * @param [in] valIn
 * @param [in] i_deb Valeur limite basse de l'intervalle
 * @param [in] i_fin Valeur limite haute de l'intervalle
 * @param [in] valOut
 */
void zoom(int valeursSource[], int nbSource, int valeursZoom[], int longueurDest, int i_deb, int i_fin)
{
    /* Fonctionnement :
     * 1. Vérifie et ajuste les indices `i_deb` et `i_fin` pour qu'ils soient dans les limites du tableau source.
     *    - Si `i_deb` est inférieur à 0, il est fixé à 0.
     *    - Si `i_fin` dépasse la taille de `valeursSource`, il est fixé à la dernière position valide.
     *    - Si `i_deb` est supérieur à `i_fin`, la fonction termine immédiatement (rien à faire).
     * 2. Calcule la plage d'indices source (entre `i_deb` et `i_fin`) et un **facteur d'échelle**.
     *    - Ce facteur détermine combien de points source correspondent à chaque point destination.
     * 3. Parcourt les indices de la destination (`valeursZoom`) et, pour chaque position :
     *    - Identifie l'indice correspondant dans le tableau source.
     *    - Copie la valeur du tableau source dans le tableau destination.
     * 4. Si le facteur est inférieur à 1.0 (plus de points destination que source), duplique certaines valeurs.
     *    - Cela permet de "remplir" le tableau destination en respectant le facteur d'échelle.
     */
    if (i_deb < 0)
        i_deb = 0;
    if (i_fin >= nbSource)
        i_fin = nbSource - 1;
    if (i_deb > i_fin)
        return;

    int plageSource = i_fin - i_deb + 1;
    float facteur = (float)plageSource / longueurDest;

    for (int i = 0; i < longueurDest; i++)
    {
        // Trouve l'indice source correspondant
        int indexSource = i_deb + (int)(i * facteur);
        valeursZoom[i] = valeursSource[indexSource];

        if (facteur < 1.0f)
        {
            for (int j = 0; j < (int)(1 / facteur); j++)
            {
                if (i + j < longueurDest)
                    valeursZoom[i + j] = valeursSource[indexSource];
            }
        }
    }
}

/**
 * @fn void frise
 * @brief Procédure qui dessine la frise chronologique en mettant en valeur l’intervalle sélectionné
 * @param [in] date_deb Valeur de début de l'intervalle
 * @param [in] date_fin Valeur de limite de l'intervalle
 */
void afficheFrise(int x_0, int y_0, int largeur, int nbPeriodes, short datesDebut[], short datesFin[], int minDate, int maxDate)
{
    /* Fonctionnement :
     * 1. Calcule un **facteur d'échelle** en fonction de la largeur de la frise et de l'intervalle entre `minDate` et `maxDate`.
     *    - Ce facteur permet de convertir les dates (qui sont dans l'intervalle `[minDate, maxDate]`) en coordonnées x (en pixels).
     * 2. Pour chaque période (définie par une date de début et de fin) :
     *    - Calcule la position `xDebut` et `xFin` des rectangles représentant les périodes sur la frise, en les ajustant selon le facteur d'échelle.
     *    - Calcule la **largeur** de chaque rectangle, qui correspond à la différence entre `xFin` et `xDebut`.
     * 3. Utilise la fonction `dessineRectanglePlein` pour dessiner un rectangle pour chaque période, avec une hauteur fixe de 10 pixels et une couleur bleue.
     *    - La position verticale (`y_0`) est constante, de même que la hauteur (fixée à 10 pixels).
     *    - La couleur du rectangle est définie en bleu `(0, 0, 255)`.
     */
    float facteurEchelle = (float)largeur / (maxDate - minDate);

    for (int i = 0; i < nbPeriodes; i++)
    {

        int xDebut = x_0 + (datesDebut[i] - minDate) * facteurEchelle;
        int xFin = x_0 + (datesFin[i] - minDate) * facteurEchelle;
        int largeurRectangle = xFin - xDebut;

        dessineRectanglePlein(xDebut, y_0, largeurRectangle, 10, IHM_Window_couleur(0, 0, 255));
    }
}