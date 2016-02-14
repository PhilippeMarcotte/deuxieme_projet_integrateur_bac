///////////////////////////////////////////////////////////////////////////////
/// @file NoeudDepart.cpp
/// @author Fr�d�ric Gr�goire
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudDepart.h"
#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "VisiteurAbstrait.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudDepart::NoeudDepart(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudDepart::NoeudDepart(const std::string& typeNoeud)
	: NoeudAbstrait{ typeNoeud }
{
	estDuplicable_ = false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudDepart::~NoeudDepart()
///
/// Ce destructeur d�sallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudDepart::~NoeudDepart()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudDepart::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudDepart::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();

	if (estSelectionne())
	{
		glColor4d(1.0, 0.20, 0.0, 1.0);
	}
	else
	{
		glColor4d(0.0, 0.0, 0.0, 1.0);
	}

	glRotated(angleRotation_, 0, 0, 1);

	// Affichage du mod�le.
	vbo_->dessiner();

	// Restauration de la matrice.
	glPopMatrix();
}

void NoeudDepart::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
