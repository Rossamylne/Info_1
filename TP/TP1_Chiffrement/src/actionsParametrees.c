#include <stdio.h>

#include "actionsParametrees.h"


/**
 * @brief ... à compléter avec votre préparation
 * 
 * @param min borne min pour la clé
 * @param max borne max pour la clé
 * @return int valeur de la clé
 */
int acquerirCle(int min, int max)
{
    int valLue;
    printf("\nQuelle valeur pour la cle (entre %d et %d) ? : ", min, max);
    scanf("%d", &valLue);
    if ((valLue < min) || (valLue > max))
    {
        printf("\nERREUR !!!");
    }
    return valLue;
}

/**
 * @brief ... à compléter avec votre préparation
 * 
 * @param car caractère à chiffrer
 * @param cle valeur de la clé
 * @return char caractère après chiffrement
 */
char chiffrerCar(char car, int cle)
{
    char carChiffre;

    if ((car >= 'a') && (car <= 'z'))
    {
        carChiffre = chiffrerMin(car, cle);
    }
    else if ((car >= 'A') && (car <= 'Z'))
    {
        carChiffre = chiffrerMaj(car, cle);
    }
    return carChiffre;
}

/**
 * @brief ... à compléter avec votre préparation
 * 
 * @param car caractère majuscule à chiffrer
 * @param cle valeur de la clé
 * @return char caractère majuscule après chiffrement
 */
char chiffrerMaj(char car, int cle)
{
    // première stragéie de codage : on calcule directement le nouveau caractère. 
    // Si vous faîtes des corrections, conservez le principe de ce calcul direct
    return ((car - 'A') + cle) + 'A';
}

/**
 * @brief ... à compléter avec votre préparation
 * 
 * @param car caractère minuscule à chiffrer
 * @param cle valeur de la clé
 * @return char caractère minuscule après chiffrement
 */
char chiffrerMin(char car, int cle)
{
    int i;
    char carCalcule = car;
    // alternative correcte : utiliser une boucle pour compter les caractères
    // Si vous faîtes des corrections, conservez le principe de cette solution avec une boucle
    for (i = 1; i < cle; i++)
    {
        if (carCalcule == 'z')
        {
            carCalcule = 'a';
        }
        else
        {
            carCalcule = carCalcule + 1;
        }
    }
    return carCalcule;
}

/**
 * @brief ... à compléter avec votre préparation
 * 
 * @param car caractère à déchiffrer
 * @param cle valeur de la clé
 * @return char caractère après déchiffrement
 */
char dechiffrerCar(char car, int cle)
{
    // A faire dans la partie 6 ! 
    // en attendant, on renvoie toujours un espace
    return ' ';
}
