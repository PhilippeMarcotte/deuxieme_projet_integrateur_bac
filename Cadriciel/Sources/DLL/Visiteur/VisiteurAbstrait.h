///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurAbstrait.h
/// @author Olivier St-Amour
/// @date 2016-01-13
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_ABSTRAIT_H
#define VISITEUR_ABSTRAIT_H

#include "NoeudTypes.h"


///////////////////////////////////////////////////////////////////////////
/// @class VisiteurAbstrait
/// @brief Classe de base du patron visiteur utilis�e pour effectuer des
///		   manipulations sur l'arbre de rendu.
///
///        Cette classe abstraite comprend l'interface de base que doivent
///        implanter tous les visiteurs concrets. 
///
/// @author Olivier St-Amour
/// @date 2016-01-13
///////////////////////////////////////////////////////////////////////////
class VisiteurAbstrait
{
public:
	/// Constructeur par d�faut.
	VisiteurAbstrait();
	
	/// Destructeur.
	virtual ~VisiteurAbstrait();

	/// Fonctionnalit� effectu�e sur un noeud de type NoeudRobot.
	virtual void visiter(NoeudRobot* noeud) = 0;
	// TODO:: Ajouter les m�thodes pour les diff�rents types de noeuds.
};


#endif // VISITEUR_ABSTRAIT_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////