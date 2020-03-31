/*!
 * \file fir.h
 * \brief Fonctions liées au filtrage FIR
 * \author Thomas BRAGUE (thomas.brague@isen-ouest.yncrea.fr)
 * \author Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * \version 1
 * \date 31/03/2020
 *
 * Fonctions liées au filtrage à réponse impulsionnelle finie
 *
 */

#ifndef FIR_H
#define FIR_H

#include "define.h"
#include "fichiers.h"

/*! 
 * \struct s_FirParams
 * \brief Structure contenant les paramètres pour les fonctions FIR
 */
typedef struct s_FirParams {
    float acrSamples[51]; /*!< Buffer circulaire des 51 dernières valeurs (avant filtrage)*/
    float acirSamples[51]; /*!< Buffer circulaire des 51 dernières valeurs (avant filtrage)*/
    int currentIdx; /* Index courant du buffer circulaire (compris entre 0 et 50 inclus) */
} s_FirParams;

/*! 
 * \fn s_FirParams* initFir()
 * \brief Initialise les paramètres utilisée par les fonctions FIR
 * 
 * Initialise les tableaux à 0 et l'index courant à 0
 * 
 * \return Un pointeur sur une sructure s_FirParams allouée dynamiquement
 */
s_FirParams* initFir();

/*! 
 * \fn void pushNewValue(s_FirParams* params, absorp* myAbsorb)
 * \brief Ajoute une nouvelle valeur acr/acir dans le buffer circulaire
 * 
 * \param params Un pointeur sur la structure contenant les paramètres FIR
 * \param myAbsorb Un pointeur sur la structure des valeurs d'absorption
 * 
 * Remplace la plus ancienne valeur du buffer par la nouvelle et décale de 1
 * l'index courant
 */
void pushNewValue(s_FirParams* params, absorp* myAbsorb);

/*! 
 * \fn void fir(s_FirParams* params, absorp* myAbsorb)
 * \brief Applique la fonction fir aux paramètres acr et acir de myAbsorb
 * 
 * \param params Un pointeur sur la structure contenant les paramètres FIR
 * \param myAbsorb Un pointeur sur la structure des valeurs d'absorption
 * 
 * Applique la fonction fir aux paramètres acr et acir de myAbsorb et ajoute
 * les nouvelles valeurs aux buffers circulaires
 */
void fir(s_FirParams* params, absorp* myAbsorb);

/*! 
 * \fn void closeFir(s_FirParams* params);
 * \brief Libère la mémoire allouée pour la structure params de FIR
 * 
 * \param params Un pointeur sur la structure contenant les paramètres FIR
 */
void closeFir(s_FirParams* params);

/*! 
 * \fn absorp firTest(char* filename);
 * \brief Fonction de test du filtrage FIR
 * 
 * \param filename Le nom du fichier à lire contenant les valeurs à filtrer
 * 
 * \return La dernière valeur absorp calculée
 */
absorp firTest(char* filename);

#endif /* FIR_H */