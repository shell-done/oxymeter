/*!
 * \file integration.h
 * \brief Fonctions liées au test d'integrations des autres fonctions
 * \author Thomas BRAGUE (thomas.brague@isen-ouest.yncrea.fr)
 * \author Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * \version 1
 * \date 31/03/2020
 *
 * Fonctions liées au test d'integrations des fonctions fir, iir, mesure et affichage
 *
 */

#ifndef INTEGRATION_H
#define INTEGRATION_H

#include "define.h"
#include "fichiers.h"
#include "fir.h"
#include "iir.h"
#include "mesure.h"
#include "affichage.h"

/*! 
 * \struct s_lastOxy
 * \brief Structure contenant les 10 derniers oxy calculés
 */
typedef struct s_lastOxyParams {
    oxy lastOxy[10];
    int currentIdx;
} s_lastOxyParams;


/*! 
 * \fn s_lastOxyParams* initLastOxy()
 * \brief Initialise les paramètres utilisée pour lisser les valeurs
 * 
 * \return Un pointeur sur une sructure s_lastOxyParams allouée dynamiquement
 * 
 * Initialise les tableaux à -1 et l'index courant à 0
 */
s_lastOxyParams* initLastOxy();

/*! 
 * \fn void pushLastOxy(s_lastOxyParams* param, oxy* myOxy)
 * \brief Ajoute une nouvelle valeur oxy dans le buffer circulaire
 * 
 * \param params Un pointeur sur la structure contenant les 10 derniers Oxy
 * \param myOxy Un pointeur sur la structure des valeurs d'absorption
 * 
 * Remplace la plus ancienne valeur du buffer par la nouvelle et décale de 1
 * l'index courant
 */
void pushLastOxy(s_lastOxyParams* param, oxy* myOxy);

/*! 
 * \fn oxy lastOxyAverage(s_lastOxyParams* param)
 * \brief Calcul la moyenne des 10 derniers oxy récupérés
 * 
 * \param param Un pointeur sur la structure contenant les 10 derniers Oxy
 * 
 * \return Un oxy dont le poul (respectivement SpO2) est la moyenne des 10 derniers pouls (respectivement SpO2)
 * 
 * Calcul la moyenne des 10 derniers oxy récupérés. Si moins de 10 oxy ont été 
 * récupéré, renvoit la moyenne de ces n derniers oxy
 */
oxy lastOxyAverage(s_lastOxyParams* param);

/*! 
 * \fn void closeLastOxy(s_lastOxy* params);
 * \brief Libère la mémoire allouée pour la structure params des 10 derniers oxy
 * 
 * \param params Un pointeur sur la structure contenant les 10 derniers oxy
 */
void closeLastOxy(s_lastOxyParams* params);

/*! 
 * \fn void integrationTest(char* filename)
 * \brief Fonction de test d'integration des autres fonctions
 * 
 * \param filename Le nom du fichier à lire contenant les valeurs à filtrer
 * 
 * Lis les données d'absorption depuis le fichier filename puis les filtres avec les fonctions fir et iir.
 * Des données filtrées sont déduis l'oxymétrie et le poul via la fonction mesure, ces données sont ensuites
 * écrites dans le fichier Data.txt par la fonction affichage
 */
void integrationTest(char* filename);

#endif /* INTEGRATION_H */