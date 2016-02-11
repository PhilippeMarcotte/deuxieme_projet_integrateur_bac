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

	//glScaled(facteurMiseAEchelle_, facteurMiseAEchelle_, 1);
	//glRotatef(90, 1, 0, 0);
	//glRotatef(90, 0, 1, 0);

	// Affichage du mod�le.
	vbo_->dessiner();

	// Restauration de la matrice.
	glPopMatrix();
}

//TODO:
//Bo�te englobante d'un mur en ce moment. Doit �tre chang�
utilitaire::BoiteEnglobante NoeudDepart::obtenirBoiteEnglobanteCourante() const
{
	utilitaire::BoiteEnglobante boiteEnglobanteCourante;
	// Mettre � jour la position en x des coins avec le facteur de mise � �chelle.
	boiteEnglobanteCourante.coinMin[0] = boiteEnglobanteModele_.coinMin[0] * facteurMiseAEchelle_;
	boiteEnglobanteCourante.coinMax[0] = boiteEnglobanteModele_.coinMax[0] * facteurMiseAEchelle_;

	// Mettre � jour la position des coins de la boite avec l'angle de rotation du noeud.
	utilitaire::calculerPositionApresRotation(boiteEnglobanteModele_.coinMin, boiteEnglobanteCourante.coinMin, angleRotation_);
	utilitaire::calculerPositionApresRotation(boiteEnglobanteModele_.coinMax, boiteEnglobanteCourante.coinMax, angleRotation_);

	// Mettre � jour les coins avec la position relative.
	boiteEnglobanteCourante.coinMin = boiteEnglobanteModele_.coinMin + positionRelative_;
	boiteEnglobanteCourante.coinMax = boiteEnglobanteModele_.coinMax + positionRelative_;

	return boiteEnglobanteCourante;
}

void NoeudDepart::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
