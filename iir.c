#include "iir.h"

s_IIRParameters* initIIR() {
	s_IIRParameters* parameters = malloc(sizeof(s_IIRParameters));

	parameters->lastacrX = 0;
	parameters->lastacrY = 0;
	parameters->lastacirX = 0;
	parameters->lastacirY = 0;
}

void iir(s_IIRParameters* parameters, absorp* myAbsorp) {
	/* Valeurs actuelles */
	float currentacrY;
	float currentacrX;
	float currentacirY;
	float currentacirX;

	/* Lecture dans myAbsorp */
	currentacrX = myAbsorp->acr;
	currentacirX = myAbsorp->acir;
	
	/* Application de IIR */
	currentacrY = currentacrX - parameters->lastacrX + (COEFF_ALPHA * parameters->lastacrY);
	currentacirY = currentacirX - parameters->lastacirX + (COEFF_ALPHA * parameters->lastacirY);

	/* Place les valeurs calculées dans lastX et lastY */
	parameters->lastacrX = currentacrX;
	parameters->lastacrY = currentacrY;
	parameters->lastacirX = currentacirX;
	parameters->lastacirY = currentacirY;

	/* Remplace les valeurs deans myAbsorp */
	myAbsorp->acr = currentacrY;
	myAbsorp->acir = currentacirY;
}

absorp iirTest(char* filename) {
	int etat=0;
	absorp	myAbsorp;

	s_IIRParameters* parameters = initIIR();
	FILE* file = initFichier(filename);

	while(etat != EOF) {
		absorp tmpAbsorp = lireFichier(file, &etat);

		if(etat != EOF) {
			myAbsorp = tmpAbsorp;
			iir(parameters, &myAbsorp);
		}
	}

	endIIR(parameters);
	finFichier(file);
	
	return myAbsorp;
}


void endIIR(s_IIRParameters* parameters) {
	free(parameters);
}
