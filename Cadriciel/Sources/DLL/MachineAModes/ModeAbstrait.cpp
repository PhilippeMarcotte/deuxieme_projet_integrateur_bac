///////////////////////////////////////////////////////////////////////////
/// @file ModeAbstrait.cpp
/// @author Fr�d�ric Gr�goire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#include "ModeAbstrait.h"
#include <math.h>
#include "Utilitaire.h"
#include <iostream>
#include "FacadeModele.h"
#include "Vue.h"
#include "Projection.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeAbstrait::ModeAbstrait()
///
/// Contructeur (vide) par d�faut de ModeAbstrait
///
///
///
////////////////////////////////////////////////////////////////////////
ModeAbstrait::ModeAbstrait()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ModeAbstrait::~ModeAbstrait()
///
/// Destructeur (vide) par d�faut de la classe ModeAbstrait
///
///
////////////////////////////////////////////////////////////////////////
ModeAbstrait::~ModeAbstrait()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::sauvegarder()
///
/// Cette fonction permet de g�rer la sauvegarde selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::sauvegarder()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeAbstrait::charger()
///
/// Cette fonction permet de g�rer le chargement selon le mode dans lequel nous sommes.
///
/// 
/// Il n'y a pas d'implantantion dans cette classe de base.
///
////////////////////////////////////////////////////////////////////////
void ModeAbstrait::charger()
{
}

void ModeAbstrait::assignerSymboleCurseur()
{
}

void ModeAbstrait::gererMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////