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

#include <iostream> 

EtatCreationPoteau::EtatCreationPoteau()
{
	typeEtat_ = CREATION_POTEAU;
	visiteurCreationPoteau_ = std::make_unique<VisiteurCreationPoteau>();
}




EtatCreationPoteau::~EtatCreationPoteau()
{

}

void EtatCreationPoteau::gererClicGaucheEnfonce(const int& x, const int& y)
{
}

void EtatCreationPoteau::gererClicGaucheRelache(const int& x, const int& y)
{
	if (!curseurEstSurTable_) return;
	glm::dvec3 positionVirtuelle;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionVirtuelle);
	visiteurCreationPoteau_->assignerPositionRelative(positionVirtuelle);
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteurCreationPoteau_.get());
}

void EtatCreationPoteau::gererMouvementSouris(const int& x, const int& y)
{
	EtatAbstrait::gererMouvementSouris(x, y);
	glm::dvec3 positionVirtuelle;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionVirtuelle);
	gererEstSurTable(positionVirtuelle);
}

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
