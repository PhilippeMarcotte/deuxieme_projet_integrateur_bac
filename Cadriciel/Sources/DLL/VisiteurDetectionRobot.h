///////////////////////////////////////////////////////////////////////////
/// @file VisiteurDetectionRobot.h
/// @author Olivier St-Amour
/// @date 2016-02-26
/// @version 2.1
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_DETECTION_LIGNE_H
#define VISITEUR_DETECTION_LIGNE_H

#include <vector>

#include "VisiteurAbstrait.h"
#include "CapteurOptique.h"


class SuiveurLigne;
class CapteurDistance;

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDetectionLigne
/// @brief Visiteur permettant � un capteur optique 
///		   de d�tecter une ligne � une certaine position. 
///
/// @author Olivier St-Amour
/// @date 2016-02-26
///////////////////////////////////////////////////////////////////////////
class VisiteurDetectionRobot : public VisiteurAbstrait
{
public:
	/// Constructeur par d�faut.
	VisiteurDetectionRobot();
    /// Constructeur par param�tres.
    VisiteurDetectionRobot(NoeudRobot* robot);
	/// Destructeur.
	virtual ~VisiteurDetectionRobot();

    /// Visiter l'arbre de rendu.
	virtual void visiter(ArbreRendu* noeud);
    /// Visiter la table.
	virtual void visiter(NoeudTable* noeud);
    /// Visiter une ligne.
	virtual void visiter(NoeudLigne* noeud);
    /// Visiter un poteau.
    virtual void visiter(NoeudPoteau* noeud);
    /// Visiter un mur.
    virtual void visiter(NoeudMur* noeud);

private:
    NoeudRobot* robot_;
};

#endif // VISITEUR_DETECTION_LIGNE_H

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////
