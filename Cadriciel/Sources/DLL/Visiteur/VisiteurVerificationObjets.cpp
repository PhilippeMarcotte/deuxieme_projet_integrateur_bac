#include "VisiteurVerificationObjets.h"
#include "ArbreRendu.h"
#include "NoeudTypes.h"


/// Constructeur par d�faut.
VisiteurVerificationObjets::VisiteurVerificationObjets()
{

}

/// Destructeur.
VisiteurVerificationObjets::~VisiteurVerificationObjets()
{

}

void VisiteurVerificationObjets::visiter(ArbreRendu* noeud)
{
	noeud->chercher("table")->accepterVisiteur(this);
}


void VisiteurVerificationObjets::visiter(NoeudTable* noeud)
{
	objetsDansZoneSimulation_ = true;
	for (int i = 0; i < noeud->obtenirNombreEnfants() && objetsDansZoneSimulation_; i++)
	{
		noeud->chercher(i)->accepterVisiteur(this);
	}
}

void VisiteurVerificationObjets::visiter(NoeudPoteau* noeud)
{
	noeud->mettreAJourQuadEnglobant();
	for (int i = 0; i < 4 && objetsDansZoneSimulation_; i++)
	{
		objetsDansZoneSimulation_ = verifierPointEstSurTable(noeud->obtenirQuadEnglobant().coins[i]);
	}
}

void VisiteurVerificationObjets::visiter(NoeudMur* noeud)
{
	noeud->mettreAJourQuadEnglobant();
	for (int i = 0; i < 4 && objetsDansZoneSimulation_; i++)
	{
		objetsDansZoneSimulation_ = verifierPointEstSurTable(noeud->obtenirQuadEnglobant().coins[i]);
	}
}


void VisiteurVerificationObjets::visiter(NoeudLigneNoire* noeud)
{
	for (int i = 0; i < noeud->obtenirNombreEnfants() && objetsDansZoneSimulation_; i++)
	{
		noeud->chercher(i)->accepterVisiteur(this);
	}
}


void VisiteurVerificationObjets::visiter(NoeudSegment* noeud)
{
	noeud->mettreAJourQuadEnglobant();
	for (int i = 0; i < 4 && objetsDansZoneSimulation_; i++)
	{
		objetsDansZoneSimulation_ = verifierPointEstSurTable(noeud->obtenirQuadEnglobant().coins[i]);
	}
}


bool VisiteurVerificationObjets::verifierPointEstSurTable(glm::dvec3 point)
{
	// Les valeurs maximales de la table.
	const int MIN_X = -48;
	const int MAX_X =  48;
	const int MIN_Y = -24;
	const int MAX_Y =  24;

	return MIN_X <= point.x && point.x <= MAX_X && MIN_Y <= point.y && point.y <= MAX_Y;
}