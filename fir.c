#include "fir.h"

s_FirParams* initFir() {
	int i;
	s_FirParams* params = malloc(sizeof(s_FirParams));

	for(i=0; i<51; i++) {
		params->acrSamples[i] = 0;
		params->acirSamples[i] = 0;
	}

	params->currentIdx = 0;

	return params;
}

void pushNewValue(s_FirParams* params, absorp* myAbsorb) {
	params->acrSamples[params->currentIdx] = myAbsorb->acr;
	params->acirSamples[params->currentIdx] = myAbsorb->acir;
}

void fir(s_FirParams* params, absorp* myAbsorb) {
	const float coeffFIR[51] = {1.4774946e-019, 1.6465231e-004, 3.8503956e-004, 7.0848037e-004, 1.1840522e-003, 1.8598621e-003, 2.7802151e-003, 3.9828263e-003, 5.4962252e-003, 7.3374938e-003, 9.5104679e-003, 1.2004510e-002, 1.4793934e-002, 1.7838135e-002, 2.1082435e-002, 2.4459630e-002, 2.7892178e-002, 3.1294938e-002, 3.4578348e-002, 3.7651889e-002, 4.0427695e-002, 4.2824111e-002, 4.4769071e-002, 4.6203098e-002, 4.7081811e-002, 4.7377805e-002, 4.7081811e-002, 4.6203098e-002, 4.4769071e-002, 4.2824111e-002, 4.0427695e-002, 3.7651889e-002, 3.4578348e-002, 3.1294938e-002, 2.7892178e-002, 2.4459630e-002, 2.1082435e-002, 1.7838135e-002, 1.4793934e-002, 1.2004510e-002, 9.5104679e-003, 7.3374938e-003, 5.4962252e-003, 3.9828263e-003, 2.7802151e-003, 1.8598621e-003, 1.1840522e-003, 7.0848037e-004, 3.8503956e-004, 1.6465231e-004, 1.4774946e-019};
	int i;

	pushNewValue(params, myAbsorb);

	float acr = 0;
	float acir = 0;
	for(i = 0; i < 51; i++) {
		acr += coeffFIR[i]*params->acrSamples[(51 - i + params->currentIdx)%51];
		acir += coeffFIR[i]*params->acirSamples[(51 - i + params->currentIdx)%51];
	}

	myAbsorb->acr = acr;
	myAbsorb->acir = acir;

	params->currentIdx = (params->currentIdx + 1)%51;
}

void closeFir(s_FirParams* params) {
	free(params);
}

absorp firTest(char* filename) {
	int etat = 0;
	absorp myAbsorp;

	s_FirParams* params = initFir();
	FILE* file = initFichier(filename);
	
	do {
		absorp tmpAbsorp = lireFichier(file, &etat);

		if (etat != EOF) {
			myAbsorp = tmpAbsorp;
			fir(params, &myAbsorp);
		}
	} while (etat != EOF);
	
	closeFir(params);
	finFichier(file);

	return myAbsorp;
}