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

//#include "./../../Enum/TypeComportementEnum.cs"

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
    void mettreAJour(const glm::dvec3& positionRobot, const double& angleRotationRobot);

    // M�thode permettant de manipuler l'�tat du capteur.
    inline EtatCapteurDistance obtenirEtat();
    inline void reinitialiserEtat();

    // M�thode de modification des attributs.
    void assignerActif(bool estActif);
    void assignerParametreZoneDanger(/*TypeComportement comportement,*/ double distance);
    void assignerParametreZoneSecuritaire(/*TypeComportement comportement,*/ double distance);

    // M�thode permettant de manipuler la largeur des zones de d�tection.
    inline void assignerLargeurZoneSecuritaire(const double& largeur);
    inline void assignerLargeurZoneDanger(const double& largeur);

    // Afficher le capteur de distance.
    void afficher() const;

    // Attributs constants publiques.
    static const double HAUTEUR;
    static const double MAX_LARGEUR_TOTALE;
    static const double LARGEUR_DEFAUT;

private:
    bool estActif_{ true };
    
    double largeurDanger_{ 5.0 };
    double largeurSecuritaire_{ 5.0 };

    EtatCapteurDistance etat_{ AUCUNE_DETECTION };
    glm::dvec3 positionCapteur_;

    RectangleEnglobant zoneSecuritaire_;
    RectangleEnglobant zoneDanger_;
    
    glm::dvec3 positionRelative_;
    double angleRelatif_;
};


////////////////////////////////////////////////////////////////////////////////
///
/// @fn inline void CapteurDistance::assignerHauteurZoneSecuritaire(const double& largeur)
///
/// Cettre m�thode permet d'assigner une largeur � la zone s�curitaire du
/// capteur de distance.
///
/// @param[in] hauteur : indique la hauteur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////////
inline void CapteurDistance::assignerLargeurZoneSecuritaire(const double& largeur)
{
    zoneSecuritaire_.assignerLargeur(largeur);
}


////////////////////////////////////////////////////////////////////////////////
///
/// inline void CapteurDistance::assignerHauteurZoneDanger(const double& largeur)
///
/// Cettre m�thode permet d'assigner une largeur � la zone de danger du
/// capteur de distance.
///
/// @param[in] hauteur : indique la hauteur.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////////
inline void CapteurDistance::assignerLargeurZoneDanger(const double& largeur)
{
    zoneDanger_.assignerLargeur(largeur);
}


////////////////////////////////////////////////////////////////////////////////
///
/// inline EtatCapteurDistance CapteurDistance::obtenirEtat()
///
/// Cette m�thode retourne l'�tat du capteur de distance.
///
/// @return Un enum indiquant s'il y a une d�tection dans l'une des zones de
///         d�tection.
///
////////////////////////////////////////////////////////////////////////////////
inline EtatCapteurDistance CapteurDistance::obtenirEtat()
{
    return etat_;
}


////////////////////////////////////////////////////////////////////////////////
///
/// inline void CapteurDistance::reinitialiserEtat()
///
/// Cette m�thode permet de r�initialiser l'�tat du capteur � aucune d�tection.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////////////
inline void CapteurDistance::reinitialiserEtat()
{
    etat_ = AUCUNE_DETECTION;
}

#endif // CAPTEUR_DISTANCE_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
