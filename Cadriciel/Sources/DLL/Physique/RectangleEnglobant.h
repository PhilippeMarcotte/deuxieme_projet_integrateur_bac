///////////////////////////////////////////////////////////////////////////////
/// @file RectangleEnglobant.h
/// @author Olivier St-Amour
/// @date 2016-03-02
/// @version 2.2
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef RECTANGLE_ENGLOBANT_H
#define RECTANGLE_ENGLOBANT_H

#include "FormeEnglobanteAbstraite.h"

#include <glm/glm.hpp> 
#include <vector>

///////////////////////////////////////////////////////////////////////////
/// @class RectangleEnglobant
/// @brief Classe qui repr�sente le rectangle orient� autour d'un objet.
///
///        Cette classe permet de calculer la d�tection de collision 
///        ainsi que la physique.		   
/// 
/// @author Olivier St-Amour
/// @date 2016-02-22
///////////////////////////////////////////////////////////////////////////
class RectangleEnglobant : public FormeEnglobanteAbstraite
{
public:
    // Constructeur par d�faut.
    RectangleEnglobant();
    // Constructeur par param�tres.
    RectangleEnglobant(const glm::dvec3& centre, const double & angle, 
        const double& hauteur, const double& largeur);
    // Destructeur.
    ~RectangleEnglobant();

    inline void assignerAngle(const double& angle);
    inline void assignerHauteur(const double& hauteur);
    inline void assignerLargeur(const double& largeur);
    
    inline double obtenirAngle() const;
    inline double obtenirHauteur() const;
    inline double obtenirLargeur() const;

    // Permet de calculer si un point se trouve dans une forme englobante.
    virtual bool calculerPointEstDansForme(const glm::dvec3& point) const;
    // Permet de calculer si une forme est en intersection avec un cercle.
    virtual bool calculerIntersection(const CercleEnglobant& cercle) const;
    // Permet de calculer si une forme est en intersection avec un rectangle.
    virtual bool calculerIntersection(const RectangleEnglobant& rectangle) const;
    // Permet de mettre � jour les attributs de la forme.
    void mettreAJour(const glm::dvec3& positionCentre, const double& angle,  
        const double& hauteur, const double& largeur);

    void calculerVecteursOrientation(glm::dvec3& orientationHauteur, glm::dvec3& orientationLargeur) const;

    double calculerRayon() const;

private:
    double angle_{ 0.0 };
    double hauteur_{ 0.0 };
    double largeur_{ 0.0 };

    void calculerIntervalleProjection(glm::dvec3 distances[4], const glm::dvec3& orientation,
        double& min, double& max) const;

    bool calculerDisjonctionSurIntervalle(const double& min1, const double& max1, 
        const double& min2, const double& max2) const;

    void calculerDistancesPoint(glm::dvec3 distances[4], const glm::dvec3& point) const;
};

inline void RectangleEnglobant::assignerAngle(const double& angle)
{
    angle_ = angle;
}

inline void RectangleEnglobant::assignerHauteur(const double& hauteur)
{
    hauteur_ = hauteur;
}

inline void RectangleEnglobant::assignerLargeur(const double& largeur)
{
    largeur_ = largeur;
}

inline double RectangleEnglobant::obtenirAngle() const
{
    return angle_;
}

inline double RectangleEnglobant::obtenirHauteur() const
{
    return hauteur_;
}

inline double RectangleEnglobant::obtenirLargeur() const
{
    return largeur_;
}

#endif // RECTANGLE_ENGLOBANT_H

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
