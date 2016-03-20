///////////////////////////////////////////////////////////////////////////////
/// @file NoeudSegment.cpp
/// @author Olivier St-Amour
/// @date 2016-02-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "NoeudSegment.h"
#include "Utilitaire.h"
#include "VisiteurAbstrait.h"
#include "GL/glew.h"
#include <cmath>

#include "Modele3D.h"
#include "OpenGL_VBO.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudSegment::NoeudSegment(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudSegment::NoeudSegment(const std::string& typeNoeud)
	: NoeudAbstrait(typeNoeud)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudSegment::~NoeudSegment()
///
/// Ce destructeur d�sallouee la liste d'affichage du cube.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudSegment::~NoeudSegment()
{
}

RectangleEnglobant* NoeudSegment::obtenirFormeEnglobante()
{
    return &rectangleEnglobant_;
}


const RectangleEnglobant* NoeudSegment::obtenirFormeEnglobante() const
{
    return &rectangleEnglobant_;
}


void NoeudSegment::animer(float dt)
{
    mettreAJourFormeEnglobante();
}

void NoeudSegment::mettreAJourFormeEnglobante()
{
    double hauteur = boiteEnglobanteModele_.coinMax.y - boiteEnglobanteModele_.coinMin.y;
    double largeur = boiteEnglobanteModele_.coinMax.x - boiteEnglobanteModele_.coinMin.x;
    largeur *= facteurMiseAEchelle_;
    rectangleEnglobant_.mettreAJour(positionCourante_, angleRotation_, hauteur, largeur);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudSegment::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction prend le pointeur de ce noeud et le passe au visiteur pour que ce dernier puisse d�l�guer
/// sa t�che � la m�thode qui se charge de ce type de noeud.
///
/// @param[in] visiteur: le pointeur au visiteur abstrait. (pour d�l�guer au concret apr�s)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudSegment::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudSegment::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudSegment::afficherConcret() const
{
	// Sauvegarde de la matrice.
	glPushMatrix();

	if (selectionne_)
    {
		glColor4d(1.0, 0.2, 0.0, 1.0);
	}
	else 
    {
		glColor4d(0.0, 0.0, 0.0, 1.0);
	}

	//Ajustement du mur avant la cr�ation
	glRotated(angleRotation_, 0, 0, 1);
	glScaled(facteurMiseAEchelle_, 1, 1);

	// Affichage du mod�le.
	vbo_->dessiner();
	// Restauration de la matrice.
	glPopMatrix();
    rectangleEnglobant_.afficher(positionCourante_);
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////