#include "VisiteurDetectionRobot.h"

#include "ArbreRenduINF2990.h"
#include "NoeudTypes.h"

#include "FacadeModele.h"
#include "CapteurDistance.h"
#include "SuiveurLigne.h"


VisiteurDetectionRobot::VisiteurDetectionRobot()
{
}


VisiteurDetectionRobot::VisiteurDetectionRobot(NoeudRobot* robot)
        : robot_(robot)
{
    ProfilUtilisateur* profil = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
    suiveurLigne_ = profil->obtenirSuiveurLigne();
    capteursDistance_ = profil->obtenirCapteursDistance();
}


VisiteurDetectionRobot::~VisiteurDetectionRobot()
{
}


void VisiteurDetectionRobot::visiter(ArbreRendu* noeud)
{
    noeud->chercher(ArbreRenduINF2990::NOM_TABLE)->accepterVisiteur(this);
}


void VisiteurDetectionRobot::visiter(NoeudTable* noeud)
{
    int nEnfants = noeud->obtenirNombreEnfants();
    for (int i = 0; i < nEnfants; i++)
    {
        noeud->chercher(i)->accepterVisiteur(this);
    }
}


void VisiteurDetectionRobot::visiter(NoeudLigne* noeud)
{
    suiveurLigne_->verifierDetection(noeud);
}


void VisiteurDetectionRobot::visiter(NoeudPoteau* noeud)
{
    for (int i = 0; i < NoeudRobot::N_CAPTEURS_DISTANCE; i++)
    {
        capteursDistance_->at(i).verifierDetection(noeud);
    }
}


void VisiteurDetectionRobot::visiter(NoeudMur* noeud)
{
    for (int i = 0; i < NoeudRobot::N_CAPTEURS_DISTANCE; i++)
    {
        capteursDistance_->at(i).verifierDetection(noeud);
    }
}