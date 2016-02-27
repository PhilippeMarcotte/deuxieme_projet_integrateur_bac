///////////////////////////////////////////////////////////////////////////
/// @file CapteurOptique.h
/// @author Olivier St-Amour
///
/// version 2.1
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef CAPTEUR_OPTIQUE_H
#define CAPTEUR_OPTIQUE_H

#include <memory>
#include "glm\glm.hpp"

class ArbreRendu;
class VisiteurDetectionLigne;

///////////////////////////////////////////////////////////////////////////
/// @class CapteurOptique
/// @brief Classe qui repr�sente l'un des 3 capteurs optiques du suiveur de ligne  
///
///        Cette classe s'occupe de g�rer la d�tection des lignes. 
///
/// @author Olivier St-Amour
/// @date 2016-02-25
///////////////////////////////////////////////////////////////////////////
class CapteurOptique
{
public:
	//Constructeur par d�faut
	CapteurOptique();
	//Constructeur par param�tres
	CapteurOptique(const glm::dvec3& positionRelative, VisiteurDetectionLigne* visiteur);
	//Destructeur
	~CapteurOptique();
	//Acc�s � l'�tat du capteur	
	inline bool ligneEstDetectee() const;
	//Mise � jour de l'�tat du capteur
	void mettreAJourEtat(const glm::dvec3& positionRobot, const double& angleRotationRobot);

private:
	bool ligneEstDetectee_{ false };
	glm::dvec3 positionRelative_{ 0.0, 0.0, 0.0 };
	glm::dvec3 positionCourante_{ 0.0, 0.0, 0.0 };
	VisiteurDetectionLigne* visiteur_{ nullptr };
	ArbreRendu* arbre_{ nullptr };
};

inline bool CapteurOptique::ligneEstDetectee() const
{
	return ligneEstDetectee_;
}

#endif // CAPTEUR_OPTIQUE_H