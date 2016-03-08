///////////////////////////////////////////////////////////////////////////////
/// @file ComportementEvitement.cpp
/// @author Olivier St-Amour
/// @date 20016-02-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "ComportementEvitement.h"
#include "ControleRobot.h"
#include "NoeudRobot.h"
#include "CommandeRobot.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementEvitement::ComportementEvitement(ControleRobot* controleRobot)
///
/// Constructeur
///
/// @param[in] controleRobot: Pointeur vers le controleur du robot auquel le comportement est assign�
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementEvitement::ComportementEvitement(ControleRobot* controleRobot) :ComportementAbstrait(controleRobot)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementEvitement::~ComportementEvitement()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementEvitement::~ComportementEvitement()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementEvitement::initialiser()
///
/// Implementation qui ramene le comportement a son etat initial
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementEvitement::initialiser(){
	startTime_ = time(nullptr);
	angleCible_ = controleRobot_->obtenirNoeud()->obtenirAngleRotation() + maxAngle_;
	gauche = maxAngle_ >= 0;
	ignorerLigne_ = true;

}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDefaut::mettreAJour()
///
/// V�rifie si le comportement doit changer ou proc�der � une prochaine action sur sa liste.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementEvitement::mettreAJour(){

	//TODO: Impl�menter l'exception
	//Impl�mentation de l'exception Rapport d'�licitation p.22
	if (controleRobot_->ligneDetectee()){
		if (!ignorerLigne_){
			controleRobot_->assignerComportement(SUIVIDELIGNE);
		}
	}
	else{
		ignorerLigne_ = false;
	}

	// tant que le timer n'est pas expir�, recule, sinon pivoter
	if (difftime(time(nullptr), startTime_) < maxTemps_){
		controleRobot_->traiterCommande(&CommandeRobot(RECULER), false);
	}
	else {

		bool angleAtteinte = false;

		// Rotation du robot
		if (gauche){
			// D�vier � gauche et v�rifier angle
			controleRobot_->traiterCommande(&CommandeRobot(ROTATION_GAUCHE), false);
			angleAtteinte = controleRobot_->obtenirNoeud()->obtenirAngleRotation() > angleCible_;
		}
		else{
			// D�vier � droite et v�rifier angle
			controleRobot_->traiterCommande(&CommandeRobot(ROTATION_DROITE), false);
			angleAtteinte = controleRobot_->obtenirNoeud()->obtenirAngleRotation() < angleCible_;
		}

		if (angleAtteinte){
			// TODO: Assigner le comportement suivant
			controleRobot_->assignerComportement(DEFAUT);
		}
	}

}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementEvitement::setAngleMaxRotation(double angle)
///
/// Assigne un nouvel angle relatif a atteindre apr�s le recul avant de changer de comportement.
///
/// @param[in] angle: Le nouvel angle relatif que le comportment doit atteindre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementEvitement::setAngleMaxRotation(double angle){
	maxAngle_ = angle;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementEvitement::setTempsMaxReculons(double temps)
///
/// Assigne la duree du recul du robot avant de changer son angle.
///
/// @param[in] temps: Le nouvel angle relatif que le comportment doit atteindre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementEvitement::setTempsMaxReculons(double temps){
	maxTemps_ = temps;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
