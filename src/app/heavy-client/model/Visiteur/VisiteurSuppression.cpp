///////////////////////////////////////////////////////////////////////////
/// @file VisiteurSuppression.cpp
/// @authors Ulric Villeneuve et Simon-Pierre Desjardins
/// @date 2016-02-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "FacadeModele.h"
#include "Vue.h"
#include "VisiteurSuppression.h"
#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"
#include "Utilitaire.h"
#include "Modele3D.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSuppression::VisiteurSuppression()
///
/// Constructeur
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSuppression::VisiteurSuppression()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSuppression::~VisiteurSuppression()
///
/// Destructeur
///
/// @param[in] Aucun
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSuppression::~VisiteurSuppression()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSuppression::visiter(NoeudTable* noeud)
///
/// Fonction qui efface tous les enfants de la table passée en paramètre qui sont sélectionnés .
///
/// @param[in] noeud : noued Table de laquelle on veut supprimer les enfants sélectionnés.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void VisiteurSuppression::visiter(NoeudTable* noeud)
{
	noeud->effacerSelection();
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////