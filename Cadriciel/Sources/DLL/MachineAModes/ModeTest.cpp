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
    actionsAppuyees_ = { { false, false, false, false, false } };
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
            CommandeRobot* commande = profil_->obtenirCommandeRobot(wParam);
            TypeCommande type = commande->obtenirTypeCommande();
            actionsAppuyees_.at(type) = true;
            controleRobot_->traiterCommande(commande, true);
        }
	}
	else if (msg == WM_KEYUP)
	{
		CommandeRobot* commande = profil_->obtenirCommandeRobot(wParam);
		if (commande != nullptr && commande->obtenirTypeCommande() != INVERSER_MODE_CONTROLE)
		{
            // Arreter les moteurs.
            std::unique_ptr<CommandeRobot> commandeArreter = std::make_unique<CommandeRobot>(ARRETER);
            controleRobot_->traiterCommande(commandeArreter.get(), true);

            // Indiquer que la commande n'est plus appuy�e dans les flags d'actions appuy�es
            CommandeRobot* commandeCourante = profil_->obtenirCommandeRobot(wParam);
            TypeCommande type = commandeCourante->obtenirTypeCommande();
            actionsAppuyees_.at(type) = false;

            // Relancer les commandes qui sont toujours appuy�es.
            for (int i = 1; i < actionsAppuyees_.size(); i++)
            {
                if (actionsAppuyees_.at((TypeCommande)i))
                {
                    std::unique_ptr<CommandeRobot> commandeMiseAJour  = std::make_unique<CommandeRobot>((TypeCommande)i, true);
                    controleRobot_->traiterCommande(commandeMiseAJour.get(), true);
                }
            }
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////