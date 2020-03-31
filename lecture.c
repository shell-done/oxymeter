#include "lecture.h"

absorp lecture(FILE* file_pf, int* file_state){
	absorp myAbsorp = {-1, -1, -1, -1};
	/**file_state=EOF;*/
	/* Attribue -1 à acr, dcr, acir et dcir afin de vérifier s'il y a bien 4 valeurs dans la ligne lue */
	int acr=-1, dcr=-1, acir=-1, dcir=-1;
	int isCorrupted = 0;

	/* Lit une ligne du fichier */
	*file_state = fscanf(file_pf, "%d,%d,%d,%d\n\r", &acr, &dcr, &acir, &dcir);

	do {
		/* Lit une ligne du fichier */
		*file_state = fscanf(file_pf, "%d,%d,%d,%d\n\r", &acr, &dcr, &acir, &dcir);

		/* Vérifie que les 4 valeurs acr, dcr, acir et dcir ont bien été lue */
		isCorrupted = (acr == -1 || dcr == -1 || acir == -1 || dcir == -1);

		if(isCorrupted) {
			/* Affichage en cas de ligne corrompue */
			printf("Ligne corrompue !\n");
		} else {
			/* Attribue les valeurs lues et recentrées aux champs de myAbsorp correspondants */
			myAbsorp.acr = acr - 2048;
			myAbsorp.dcr = dcr;
			myAbsorp.acir = acir - 2048;
			myAbsorp.dcir = dcir;
		}
		

	} while(isCorrupted == 1 && *file_state != EOF);

	/* Renvoie myAbsorp rempli de -1 en cas de ligne corrompue et rempli des valeurs lues en cas de ligne valide */
	return myAbsorp;
}
