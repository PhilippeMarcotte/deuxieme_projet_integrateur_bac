///////////////////////////////////////////////////////////////////////////
/// @file VisiteurVerificationQuad.cpp
/// @author Olivier St-Amour 
/// @date 2016-02-13
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#include "VisiteurVerificationQuad.h"
#include "VisiteurMiseAJourQuad.h"
#include "ArbreRendu.h"
#include "NoeudTypes.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurVerificationQuad::VisiteurVerificationQuad()
///
/// Constructeur
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurVerificationQuad::VisiteurVerificationQuad()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurVerificationQuad::~VisiteurVerificationQuad()
///
/// Destructeur
///
/// @param[in] Aucun
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurVerificationQuad::~VisiteurVerificationQuad()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurVerificationQuad::visiter(ArbreRendu* noeud)
///
/// Fonction servant � donner l'acc�s au noeud Table.
///
/// @param[in] noeud : l'arbre rendu contenant le noeud Table, entre autres.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerificationQuad::visiter(ArbreRendu* noeud)
{
	noeud->chercher("table")->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurVerificationQuad::visiter(NoeudTable* noeud)
///
/// Fonction servant � donner l'acc�s aux enfants du noeud Table.
///
/// @param[in] noeud : Le noeud Table contenant les enfants auxquels on veut avoir acc�s.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerificationQuad::visiter(NoeudTable* noeud)
{
	objetsDansZoneSimulation_ = true;
	NoeudAbstrait* enfant = nullptr;
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants() && objetsDansZoneSimulation_; i++)
	{
		enfant = noeud->chercher(i);
		enfant->accepterVisiteur(this);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurVerificationQuad::visiter(NoeudDuplication* noeud)
///
/// Fonction servant � donner l'acc�s au nouveau noeud cr��e lors de la duplication.
///
/// @param[in] noeud : Le noeud Duplication contenant les enfants auxquels on veut avoir acc�s.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerificationQuad::visiter(NoeudDuplication* noeud)
{
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants() && objetsDansZoneSimulation_; i++)
	{
		noeud->chercher(i)->accepterVisiteur(this);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurVerificationQuad::visiter(NoeudPoteau* noeud)
///
/// Fonction qui v�rifie que le poteau pass� en param�tre se trouve dans les limites de la table.
///
/// @param[in] noeud : Le noeud Poteau sur lequel on veut effectuer la v�rication.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerificationQuad::visiter(NoeudPoteau* noeud)
{
	for (int i = 0; i < 4 && objetsDansZoneSimulation_; i++)
	{
		objetsDansZoneSimulation_ = verifierPointEstSurTable(noeud->obtenirQuadEnglobantCourant().coins[i]);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurVerificationQuad::visiter(NoeudMur* noeud)
///
/// Fonction qui v�rifie que le mur pass� en param�tre se trouve dans les limites de la table.
///
/// @param[in] noeud : Le noeud Mur sur lequel on veut effectuer la v�rication.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerificationQuad::visiter(NoeudMur* noeud)
{
	for (int i = 0; i < 4 && objetsDansZoneSimulation_; i++)
	{
		objetsDansZoneSimulation_ = verifierPointEstSurTable(noeud->obtenirQuadEnglobantCourant().coins[i]);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurVerificationQuad::visiter(NoeudDepart* noeud)
///
/// Fonction qui v�rifie que la fl�che de d�part pass�e en param�tre se trouve dans les limites de la table.
///
/// @param[in] noeud : Le noeud Depart sur lequel on veut effectuer la v�rication.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerificationQuad::visiter(NoeudDepart* noeud)
{
	for (int i = 0; i < 4 && objetsDansZoneSimulation_; i++)
	{
		objetsDansZoneSimulation_ = verifierPointEstSurTable(noeud->obtenirQuadEnglobantCourant().coins[i]);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurVerificationQuad::visiter(NoeudLigne* noeud)
///
/// Fonction qui v�rifie que la ligne pass�e en param�tre se trouve dans les limites de la table.
///
/// @param[in] noeud : Le noeud Ligne sur lequel on veut effectuer la v�rication.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerificationQuad::visiter(NoeudLigne* noeud)
{
	for (unsigned int i = 0; i < noeud->obtenirNombreEnfants() && objetsDansZoneSimulation_; i++)
	{
		noeud->chercher(i)->accepterVisiteur(this);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurVerificationQuad::visiter(NoeudSegment* noeud)
///
/// Fonction qui v�rifie que le segment pass� en param�tre se trouve dans les limites de la table.
///
/// @param[in] noeud : Le noeud Segment sur lequel on veut effectuer la v�rication.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurVerificationQuad::visiter(NoeudSegment* noeud)
{
	for (int i = 0; i < 4 && objetsDansZoneSimulation_; i++)
	{
		objetsDansZoneSimulation_ = verifierPointEstSurTable(noeud->obtenirQuadEnglobantCourant().coins[i]);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurVerificationQuad::verifierPointEstSurTable(glm::dvec3 point)
///
/// Fonction qui v�rifie que le point pass� en param�tre se trouve dans les limites de la table.
///
/// @param[in] point : Le point sur lequel on veut effectuer la v�rication.
///
/// @return bool :`Bool�en qui indique si le poitn pass� en param�tre se trouve ou non dans les limites de la table.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurVerificationQuad::verifierPointEstSurTable(glm::dvec3 point)
{
	// Les valeurs maximales de la table.
	const int MIN_X = -48;
	const int MAX_X =  48;
	const int MIN_Y = -24;
	const int MAX_Y =  24;

	return MIN_X <= point.x && point.x <= MAX_X && MIN_Y <= point.y && point.y <= MAX_Y;
}