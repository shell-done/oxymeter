/*!
 * \file mesure.h
 * \brief Fonctions liées à la mesure du poul et du SpO2
 * \author Thomas BRAGUE (thomas.brague@isen-ouest.yncrea.fr)
 * \author Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * \version 1
 * \date 31/03/2020
 *
 */

#ifndef MESURE_H
#define MESURE_H

#include "define.h"
#include "fichiers.h"

/*! 
 * \enum e_EtatMesure
 * \brief Enumeration contenant les états de mesure de la courbe
 */
typedef enum e_EtatMesure {
    PIC_HAUT, /*!< Actuellement sur un pic haut (supérieur à 0) */
    PIC_BAS /*!< Actuellement sur un pic bas (inférieur à 0) */
} e_EtatMesure;

/*! 
 * \struct s_MesureParams
 * \brief Structure contenant les paramètres pour les fonctions de mesure
 */
typedef struct s_MesureParams {
    float minAcr, maxAcr; /*!< Minimum et maximum d'acr sur la période courante */
    float minAcir, maxAcir; /*!< Minimum et maximum d'acir sur la période courant */
    int nbEch; /*!< Nombre d'échantillon traités depuis le début de la période */

    e_EtatMesure etat; /*!< Etat de la période actuelle */
} s_MesureParams;

/*! 
 * \fn float maxMesure(float a, float b)
 * \brief Retourne le maximum entre a et b
 * 
 * \param a Un nombre flottant quelconque
 * \param b Un nombre flottant quelconque
 * 
 * \return Le maximum de {a,b}
 */
float maxMesure(float a, float b);

/*! 
 * \fn float minMesure(float a, float b)
 * \brief Retourne le minimum entre a et b
 * 
 * \param a Un nombre flottant quelconque
 * \param b Un nombre flottant quelconque
 * 
 * \return Le minimum de {a,b}
 */
float minMesure(float a, float b);

/*! 
 * \fn s_MesureParams* initMesure()
 * \brief Initialise les paramètres utilisée par les fonctions de mesure
 * 
 * \return Un pointeur sur une sructure s_MesureParams allouée dynamiquement
 * 
 * Initialise toutes les valeurs de la structure à 0 et l'etat à "PIC_HAUT"
 */
s_MesureParams* initMesure();

/*! 
 * \fn int checkPicPosition(s_MesureParams* params, absorp* myAbsorp)
 * \brief Modifie la structure params en fonction de l'avancée dans la courbe d'absorption
 * 
 * \param params Un pointeur sur la structure contenant les paramètres de mesure
 * \param myAbsorb Un pointeur sur la structure des valeurs d'absorption
 * 
 * \return 1 si une période vient de se terminer, 0 sinon
 * 
 * Incremente le compteur d'échantillon à chaque mesure et regarde s'il existe un nouveau
 * maximum sur cette période. Une période des considérée finie lorsque acr est devenu
 * négative alors que l'état était "PIC_HAUT" puis qu'acr est devenu positif alors que l'état était "PIC_BAS"
 */
int checkPicPosition(s_MesureParams* params, absorp* myAbsorp);

/*! 
 * \fn int calculatePoul(s_MesureParams* params)
 * \brief Calcul le poul
 * 
 * \param params Un pointeur sur la structure contenant les paramètres de mesure
 * 
 * \return Le poul arrondi à l'entier inférieur
 * 
 * Calcul le poul en sachant qu'un échantillon est reçu toute les 2ms
 */
int calculatePoul(s_MesureParams* params);

/*! 
 * \fn int calculateSpO2(s_MesureParams* params, absorp* myAbsorp)
 * \brief Calcul le pourcentage de saturation en oxygène du sang
 * 
 * \param params Un pointeur sur la structure contenant les paramètres de mesure
 * \param myAbsorb Un pointeur sur la structure des valeurs d'absorption
 * 
 * \return Le pourcentage de saturation en oxygène du sang (SpO2) arrondi à l'entier inférieur
 * 
 * Calcul le SpO2 en faisant une approximation de droite entre 0.4 et 1, et entre 1 et 3
 */
int calculateSpO2(s_MesureParams* params, absorp* myAbsorp);

/*! 
 * \fn oxy mesure(s_MesureParams* params, absorp* myAbsorp)
 * \brief Effectue la mesure du poul et du SpO2
 * 
 * \param params Un pointeur sur la structure contenant les paramètres de mesure
 * \param myAbsorb Un pointeur sur la structure des valeurs d'absorption
 * 
 * \return Une structure oxy contenant le poul et le SpO2 de la période précédente
 * 
 * Effectue la mesure du poul et du SpO2 et réinitialise les valeurs de params pour
 * la prochaine période
 */
oxy mesure(s_MesureParams* params, absorp* myAbsorp);

/*! 
 * \fn void closeMesure(s_MesureParams* params);
 * \brief Libère la mémoire allouée pour la structure params de mesure
 * 
 * \param params Un pointeur sur la structure contenant les paramètres de mesure
 */
void closeMesure(s_MesureParams* params);

/*! 
 * \fn absorp mesureTest(char* filename);
 * \brief Fonction de test des fonctions de mesure
 * 
 * \param filename Le nom du fichier à lire contenant les valeurs à traiter
 * 
 * \return La dernière valeur d'oxy calculée
 */
oxy mesureTest(char* filename);

#endif /* MESURE_H */