///////////////////////////////////////////////////////////////////////////////
/// @file ComporterSuiviLigne.cpp
/// @author Olivier St-Amour
/// @date 20016-02-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "ComportementSuiviLigne.h"
#include "ControleRobot.h"
#include "NoeudRobot.h"
#include "CommandeRobot.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementSuiviLigne::ComportementSuiviLigne()
///
/// Constructeur
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementSuiviLigne::ComportementSuiviLigne(ControleRobot* controleRobot) :ComportementAbstrait(controleRobot)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementSuiviLigne::~ComportementSuiviLigne()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementSuiviLigne::~ComportementSuiviLigne()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementSuiviLigne::initialiser()
///
/// Implementation qui ramene le comportement a son etat initial
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementSuiviLigne::initialiser(){

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
void ComportementSuiviLigne::mettreAJour(){
	//TODO: D�commenter ceci pour assurer fonctionnement dynamique du robot.
	//uint8_t etatSuiveurLigne = controleRobot_->obtenirNoeud()->obtenirEtatSuiveurLigne();
	uint8_t etatSuiveurLigne = 0x00;

	// D�tection d'une ligne � gauche
	if ((etatSuiveurLigne & 0x04) == 0x04){
		controleRobot_->traiterCommande(&CommandeRobot(ROTATION_GAUCHE), false);
	}
	// D�tection d'une ligne � gauche
	else if ((etatSuiveurLigne & 0x01) == 0x01){
		controleRobot_->traiterCommande(&CommandeRobot(ROTATION_DROITE), false);
	}
	// Sinon, si ligne au centre, aller tout droit.
	else if ((etatSuiveurLigne & 0x02) == 0x02){
		controleRobot_->traiterCommande(&CommandeRobot(AVANCER), false);
	}
	// TODO: Sinon, si rien n'est d�tect�, passer au comportement profil.
	else {
		controleRobot_->assignerComportement(BALAYAGE180);
	}
}

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
