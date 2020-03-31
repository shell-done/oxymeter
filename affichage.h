/*!
 * \file affichage.h
 * \brief Fonctions d'affichages
 * \author Thomas BRAGUE (thomas.brague@isen-ouest.yncrea.fr)
 * \author Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * \version 1
 * \date 31/03/2020
 *
 * Fonctions liées à la création d'un fichier contenant les valeurs du poul et du SpO2
 * utilisé pour l'interface Java.
 *
 */

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "define.h"

#define DATA_FILE_NAME "Data.txt" /* Fichier de destination du poul et de SpO2 */
#define LOCK_FILE_NAME ".verrouData" /* Fichier bloquant la lecture/écriture du fichier de destination */

/*! 
 * \fn void createLock()
 * \brief Créer le fichier de lock
 * 
 * Créer le fichier défini par LOCK_FILE_NAME bloquant la lecture/écriture de DATA_FILE_NAME
 */
void createLock();

/*! 
 * \fn void deleteLock()
 * \brief Supprime le fichier de lock
 * 
 * Supprime le fichier défini par LOCK_FILE_NAME bloquant la lecture/écriture de DATA_FILE_NAME
 */
void deleteLock();

/*! 
 * \fn int lockExists()
 * \brief Vérifie si le fichier LOCK_FILE_NAME existe
 * 
 * \return 1 si le fichier existe, 0 sinon
 */
int lockExists();

/*! 
 * \fn void writeData(oxy* myOxy);
 * \brief Ecrit les informations de myOxy dans le fichier DATA_FILE_NAME
 * 
 * \param myOxy Pointeur sur une structure oxy contenant le poul et le SpO2 a écrire
 * 
 * Ecrit le SpO2 (sur la première ligne) et le poul (sur la seconde) dans le fichier DATA_FILE_NAME
 * pour l'interface Java. Doit être utilisée avec les méthodes createLock(), deleteLock() et lockExists()
 * afin de vérifier qu'il est bien possible de modifier le fichier et de le bloquer pendant la modification.
 */
void writeData(oxy* myOxy);

/*! 
 * \fn void affichage(oxy* myOxy);
 * \brief Ecrit les informations de myOxy dans le fichier DATA_FILE_NAME avec vérification et bloquage du lock
 * 
 * \param myOxy Pointeur sur une structure oxy contenant le poul et le SpO2 a écrire
 * 
 * Ecrit le SpO2 (sur la première ligne) et le poul (sur la seconde) dans le fichier DATA_FILE_NAME
 * en vérifiant que le fichier de verrou LOCK_FILE_NAME n'est pas présent, et en créant le verrou
 * pendant sa modification.
 */
void affichage(oxy myOxy);

#endif /* AFFICHAGE_H */