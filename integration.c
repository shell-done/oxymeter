#include "integration.h"

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

            /* Si une période vient de se finir, on recalcul le poul et le Spo2 */
			if(redoMesure) {
				myOxy = mesure(paramsMesure, &myAbsorp);
			}

            /* Ecriture des données calculées dans le fichier data.txt */
            affichage(myOxy);
        }
    } while (etat != EOF);

    /* Fermeture du fichier */
    finFichier(file);
    
    /* Désallocation des paramètres utilisés pour les fonctions */
    closeMesure(paramsMesure);
    closeFir(paramsFir);
    closeIIR(paramsIir);
}