#include "CapteurOptique.h"

#include <glm/glm.hpp>

#include "Utilitaire.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"

////////////////////////////////////////////////////////////////////////////////
///
/// @fn CapteurOptique::CapteurOptique()
///
/// Constructeur par d�faut
///
/// @param[in] Aucun
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////////////
CapteurOptique::CapteurOptique()
{
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn CapteurOptique::CapteurOptique(const glm::dvec3& positionRelative) 
///
/// Constructeur par param�tres
///
/// @param[in] positionRelative : La positon relative du capteur
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////////////
CapteurOptique::CapteurOptique(const glm::dvec3& positionRelative)
    : positionRelative_(positionRelative) 
{
}
 
////////////////////////////////////////////////////////////////////////////////
///
/// @fn CapteurOptique::~CapteurOptique()
///
/// Destructeur
///
/// @param[in] Aucun.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////////////
CapteurOptique::~CapteurOptique()
{
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn CapteurOptique::mettreAJourPosition(const glm::dvec3& positionRobot, 
///                                         const double& angleRotationRobot)
///
/// M�thode permettant de faire la mise � jour la position courante du capteur. 
///
/// @param[in] positionRobot : La positon du robot. 
///
/// @param[in] angleRotationRobot : L'angle de rotation du robot.
///
/// @return Aucune. 
///
////////////////////////////////////////////////////////////////////////////////
void CapteurOptique::mettreAJourPosition(const glm::dvec3& positionRobot, 
                                         const double&     angleRotationRobot)
{
	glm::dvec3 positionApresRotation = { 0.0, 0.0, 0.0 };
	utilitaire::calculerPositionApresRotation(positionRelative_, 
                                              positionApresRotation, 
                                              angleRotationRobot);
    positionCourante_ = positionApresRotation + positionRobot;	
}
