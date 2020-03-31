/*!
 * \file lecture.h
 * \brief Fonctions liées à la lecture avec prise en compte des erreurs
 * \author Thomas BRAGUE (thomas.brague@isen-ouest.yncrea.fr)
 * \author Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * \version 1
 * \date 31/03/2020
 *
 * Fonctions liées à la lecture avec prise en compte des erreurs, simulant
 * la lecture sur un port USB
 *
 */

#ifndef LECTURE_H
#define LECTURE_H

#include "define.h"

#define AC_REFOCUS_VALUE 2048 /* Valeur de recentrage des paramètres AC */

/*! 
 * \fn absorp lecture(FILE* file_pf, int* file_state);
 * \brief Fonction de lecture d'une ligne du fichier passé en paramètre
 * 
 * \param file_pf Un pointeur sur le fichier ouvert à lire
 * \param file_state Un pointeur sur un entier décrivant le statut de lecture du fichier, vaut EOF si la lecture est terminée
 * 
 * \return absorp Les prochaines valeurs d'absorptions non corrompus. Les 4 valeurs sont mises à -1 s'il s'agit de la dernière ligne
 * 
 * Lis les prochaines données d'absorption non corrompus depuis le fichier file_pf (doit être ouvert avec fopen auparavant)
 */
absorp lecture(FILE* file_pf, int* file_state);

#endif /* LECTURE_H */