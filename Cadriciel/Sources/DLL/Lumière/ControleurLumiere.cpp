///////////////////////////////////////////////////////////////////////////
/// @file ControleurLumiere.cpp
/// @author Simon-Pierre Desjardins
/// @date 2016-04-1
/// @version 3.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////


#include "ControleurLumiere.h"
#include "FacadeModele.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumiere::ControleurLumiere()
///
/// Constructeur par d�faut
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
ControleurLumiere::ControleurLumiere()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumiere::ControleurLumiere()
///
/// Destructeur par d�faut
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
ControleurLumiere::~ControleurLumiere()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumiere::afficherLumiereAmbianteGlobale()
///
/// Fonction qui affiche la lumiere ambiante globale selon un bool�en
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumiere::afficherLumiereAmbianteGlobale()
{
	if (lumiereAmbiante)
	{
		glm::vec4 ambiant{ 0.2f, 0.2f, 0.2f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, glm::value_ptr(ambiant));
	}
	else
	{
		glm::vec4 ambiant{ 0.0f, 0.0f, 0.0f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, glm::value_ptr(ambiant));
	}

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumiere::afficherLumiereDirectionnelle()
///
/// Fonction qui affiche la lumiere directionelle selon un bool�en
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumiere::afficherLumiereDirectionnelle()
{
	// Positionner la lumi�re.
	glm::vec4 position{ 1, 1, 1, 0 };

	glm::vec4 zeroContribution{ 0.0f, 0.0f, 0.0f, 1 };
	glm::vec4 contributionMaximale{ 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(position));
	// La plupart des mod�les export�s n'ont pas de composante ambiante. (Ka dans les mat�riaux .mtl)
	glLightfv(GL_LIGHT0, GL_AMBIENT, glm::value_ptr(zeroContribution));
	// On sature les objets de lumi�re
	if (lumiereDirectionnelle)
		glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(contributionMaximale));
	else
		glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(zeroContribution));
	// Pas de composante sp�culaire.
	glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(zeroContribution));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumiere::assignerLumiereAmbianteGlobale(bool estIllumine)
///
/// Fonction qui assigne une valeur de vrai ou faux pour la lumi�re ambiante
///
/// @param[in] estIllumine : Si vrai, la lumiere est affich�e.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumiere::assignerLumiereAmbianteGlobale(bool estIllumine)
{
	lumiereAmbiante = estIllumine;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumiere::assignerLumiereDirectionnelle(bool estIllumine)
///
/// Fonction qui assigne une valeur de vrai ou faux pour la lumi�re directionelle
///
/// @param[in] estIllumine : Si vrai, la lumiere est affich�e.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumiere::assignerLumiereDirectionnelle(bool estIllumine)
{
	lumiereDirectionnelle = estIllumine;
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void ControleurLumiere::assignerLumiereSpot(bool estIllumine)
///
/// Fonction qui assigne une valeur de vrai ou faux pour la lumi�re du spot
///
/// @param[in] estIllumine : Si vrai, la lumiere est affich�e.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ControleurLumiere::assignerLumiereSpot(bool estIllumine)
{
	lumiereSpot = estIllumine;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////