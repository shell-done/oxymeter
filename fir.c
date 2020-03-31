#include "fir.h"

/* Initialise les paramètres utilisée par les fonctions FIR */
s_FirParams* initFir() {
	int i;

	/* Alloue dynamiquement la structure */
	s_FirParams* params = malloc(sizeof(s_FirParams));

	/* Initialise le buffer circulaire à 0 */
	for(i=0; i<51; i++) {
		params->acrSamples[i] = 0;
		params->acirSamples[i] = 0;
	}

	/* Initialise l'index courant à 0 */
	params->currentIdx = 0;

	return params;
}

/* Ajoute une nouvelle valeur acr/acir dans le buffer circulaire */
void pushNewValue(s_FirParams* params, absorp* myAbsorb) {
	params->acrSamples[params->currentIdx] = myAbsorb->acr;
	params->acirSamples[params->currentIdx] = myAbsorb->acir;
}

/* Applique la fonction fir aux paramètres acr et acir de myAbsorb */
void fir(s_FirParams* params, absorp* myAbsorb) {
	/* Coefficients utilisés pour le filtrage */
	const float coeffFIR[51] = {1.4774946e-019, 1.6465231e-004, 3.8503956e-004, 7.0848037e-004, 1.1840522e-003, 1.8598621e-003, 2.7802151e-003, 3.9828263e-003, 5.4962252e-003, 7.3374938e-003, 9.5104679e-003, 1.2004510e-002, 1.4793934e-002, 1.7838135e-002, 2.1082435e-002, 2.4459630e-002, 2.7892178e-002, 3.1294938e-002, 3.4578348e-002, 3.7651889e-002, 4.0427695e-002, 4.2824111e-002, 4.4769071e-002, 4.6203098e-002, 4.7081811e-002, 4.7377805e-002, 4.7081811e-002, 4.6203098e-002, 4.4769071e-002, 4.2824111e-002, 4.0427695e-002, 3.7651889e-002, 3.4578348e-002, 3.1294938e-002, 2.7892178e-002, 2.4459630e-002, 2.1082435e-002, 1.7838135e-002, 1.4793934e-002, 1.2004510e-002, 9.5104679e-003, 7.3374938e-003, 5.4962252e-003, 3.9828263e-003, 2.7802151e-003, 1.8598621e-003, 1.1840522e-003, 7.0848037e-004, 3.8503956e-004, 1.6465231e-004, 1.4774946e-019};
	int i, arrayIdx;

	/* Ajoute les dernières valeurs acr/acir */
	pushNewValue(params, myAbsorb);

	/* Effectue le calcul de la valeur filtrée */
	float acr = 0;
	float acir = 0;
	for(i = 0; i < 51; i++) {
		/* Index à récupérer dans le buffer circulaire */
		arrayIdx = (51 - i + params->currentIdx)%51;

		acr += coeffFIR[i]*params->acrSamples[arrayIdx];
		acir += coeffFIR[i]*params->acirSamples[arrayIdx];
	}

	/* Définit les valeurs ainsi calculées */
	myAbsorb->acr = acr;
	myAbsorb->acir = acir;

	/* Passe à l'index suivant du buffer circulaire */
	params->currentIdx = (params->currentIdx + 1)%51;
}

/* Libère la mémoire allouée pour la structure params de FIR */
void closeFir(s_FirParams* params) {
	free(params);
}

/* Fonction de test du filtrage FIR */
absorp firTest(char* filename) {
	int etat = 0; /* Etat de la lecture */
	absorp myAbsorp;

	s_FirParams* params = initFir(); /* Params du FIR */
	FILE* file = initFichier(filename); /* Fichier contenant les valeurs à filtrer */
	
	while (etat != EOF) {
		absorp tmpAbsorp = lireFichier(file, &etat); /* On récupère les données */

		/* Si on est pas en fin de fichier (EOF) */
		if (etat != EOF) {
			/* Les valeurs sont valides donc on les filtres */
			myAbsorp = tmpAbsorp;
			fir(params, &myAbsorp);
		}
	};
	
	/* Désallocation et fermeture */
	closeFir(params);
	finFichier(file);

	/* Retourne la dernière absorption filtrée */
	return myAbsorp;
}