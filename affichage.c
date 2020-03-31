#include "affichage.h"

void createLock() {
	FILE* lock = fopen(LOCK_FILE_NAME, "w");
	
	if(lock == NULL) {
		printf("dans affichage.c : erreur création fichier %s\n", LOCK_FILE_NAME);
		exit(EXIT_FAILURE);
	}

	fclose(lock);
}

void deleteLock() {
	remove(LOCK_FILE_NAME);
}

int lockExists() {
	return (access(LOCK_FILE_NAME, F_OK) != -1);
}

void writeData(oxy* myOxy) {
	FILE* data = fopen(DATA_FILE_NAME, "w");

	if(data == NULL) {
		printf("dans affichage.c : erreur création fichier %s\n", DATA_FILE_NAME);
		exit(EXIT_FAILURE);
	}

	fprintf(data, "%d\n%d", myOxy->spo2, myOxy->pouls);

	fclose(data);
}

void affichage(oxy myOxy) {
	if(!lockExists()) {
		createLock();
		writeData(&myOxy);
		deleteLock();
	} else {
		printf("Attente...");
	}
}
