#include "RectangleEnglobant.h"

#include "GL/glew.h"
#include <glm/glm.hpp>
#include <vector>
#include "Utilitaire.h"
#include "CercleEnglobant.h"

RectangleEnglobant::RectangleEnglobant()
{
}


RectangleEnglobant::RectangleEnglobant(const glm::dvec3& centre, const double& angle, 
    const double& hauteur, const double& largeur)
        : FormeEnglobanteAbstraite(centre), angle_(angle), hauteur_(hauteur), largeur_(largeur)
{
}


RectangleEnglobant::~RectangleEnglobant()
{
}

void RectangleEnglobant::initialiser(const utilitaire::BoiteEnglobante& boiteEnglobante)
{
    hauteur_ = glm::abs(boiteEnglobante.coinMax.y - boiteEnglobante.coinMin.y);
    largeur_ = glm::abs(boiteEnglobante.coinMax.x - boiteEnglobante.coinMin.x);
}

bool RectangleEnglobant::calculerEstDansLimites(const double& xMin, const double& xMax,
                                                const double& yMin, const double& yMax) const
{
    const int N_COINS = 4;
    glm::dvec3 coins[N_COINS];
    calculerPositionCoins(coins);
    
    bool coinsDansLimite = true;

    for (int i = 0; i < N_COINS && coinsDansLimite; i++)
    {
        coinsDansLimite = utilitaire::DANS_LIMITESXY(coins[i].x, xMin, xMax,
                                                     coins[i].y, yMin, yMax);
    }
    return coinsDansLimite;
}

bool RectangleEnglobant::calculerEstDansForme(const glm::dvec3& point) const
{
    // Obtenir les vecteurs unitaires qui repr�sentent l'orientation du rectangle.
    glm::dvec3 orientationHauteur, orientationLargeur;
    calculerVecteursOrientation(orientationHauteur, orientationLargeur);

    // Le vecteur qui repr�sente la distance entre le centre du rectangle et le point.
    glm::dvec3 distancePointCentre = point - positionCentre_;

    // La projection du vecteur sur la largeur et la hauteur du rectangle
    double projectionHauteur = glm::dot(distancePointCentre, orientationHauteur);
    double projectionLargeur = glm::dot(distancePointCentre, orientationLargeur);
    
    // Si les projections se situent dans le rectangle, le point est �galement dans le rectangle.
    return utilitaire::DANS_LIMITESXY(projectionHauteur, -hauteur_ / 2.0, hauteur_ / 2.0,
                                      projectionLargeur, -largeur_ / 2.0, largeur_ / 2.0);
}


bool RectangleEnglobant::calculerIntersection(const RectangleEnglobant& rectangle) const
{     
    const int HAUTEUR = 0;
    const int LARGEUR = 1;

    const int N_RECTANGLES = 2;
    const int N_ORIENTATIONS = 2;

    const int N_COINS = 4;

    const RectangleEnglobant* rectangles[N_RECTANGLES];
    rectangles[0] = this;
    rectangles[1] = &rectangle;

    bool enIntersection = true;
    for (int i = 0; i < N_RECTANGLES && enIntersection; i++)
    {
        glm::dvec3 orientations[N_ORIENTATIONS];
        rectangles[i]->calculerVecteursOrientation(orientations[HAUTEUR], orientations[LARGEUR]);

        glm::dvec3 distances[N_COINS];

        // Index circulaire pour obtenir l'autre rectangle.
        int k = (i + 1) % 2;
         
        // Calcule des distances entre le centre du rectangle courant et les 4 coins de l'autre rectangle. 
        rectangles[k]->calculerDistancesPoint(distances, rectangles[i]->obtenirPositionCentre());

        // On place les dimensions dans un tableau afin de pouvoir les utiliser dans une boucle.
        double dimensions[N_ORIENTATIONS];
        dimensions[HAUTEUR] = rectangles[i]->hauteur_;
        dimensions[LARGEUR] = rectangles[i]->largeur_;

        // Projeter les distances sur chaque vecteur d'orientation du rectangle puis v�rifier la disjonction.
        for (int j = 0; j < N_ORIENTATIONS && enIntersection; j++)
        {
            double min, max;
            rectangles[i]->calculerIntervalleProjection(distances, orientations[j], min, max);
            enIntersection = !rectangles[i]->calculerDisjonctionSurIntervalle(min, max,
                -dimensions[j] / 2.0, dimensions[j] / 2.0);
        }
    }
    return enIntersection;
}



