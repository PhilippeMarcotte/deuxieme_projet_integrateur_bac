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
	// Sauvegarde de la matrice.
	glPushMatrix();

	if (estSelectionne())
	{
		glColor4d(1.0, 0.2, 0.0, 1.0);
	}
	else
	{
		glColor4d(0.0, 0.0, 0.0, 1.0);
	}
	// Effectuer la mise � �chelle.
	glScaled(facteurMiseAEchelle_, facteurMiseAEchelle_, 1);
	
	// Affichage du mod�le.
	vbo_->dessiner();

	// Restauration de la matrice.
	glPopMatrix();
}

void NoeudPoteau::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
