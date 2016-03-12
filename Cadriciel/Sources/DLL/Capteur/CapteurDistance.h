///////////////////////////////////////////////////////////////////////////
/// @file CapteurDistance.h
/// @author Olivier St-Amour
///
/// version 2.1
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef CAPTEUR_DISTANCE_H
#define CAPTEUR_DISTANCE_H

#include "RectangleEnglobant.h"

class NoeudPoteau;
class NoeudMur;

enum PositionCapteurDistance
{
    CAPTEUR_DISTANCE_DROITE,
    CAPTEUR_DISTANCE_CENTRE,
    CAPTEUR_DISTANCE_GAUCHE
};

enum EtatCapteurDistance
{
    AUCUNE_DETECTION,
    DETECTION_ZONE_SECURITAIRE,
    DETECTION_ZONE_DANGER
};

///////////////////////////////////////////////////////////////////////////
/// @class CapteurDistance
/// @brief Classe qui repr�sente un capteur de distance du robot.  
///
///        Cette classe s'occupe de g�rer la d�tection des poteaux et des murs. 
///
/// @author Olivier St-Amour
/// @date 2016-02-23
///////////////////////////////////////////////////////////////////////////
class CapteurDistance
{
public:
    // Constructeur par d�faut.
    CapteurDistance();
    // Constructeur par param�tres.
    CapteurDistance(const glm::dvec3& positionCentre, const double& angle);
    //Destructeur
    ~CapteurDistance();

    // M�thodes permettant de mettre � jour l'�tat du capteur.
    void verifierDetection(NoeudPoteau* noeud);
    void verifierDetection(NoeudMur* noeud);

    // M�thode permettant de manipuler l'�tat du capteur.
    inline EtatCapteurDistance obtenirEtat();
    inline void reinitialiserEtat();

    // M�thode permettant de manipuler la largeur des zones de d�tection.
    inline void assignerHauteurZoneSecuritaire(const double& hauteur);
    inline void assignerHauteurZoneDanger(const double& hauteur);

    //TODO: Ajouter les m�thodes pour assigner un prochain comportement (danger/securitaire)

    // M�thode permettant de mettre � jour 
	void mettreAJourPosition(const glm::dvec3& positionRobot, const double& angleRotationRobot);

private:
    static const double LARGEUR;
    static const double MAX_HAUTEUR_TOTALE;

	bool estActif_{ true };
    EtatCapteurDistance etat_{ AUCUNE_DETECTION };

    RectangleEnglobant zoneSecuritaire_;
    RectangleEnglobant zoneDanger_;
};

inline void CapteurDistance::assignerHauteurZoneSecuritaire(const double& hauteur)
{
    zoneSecuritaire_.assignerHauteur(hauteur);
}

inline void CapteurDistance::assignerHauteurZoneDanger(const double& hauteur)
{
    zoneDanger_.assignerHauteur(hauteur);
}

inline EtatCapteurDistance CapteurDistance::obtenirEtat()
{
    return etat_;
}

inline void CapteurDistance::reinitialiserEtat()
{
    etat_ = AUCUNE_DETECTION;
}

#endif // CAPTEUR_DISTANCE_H