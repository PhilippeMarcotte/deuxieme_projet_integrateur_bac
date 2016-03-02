///////////////////////////////////////////////////////////////////////////////
/// @file Comportement.h
/// @author Olivier St-Amour
/// @date 20016-02-22
/// @version 2.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef CONTROLE_ROBOT_H
#define CONTROLE_ROBOT_H

#include <memory>

class ComportementAbstrait;
class CommandeRobot;
class NoeudAbstrait;
class NoeudRobot;
class ArbreRendu;


///////////////////////////////////////////////////////////////////////////
/// @class ControleRobot
/// @brief Classe qui permet de contr�ler le robot. 
///
///        Cette classe permet de contr�ler le robot de fa�on automatique ou 
///		   de fa�on manuelle em recevant des commandes.
///		   
/// @author Olivier St-Amour
/// @date 2016-02-22
///////////////////////////////////////////////////////////////////////////
class ControleRobot
{
public:
	ControleRobot();
	~ControleRobot();
	
	void traiterCommande(CommandeRobot* commande);

	void passerAuProchainComportement();


	void inverserModeControle();
	void passerAModeManuel();
	void passerAModeAutomatique();

	void assignerVitessesMoteurs(double vit_G, double vit_D);

private:
	bool manuel{ false };

	ArbreRendu* arbre_;
	NoeudAbstrait* table_;
	NoeudRobot* robot_;
	std::shared_ptr<ComportementAbstrait> comportement;

	// devrait etre migree vers les capteurs
	bool ligneDetectee();
};

#endif // CONTROLE_ROBOT_H

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////