void RectangleEnglobant::calculerVecteursOrientation(glm::dvec3& orientationHauteur, glm::dvec3& orientationLargeur) const
{
    // Calcule du vecteur qui repr�sente la hauteur.
    orientationLargeur = { glm::cos(utilitaire::DEG_TO_RAD(angle_)),
                           glm::sin(utilitaire::DEG_TO_RAD(angle_)),
                           0.0 };

    // Calcule rapide de la perpendiculaire du vecteur.
    orientationHauteur = { -orientationLargeur.y, orientationLargeur.x, 0.0 };

    // On normalise les vecteurs pour faciliter d'autres calcules.
    orientationLargeur = glm::normalize(orientationLargeur);
    orientationHauteur = glm::normalize(orientationHauteur);
}


double RectangleEnglobant::calculerRayon() const
{
    // Obtenir les vecteurs unitaires qui repr�sente l'orientation du rectangle.
    glm::dvec3 orientationLargeur, orientationHauteur;
    calculerVecteursOrientation(orientationHauteur, orientationLargeur);

    orientationHauteur *= hauteur_;
    orientationLargeur *= largeur_;

    return glm::distance(orientationHauteur, orientationLargeur);
}


void RectangleEnglobant::calculerDistancesPoint(glm::dvec3 distances[4], 
    const glm::dvec3& point) const
{
    glm::dvec3 orientationHauteur, orientationLargeur;
    calculerVecteursOrientation(orientationHauteur, orientationLargeur);

    // Caculer la distance entre le point et le centre puis 
    // la distance entre le centre et les 2 dimensions.
    glm::dvec3 distancePointCentre = point - positionCentre_;
    glm::dvec3 distanceCentreHauteur = orientationHauteur * hauteur_ / 2.0;
    glm::dvec3 distanceCentreLargeur = orientationLargeur * largeur_ / 2.0;

    // Calculer la distance des coins pour chacun des cadrans. 
    distances[0] = ( distancePointCentre + distanceCentreHauteur + distanceCentreLargeur );
    distances[1] = ( distancePointCentre - distanceCentreHauteur + distanceCentreLargeur );
    distances[2] = ( distancePointCentre - distanceCentreHauteur - distanceCentreLargeur );
    distances[3] = ( distancePointCentre + distanceCentreHauteur - distanceCentreLargeur );
}


void RectangleEnglobant::calculerIntervalleProjection(glm::dvec3 distances[4], 
    const glm::dvec3& orientation, double& min, double& max) const
{
    double projection = 0.0;

    // Initialiser les min/max au premier index.
    min = glm::dot(distances[0], orientation);
    max = glm::dot(distances[0], orientation);

    for (int i = 1; i < 4; i++)
    {
        projection = glm::dot(distances[i], orientation);

        // Trouver les min/max pour la projection.
        if (projection < min)
        {
            min = projection;
        }
        if (projection > max)
        {
            max = projection;
        }
    }
}


bool RectangleEnglobant::calculerDisjonctionSurIntervalle(const double& min1, const double& max1,
    const double& min2, const double& max2) const
{
    // Il y a une disjonction si les deux extr�mit�s ne se trouvent pas dans le m�me intervalle
    // que les deux autres extr�mit�s.

    // min1 --- max1 ---------- min2 --- max2
    bool disjonction12 = max1 < min2;
    // min2 --- max2 ---------- min1 --- max1
    bool disjonction21 = max2 < min1;

    return disjonction12 || disjonction21;
}


