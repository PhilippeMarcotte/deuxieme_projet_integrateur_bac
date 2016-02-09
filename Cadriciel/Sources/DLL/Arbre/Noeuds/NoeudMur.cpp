///////////////////////////////////////////////////////////////////////////////
/// @file NoeudMur.cpp
/// @author Philippe Marcotte et Camille Gendreau
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudMur.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>
#include <iostream>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "VisiteurAbstrait.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMur::NoeudMur(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMur::NoeudMur(const std::string& typeNoeud)
: NoeudAbstrait{ typeNoeud }
{
	angleRotation_ = 0;
	facteurMiseAEchelle_ = 1;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudMur::~NoeudMur()
///
/// Ce destructeur d�sallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudMur::~NoeudMur()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudMur::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudMur::afficherConcret() const
{
	// Appel � la version de la classe de base pour l'affichage des enfants.
//	NoeudComposite::afficherConcret();

	// Sauvegarde de la matrice.
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	//glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor3f(1, 0, 0);
	//Ajustement du mur avant la cr�ation
	glRotated(angleRotation_, 0, 0, 1);
	glScaled(facteurMiseAEchelle_, 1, 1);
	
	// Affichage du mod�le.
	vbo_->dessiner();

	//glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);

	// Restauration de la matrice.
	glPopMatrix();
}


void NoeudMur::mettreAJourQuadEnglobantConcret()
{
	// Mettre � jour la position en x des coins avec le facteur de mise � �chelle.
	glm::dvec3 tmp;
	std::cout << "Mise � jour Mur:" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		quadEnglobant_.coins[i].x *= facteurMiseAEchelle_;
		tmp = quadEnglobant_.coins[i];
		utilitaire::calculerPositionApresRotation(tmp, quadEnglobant_.coins[i], angleRotation_);
		quadEnglobant_.coins[i] += positionRelative_;
		std::cout << "coin " << i << ": " << quadEnglobant_.coins[i].x << ", " << quadEnglobant_.coins[i].y << std::endl;
	}
}
void NoeudMur::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
