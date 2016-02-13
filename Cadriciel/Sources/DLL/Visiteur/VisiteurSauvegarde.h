///////////////////////////////////////////////////////////////////////////
/// @file VisiteurSauvegarde.h
/// @author Philippe Marcotte
/// @date 2016-02-09
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_SAUVEGARDE_H
#define VISITEUR_SAUVEGARDE_H

#include "VisiteurAbstrait.h"

#include "rapidjson\writer.h"

class NoeudComposite;

namespace rapidjson{
	class FileWriteStream;
}

class VisiteurSauvegarde : public VisiteurAbstrait
{
public:
	/// Constructeur par d�faut.
	VisiteurSauvegarde();

	/// Destructeur.
	virtual ~VisiteurSauvegarde();

	/// Sauvegarde en JSON de l'arbre de rendu.
	virtual void visiter(ArbreRendu* noeud);

	/// Sauvegarde en JSON d'un NoeudTable.
	virtual void visiter(NoeudTable* noeud);

	/// Sauvegarde en JSON d'un NoeudPoteau.
	virtual void visiter(NoeudPoteau* noeud);

	/// Sauvegarde en JSON d'un NoeudMur.
	virtual void visiter(NoeudMur* noeud);

	/// Sauvegarde en JSON d'un NoeudLigne.
	virtual void visiter(NoeudLigne* noeud);

	/// Sauvegarde en JSON d'un NoeudSegment.
	virtual void visiter(NoeudSegment* noeud);

	/// Sauvegarde en JSON d'un NoeudDupliquation.
	virtual void visiter(NoeudDepart* noeud);

	/// Sauvegarde en JSON d'un NoeudDupliquation.
	virtual void visiter(NoeudJonction* noeud);
private:

	/// Objet pour �crire dans un fichier.
	rapidjson::Writer<rapidjson::FileWriteStream>* writer ;

	/// Visite tous les enfants d'un NoeudComposite.
	void visiterEnfants(NoeudComposite* noeud);
	
};


#endif // VISITEUR_SAUVEGARDE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
