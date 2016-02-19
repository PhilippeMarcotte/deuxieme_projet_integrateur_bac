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

enum Commande{
	AVANCER,
	RECULER,
	ROTQ,
	ROTDROITE,
	MODEMANUEL,
	MODEAUTO
};

///////////////////////////////////////////////////////////////////////////
/// @class CommandeRobot
/// @brief Classe qui repr�sente une commande qu'on envoie au robot
///		   pour changer ses d�placements ou passer du mode manuel au mode automatique
///
///
/// @author Philippe Marcotte
/// @date 2016-02-16
///////////////////////////////////////////////////////////////////////////
class CommandeRobot{
	public:

		/// Constructeur par param�tre permettant de changer la puissance des moteurs du robot
		CommandeRobot(int puissanceMoteurG, int puissanceMoteurD);

		/// Constructeur par param�tre permettant de changer le mode d'utilisation du robot
		CommandeRobot(bool changeAManuel);

		/// Execute les changements associ�s � la commande sur le robot
		void executer(NoeudRobot* noeud);

	private:
		/// Repr�sente la puissance du moteur de gauche
		int puissanceMoteurG_{ 0 };

		/// Repr�sente la puissance du moteur de droite
		int puissanceMoteurD_{ 0 };

		/// Repr�sente si on change vesr le mode d'utilisation manuel ou non
		bool changeAManuel_{ false };
};

#endif/// COMMANDE_ROBOT_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////