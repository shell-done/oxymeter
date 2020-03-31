#include "integration.h"

/* Initialise les paramètres utilisée pour lisser les valeurs */
s_lastOxyParams* initLastOxy() {
    int i;

    /* Alloue dynamiquement la structure */
    s_lastOxyParams* params = malloc(sizeof(s_lastOxyParams));

    /* Initialise le buffer circulaire à -1 */
    for(i=0; i<10; i++) {
        params->lastOxy[i].pouls = -1;
        params->lastOxy[i].spo2 = -1;
    }

    /* Initialise l'index courant à 0 */
    params->currentIdx = 0;

    return params;
}

/* Ajoute une nouvelle valeur oxy dans le buffer circulaire */
void pushLastOxy(s_lastOxyParams* param, oxy* myOxy) {
    /* Ajoute l'oxy à l'index courant */
    param->lastOxy[param->currentIdx].pouls = myOxy->pouls;
    param->lastOxy[param->currentIdx].spo2 = myOxy->spo2;

    /* Décalage de l'index */
    param->currentIdx = (param->currentIdx+1)%10;
}

/* Calcul la moyenne des 10 derniers oxy récupérés */
oxy lastOxyAverage(s_lastOxyParams* param) {
    int i;
    int nbOfValidValues = 0; /* Nombre d'oxy valides (dont les valeurs sont diff de -1) */
    oxy avgOxy = {0,0};

    for(i=0; i<10; i++) {
        /* Si l'oxy est valide (toujours vrai après 10 périodes) */
        if(param->lastOxy[i].pouls != -1) {
            /* On l'ajoute pour calculer la somme */
            avgOxy.pouls += param->lastOxy[i].pouls;
            avgOxy.spo2 += param->lastOxy[i].spo2;

            nbOfValidValues++;
        }
    }

    /* On fait la moyenne des derniers oxy valide */
    avgOxy.pouls /= nbOfValidValues;
    avgOxy.spo2 /= nbOfValidValues;

    return avgOxy;
}

/* Libère la mémoire allouée pour la structure params des 10 derniers oxy */
void closeLastOxy(s_lastOxyParams* params) {
    free(params);
}

/* Fonction de test d'integration des autres fonctions */
void integrationTest(char* filename) {
    int etat = 0; /* Etat du fichier (vaut EOF si en fin de fichier) */
    int redoMesure = 0; /* 0: En cours de période, 1: Fin de période, le poul/SpO2 peuvent être recalculés*/
    
    absorp myAbsorp; /* Absorptions récupérées */
    oxy myOxy; /* Oxymétrie/Poul calculés */
    
    /* Initialisation des structure pour les calculs */
    s_FirParams* paramsFir = initFir();
    s_IirParams* paramsIir = initIir();
    s_MesureParams* paramsMesure = initMesure();
    s_lastOxyParams* paramsLastOxy = initLastOxy();
    
    /* Ouverture du fichier */
    FILE* file = initFichier(filename);
    do {
        /* Lecture d'une ligne */
        myAbsorp = lireFichier(file, &etat);

        /* Si etat != EOF, alors c'est une ligne valide */
        if(etat != EOF) {
            /* Filtrage des données via FIR et IIR */
            fir(paramsFir, &myAbsorp);
            iir(paramsIir, &myAbsorp);

            /* Vérifie l'avancement dans la période */
            redoMesure = checkPicPosition(paramsMesure, &myAbsorp);

            /* Si une période vient de se finir, on recalcul le poul et le Spo2 et on l'affiche*/
			if(redoMesure) {
				myOxy = mesure(paramsMesure, &myAbsorp);
                
                /* Ajoute le dernier oxy à la liste */
                pushLastOxy(paramsLastOxy, &myOxy);

                /* Calcul la moyenne des 10 derniers oxy */
                myOxy = lastOxyAverage(paramsLastOxy);
                
                /* Affiche cette moyenne */
                affichage(myOxy);
			}
        }
    } while (etat != EOF);

    /* Fermeture du fichier */
    finFichier(file);
    
    /* Désallocation des paramètres utilisés pour les fonctions */
    closeLastOxy(paramsLastOxy);
    closeMesure(paramsMesure);
    closeFir(paramsFir);
    closeIIR(paramsIir);
}