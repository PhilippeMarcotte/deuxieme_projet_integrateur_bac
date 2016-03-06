///////////////////////////////////////////////////////////////////////////
/// @file CommandeRobot.h
/// @author Philippe Marcotte
/// @date 2016-02-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef COMMANDE_ROBOT_H
#define COMMANDE_ROBOT_H

#include "ControleRobot.h"

enum TypeCommande
{
	INVERSER_MODE_CONTROLE,
	AVANCER,
	RECULER,
	ROTATION_GAUCHE,
	ROTATION_DROITE,
	DEVIATION_GAUCHE,
	DEVIATION_DROITE,
	ARRETER
};

///////////////////////////////////////////////////////////////////////////
/// @class CommandeRobot
/// @brief Classe qui repr�sente une commande qu'on envoie au robot
///		   pour changer ses d�placements ou passer du mode manuel au mode automatique.
///		   Celle-ci fonctionne selon les principes du patron Visiteur.
///
///
/// @author Philippe Marcotte
/// @date 2016-02-16
///////////////////////////////////////////////////////////////////////////
class CommandeRobot{
	public:
		/// Constructeur par param�tre permettant de changer la puissance des moteurs du robot ou de changer le mode d'utilisation de celui-ci
		CommandeRobot(TypeCommande commande);

		/// Execute les changements associ�s � la commande sur le robot
		void executer(ControleRobot* ia);

		void assignerVitessesMoteurs(double vit_g, double vit_d);

		inline TypeCommande obtenirTypeCommande();

		inline bool provientUtilisateur();

	private:
		/// Repr�sente la nouvelle vitesse du moteur de gauche
		double vitesseMoteurG_{ 0 };

		/// Repr�sente la nouvelle vitesse du moteur de droite
		double vitesseMoteurD_{ 0 };

		/// Repr�sente si l'on change le mode d'utilisation du robot ou non. Si oui, celle-ci correspondra � un des deux modes d'utilisation (MODE_MANUEL ou MODE_AUTO)
		TypeCommande typeCommande_;
};


///////////////////////////////////////////////////////////////////////////
/// @fn CommandeRobot::obtenirTypeCommande()
/// @brief Fonction permettant d'obtenir la nature de la commande.
///
/// @return Retourne le type de commande associ�.
///
/// @author Philippe Marcotte
/// @date 2016-02-20
///////////////////////////////////////////////////////////////////////////
inline TypeCommande CommandeRobot::obtenirTypeCommande()
{
	return typeCommande_;
}

#endif/// COMMANDE_ROBOT_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////