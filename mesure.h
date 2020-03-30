#ifndef MESURE_H
#define MESURE_H

#include "define.h"
#include "fichiers.h"

typedef enum e_EtatMesure {
    PIC_HAUT, PIC_BAS
} e_EtatMesure;

typedef struct s_MesureParams {
    float minAcr, maxAcr;
    float minAcir, maxAcir;
    int nbEch;

    e_EtatMesure etat;
} s_MesureParams;

/** 
 * Fonctions
 */
oxy mesureTest(char* filename);

#endif /* MESURE_H */