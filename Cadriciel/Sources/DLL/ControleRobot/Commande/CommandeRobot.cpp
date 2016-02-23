///////////////////////////////////////////////////////////////////////////
/// @file CommandeRobot.cpp
/// @author Philippe Marcotte
/// @date 2016-02-20
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "CommandeRobot.h"

///////////////////////////////////////////////////////////////////////////
/// @fn Commande::CommandeRobot(Commande commande)
/// @brief Constructeur par param�tre d'une CommandeRobot.
///		   Elle d�finie la puissance des moteurs selon le type de commande.
///
///
/// @author Philippe Marcotte
/// @date 2016-02-20
///////////////////////////////////////////////////////////////////////////
CommandeRobot::CommandeRobot(TypeCommande commande){
	typeCommande_ = commande;
	switch (commande)
	{
	case AVANCER:
		puissanceMoteurD_ = 100;
		puissanceMoteurG_ = 100;
		break;
	case RECULER:
		puissanceMoteurD_ = -100;
		puissanceMoteurG_ = -100;
		break;
	case ROTATION_GAUCHE:
		puissanceMoteurD_ = 100;
		puissanceMoteurG_ = -100;
		break;
	case ROTATION_DROITE:
		puissanceMoteurD_ = -100;
		puissanceMoteurG_ = 100;
		break;
	default:
		break;
	}
}

///////////////////////////////////////////////////////////////////////////
/// @fn void CommandeRobot::executer(NoeudRobot* noeud)
/// @brief Fonction ex�cutant la commande en modifiant les attributs du robot.
///
///
/// @author Philippe Marcotte
/// @date 2016-02-20
///////////////////////////////////////////////////////////////////////////
void CommandeRobot::executer(ControleRobot* ia){
	if (typeCommande_ == INVERSER_MODE_CONTROLE)
		ia->inverserModeControle();
	ia->assignerVitessesMoteurs( puissanceMoteurG_, puissanceMoteurD_);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////