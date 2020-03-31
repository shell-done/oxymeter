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