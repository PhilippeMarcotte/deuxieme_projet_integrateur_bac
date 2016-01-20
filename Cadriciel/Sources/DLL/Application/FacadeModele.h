//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.h
/// @author DGI
/// @date 2005-06-15
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_FACADEMODELE_H__
#define __APPLICATION_FACADEMODELE_H__


#include <windows.h>
#include <string>
#include <memory>

class NoeudAbstrait;
class ArbreRenduINF2990;
class EtatAbstrait;

namespace vue {
   class Vue;
}


///////////////////////////////////////////////////////////////////////////
/// @class FacadeModele
/// @brief Classe qui constitue une interface (une fa�ade) sur l'ensemble
///        du mod�le et des classes qui le composent.
///
/// @author Martin Bisson
/// @date 2007-02-20
///////////////////////////////////////////////////////////////////////////
class FacadeModele
{
public:

   /// Destructeur.
   ~FacadeModele();

   /// Obtient l'instance unique de la classe.
   static std::shared_ptr<FacadeModele> obtenirInstance();
   /// Lib�re l'instance unique de la classe.
   static void libererInstance();

   /// Cr�e un contexte OpenGL et initialise celui-ci.
   void initialiserOpenGL(HWND hWnd);
   /// Charge la configuration � partir d'un fichier XML.
   void chargerConfiguration() const;
   /// Enregistre la configuration courante dans un fichier XML.
   void enregistrerConfiguration() const;
   /// Lib�re le contexte OpenGL.
   void libererOpenGL();
   /// Affiche le contenu du mod�le.
   void afficher() const;
   /// Affiche la base du contenu du mod�le.
   void afficherBase() const;

   /// Modifie l'etat courant.
   void modifierEtat(std::shared_ptr<EtatAbstrait> etat);
   // Obtenir l'etat courant.
   inline std::shared_ptr<EtatAbstrait> obtenirEtat();

   /// Retourne la vue courante.
   inline std::shared_ptr<vue::Vue> obtenirVue();
   /// Retourne l'arbre de rendu.
   inline std::shared_ptr<ArbreRenduINF2990> obtenirArbreRenduINF2990() const;
   /// Retourne l'arbre de rendu.
   inline std::shared_ptr<ArbreRenduINF2990> obtenirArbreRenduINF2990();

   /// R�initialise la sc�ne.
   void reinitialiser();

   /// Anime la sc�ne.
   void animer(float temps);


private:
   /// Constructeur par d�faut.
   FacadeModele() = default;

   /// Constructeur copie d�sactiv�.
   FacadeModele(const FacadeModele&) = delete;
   /// Op�rateur d'assignation d�sactiv�.
   FacadeModele& operator =(const FacadeModele&) = delete;

   /// Nom du fichier XML dans lequel doit se trouver la configuration.
   static const std::string FICHIER_CONFIGURATION;

   /// Pointeur vers l'instance unique de la classe.
   static std::shared_ptr<FacadeModele> instance_;

   /// Poign�e ("handle") vers la fen�tre o� l'affichage se fait.
   HWND  hWnd_{ nullptr };
   /// Poign�e ("handle") vers le contexte OpenGL.
   HGLRC hGLRC_{ nullptr };
   /// Poign�e ("handle") vers le "device context".
   HDC   hDC_{ nullptr };

   /// Vue courante de la sc�ne.
   std::shared_ptr<vue::Vue> vue_{ nullptr };
   /// Arbre de rendu contenant les diff�rents objets de la sc�ne.
   std::shared_ptr<ArbreRenduINF2990> arbre_{ nullptr };
   
   std::shared_ptr<EtatAbstrait> etat_{ nullptr };
  
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline std::shared_ptr<EtatAbstrait> FacadeModele::obtenirEtat()
///
/// Cette fonction retourne l'�tat dans lequel se trouve pr�sentement
/// le mod�le.
///
/// @return L'�tat courant.
///
////////////////////////////////////////////////////////////////////////
inline std::shared_ptr<EtatAbstrait> FacadeModele::obtenirEtat()
{
	return etat_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline vue::Vue* FacadeModele::obtenirVue()
///
/// Cette fonction retourne la vue qui est pr�sentement utilis�e pour
/// voir la sc�ne.
///
/// @return La vue courante.
///
////////////////////////////////////////////////////////////////////////
inline std::shared_ptr<vue::Vue> FacadeModele::obtenirVue()
{
   return vue_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const shared_ptr<ArbreRenduINF2990> FacadeModele::obtenirArbreRenduINF2990() const
///
/// Cette fonction retourne l'arbre de rendu de la sc�ne (version constante
/// de la fonction).
///
/// @return L'arbre de rendu de la sc�ne.
///
////////////////////////////////////////////////////////////////////////
inline std::shared_ptr<ArbreRenduINF2990> FacadeModele::obtenirArbreRenduINF2990() const
{
   return arbre_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline shared_ptr<ArbreRenduINF2990> FacadeModele::obtenirArbreRenduINF2990()
///
/// Cette fonction retourne l'arbre de rendu de la sc�ne (version non constante
/// de la fonction).
///
/// @return L'arbre de rendu de la sc�ne.
///
////////////////////////////////////////////////////////////////////////
inline std::shared_ptr<ArbreRenduINF2990> FacadeModele::obtenirArbreRenduINF2990()
{
   return arbre_;
}


#endif // __APPLICATION_FACADEMODELE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
