#ifndef FIR_H
#define FIR_H

#include "define.h"
#include "fichiers.h"

typedef struct s_FirParams {
    float acrSamples[51];
    float acirSamples[51];
    int currentIdx;
} s_FirParams;

/** 
 * Fonctions 
 */
s_FirParams* initFir();
void pushNewValue(s_FirParams* params, absorp* myAbsorb);
void fir(s_FirParams* params, absorp* myAbsorb);
void closeFir(s_FirParams* params);
absorp firTest(char* filename);

#endif /* FIR_H */