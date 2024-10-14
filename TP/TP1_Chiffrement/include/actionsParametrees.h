#ifndef ACTIONSPARAMETREES_H_
#define ACTIONSPARAMETREES_H_

#define NB_LETTRES 26
#define NB_CAR_SPE 10

/* Prototypes des actions paramétrées utilisées */
int acquerirCle(int min, int max);
char chiffrerCar(char car, int cle);
char chiffrerMaj(char car, int cle);
char chiffrerMin(char car, int cle);
char dechiffrerCar(char car, int cle);

#endif //ACTIONSPARAMETREES_H_