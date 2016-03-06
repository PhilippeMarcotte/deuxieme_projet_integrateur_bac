///////////////////////////////////////////////////////////////////////////////
/// @file ComporterDeviation.cpp
/// @author Olivier St-Amour
/// @date 20016-02-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "ComportementDeviation.h"
#include "ControleRobot.h"
#include "CommandeRobot.h"
#include "NoeudRobot.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::ComportementDeviation()
///
/// Constructeur
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementDeviation::ComportementDeviation(ControleRobot* controleRobot) :ComportementAbstrait(controleRobot)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::~ComportementDeviation()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementDeviation::~ComportementDeviation()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::initialiser()
///
/// Implementation qui ramene le comportement a son etat initial
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementDeviation::initialiser(){
	angleCible_ = controleRobot_->obtenirNoeud()->obtenirAngleRotation() + maxAngle_;
	gauche = maxAngle_ >= 0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::mettreAJour()
///
/// V�rifie si le comportement doit changer ou proc�der � une prochaine action sur sa liste.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementDeviation::mettreAJour(){
	
	//Si une ligne est trouv�e nous passons � la suivie de ligne
	if (controleRobot_->ligneDetectee()){
		controleRobot_->assignerComportement(SUIVIDELIGNE);
	}

	bool angleAtteinte = false;

	if (gauche){
		// D�vier � gauche et v�rifier angle
		controleRobot_->traiterCommande(&CommandeRobot(DEVIATION_GAUCHE), false);
		angleAtteinte = controleRobot_->obtenirNoeud()->obtenirAngleRotation() > angleCible_;
	}
	else{
		// D�vier � droite et v�rifier angle
		controleRobot_->traiterCommande(&CommandeRobot(DEVIATION_DROITE), false);
		angleAtteinte = controleRobot_->obtenirNoeud()->obtenirAngleRotation() < angleCible_;
	}

	if (angleAtteinte){
		// TODO: Assigner le comportement suivant
		controleRobot_->assignerComportement(DEFAUT);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementDeviation::setAngleMaxRotation(double angle)
///
/// Ajuste l'angle pour la d�viation
///
/// @param[in] angle: l'angle � partir duquel on change decomportement. negatif implique une deviation vers la droite.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementDeviation::setAngleMaxRotation(double angle){
	maxAngle_ = angle;
}
///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
