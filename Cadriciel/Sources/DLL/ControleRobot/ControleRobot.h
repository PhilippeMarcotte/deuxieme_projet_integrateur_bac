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
#include <thread>
#include "ComportementAbstrait.h"
#include <mutex>

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

	void traiterCommande(CommandeRobot* commande, bool provientUtilisateur);

	void assignerComportement(eComportement nouveauComportement);


	void inverserModeControle();
	void passerAModeManuel();
	void passerAModeAutomatique();

	// Fonctions pour g�rer multithreading robot
	void initialiserBoucleRobot();
	void terminerBoucleRobot();
	void boucleInfinieLogiqueRobot();

	void assignerVitessesMoteurs(double vit_G, double vit_D);

private:
	bool manuel{ false };

	ArbreRendu* arbre_;
	NoeudAbstrait* table_;
	NoeudRobot* robot_;

	// Pointeur vers le comportement pr�sentement adopt� par le robot.
	ComportementAbstrait* comportement_;

	//Mutex servant � traiter l'acc�s au comportement du robot.
	std::mutex mutexComportement;

	// Pointeur vers le thread d'ex�cution du robot
	std::unique_ptr<std::thread> logiqueRobot;

	// devrait etre migree vers les capteurs
	bool ligneDetectee();
};

#endif // CONTROLE_ROBOT_H

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////