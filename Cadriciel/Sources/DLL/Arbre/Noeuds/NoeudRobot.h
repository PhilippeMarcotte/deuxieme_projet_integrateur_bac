///////////////////////////////////////////////////////////////////////////
/// @file NoeudRobot.h
/// @author Martin Paradis
/// @date 2015-08-30
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUD_ROBOT_H__
#define __ARBRE_NOEUD_ROBOT_H__

#include "NoeudComposite.h"
#include "GL/glew.h"
#include "SuiveurLigne.h"
#include "CapteurDistance.h"
#include "RectangleEnglobant.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudRobot
/// @brief Classe qui repr�sente le robot du premier projet int�grateur.
///
/// @author Martin Paradis
/// @date 2015-08-30
///////////////////////////////////////////////////////////////////////////
class NoeudRobot : public NoeudComposite
{
public:
	/// Constructeur � partir du type du noeud.
	NoeudRobot(const std::string& typeNoeud);
	/// Destructeur.
	~NoeudRobot();

	/// Affiche le robot.
	virtual void afficherConcret() const;
	virtual void accepterVisiteur(VisiteurAbstrait* visiteur);
	virtual void animer(const float& dt);

	//Permet de modifier les param�tres du robot
	void assignerVitesseRotation(float vitesse);
	void assignerVitesseDroite(float vitesse);
	void assignerVitesseGauche(float vitesse);

	void assignerVitesseDroiteCourante(float vitesse);
	void assignerVitesseGaucheCourante(float vitesse);

	//Permet de r�cup�rer les param�tres du robot.
	float obtenirVitesseDroite() const;
	float obtenirVitesseGauche() const;
	float obtenirVitesseDroiteCourante() const;
	float obtenirVitesseGaucheCourante() const;
    
    // Mise � jour des capteurs du robot. 	
	void mettreAJourCapteurs();
	// Retourne l'�tats des capeurs du robot.
	// Les 3 premiers indiquent la d�tection d'une ligne pour les 3 capteurs optiques du suiveur de ligne.
	uint8_t obtenirEtatSuiveurLigne();

    inline SuiveurLigne* obtenirSuiveurLigne();     
    CapteurDistance* obtenirCapteursDistance(PositionCapteurDistance position);

    // M�thodes d'affichage permettant le d�bogage.
    void afficherCapteursOptique() const;
    void afficherCapteursDistance() const;
    void afficherFormeEnglobante() const;

private:
	float angle_{ 0.f };
	float acceleration_{ 200.0 };
    
    static const int N_CAPTEUR_DISTANCE{ 3 };

	SuiveurLigne suiveurLigne_;
	CapteurDistance capteursDistance_[N_CAPTEUR_DISTANCE];
};

inline SuiveurLigne* NoeudRobot::obtenirSuiveurLigne()
{
    return &suiveurLigne_;
}

#endif // __ARBRE_NOEUD_ROBOT_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
