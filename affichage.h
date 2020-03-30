#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "define.h"

#define DATA_FILE_NAME "Data.txt"
#define LOCK_FILE_NAME ".verrouData"

/** 
 * Fonctions 
 */
void createLock();
void deleteLock();
int lockExists();
void writeData(oxy* myOxy);
void affichage(oxy myOxy);

#endif /* AFFICHAGE_H */