///////////////////////////////////////////////////////////////////////////
/// @file NoeudRobot.h
/// @author Martin Paradis
/// @date 2015-08-30
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUD_ROBOT_H__
#define __ARBRE_NOEUD_ROBOT_H__


#include "NoeudComposite.h"
#include "GL/glew.h"


///////////////////////////////////////////////////////////////////////////
/// @class NoeudRobot
/// @brief Classe qui repr�sente le robot du premier projet int�grateur.
///
/// @author Martin Paradis
/// @date 2015-08-30
///////////////////////////////////////////////////////////////////////////
class NoeudRobot : public NoeudComposite
{
public:
	/// Constructeur � partir du type du noeud.
	NoeudRobot(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudRobot();

	/// Affiche le robot.
	virtual void afficherConcret() const;

	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);

private:
	//test stuff
	float angle_{ 0.f };
};


#endif // __ARBRE_NOEUD_ROBOT_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
