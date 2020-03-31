#include "iir.h"

/* Initialise les paramètres utilisée par les fonctions IIR */
s_IirParams* initIir() {
	/* Alloue dynamiquement la structure */
	s_IirParams* parameters = malloc(sizeof(s_IirParams));

	/* Initialise les valeurs à 0 */
	parameters->lastacrX = 0;
	parameters->lastacrY = 0;
	parameters->lastacirX = 0;
	parameters->lastacirY = 0;

	return parameters;
}

/* Applique la fonction iir aux paramètres acr et acir de myAbsorb */
void iir(s_IirParams* parameters, absorp* myAbsorp) {
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

/* Libère la mémoire allouée pour la structure params de IIR */
void closeIIR(s_IirParams* parameters) {
	free(parameters);
}

/* Fonction de test du filtrage IIR */
absorp iirTest(char* filename) {
	int etat = 0; /* Etat de la lecture */
	absorp myAbsorp;

	s_IirParams* parameters = initIir(); /* Params du IIR */
	FILE* file = initFichier(filename); /* Fichier contenant les valeurs à filtrer */

	while(etat != EOF) {
		/* On récupère les données */
		absorp tmpAbsorp = lireFichier(file, &etat);

		/* Si on est pas en fin de fichier (EOF) */
		if(etat != EOF) {
			/* Les valeurs sont valides donc on les filtres */
			myAbsorp = tmpAbsorp;
			iir(parameters, &myAbsorp);
		}
	}

	/* Désallocation et fermeture */
	closeIIR(parameters);
	finFichier(file);
	
	/* Retourne la dernière absorption filtrée */
	return myAbsorp;
}
