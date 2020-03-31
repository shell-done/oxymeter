#define _DEFAULT_SOURCE /* Permet d'autoriser la fonction 'usleep()' utilisée pour la simulation */

#include "lecture.h"
#include "fir.h"
#include "iir.h"
#include "mesure.h"
#include "affichage.h"

int main() {
    int etat = 0; /* Etat du fichier (vaut EOF si en fin de fichier) */
    int redoMesure = 0; /* 0: En cours de période, 1: Fin de période, le poul/SpO2 peuvent être recalculés*/
    
    absorp myAbsorp; /* Absorptions récupérées */
    oxy myOxy; /* Oxymétrie/Poul calculés */
    
    /* Initialisation des structure pour les calculs */
    s_FirParams* paramsFir = initFir();
    s_IirParams* paramsIir = initIir();
    s_MesureParams* paramsMesure = initMesure();

    printf("### Début du programme ###\n");
    printf("--------------------------\n");
    printf("Projet CIR 3 - ISEN Yncréa Brest - 2020\n");
    printf("Réalisé par Thomas BRAGUE et Alexandre THOMAS\n");
    printf("--------------------------\n");
    printf("Fonctionnement en cours...\n");
    
    /* Ouverture du fichier */
    FILE* file = initFichier("records/record1_bin.dat");
    do {
        /* Lecture d'une ligne */
        myAbsorp = lecture(file, &etat);

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
                affichage(myOxy);
			}
        }

        /* Attente de 2ms pour simuler la réception des échantillons */
        usleep(2000);
    } while (etat != EOF);

    printf("### Fin du programme ###\n");

    /* Fermeture du fichier */
    finFichier(file);
    
    /* Désallocation des paramètres utilisés pour les fonctions */
    closeMesure(paramsMesure);
    closeFir(paramsFir);
    closeIIR(paramsIir);

    /* Fin du programme, éxecution réussie */
    return EXIT_SUCCESS;
}
