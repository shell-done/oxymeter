#include "mesure.h"

float maxMesure(float a, float b) {
	if (a > b) {
		return a;
	} else {
		return b;
	}
}

float minMesure(float a, float b) {
	if (a < b) {
		return a;
	} else {
		return b;
	}
}

s_MesureParams* initMesure() {
	s_MesureParams* params = malloc(sizeof(s_MesureParams));

	params->minAcr = 0;
	params->maxAcr = 0;
	params->minAcir = 0;
	params->maxAcir = 0;
	params->nbEch = 0;
	params->etat = PIC_HAUT;

	return params;
}

int checkPicPosition(s_MesureParams* params, absorp* absorp) {
	int doCalculation = 0;

	if(params->etat == PIC_HAUT) {
		params->maxAcr = maxMesure(params->maxAcr, absorp->acr);
		params->maxAcir = maxMesure(params->maxAcir, absorp->acir);

		if(absorp->acr < 0) {
			params->etat = PIC_BAS;
		}

	} else {
		params->minAcr = minMesure(params->minAcr, absorp->acr);
		params->minAcir = minMesure(params->minAcir, absorp->acir);

		if(absorp->acr > 0) {
			params->etat = PIC_HAUT;
			doCalculation = 1;
		}
	}

	params->nbEch++;
	return doCalculation;
}

int calculatePoul(s_MesureParams* params) {
	return 30000/params->nbEch;
}

int calculateSpO2(s_MesureParams* params, absorp* myAbsorp) {
	float ptpAcr = params->maxAcr - params->minAcr;
	float ptpAcir = params->maxAcir - params->minAcir;

	float RsIR = (ptpAcr*myAbsorp->dcir)/(ptpAcir*myAbsorp->dcr);

	if(RsIR < 0.4) {
		return 0;
	} else if(RsIR < 1) {
		return 110 - 25*RsIR;
	} else {
		return 118 - 100*RsIR/3;
	}
}

oxy mesure(s_MesureParams* params, absorp* myAbsorp) {
	oxy myOxy;

	myOxy.spo2 = calculateSpO2(params, myAbsorp);
	myOxy.pouls = calculatePoul(params);

	params->nbEch = 0;
	params->minAcr = 0;
	params->minAcir = 0;
	params->maxAcr = 0;
	params->maxAcir = 0;

	return myOxy;
}

void closeMesure(s_MesureParams* params) {
	free(params);
}

oxy mesureTest(char* filename){
	int etat = 0;
	int redoMesure = 0;
	absorp myAbsorp;
	oxy myOxy;

	s_MesureParams* params = initMesure();
	FILE* file = initFichier(filename);
	
	while (etat != EOF) {
		myAbsorp = lireFichier(file, &etat);

		if (etat != EOF) {
			redoMesure = checkPicPosition(params, &myAbsorp);

			if(redoMesure) {
				myOxy = mesure(params, &myAbsorp);
			}
		}
	}
	
	closeMesure(params);
	finFichier(file);

	return myOxy;
}