void RectangleEnglobant::mettreAJour(const glm::dvec3& positionCentre,
    const double& angle, const double& hauteur, const double& largeur)
{
    positionCentre_ = positionCentre;
    angle_ = angle;
    hauteur_ = hauteur;
    largeur_ = largeur;
}


bool RectangleEnglobant::calculerIntersection(const CercleEnglobant& cercle) const
{
    glm::dvec3 positionCercle = cercle.obtenirPositionCentre();
    const int HAUTEUR = 0;
    const int LARGEUR = 1;
    const int N_ORIENTATIONS = 2;
    glm::dvec3 orientations[N_ORIENTATIONS];
    calculerVecteursOrientation(orientations[HAUTEUR], orientations[LARGEUR]);

    glm::dvec3 distances[4];
    calculerDistancesPoint(distances, positionCercle);
    
    double rayon = cercle.obtenirRayon();

    glm::dvec3 distanceCentres = positionCercle - positionCentre_;
    glm::dvec3 orientationDistanceCentre = glm::normalize(distanceCentres);
    
    double min = 0.0;
    double max = 0.0;
    calculerIntervalleProjection(distances, orientationDistanceCentre, min, max);
    bool intersection = !calculerDisjonctionSurIntervalle(-rayon, rayon, min, max);

    for (int i = 0; i < N_ORIENTATIONS && intersection; i++)
    {
        min = 0.0;
        max = 0.0;

        calculerIntervalleProjection(distances, orientations[i], min, max);
        intersection = !calculerDisjonctionSurIntervalle(-rayon, rayon, min, max);
    }
    return intersection;
}


void RectangleEnglobant::afficher(const glm::dvec3& origine) const
{
    glm::dvec3 positionRelative = positionCentre_ - origine;

    glPushMatrix();

    if (enCollision_)
    {
        glColor3d(0.0, 1.0, 0.0);
    }
    else
    {
        glColor3d(1.0, 0.0, 0.0);
    }

    glTranslated(positionRelative.x, positionRelative.y, 0.0);
    glRotated(angle_, 0.0, 0.0, 1.0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex3d(largeur_ / 2.0, hauteur_ / 2.0, 5.0);
	glVertex3d(-largeur_ / 2.0, hauteur_ / 2.0, 5.0);
	glVertex3d(-largeur_ / 2.0, -hauteur_ / 2.0, 5.0);
	glVertex3d(largeur_ / 2.0, -hauteur_ / 2.0, 5.0);

	glEnd();
    glPopMatrix();
}


void RectangleEnglobant::afficher() const
{
    afficher({ 0.0, 0.0, 5.0 });
}


void RectangleEnglobant::calculerPositionCoins(glm::dvec3 coins[4]) const
{
    glm::dvec3 orientationHauteur, orientationLargeur;
    calculerVecteursOrientation(orientationHauteur, orientationLargeur);

    glm::dvec3 distanceCentreHauteur = orientationHauteur * hauteur_ / 2.0;
    glm::dvec3 distanceCentreLargeur = orientationLargeur * largeur_ / 2.0;

    coins[0] = positionCentre_ + distanceCentreLargeur + distanceCentreHauteur;
    coins[1] = positionCentre_ - distanceCentreLargeur + distanceCentreHauteur;
    coins[2] = positionCentre_ - distanceCentreLargeur - distanceCentreHauteur;
    coins[3] = positionCentre_ + distanceCentreLargeur - distanceCentreHauteur;
}

bool RectangleEnglobant::calculerCollision(const RectangleEnglobant& rectangle, glm::dvec3& normale) const
{
    return false;
}

bool RectangleEnglobant::calculerCollision(const CercleEnglobant& cercle, glm::dvec3& normale) const
{
    glm::dvec3 normaleCollision = cercle.obtenirPositionCentre() - positionCentre_;
    normale = glm::normalize(normaleCollision);
    return true;
}
