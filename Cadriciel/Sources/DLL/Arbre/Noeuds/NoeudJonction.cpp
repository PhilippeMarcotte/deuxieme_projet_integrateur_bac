///////////////////////////////////////////////////////////////////////////////
/// @file NoeudPoteau.cpp
/// @author Camille Gendreau
/// @date 2016-02-11
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudJonction.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>
#include <iostream>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "VisiteurAbstrait.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPoteau::NoeudPoteau(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudJonction::NoeudJonction(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudPoteau::~NoeudPoteau()
///
/// Ce destructeur d�sallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudJonction::~NoeudJonction()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudPoteau::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudJonction::afficherConcret() const
{
	// Appel � la version de la classe de base pour l'affichage des enfants.
	//	NoeudComposite::afficherConcret();

	// Sauvegarde de la matrice.
	glPushMatrix();

	if (estSelectionne())
	{
		glColor4f(1.0, 0.0, 0.0, 1.0);
	}
	else
	{
		glColor4f(0.0, 1.0, 0.0, 1.0);
	}

	// Affichage du mod�le.
	vbo_->dessiner();

	// Restauration de la matrice.
	glPopMatrix();
}
/*
void NoeudJonction::mettreAJourQuadEnglobantConcret(const glm::dvec3& positionRelative)
{
	// Mettre � jour les coins avec le facteur de mise � �chelle.
	std::cout << "Mise � jour Jonction:" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		quadEnglobant_.coins[i] *= facteurMiseAEchelle_;
		quadEnglobant_.coins[i] += positionRelative_ + positionRelative;
		std::cout << "coin " << i << ": " << quadEnglobant_.coins[i].x << ", " << quadEnglobant_.coins[i].y << std::endl;
	}
}
*/

void NoeudJonction::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
