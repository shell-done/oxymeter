/*!
 * \file iir.h
 * \brief Fonctions liées au filtrage IIR
 * \author Thomas BRAGUE (thomas.brague@isen-ouest.yncrea.fr)
 * \author Alexandre THOMAS (alexandre.thomas@isen-ouest.yncrea.fr)
 * \version 1
 * \date 31/03/2020
 *
 * Fonctions liées au filtrage à réponse impulsionnelle infinie
 *
 */

#ifndef IIR_H
#define IIR_H

#include "define.h"
#include "fichiers.h"

#define COEFF_ALPHA 0.992 /* Coefficient alpha utilisé dans le calcul */

/*! 
 * \struct s_IirParams
 * \brief Structure contenant les paramètres pour les fonctions IIR
 */
typedef struct s_IirParams {
    float lastacrX; /*!< Dernière valeur acr avant filtrage */
    float lastacrY; /*!< Dernière valeur acr après filtrage */
    float lastacirX; /*!< Dernière valeur acir avant filtrage */
    float lastacirY; /*!< Dernière valeur acir après filtrage */
} s_IirParams;


/*! 
 * \fn s_IirParams* initIir()
 * \brief Initialise les paramètres utilisée par les fonctions IIR
 * 
 * Initialise les variables à 0
 * 
 * \return Un pointeur sur une sructure s_IirParams allouée dynamiquement
 */
s_IirParams* initIir();

/*! 
 * \fn void void iir(s_IirParams* parameters, absorp* myAbsorp)
 * \brief Applique la fonction iir aux paramètres acr et acir de myAbsorb
 * 
 * \param parameters Un pointeur sur la structure contenant les paramètres IIR
 * \param myAbsorb Un pointeur sur la structure des valeurs d'absorption
 * 
 * Applique la fonction iir aux paramètres acr et acir de myAbsorb et change les
 * valeurs précédentes contenues dans les paramètres IIR
 */
void iir(s_IirParams* parameters, absorp* myAbsorp);

/*! 
 * \fn closeIIR(s_IirParams* parameters)
 * \brief Libère la mémoire allouée pour la structure params de IIR
 * 
 * \param parameters Un pointeur sur la structure contenant les paramètres IIR
 */
void closeIIR(s_IirParams* parameters);

/*! 
 * \fn absorp iirTest(char* filename);
 * \brief Fonction de test du filtrage IIR
 * 
 * \param filename Le nom du fichier à lire contenant les valeurs à filtrer
 * 
 * \return La dernière valeur absorp calculée
 */
absorp iirTest(char* filename);

#endif /* IIR_H */