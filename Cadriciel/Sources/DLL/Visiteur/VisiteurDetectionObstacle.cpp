#include "VisiteurDetectionObstacle.h"

#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"

////////////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDetectionObstacle::VisiteurDetectionObstacle()
///
/// Constructeur par d�faut.
///
/// @return Aucune(constructeur). 
///
////////////////////////////////////////////////////////////////////////////////
VisiteurDetectionObstacle::VisiteurDetectionObstacle()
{
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDetectionObstacle::~VisiteurDetectionObstacle()
///
/// Destructeur.
///
/// @return Aucune(destructeur). 
///
////////////////////////////////////////////////////////////////////////////////
VisiteurDetectionObstacle::~VisiteurDetectionObstacle()
{
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurDetectionObstacle::visiter(ArbreRendu* noeud)
///
/// M�thode permettant d'acc�der aux enfants de l'arbre de rendu. 
///
/// @param[in] noeud : le pointeur qui r�f�rence l'arbre de rendu.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////////
void VisiteurDetectionObstacle::visiter(ArbreRendu* noeud)
{
	obstacleEstDetecte_ = false;
	noeud->chercher(ArbreRenduINF2990::NOM_TABLE)->accepterVisiteur(this);
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDetectionLigne::visiter(NoeudTable* noeud)
///
/// M�thode permettant d'acc�der aux lignes de la table. 
///
/// @param[in] noeud : le pointeur qui r�f�rence la table.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////////
void VisiteurDetectionObstacle::visiter(NoeudTable* noeud)
{
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDetectionObstacle::visiter(NoeudPoteau* noeud)
///
/// M�thode permettant d'ajuster l'�tat du capteur en fonction de la distance 
/// du poteau.
///
/// @param[in] noeud : le pointeur qui r�f�rence le poteau
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////////
void VisiteurDetectionObstacle::visiter(NoeudPoteau* noeud)
{
}

////////////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurDetectionObstacle::visiter(Noeudmur* noeud)
///
/// M�thode permettant d'ajuster l'�tat du capteur en fonction de la distance 
/// du mur.
///
/// @param[in] noeud : le pointeur qui r�f�rence le mur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////////
void VisiteurDetectionObstacle::visiter(NoeudMur* noeud)
{
}
