///////////////////////////////////////////////////////////////////////////
/// @file VisiteurDetectionObstacle.h
/// @author Olivier St-Amour
/// @date 2016-02-28
/// @version 2.1
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_DETECTION_OBSTACLE_H
#define VISITEUR_DETECTION_OBSTACLE_H

#include "VisiteurAbstrait.h"
#include "CapteurDistance.h"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDetectionLigne
/// @brief Visiteur permettant � un capteur de distance de d�tecter un 
///        mur ou un poteau.
///
/// @author Olivier St-Amour
/// @date 2016-02-28
///////////////////////////////////////////////////////////////////////////
class VisiteurDetectionObstacle : public VisiteurAbstrait
{
public:
	/// Constructeur par d�faut.
	VisiteurDetectionObstacle();
	/// Destructeur.
	virtual ~VisiteurDetectionObstacle();

    /// Assigner une r�f�rence � un capteur optique.
	inline void assignerCapteurDistance(CapteurDistance* capteur);

    /// Visiter l'arbre de rendu.
	virtual void visiter(ArbreRendu* noeud);
    /// Visiter la table.
	virtual void visiter(NoeudTable* noeud);
    /// Visiter un poteau.
	virtual void visiter(NoeudPoteau* noeud);
    /// Visiter un mur.
	virtual void visiter(NoeudMur* noeud);

private:
    CapteurDistance* capteur_;
    
	bool obstacleEstDetecte_{ false };
	glm::dvec3 positionCapteur_;
};

////////////////////////////////////////////////////////////////////////////////
///
/// @fn CapteurOptique::assignerCapteurDistance(CapteurDistance* capteur)
///
/// Cette m�thode assigne une r�f�rence au capteur.
///
/// @param[in] capteur : le pointeur qui r�f�rence le capteur.
///
/// @return Aucune. 
///
////////////////////////////////////////////////////////////////////////////////
inline void VisiteurDetectionObstacle::assignerCapteurDistance(CapteurDistance* capteur)
{
}

#endif // VISITEUR_DETECTION_OBSTACLE_H

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

