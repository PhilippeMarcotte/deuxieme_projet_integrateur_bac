///////////////////////////////////////////////////////////////////////////////
/// @file NoeudRobot.cpp
/// @author Martin Paradis
/// @date 2015-08-30
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "NoeudRobot.h"

#include "NoeudRoues.h"

#include "Utilitaire.h"

#include "GL/glew.h"
#include <cmath>
#include <iostream>

#include "Modele3D.h"
#include "OpenGL_VBO.h"

#include "VisiteurAbstrait.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"

#include "NoeudTypes.h"

#include "RectangleEnglobant.h"

const glm::dvec3 NoeudRobot::POSITION_CAPTEUR_DISTANCE_GAUCHE = { 3.47, 1.85, 5.0 };
const glm::dvec3 NoeudRobot::POSITION_CAPTEUR_DISTANCE_CENTRE = { 4.2695, 0.1, 5.0 };
const glm::dvec3 NoeudRobot::POSITION_CAPTEUR_DISTANCE_DROITE = { 3.60, -1.80, 5.0 };

const double NoeudRobot::ANGLE_RELATIF_CAPTEUR_DISTANCE_DROITE{ -45.0 };
const double NoeudRobot::ANGLE_RELATIF_CAPTEUR_DISTANCE_CENTRE{ 0.0 };
const double NoeudRobot::ANGLE_RELATIF_CAPTEUR_DISTANCE_GAUCHE{ 45.0 };

const glm::dvec3 NoeudRobot::POSITION_RELATIVE_CERCLE_ENGLOBANT = { 0.0, 0.0, 0.0 };/*{ 1.35, 0.1, 0.0 };*/
const double FACTEUR_ATTENUATION = 0.7;
const double MINIMUM_REBOND = 5;

#define PI 3.14159265

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRobot::NoeudRobot(const std::string& typeNoeud)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par d�faut aux variables membres.
///
/// @param[in] typeNoeud : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRobot::NoeudRobot(const std::string& typeNoeud)
: NoeudComposite{ typeNoeud }
{

	arbre_ = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	table_ = arbre_->chercher(ArbreRenduINF2990::NOM_TABLE);

	NoeudAbstrait* depart_ = table_->chercher(ArbreRenduINF2990::NOM_DEPART);


    profil_ = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
    suiveurLigne_ = profil_->obtenirSuiveurLigne();
    capteursDistance_ = profil_->obtenirCapteursDistance();

    // � modifier avec le merge du profile.
    visiteur_ = make_unique<VisiteurDetectionRobot>(this);

	positionRelative_ = depart_->obtenirPositionRelative();
	angleRotation_ = depart_->obtenirAngleRotation();

	positionDepart();	

	std::shared_ptr<NoeudAbstrait> roueGauche = arbre_->creerNoeud(ArbreRenduINF2990::NOM_ROUES);
	std::shared_ptr<NoeudAbstrait> roueDroite = arbre_->creerNoeud(ArbreRenduINF2990::NOM_ROUES);

	roueGauche_ = std::static_pointer_cast<NoeudRoues>(roueGauche).get();
	roueDroite_ = std::static_pointer_cast<NoeudRoues>(roueDroite).get();

	positionnerRoues();
	table_->ajouter(roueGauche);
	table_->ajouter(roueDroite);

}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudRobot::~NoeudRobot()
///
/// Ce destructeur ne fait rien.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudRobot::~NoeudRobot()
{
	table_->effacer(roueGauche_);
	table_->effacer(roueDroite_);
}

