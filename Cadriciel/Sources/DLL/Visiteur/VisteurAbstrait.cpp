////////////////////////////////////////////////
/// @file   VisiteurAbstrait.cpp
/// @author Olivier St-Amour
/// @date   20016-01-13
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////


#include "VisiteurAbstrait.h"
#include "FacadeModele.h"
#include "Vue.h"
#include "Projection.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurAbstrait::VisiteurAbstrait()
///
/// Constructeur par d�faut.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurAbstrait::VisiteurAbstrait()
{
	glm::vec2 dimensionsCloture_ = FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().obtenirDimensionCloture();
}


VisiteurAbstrait::VisiteurAbstrait(const int& x, const int& y) : x_(x), y_(y)
{
	glm::vec2 dimensionsCloture_ = FacadeModele::obtenirInstance()->obtenirVue()->obtenirProjection().obtenirDimensionCloture();
	changerPointdeRepere(x_, y_);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn  VisiteurAbstrait::~VisiteurAbstrait()
///
/// Destructeur d�clar� virtuel pour les classes d�riv�es.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurAbstrait::~VisiteurAbstrait()
{

}


void VisiteurAbstrait::visiter(ArbreRendu* noeud)
{

}
void VisiteurAbstrait::visiter(NoeudTable* noeud)
{

}
void VisiteurAbstrait::visiter(NoeudPoteau* noeud)
{

}
void VisiteurAbstrait::visiter(NoeudMur* noeud)
{

}
void VisiteurAbstrait::visiter(NoeudLigneNoire* noeud)
{

}

void VisiteurAbstrait::changerPointdeRepere(int& x, int& y)
{
	// D�placer l'origine au milieu de l'�cran.
	x = x - dimensionsCloture_[0] / 2;
	y = y - dimensionsCloture_[1] / 2;
}