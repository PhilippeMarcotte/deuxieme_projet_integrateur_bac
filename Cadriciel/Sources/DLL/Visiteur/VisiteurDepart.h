///////////////////////////////////////////////////////////////////////////
/// @file VisiteurD�part.h
/// @author Fr�d�ric Gr�goire
/// @date 2016-02-10
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_DEPART_H
#define VISITEUR_DEPART_H

#include "VisiteurAbstrait.h"

class VisiteurDepart : public VisiteurAbstrait
{
public:
	/// Constructeur par d�faut.
	VisiteurDepart();
	
	/// Constructeur par param�tre
	VisiteurDepart(const int& x, const int& y);
	/// Destructeur.
	virtual ~VisiteurDepart();

	/// Creation de poteau sur l'arbre de rendu.
	virtual void visiter(ArbreRendu* noeud);

	/// Creation de poteau sur la table.
	virtual void visiter(NoeudTable* noeud);
	virtual void visiter(NoeudDepart* noeud);
};


#endif // VISITEUR_DEPART_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////