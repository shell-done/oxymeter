#include "affichage.h"

/* Créer le fichier de lock */
void createLock() {
	/* Créer le fichier de lock s'il n'existe pas*/
	FILE* lock = fopen(LOCK_FILE_NAME, "w");
	
	/* Vérification qu'il n'y a pas d'erreur à la création du fichier */
	if(lock == NULL) {
		printf("dans affichage.c : erreur création fichier %s\n", LOCK_FILE_NAME);
		exit(EXIT_FAILURE);
	}

	fclose(lock);
}

/* Supprime le fichier de lock */
void deleteLock() {
	remove(LOCK_FILE_NAME);
}

/* Vérifie si le fichier LOCK_FILE_NAME existe */
int lockExists() {
	/*Si access(LOCK_FILE_NAME, F_OK) == -1 le fichier n'existe pas, sinon il existe*/
	return (access(LOCK_FILE_NAME, F_OK) != -1);
}

/* Ecrit les informations de myOxy dans le fichier DATA_FILE_NAME */
void writeData(oxy* myOxy) {
	/* Créer le fichier data s'il n'existe pas et le prépare en lecture*/
	FILE* data = fopen(DATA_FILE_NAME, "w");

	/* Vérification qu'il n'y a pas d'erreur à la création du fichier */
	if(data == NULL) {
		printf("dans affichage.c : erreur création fichier %s\n", DATA_FILE_NAME);
		exit(EXIT_FAILURE);
	}

	/* Ecrit le SpO2 et le poul dans le fichier */
	fprintf(data, "%d\n%d", myOxy->spo2, myOxy->pouls);

	fclose(data);
}

/* Ecrit les informations de myOxy dans le fichier DATA_FILE_NAME avec vérification et bloquage du lock */
void affichage(oxy myOxy) {
	/* Si le lock n'existe pas */
	if(!lockExists()) {
		/* On le créer, on écrit les données puis on le supprime */
		createLock();
		writeData(&myOxy);
		deleteLock();
	} else {
		/* Sinon on affiche un message d'attente */
		printf("Attente...\n");
	}
}
