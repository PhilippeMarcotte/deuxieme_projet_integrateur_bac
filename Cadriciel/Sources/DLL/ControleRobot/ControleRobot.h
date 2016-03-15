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
#include <vector>

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

	// Demande au robot de traiter une commande donn�e
	void traiterCommande(CommandeRobot* commande, bool provientUtilisateur);

	// Assigne le comportement correspondant � l'enum � l'IA du robot.
	void assignerComportement(TypeComportement nouveauComportement, std::string declencheur);

	// perme d'obtenir le noeud du robot. Souvent appel� par les comportements pour v�rifier des conditions.
	NoeudRobot* obtenirNoeud();

	// Fonctions permettant d'alterner entre les modes de contr�le
	void inverserModeControle();
	void passerAModeManuel();
	void passerAModeAutomatique();

	// Peut-�tre rendre ceci priv�, l'ajustement de moteurs devrait se faire par commandes
	void assignerVitessesMoteurs(double vit_G, double vit_D);
    void ajouterVitessesMoteurs(double vit_G, double vit_D);

	// Permet aux comportements de savoir si une ligne est d�tect�e
	bool ligneDetectee();

	void assignerVecteurComportements(std::vector<std::unique_ptr<ComportementAbstrait>>* vecteur);

private:
	// Fonctions pour g�rer multithreading robot
	void initialiserBoucleRobot();
	void terminerBoucleRobot();
	void boucleInfinieLogiqueRobot();

	// d�finit si oui ou non le robot est en mode manuel
	bool manuel{ false };

	// d�finit si en mode debug
	bool debug{ true };

	ArbreRendu* arbre_;
	NoeudAbstrait* table_;

	// pointeur vers le noeud du robot
	NoeudRobot* robot_;

	std::vector<std::unique_ptr<ComportementAbstrait>>* vecteurComportements_;

	// Pointeur vers le comportement pr�sentement adopt� par le robot.
	ComportementAbstrait* comportement_;

	//Mutex servant � traiter l'acc�s au comportement du robot.
	std::mutex mutexComportement;

	// Pointeur vers le thread d'ex�cution du robot
	std::unique_ptr<std::thread> logiqueRobot;
};

#endif // CONTROLE_ROBOT_H

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////