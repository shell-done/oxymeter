#include "mesure.h"

/* Retourne le maximum entre a et b */
float maxMesure(float a, float b) {
	if (a > b) {
		return a;
	} else {
		return b;
	}
}

/* Retourne le minimum entre a et b */
float minMesure(float a, float b) {
	if (a < b) {
		return a;
	} else {
		return b;
	}
}

/* Initialise les paramètres utilisée par les fonctions de mesure */
s_MesureParams* initMesure() {
	/* Alloue dynamiquement la structure */
	s_MesureParams* params = malloc(sizeof(s_MesureParams));

	/* Initialise les paramètres à 0 */
	params->minAcr = 0;
	params->maxAcr = 0;
	params->minAcir = 0;
	params->maxAcir = 0;
	params->nbEch = 0;

	/* On considère qu'on est en début de période */
	params->etat = PIC_HAUT;

	return params;
}

/* Modifie la structure params en fonction de l'avancée dans la courbe d'absorption */
int checkPicPosition(s_MesureParams* params, absorp* absorp) {
	int doCalculation = 0; /* Vaut 0 si on est en cours de période, 1 sinon */

	/* Si on est à l'état haut... */
	if(params->etat == PIC_HAUT) {
		/* On regarde s'il n'existe pas un "nouveau max" depuis le début de la période */
		params->maxAcr = maxMesure(params->maxAcr, absorp->acr);
		params->maxAcir = maxMesure(params->maxAcir, absorp->acir);

		/* Si acr est négatif, c'est qu'il s'agit du milieu de la période, on passe alors en état "PIC_BAS" */
		if(absorp->acr < 0) {
			params->etat = PIC_BAS;
		}

	} else {
		/* Si on est à l'état bas... */
		/* On regarde s'il n'existe pas un "nouveau min" depuis le début de la période */
		params->minAcr = minMesure(params->minAcr, absorp->acr);
		params->minAcir = minMesure(params->minAcir, absorp->acir);

		/* Si acr est positif, c'est que la période vient de se finir, on passe alors en état "PIC_HAUT" */
		if(absorp->acr > 0) {
			params->etat = PIC_HAUT;
			doCalculation = 1;
		}
	}

	/* On incrémente le nombre d'échantillon reçu depuis le début de la période */
	params->nbEch++;

	return doCalculation;
}

/* Calcul le poul */
int calculatePoul(s_MesureParams* params) {
	/* On considère qu'on reçoit un échantillon toutes les 2ms, on a donc la relation poul = 60/(nbEch*2e-3) = 30000/nbEch */
	return 30000/params->nbEch;
}

/* Calcul le pourcentage de saturation en oxygène du sang */
int calculateSpO2(s_MesureParams* params, absorp* myAbsorp) {
	float ptpAcr = params->maxAcr - params->minAcr; /* Hauteur peek to peek d'acr */
	float ptpAcir = params->maxAcir - params->minAcir; /* Hauteur peek to peek d'acir */

	float RsIR = (ptpAcr*myAbsorp->dcir)/(ptpAcir*myAbsorp->dcr); /* Coefficient d'absorption */

	if(RsIR < 0.4) {
		/* Si RsIR < 0.4, il y a probablement une erreur dans les données, on renvoit 0*/
		return 0;
	} else if(RsIR < 1) {
		/* Si RsIR est compris entre 0.4 et 1, on approxime selon une portion de droite */
		return 110 - 25*RsIR;
	} else {
		/* Si RsIR est supérieur à 1, on approxime selon une autre portion de droite */
		return 118 - 100*RsIR/3;
	}
}

/* Effectue la mesure du poul et du SpO2 */
oxy mesure(s_MesureParams* params, absorp* myAbsorp) {
	oxy myOxy;

	/* Calcul le poul et le SpO2 */
	myOxy.spo2 = calculateSpO2(params, myAbsorp);
	myOxy.pouls = calculatePoul(params);

	/* Réinitialise les paramètres pour la prochaine période */
	params->nbEch = 0;
	params->minAcr = 0;
	params->minAcir = 0;
	params->maxAcr = 0;
	params->maxAcir = 0;

	return myOxy;
}

/* Libère la mémoire allouée pour la structure params de mesure */
void closeMesure(s_MesureParams* params) {
	free(params);
}

/* Fonction de test des fonctions de mesure */
oxy mesureTest(char* filename){
	int etat = 0; /* Etat de lecture du fichier */
	int redoMesure = 0; /* Vaut 1 si une période vient de se finir */
	absorp myAbsorp;
	oxy myOxy;

	/* Initialisation des paramètres et ouverture du fichier */
	s_MesureParams* params = initMesure();
	FILE* file = initFichier(filename);
	
	while (etat != EOF) {
		/* Tant que le fichier n'est pas fini on récupère les données */
		myAbsorp = lireFichier(file, &etat);

		/* On vérifie qu'on ne vient pas de lire après la dernière ligne */
		if (etat != EOF) {
			/* On vérifie si une période vient de se terminer */
			redoMesure = checkPicPosition(params, &myAbsorp);

			if(redoMesure) {
				/* Si c'est le cas, on fait la mesure du poul et de SpO2 */
				myOxy = mesure(params, &myAbsorp);
			}
		}
	}
	
	/* Fermeture du fichier et désallocation des paramètres */
	closeMesure(params);
	finFichier(file);

	/* Dernières valeurs calculées */
	return myOxy;
}
