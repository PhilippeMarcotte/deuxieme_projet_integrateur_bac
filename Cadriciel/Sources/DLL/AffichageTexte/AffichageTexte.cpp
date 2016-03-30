#include <Windows.h>
#include <chrono>
#include <ctime>
#include <FTGL/ftgl.h>
#include "FacadeModele.h"
#include "ProjectionOrtho.h"
#include "ProfilUtilisateur.h"
#include "AffichageTexte.h"


AffichageTexte::AffichageTexte()
{
    assert(!font_.Error());
    font_.FaceSize(16);
    profil_ = FacadeModele::obtenirInstance()->obtenirProfilUtilisateur();
    vue_ = FacadeModele::obtenirInstance()->obtenirVue();
    reinitialiserChrono();
}

AffichageTexte::~AffichageTexte()
{
}

void AffichageTexte::demarrerChrono()
{
    if (enPause_)
    {
        debut_ = std::chrono::system_clock::now() - (pause_ - debut_);
        enPause_ = false;
    }
}

void AffichageTexte::pauseChrono()
{
    if (!enPause_)
    {
        pause_ = std::chrono::system_clock::now();
        enPause_ = true;
    }
}

void AffichageTexte::reinitialiserChrono()
{
    debut_ = std::chrono::system_clock::now();
    pause_ = std::chrono::system_clock::now();
}

void AffichageTexte::afficher()
{
    glm::ivec2 dimensions = vue_->obtenirProjection().obtenirDimensionCloture();
    
    // Positionner le texte � un certain d�callage par rapport � la cl�ture.
    FTPoint positionProfil(OFFSET_X, dimensions.y - OFFSET_Y, 0.0);
    FTPoint positionTemps(OFFSET_X, OFFSET_Y, 0.0);

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    // TODO: figurer comment changer la couleur du texte.
    glColor3f(1.0, 1.0, 1.0);

    if (profilEstAffiche_)
    {
        std::string profil = profil_->obtenirNomDernierProfil();
        font_.Render(profil.c_str(), -1, positionProfil);
    }

    if (tempsEstAffiche_)
    {
        std::chrono::time_point<std::chrono::system_clock> courant = std::chrono::system_clock::now();

        double duree = 0.0;
        if (!enPause_)
        {
            // Si on ne se trouve pas en pause, on affiche la dur�e entre le d�but et le temps courant.
            duree = std::chrono::duration<double>(courant - debut_).count() + duree;
        }
        else
        {
            // Si on se trouve en pause, on affiche la dur�e entre la pause et le temps courant.
            duree = std::chrono::duration<double>(pause_ - debut_).count();
        }

        // Obtenir la dur�e en secondes sous forme de string.
        std::string secondes{ std::to_string((int)duree % 60) };
        if (secondes.size() < 2)
        {
            secondes = "0" + secondes;
        }

        // Obtenir la dur�e en minutes sous forme de string.
        std::string minutes{ std::to_string(((int)duree / 60) % 60) };
        if (minutes.size() < 2)
        {
            minutes = "0" + minutes;
        }

        // Formatage du temps sous la forme "MM : SS".
        std::string compteur = minutes + " : " + secondes;
        font_.Render(compteur.c_str(), -1, positionTemps);
    }

    glPopAttrib();
}
