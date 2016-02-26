///////////////////////////////////////////////////////////////////////////
/// @file SuiveurLigne.h
/// @author Olivier St-Amour
///
/// version 2.1
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef SUIVEUR_LIGNE_H
#define SUIVEUR_LIGNE_H

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "VisiteurDetectionLigne.h"

class CapteurOptique;

enum PositionCapteur
{
	GAUCHE,
	CENTRE,
	DROITE
};

///////////////////////////////////////////////////////////////////////////
/// @class SuiveurLigne
/// @brief Classe qui repr�sente le suiveur de ligne. 
///
///        Cette classe s'occupe de g�rer la d�tection de ligne. 
///
/// @author Olivier St-Amour
/// @date 2016-02-23
///////////////////////////////////////////////////////////////////////////
class SuiveurLigne
{
public:
	//Constructeur par d�faut
	SuiveurLigne();
	//Destructeur
	~SuiveurLigne();

	bool obtenirEtatCapteur(const PositionCapteur& position);
		
private:
	static const glm::dvec3 POSITION_RELATIVE_GAUCHE;
	static const glm::dvec3 POSITION_RELATIVE_CENTRE;
	static const glm::dvec3 POSITION_RELATIVE_DROITE;

	std::vector<CapteurOptique> capteursOptique_;
	std::unique_ptr<VisiteurDetectionLigne> visiteurDetectionLigne_{ nullptr };
};

#endif // SUIVEUR_LIGNE_H