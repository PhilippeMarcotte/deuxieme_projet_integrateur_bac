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

#include "NoeudRobot.h"

enum Commande
{
	MODE_MANUEL,
	MODE_AUTO,
	AVANCER,
	RECULER,
	ROTATION_GAUCHE,
	ROTATION_DROITE
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
		CommandeRobot(Commande commande);

		/// Execute les changements associ�s � la commande sur le robot
		void executer(NoeudRobot* noeud);

	private:
		/// Repr�sente la nouvelle puissance du moteur de gauche
		int puissanceMoteurG_{ 0 };

		/// Repr�sente la nouvelle puissance du moteur de droite
		int puissanceMoteurD_{ 0 };

		/// Repr�sente si l'on change le mode d'utilisation du robot ou non. Si oui, celle-ci correspondra � un des deux modes d'utilisation (MODE_MANUEL ou MODE_AUTO)
		Commande typeCommande_;
};

#endif/// COMMANDE_ROBOT_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////