void NoeudRobot::positionDepart()
{
	NoeudAbstrait* depart = arbre_->chercher(ArbreRenduINF2990::NOM_TABLE)->chercher(ArbreRenduINF2990::NOM_DEPART);
	positionRelative_ = depart->obtenirPositionRelative();
	angleRotation_ = depart->obtenirAngleRotation();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::afficherConcret() const
///
/// Cette fonction effectue le v�ritable rendu de l'objet.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::afficherConcret() const
{
	// Appel � la version de la classe de base pour l'affichage des enfants.
	NoeudComposite::afficherConcret();

	// Sauvegarde de la matrice.
	glPushMatrix();

	glRotatef(angleRotation_, 0.0, 0.0, 1.0);

	// TODO: Figurer pourquoi plateforme est transparente sans cette ligne.
	glColor3f(0.0, 0.0, 0.0);

	// Affichage du mod�le.
	vbo_->dessiner();

    // D�bugage des capteurs de distance.
    suiveurLigne_->afficher();
	if (profil_->obtenirOptionDebogage(DEBOGAGE_CAPTEURS))
	{
		// D�bugage des capteurs de distance.
		for (int i = 0; i < N_CAPTEURS_DISTANCE; i++)
		{
			capteursDistance_->at(i).afficher();
		}
	}
    
	// D�bugage des capteurs de distance.
	suiveurLigne_->afficher();

	// D�bugage des capteurs de distance.
	for (int i = 0; i < N_CAPTEURS_DISTANCE; i++)
	{
		capteursDistance_->at(i).afficher();
	}

	// Restauration de la matrice.
	glPopMatrix();

	rectangleEnglobant_.afficher(positionCourante_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::accepterVisiteur(VisiteurAbstrait* visiteur)
///
/// Cette fonction prend le pointeur de ce noeud et le passe au visiteur pour que ce dernier puisse d�l�guer
/// sa t�che � la m�thode qui se charge de ce type de noeud.
///
/// @param[in] visiteur: le pointeur au visiteur abstrait. (pour d�l�guer au concret apr�s)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::accepterVisiteur(VisiteurAbstrait* visiteur)
{
	visiteur->visiter(this);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::animer(float dt)
///
/// Cette fonction calcule les changements effectuer aux attributs du robot selon les
/// vitesses des moteurs de droite et de gauche
///
/// @param[in] dt: difference de temps entre deux animations (autour de 0,0166)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::animer(float dt)
{
    mettreAJourPosition(dt);
    mettreAJourCapteurs();
    mettreAJourFormeEnglobante();

    arbre_->accepterVisiteur(visiteur_.get());

	positionnerRoues();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::verifierCollision(NoeudPoteau* poteau)
///
/// Cette fonction v�rifie s'il y a une collision avec le robot et un poteau
///
/// @param[in] noeud: Prend le NoeudPoteau en param�tre ce qui correspond aux poteaux.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

bool NoeudRobot::verifierCollision(NoeudPoteau* poteau)
{
	CercleEnglobant* cercle = poteau->obtenirFormeEnglobante();
    bool collision = false; // rectangleEnglobant_.calculerIntersection(*cercle);

    /*
	if (collision)
	{
        glm::dvec3 normaleCollision;
        rectangleEnglobant_.calculerCollision(*cercle, normaleCollision);
		effectuerCollision(normaleCollision);
	}
    */
	return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::verifierCollision(NoeudMur* noeud)
///
/// Cette fonction v�rifie s'il y a une collision avec le robot et un mur.
///
/// @param[in] noeud: Prend le NoeudMur en param�tre ce qui correspond aux murs.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////



bool NoeudRobot::verifierCollision(NoeudMur* noeud)
{
    RectangleEnglobant* rectangle = noeud->obtenirFormeEnglobante();
    bool collision = false; //rectangleEnglobant_.calculerIntersection(*rectangle);
 
    /*
	if (collision)
	{
		glm::dvec3 normaleMur, perpendiculaireMur;
		rectangle->calculerVecteursOrientation(normaleMur, perpendiculaireMur);

		effectuerCollision(normaleMur);
	}
    */
	return collision;

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::verifierCollision(NoeudTable* noeud)
///
/// Cette fonction v�rifie s'il y a une collision avec le robot et la table.
///
/// @param[in] noeud: Prend le noeudTable en param�tre ce qui correspond � la table.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////


bool NoeudRobot::verifierCollision(NoeudTable* noeud)
{
	RectangleEnglobant* rectangle = noeud->obtenirFormeEnglobante();
	// TODO: � changer pour v�rifier
	glm::dvec3 coins[4];
    rectangleEnglobant_.calculerPositionCoins(coins);
	bool collision = false;

	for (unsigned i = 0; i < 4 && !collision; i++)
	{
		if (!rectangle->calculerEstDansForme(coins[i]))
		{
			//collision = true;
		}
	}
    /*
	if (collision)
	{
		glm::dvec3 normaleTable, perpendiculaireTable;
		rectangle->calculerVecteursOrientation(normaleTable, perpendiculaireTable);

		effectuerCollision(normaleTable);
	}
    */
	return collision;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::mettreAJourCapteurs()
///
/// Cette fonction met � jour les capteurs de distance selon leur position et leur angle.
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void NoeudRobot::mettreAJourCapteurs()
{
	suiveurLigne_->mettreAJourCapteurs(positionRelative_, angleRotation_);
	for (int i = 0; i < N_CAPTEURS_DISTANCE; i++)
	{
		capteursDistance_->at(i).mettreAJour(positionRelative_, angleRotation_);
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::mettreAJourPosition(const float& dt)
///
/// Cette fonction met � jour la position du robot selon sa vitesse et son acc�l�ration.
///
/// @param[in] dt: difference de temps entre deux animations (autour de 0,0166)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::mettreAJourPosition(const float& dt)
{
	//std::cout << estEnCollision_ << std::endl;
	float vitesseDroiteTemp = vitesseDroite_, vitesseGaucheTemp = vitesseGauche_;
	//std::cout << "d c : " << vitesseCouranteDroite_ << "d : " << vitesseDroite_ << std::endl;
	//std::cout << "g c : " << vitesseCouranteDroite_ << "g : " << vitesseGauche_ << std::endl;
	if (!estEnCollision_)
	{
		//Calcul de la diff�rence entre les vitesses de gauche et droite
		vitesseRotation_ = vitesseCouranteGauche_ - vitesseCouranteDroite_;
	}
	else
	{
		vitesseDroite_ = vitesseDroiteCollision_;
		vitesseGauche_ = vitesseGaucheCollision_;
	}
	//std::cout << "d c : " << vitesseCouranteDroite_ << "d : " << vitesseDroite_ << std::endl;
	//Calcul de la r�sultante de la vitesse relative
	float diffD = vitesseDroite_ - vitesseCouranteDroite_, diffG = vitesseGauche_ - vitesseCouranteGauche_;
	if (diffD < 0)
	{
		diffD = -diffD;
	}
	if (diffG < 0)
	{
		diffG = -diffG;
	}
	if (diffD < (acceleration_ * dt) && vitesseDroite_ == 0)
	{
		vitesseCouranteDroite_ = 0;
	}
	else
	{
		if (vitesseDroite_ < 0)
		{
			if (vitesseCouranteDroite_ > vitesseDroite_)
			{
				vitesseCouranteDroite_ -= acceleration_ * dt;
			}
			else
			{
				vitesseCouranteDroite_ += acceleration_ * dt;
			}
		}
		else
		{
			if (vitesseCouranteDroite_ < vitesseDroite_)
			{
				vitesseCouranteDroite_ += acceleration_ * dt;
			}
			else
			{
				vitesseCouranteDroite_ -= acceleration_ * dt;
			}
		}
	}
	if (diffG < (acceleration_*dt) && vitesseGauche_ == 0)
	{
		vitesseCouranteGauche_ = 0;
	}
	else
	{
		if (vitesseGauche_ < 0)
		{
			if (vitesseCouranteGauche_ > vitesseGauche_)
			{
				vitesseCouranteGauche_ -= acceleration_ * dt;
			}
			else
			{
				vitesseCouranteGauche_ += acceleration_ * dt;
			}
		}
		else
		{
			if (vitesseCouranteGauche_ < vitesseGauche_)
			{
				vitesseCouranteGauche_ += acceleration_ * dt;
			}
			else
			{
				vitesseCouranteGauche_ -= acceleration_ * dt;
			}
		}
	}
	float relativeGaucheDroite = vitesseCouranteGauche_ + vitesseCouranteDroite_;
	//Calculs des nouvelles positions et du nouvel angle
	angleRotation_ -= dt * vitesseRotation_;
	positionRelative_.x += dt * relativeGaucheDroite / 10 * cos(utilitaire::DEG_TO_RAD(angleRotation_));
	positionRelative_.y += dt * relativeGaucheDroite / 10 * sin(utilitaire::DEG_TO_RAD(angleRotation_));
	vitesseDroite_ = vitesseDroiteTemp;
	vitesseGauche_ = vitesseGaucheTemp;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::mettreAJourRectangleEnglobant()
///
/// Cette fonction permet de mettre � jour le rectangle englobant du robot avec un cercle.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::mettreAJourFormeEnglobante()
{
    double hauteur = boiteEnglobanteModele_.coinMax.y - boiteEnglobanteModele_.coinMin.y;
    double largeur = boiteEnglobanteModele_.coinMax.x - boiteEnglobanteModele_.coinMin.x;

    double positionBoiteX = boiteEnglobanteModele_.coinMin.x + largeur / 2.0;
    double positionBoiteY = boiteEnglobanteModele_.coinMin.y + hauteur / 2.0;
    glm::dvec3 positionBoite = { positionBoiteX, positionBoiteY, 0.0 };

    utilitaire::calculerPositionApresRotation(positionBoite, positionBoite, angleRotation_);
    glm::dvec3 positionRectangle = { positionCourante_.x + positionBoite.x, positionCourante_.y + positionBoite.y, 0.0 };

    rectangleEnglobant_.mettreAJour(positionRectangle, angleRotation_, hauteur, largeur);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::effectuerCollision()
///
/// Cette fonction permet d'effectuer la collision lorsque celle-ci est d�tect�e.
/// Les vitesses sont chang�es selon les vecteurs r�sultants de la collision.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::effectuerCollision(glm::dvec3 normale)
{
	// TODO: Continuer l'impl�mentation de cette m�thode.
	estEnCollision_ = true;
	glm::dvec3 robotReflechi, vitesseAngulaireRobotReflechi;

	glm::dvec3 vitesseRobot, vitesseAngulaireRobot;
	rectangleEnglobant_.calculerVecteursOrientation(vitesseRobot, vitesseAngulaireRobot);

	robotReflechi = glm::reflect(vitesseRobot, normale);
	vitesseAngulaireRobotReflechi = glm::reflect(vitesseAngulaireRobot, normale);

	double vitesseAngulaire = vitesseCouranteGauche_ - vitesseCouranteDroite_;

	vitesseRotation_ = atan(vitesseAngulaireRobotReflechi.y / vitesseAngulaireRobotReflechi.x)/*+ MINIMUM_REBOND*vitesseAngulaire*/;

	double vitesseRelative = vitesseCouranteDroite_ + vitesseCouranteGauche_;

	glm::dvec3 vecVitesseDroite = robotReflechi * vitesseAngulaireRobotReflechi;

	vitesseCouranteDroite_ = glm::sign(vitesseRelative)*-MINIMUM_REBOND + FACTEUR_ATTENUATION*(-vitesseRelative * sqrt(pow(vecVitesseDroite.x, 2) + pow(vecVitesseDroite.y, 2)));
	vitesseCouranteGauche_ = glm::sign(vitesseRelative)*-MINIMUM_REBOND + FACTEUR_ATTENUATION*(-vitesseRelative + vitesseCouranteDroite_);
	/*if (vitesseRelative == 0)
	{
		vitesseRotation_ = glm::sign(vitesseAngulaire) * MINIMUM_REBOND*3;
	}*/

	////Hein
	//	if (0.0 < vitesseRelative && vitesseRelative < 3.0)
	//	{
	//		vitesseCouranteDroite_ -= 10.0;
	//		vitesseCouranteGauche_ -= 6.0;
	//	}
	//	else if (-3.0 < vitesseRelative && vitesseRelative < 0.0)
	//	{
	//		vitesseCouranteDroite_ += 10.0;
	//		vitesseCouranteGauche_ += 6.0;
	//	}
	//	std::cout << "Vitesse Courante Droite" << vitesseCouranteDroite_ << std::endl;
	//	std::cout << "Vitesse Courante Gauche" << vitesseCouranteGauche_ << std::endl;
	//	std::cout << "Vitesse relative" << vitesseRelative << std::endl;


	vitesseDroiteCollision_ = 0;
	vitesseGaucheCollision_ = 0;

	//std::cout << "Collision avec un mur." << std::endl;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudRobot::positionnerRoues()
///
/// Cette fonctione permet de positionner les roues du robot par rapport �
/// son angle de rotation et sa position relative.
///
/// @param[in] Aucun
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void NoeudRobot::positionnerRoues()
{
	//Positionner la roue gauche en fonction du robot
	roueGauche_->assignerAngleRotation(angleRotation_);
	glm::dvec3 position = positionRelative_;
	position[0] = position[0] - sin(angleRotation_*PI / 180)*0.0;
	position[1] = position[1] + cos(angleRotation_*PI / 180)*0.0;
	position[2] = 0.8;
	roueGauche_->assignerPositionRelative(position);
	roueGauche_->setVitesseCourante(vitesseCouranteGauche_);

	//Positionner la roue droite en fonction du robot
	roueDroite_->assignerAngleRotation(angleRotation_);
	position = positionRelative_;
	position[0] = position[0] + sin(angleRotation_*PI / 180)*4.2;
	position[1] = position[1] - cos(angleRotation_*PI / 180)*4.2;
	position[2] = 0.8;
	roueDroite_->assignerPositionRelative(position);
	roueDroite_->setVitesseCourante(vitesseCouranteDroite_);
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////