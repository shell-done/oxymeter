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
float maxMesure(float a, float b);
float minMesure(float a, float b);
s_MesureParams* initMesure();
int mesure(s_MesureParams* params, absorp* absorp);
int calculatePoul(s_MesureParams* params);
int calculateSpO2(s_MesureParams* params, absorp* myAbsorp);
oxy calculate(s_MesureParams* params, absorp* myAbsorp);
void closeMesure(s_MesureParams* params);
oxy mesureTest(char* filename);

#endif /* MESURE_H */