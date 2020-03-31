#include "lecture.h"

/* Fonction de lecture d'une ligne du fichier passé en paramètre */
absorp lecture(FILE* file_pf, int* file_state){
	absorp myAbsorp = {-1, -1, -1, -1}; /* Initialisation de l'absorption en état "invalide" */

	/* Attribue -1 à acr, dcr, acir et dcir afin de vérifier s'il y a bien 4 valeurs dans la ligne lue */
	int acr=-1, dcr=-1, acir=-1, dcir=-1;
	int isCorrupted = 0; /* Vaut 0 si la ligne n'est pas corrompue, 1 sinon*/

	do {
		/* Lit une ligne du fichier en récupérant les 4 valeurs, séparés par des virgules et se finissant par LFCR */
		*file_state = fscanf(file_pf, "%d,%d,%d,%d\n\r", &acr, &dcr, &acir, &dcir);

		/* Vérifie que les 4 valeurs acr, dcr, acir et dcir ont bien été lue */
		/* Si ce n'est pas le cas, isCorrupted = 1 */
		isCorrupted = (acr == -1 || dcr == -1 || acir == -1 || dcir == -1);

		/* Si on est pas après la dernière ligne */
		if(*file_state != EOF) {
			/* Si le fichier est corrompu on affiche un message d'erreur */
			if(isCorrupted) {
				printf("Ligne corrompue !\n");
			} else {
				/* Attribue les valeurs lues et recentrées aux champs de myAbsorp correspondants */
				myAbsorp.acr = acr - AC_REFOCUS_VALUE;
				myAbsorp.dcr = dcr;
				myAbsorp.acir = acir - AC_REFOCUS_VALUE;
				myAbsorp.dcir = dcir;
			}
		}

	} while(isCorrupted == 1 && *file_state != EOF); 
	/* On continue de lire le fichier tant qu'on a pas récupérer une ligne valide et que le fichier n'est pas fini */

	/* Renvoie myAbsorp rempli de -1 si EOF et rempli des valeurs lues en cas de ligne valide */
	return myAbsorp;
}
