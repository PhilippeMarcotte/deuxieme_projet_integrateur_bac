///////////////////////////////////////////////////////////////////////////
/// @file EtatCreationMur.cpp
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "EtatCreationMur.h"
#include "FacadeModele.h"
#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "Utilitaire.h"

#include <iostream> 

EtatCreationMur::EtatCreationMur()
{
	std::cout << "Creation de mur" << std::endl;
	visiteur_ = std::make_unique<VisiteurCreationMur>();
}

EtatCreationMur::~EtatCreationMur()
{

}

void EtatCreationMur::gererClicGaucheEnfonce(const int& x, const int& y)
{
	std::cout << x << " " << y << std::endl;
}

void EtatCreationMur::gererClicGaucheRelache(const int& x, const int& y)
{
	if (!curseurEstSurTable_) return;
	
	//Premier clic
	if (!enCreation_)
	{
		enCreation_ = true;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionPremierClic_);
		visiteur_->assignerPositionRelative(positionPremierClic_);
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur_.get());
		table_ = visiteur_.get()->obtenirReferenceNoeud();
	}
	//Deuxieme clic
	else
	{
		enCreation_ = false;
	}
}

void EtatCreationMur::gererToucheEchappe()
{
	if (enCreation_)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(table_);
		enCreation_ = false;
	}
}

void EtatCreationMur::gererMouvementSouris(const int& x, const int&y)
{

	// Calculer la position virtuelle.
	glm::dvec3 positionVirtuelle;
	FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, positionVirtuelle);
	
	gererEstSurTable(positionVirtuelle);

	if (enCreation_)
	{		
		// Calculer et assigner de l'angle de rotation.
		double angle = utilitaire::calculerAngleRotation(positionPremierClic_, positionVirtuelle);
		table_->assignerAngleRotation(angle);
		
		// Calculer et assigner le facteur de mise � �chelle.
		double distance = utilitaire::calculerDistanceHypothenuse(positionPremierClic_, positionVirtuelle);
		table_->assignerFacteurMiseAEchelle(distance);

		// Calculer et assigner la position relative.
		glm::dvec3 nouvellePosition = utilitaire::calculerPositionEntreDeuxPoints(positionPremierClic_, positionVirtuelle);
		table_->assignerPositionRelative(nouvellePosition);
	}
}

void EtatCreationMur::gererEstSurTableConcret(bool positionEstSurTable)
{
	if (positionEstSurTable && !curseurEstSurTable_)
	{
		curseurEstSurTable_ = true;
		if (table_ != nullptr)
		{
			table_->assignerAffiche(true);
		}
		// TODO: Ajouter changement de curseur ici.
		//HCURSOR handle = GetCursor();
		//SetSystemCursor(handle, 32650);
		std::cout << "in" << std::endl;
	}
	else if (!positionEstSurTable && curseurEstSurTable_)
	{
		curseurEstSurTable_ = false;
		if (table_ != nullptr)
		{
			table_->assignerAffiche(false);
		}
		std::cout << "out" << std::endl;
		//TODO: Ajouter changement de curseur ici.
		//HCURSOR handle = GetCursor();
		//SetSystemCursor(handle, 32648);
	}
}