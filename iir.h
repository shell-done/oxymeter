#ifndef IIR_H
#define IIR_H

#include "define.h"
#include "fichiers.h"

#define COEFF_ALPHA 0.992

typedef struct IIRParameters {
    float lastacrX;
    float lastacrY;
    float lastacirX;
    float lastacirY;
} s_IIRParameters;

/** 
 * Fonctions 
 */
s_IIRParameters* initIIR();
void iir(s_IIRParameters* parameters, absorp* myAbsorp);
absorp iirTest(char* filename);
void closeIIR(s_IIRParameters* parameters);

#endif /* IIR_H */