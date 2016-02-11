///////////////////////////////////////////////////////////////////////////
/// @file EtatDeplacement.h
/// @author 
/// @date 2016-01-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef ETAT_DEPLACEMENT_H
#define ETAT_DEPLACEMENT_H

#include "EtatAbstrait.h"

class EtatDeplacement : public EtatAbstrait
{
public:
	EtatDeplacement();
	virtual ~EtatDeplacement();
	virtual void gererClicGaucheEnfonce(const int& x, const int& y);
	virtual void gererClicGaucheRelache(const int& x, const int& y);
	virtual void gererMouvementSouris(const int& x, const int& y);
private:
	glm::dvec3 dernierePositionVirtuelle_{ glm::dvec3() };
	glm::dvec3 positionVirtuelleInitiale_{ glm::dvec3() };
};

#endif

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
