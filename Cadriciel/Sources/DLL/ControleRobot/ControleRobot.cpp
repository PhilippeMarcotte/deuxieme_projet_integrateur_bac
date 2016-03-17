///////////////////////////////////////////////////////////////////////////////
/// @file ControleRobot.cpp
/// @author Olivier St-Amour, Camille Gendreau
/// @date 20016-02-22
/// @version 2.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "ControleRobot.h"

#include <iostream>

#include "CommandeRobot.h"
#include "NoeudRobot.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"

// Inclusion pour l'Enum de comportements
#include "ComportementAbstrait.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::ControleRobot()
///
/// Constructeur
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ControleRobot::ControleRobot()
{
	arbre_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	table_ = arbre_->chercher(ArbreRenduINF2990::NOM_TABLE);
	std::shared_ptr<NoeudAbstrait> robot = arbre_->creerNoeud(ArbreRenduINF2990::NOM_ROBOT);
	table_->ajouter(robot);
	robot_ = std::static_pointer_cast<NoeudRobot>(robot).get();
	comportement_ = nullptr;
	vecteurComportements_ = nullptr;

	profil_ = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::~ControleRobot()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ControleRobot::~ControleRobot()
{
	//Nous utilisons ceci pour terminer le thread d'IA du robot
	passerAModeManuel();
	NoeudAbstrait* robot = table_->chercher(ArbreRenduINF2990::NOM_ROBOT);
	table_->effacer(robot);
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::traiterCommande()
///
/// Demande au controlleur du robot de traiter la commande donnee.
/// Le traitement de la commande d�pend du mode du robot. Si le robot est en manuel, les commandes utilisateurs sont trait�es.
/// Sinon, les commandes de l'IA sont trait�es. La commande d'inversion de mode est toujours trait�e.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::traiterCommande(CommandeRobot* commande, bool provientUtilisateur)
{
	if (commande != nullptr)
	{
		TypeCommande typeCommande = commande->obtenirTypeCommande();
        
		// Execute la commande que si elle sert � inverser le mode de contr�le.
		if ((typeCommande == INVERSER_MODE_CONTROLE) || (manuel == provientUtilisateur))
		{
			commande->executer(this);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::assignerComportement(std::shared_ptr<ComportementAbstrait> nouveauComportement)
///
/// Assigne un vecteur de comportements au controleur du robot auquel il se r�f�rera lors de son �x�cution.
///
/// @param[in] vecteur: Le pointeur au vecteur de comportements que le controlleur devra utiliser.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void ControleRobot::assignerVecteurComportements(std::vector<std::unique_ptr<ComportementAbstrait>>* vecteur){
	vecteurComportements_ = vecteur;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::assignerComportement(std::shared_ptr<ComportementAbstrait> nouveauComportement)
///
/// Assigne un nouveau comportement � suivre au robot de fa�on threadsafe et memory safe.
///
/// @param nouveauComportement: Le pointeur au comportement assign�.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::assignerComportement(TypeComportement nouveauComportement, std::string declencheur)
{
	// Nous devons v�rouiller l'acc�s au comportement temporairement pour sa modification
	mutexComportement.lock();

	//ComportementAbstrait* ancienComportement = comportement_;
	comportement_ = vecteurComportements_ -> at(nouveauComportement).get();
	
	if (profil_->obtenirOptionDebogage(DEBOGAGE_COMPORTEMENTS)){
		utilitaire::time_in_HH_MM_SS_MMM();
		std::cout << " - " << declencheur << " - " << comportement_->obtenirNomComportement() << endl;

	}

	// Assignation du controleur au comportement et initialisation
	comportement_->assignerRobot(this);
	comportement_->initialiser();

	// Lib�ration du mutex, l'acc�s au comportement redevient valide
	mutexComportement.unlock();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::inverserModeControle()
///
/// Dit au controleur de robot de gerer la passation au mode automatique.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::inverserModeControle(){
	if (manuel){
		passerAModeAutomatique();
	}
	else{
		passerAModeManuel();
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::passerAModeAutomatique()
///
/// Dit au controleur de robot de gerer la passation au mode automatique.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::passerAModeAutomatique() {
	manuel = false;
	assignerComportement(DEFAUT, "Passage au mode automatique");
	initialiserBoucleRobot();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::passerAModeManuel()
///
/// Dit au controleur de robot de gerer la passation au mode manuel.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::passerAModeManuel(){
	manuel = true;
	terminerBoucleRobot();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::initialiserBoucleRobot()
///
/// Initialise le thread de boucle d'�x�cution du robot. Appel � l'ex�cution de boucleInfinieLogiqueRobot.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::initialiserBoucleRobot(){
	logiqueRobot = std::make_unique<std::thread>(&ControleRobot::boucleInfinieLogiqueRobot, this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::terminerBoucleRobot()
///
/// Termine le thread de boucle d'�x�cution du robot. Aleterne temporairement manuel pour join le thread.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::terminerBoucleRobot(){
	
	// On garde temporairemtn la valeur de manuel
	bool man = manuel;

	// Le thread roule une fonction tant que manuel = false, alors on change la condition
	manuel = true;

	// Fermeture du thread s'il est joignable
	if ((logiqueRobot != nullptr) && (logiqueRobot->joinable())){
		logiqueRobot->join();
	}

	// Nous redonnons � manuel sa valeur de d�part
	manuel = man;
	
	traiterCommande(&CommandeRobot(ARRETER), false);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::boucleInfinieLogiqueRobot()
///
/// Appel la mise � jour du comportement tant que manuel est faux. S'ex�cute normalement dans un thread diff�rent.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::boucleInfinieLogiqueRobot()
{
	
	while (!manuel) 
	{
		if (!enPause){
			verifierCapteurs();
			comportement_->mettreAJour();
		}
		else{
			traiterCommande(&CommandeRobot(ARRETER), false);
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::boucleInfinieLogiqueRobot()
///
/// V�rifie l'�tat des capteurs � obstacles et change de comportement au besoin.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::verifierCapteurs(){
	NoeudRobot::ConteneurCapteursDistance* capteurs = robot_->obtenirCapteursDistance();
	std::string declencheur;
	for (int i = 0; i < capteurs->size(); i++)
	{
		declencheur = "Capteur distance ";
		switch (i)
		{
		case 0:
			declencheur += "droite: ";
			break;
		case 1:
			declencheur += "centre: ";
			break;
		case 2:
			declencheur += "gauche: ";
			break;
		}
		if (capteurs->at(i).obtenirEtat() == 1)
		{
			declencheur += "Zone securitaire";
			assignerComportement(capteurs->at(i).obtenirComportementZoneSecuritaire(), declencheur);
		}
		else if (capteurs->at(i).obtenirEtat() == 2)
		{
			declencheur += "Zone dangereuse";
			assignerComportement(capteurs->at(i).obtenirComportementZoneDanger(), declencheur);
		}
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::assignerVitessesMoteurs(double vit_G, double vit_D)
///
/// Assigne une nouvelle vitesse aux roues du noeud du robot
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::assignerVitessesMoteurs(double vit_G, double vit_D)
{
	robot_->assignerVitesseGauche(vit_G);
	robot_->assignerVitesseDroite(vit_D);
}


void ControleRobot::ajouterVitessesMoteurs(double vit_G, double vit_D)
{
    vit_G += robot_->obtenirVitesseGauche();
    vit_D += robot_->obtenirVitesseDroite();
    robot_->assignerVitesseGauche(vit_G);
    robot_->assignerVitesseDroite(vit_D);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::obtenirNoeud()
///
/// Retourne la r�f�rence au noeud du robot dans l'arbre de rendu.
///
/// @return Pointeur vers le noeud de noeud de rendu du robot.
///
////////////////////////////////////////////////////////////////////////
NoeudRobot* ControleRobot::obtenirNoeud(){
	return robot_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::ligneDetectee()
///
/// Fonction indiquant si le robot d�tecte une ligne. Utilis�e par les comportements pour ne pas qu'ils aient
/// � passer par le noeud du robot.
///
/// @return Si oui ou non une ligne est detectee.
///
////////////////////////////////////////////////////////////////////////
bool ControleRobot::ligneDetectee(){
	return 	obtenirNoeud()->obtenirSuiveurLigne() -> obtenirEtatCapteurs() != 0x00;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ControleRobot::ligneDetectee()
///
/// Fonction indiquant si le robot d�tecte une ligne. Utilis�e par les comportements pour ne pas qu'ils aient
/// � passer par le noeud du robot.
///
/// @return Si oui ou non une ligne est detectee.
///
////////////////////////////////////////////////////////////////////////
void ControleRobot::setEnPause(bool pause)
{
	enPause = pause;
}

bool ControleRobot::getEnPause()
{
	return enPause;
}
///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
