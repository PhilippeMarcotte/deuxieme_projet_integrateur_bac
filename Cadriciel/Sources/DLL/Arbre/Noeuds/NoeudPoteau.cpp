///////////////////////////////////////////////////////////////////////////////
/// @file NoeudPoteau.cpp
/// @author Philippe Marcotte et Camille Gendreau
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudPoteau.h"
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
NoeudPoteau::NoeudPoteau(const std::string& typeNoeud)
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
NoeudPoteau::~NoeudPoteau()
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
void NoeudPoteau::afficherConcret() const
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
	
	glScaled(facteurMiseAEchelle_, facteurMiseAEchelle_, 1);
	

	//glRotatef(90, 1, 0, 0);
	//glRotatef(90, 0, 1, 0);

	// Affichage du mod�le.
	vbo_->dessiner();

	// Restauration de la matrice.
	glPopMatrix();
}

void NoeudPoteau::mettreAJourQuadEnglobantConcret(const glm::dvec3& positionRelative)
{
	// Mettre � jour les coins avec le facteur de mise � �chelle.
	std::cout << "Mise � jour Poteau:" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		quadEnglobant_.coins[i] *= facteurMiseAEchelle_;
		quadEnglobant_.coins[i] += positionRelative_ + positionRelative;
		std::cout << "coin " << i << ": " << quadEnglobant_.coins[i].x << ", " << quadEnglobant_.coins[i].y << std::endl;
	}
}


void NoeudPoteau::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
