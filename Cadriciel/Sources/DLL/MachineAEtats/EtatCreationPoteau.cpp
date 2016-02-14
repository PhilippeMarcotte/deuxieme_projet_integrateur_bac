///////////////////////////////////////////////////////////////////////////
/// @file EtatCreationPoteau.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatCreationPoteau.h"
#include "FacadeModele.h"
#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "glm\glm.hpp"

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatCreationPoteau::EtatCreationPoteau()
///
/// Constructeur par d�fault
///
////////////////////////////////////////////////////////////////////////
EtatCreationPoteau::EtatCreationPoteau()
{
	typeEtat_ = CREATION_POTEAU;
	visiteurCreationPoteau_ = std::make_unique<VisiteurCreationPoteau>();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn EtatCreationPoteau::~EtatCreationPoteau()
///
/// Destructeur par d�fault
///
////////////////////////////////////////////////////////////////////////
EtatCreationPoteau::~EtatCreationPoteau()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationPoteau::gererClicGaucheEnfonce(const int& x, const int& y)
///
/// Cette fonction assigne un bool�an � true si le bouton gauche de la souris est
/// appuy� et sauvegarde la position courante.
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatCreationPoteau::gererClicGaucheEnfonce(const int& x, const int& y)
{
	EtatAbstrait::gererClicGaucheEnfonce(x, y);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationPoteau::gererClicGaucheRelache(const int& x, const int& y)
///
/// Cette fonction assigne un bool�an � false si le bouton gauche de la souris est
/// rel�ch� et cr�e un poteau sur la table
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatCreationPoteau::gererClicGaucheRelache(const int& x, const int& y)
{
	EtatAbstrait::gererClicGaucheRelache(x, y);
	if (!estClickDrag())
	{
		if (!curseurEstSurTable_) return;
		glm::dvec3 positionVirtuelle;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionVirtuelle);
		visiteurCreationPoteau_->assignerPositionRelative(positionVirtuelle);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurCreationPoteau_.get());
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationPoteau::gererMouvementSouris(const int& x, const int& y)
///
/// Cette fonction g�re les mouvements de la souris. Si le clique droit est enfonc�
/// on peux d�placer la cam�ra, sinon rien
///
/// @param const int& x: position en x du cursor
/// @param const int& y: position en y du cursor
///
////////////////////////////////////////////////////////////////////////
void EtatCreationPoteau::gererMouvementSouris(const int& x, const int& y)
{
	EtatAbstrait::gererMouvementSouris(x, y);
	glm::dvec3 positionVirtuelle;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionVirtuelle);
	gererEstSurTable(positionVirtuelle);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void EtatCreationPoteau::gererEstSurTableConcret(bool positionEstSurTable)
///
/// Cette fonction affiche l'objet si le curseur est sur la table et arr�te
/// d'afficher l'objet si le curseur n'est pas sur la table.
///
/// @param bool positionEstSurTable: True si curseur est sur la table, sinon false.
///
////////////////////////////////////////////////////////////////////////
void EtatCreationPoteau::gererEstSurTableConcret(bool positionEstSurTable)
{
	EtatAbstrait::gererEstSurTableConcret(positionEstSurTable);

	if (positionEstSurTable && !curseurEstSurTable_)
	{
		curseurEstSurTable_ = true;
	}
	else if (!positionEstSurTable && curseurEstSurTable_)
	{
		curseurEstSurTable_ = false;
	}
}
