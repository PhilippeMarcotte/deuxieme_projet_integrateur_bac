///////////////////////////////////////////////////////////////////////////
/// @file VisiteurDetectionLigne.h
/// @author Olivier St-Amour
/// @date 2016-02-26
/// @version 2.1
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef VISITEUR_DETECTION_LIGNE_H
#define VISITEUR_DETECTION_LIGNE_H

#include "VisiteurAbstrait.h"
#include "CapteurOptique.h"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDetectionLigne
/// @brief Visiteur permettant � un capteur optique 
///		   de d�tecter une ligne � une certaine position. 
///
/// @author Olivier St-Amour
/// @date 2016-02-26
///////////////////////////////////////////////////////////////////////////
class VisiteurDetectionLigne : public VisiteurAbstrait
{
public:
	/// Constructeur par d�faut.
	VisiteurDetectionLigne();
	/// Destructeur.
	virtual ~VisiteurDetectionLigne();

    /// Assigner une r�f�rence � un capteur optique.
	inline void assignerCapteurOptique(CapteurOptique* capteur);

    /// Visiter l'arbre de rendu.
	virtual void visiter(ArbreRendu* noeud);
    /// Visiter la table.
	virtual void visiter(NoeudTable* noeud);
    /// Visiter une ligne.
	virtual void visiter(NoeudLigne* noeud);

private:
    CapteurOptique* capteur_;
    
	bool ligneEstDetectee_{ false };
	glm::dvec3 positionCapteur_;
};

////////////////////////////////////////////////////////////////////////////////
///
/// @fn CapteurOptique::assignerCapteurOptique(CapteurOptique* capteur)
///
/// Cette assigne m�thode une r�f�rence au capteur.
///
/// @param[in] capteur : le pointeur qui r�f�rence le capteur.
///
/// @return Aucune. 
///
////////////////////////////////////////////////////////////////////////////////
inline void VisiteurDetectionLigne::assignerCapteurOptique(CapteurOptique* capteur)
{
    capteur_ = capteur;
    positionCapteur_ = capteur->obtenirPositionCourante();
}

#endif // VISITEUR_DETECTION_LIGNE_H

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////
