#include "integration.h"

void integrationTest(char* filename) {
    int etat = 0;
    int redoMesure = 0;
    
    absorp myAbsorp;
    oxy myOxy;
    
    s_FirParams* paramsFir = initFir();
    s_IIRParameters* paramsIir = initIIR();
    s_MesureParams* paramsMesure = initMesure();
    
    FILE* file = initFichier(filename);
    do {
        myAbsorp = lireFichier(file, &etat);

        if(etat != EOF) {
            fir(paramsFir, &myAbsorp);
            iir(paramsIir, &myAbsorp);

            redoMesure = checkPicPosition(paramsMesure, &myAbsorp);

			if(redoMesure) {
				myOxy = mesure(paramsMesure, &myAbsorp);
			}

            affichage(myOxy);
        }
    } while (etat != EOF);

    finFichier(file);
    
    closeMesure(paramsMesure);
    closeFir(paramsFir);
    closeIIR(paramsIir);
}