///////////////////////////////////////////////////////////////////////////
/// @file ModeTest.cpp
/// @author Fr�d�ric Gr�goire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////


#include <math.h>
#include "ModeTest.h"
#include "Utilitaire.h"
#include "FacadeModele.h"
#include "Vue.h"
#include "Projection.h"

#include <iostream>

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeTest::ModeTest()
///
/// Constructeur par d�faut pour le mode test
///
////////////////////////////////////////////////////////////////////////
ModeTest::ModeTest()
{
	typeMode_ = TEST;
	controleRobot_ = std::make_unique<ControleRobot>();
	profil_ = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
	controleRobot_->assignerVecteurComportements(profil_->obtenirVecteurComportements());
	// On fait d�marrer le robot en mode automatique
	controleRobot_->passerAModeAutomatique();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ModeTest::~ModeTest()
///
/// Destructeur de la classe ModeTest
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ModeTest::~ModeTest()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeTest::preChangementDeProfil()
///
/// Fonction appel�e avant qu'il y ait changement de profil pour arr�ter les acc�s. Arr�te aussi le thread du robot.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void ModeTest::preChangementDeProfil(){
	//Terminer le thread du robot et pr�parer � un changement au mode automatique
	controleRobot_->passerAModeManuel();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeTest::postChangementDeProfil()
///
/// Fonction appel�e apr�s qu'il y ait changement de profil pour repartir la simulation. Passe le robot en mode automatique.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void ModeTest::postChangementDeProfil(){
	//Repartir le thread en mode automatique, comportement defaut
	controleRobot_->passerAModeAutomatique();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererTouchePlus()
///
/// Cette fonction permet de g�rer la touche + dans le modeEdition.
///
/// Si nous ne sommes pas en perspective, la touche plus effectue un zoom in.
///
////////////////////////////////////////////////////////////////////////
void ModeTest::gererTouchePlus()
{
	if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().estPerspective()) {

	}
	else {
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
	}

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererToucheMoins()
///
/// Cette fonction permet de g�rer la touche - dans le modeEdition.
///
/// Si nous ne sommes pas en perspective, la touche plus effectue un zoom out.
///
////////////////////////////////////////////////////////////////////////
void ModeTest::gererToucheMoins()
{
	if (FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().estPerspective()) {

	}
	else {
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
	}

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererFlecheGauche()
///
/// Cette fonction permet de g�rer la touche fl�che gauche dans le modeEdition.
///
/// Fait un d�placement de 10 pixels selon l'axe des x.
///
////////////////////////////////////////////////////////////////////////

void ModeTest::gererFlecheGauche()
{
	FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(10, 0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererFlecheBas()
///
/// Cette fonction permet de g�rer la touche fl�che bas dans le modeEdition.
///
/// Fait un d�placement de 10 pixels selon l'axe des y.
///
////////////////////////////////////////////////////////////////////////
void ModeTest::gererFlecheBas()
{
	FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(0, 10);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererFlecheHaut()
///
/// Cette fonction permet de g�rer la touche fl�che haut dans le modeEdition.
///
/// Fait un d�placement de -10 pixels selon l'axe des y.
///
////////////////////////////////////////////////////////////////////////
void ModeTest::gererFlecheHaut()
{
	FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(0, -10);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeEdition::gererFlecheDroit()
///
/// Cette fonction permet de g�rer la touche fl�che droit dans le modeEdition.
///
/// Fait un d�placement de -10 pixels selon l'axe des x.
///
////////////////////////////////////////////////////////////////////////
void ModeTest::gererFlecheDroit()
{
	FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(-10, 0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeTest::gererMessage(UINT msg, WPARAM wParam, LPARAM lParam)
///
/// Fonction qui permet de traiter les entr�es utilisateur en mode test. 
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
void ModeTest::gererMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_KEYDOWN)
	{
        const bool estRepetition = ((HIWORD(lParam) & KF_REPEAT) == KF_REPEAT);
        if (!estRepetition)
        {
		    controleRobot_->traiterCommande(profil_->obtenirCommandeRobot(wParam), true);
        }
	}
	else if (msg == WM_KEYUP)
	{
		CommandeRobot* commande = profil_->obtenirCommandeRobot(wParam);
		if (commande != nullptr && commande->obtenirTypeCommande() != INVERSER_MODE_CONTROLE)
		{
            // Obtenir la commande associ�e et inverser la vitesse des moteurs.
            CommandeRobot* commande = profil_->obtenirCommandeRobot(wParam);
            commande->inverserVitesseMoteurs();
			controleRobot_->traiterCommande(commande, true);

            // R�tablir l'�tat initial de la commande.
            commande->inverserVitesseMoteurs();
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////