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

#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "EtatAbstrait.h"
#include "ModeAbstrait.h"

class NoeudAbstrait;

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
   static FacadeModele* obtenirInstance();
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
   void assignerEtat(Etat etat);
   // Obtenir l'etat courant.
   inline EtatAbstrait* obtenirEtat();

   /// Modifie l'etat courant.
   void assignerMode(Mode mode);
   // Obtenir l'etat courant.
   inline ModeAbstrait* obtenirMode();

   // Obtenir le nombre d'objet s�lectionn�
   int obtenirNombreSelection();

   // Obtient si le mod�le est autoris� � recevoir des entr�es utilisateurs. 
   inline bool obtenirAutorisationInputSouris() const; 
   // Assigne si le mod�le est autoris� � recevoir des entr�es utilisateurs. 
   inline void assignerAutorisationInputSouris(const bool& autorisation);

   inline bool obtenirAutorisationInputClavier() const;

   inline void assignerAutorisationInputClavier(const bool& autorisation);

   // Obtient l'angle de rotaion du noeud selectionn�. 
   double obtenirAngleRotation();
   // Obtient le facteur de mise � �chelle du noeud selectionn�. 
   double obtenirFacteurMiseAEchelle();
   // Obtient la position relative en X du noeud selectionn�.
   double obtenirPositionRelativeX();
   // Obtient la position relative en Y du noeud selectionn�.
   double obtenirPositionRelativeY();

   // Assigne l'angle de rotaion du noeud selectionn�. 
   void assignerAngleRotation(const double& angle);
   // Assigne le facteur de mise � �chelle du noeud selectionn�.
   void assignerFacteurMiseAEchelle(const double& facteurMiseAEchelle);
   // Assigne la position relative en x du noeud s�lectionn�.
   void assignerPositionRelativeX(const double& positionRelativeX);
   // Assigne la position relative en x du noeud s�lectionn�. 
   void assignerPositionRelativeY(const double& positionRelativeY);

   /// Retourne la vue courante.
   inline vue::Vue* obtenirVue();
   /// Retourne l'arbre de rendu.
   inline ArbreRenduINF2990* obtenirArbreRenduINF2990() const;
   /// Retourne l'arbre de rendu.
   inline ArbreRenduINF2990* obtenirArbreRenduINF2990();

   /// R�initialise la sc�ne.
   void reinitialiser();

   /// Anime la sc�ne.
   void animer(float temps);
   void stopAffichage();
   void continuerAffichage();

private:
   /// Constructeur par d�faut.
   FacadeModele() = default;

   bool peutAfficher_{true};
   bool autorisationInputSouris_{ true };
   bool autorisationInputClavier_{ true };
   /// Constructeur copie d�sactiv�.
   FacadeModele(const FacadeModele&) = delete;
   /// Op�rateur d'assignation d�sactiv�.
   FacadeModele& operator =(const FacadeModele&) = delete;

   /// Nom du fichier XML dans lequel doit se trouver la configuration.
   static const std::string FICHIER_CONFIGURATION;

   /// Pointeur vers l'instance unique de la classe.
   static std::unique_ptr<FacadeModele> instance_;

   /// Poign�e ("handle") vers la fen�tre o� l'affichage se fait.
   HWND  hWnd_{ nullptr };
   /// Poign�e ("handle") vers le contexte OpenGL.
   HGLRC hGLRC_{ nullptr };
   /// Poign�e ("handle") vers le "device context".
   HDC   hDC_{ nullptr };

   /// Vue courante de la sc�ne.
   std::unique_ptr<vue::Vue> vue_{ nullptr };
   /// Arbre de rendu contenant les diff�rents objets de la sc�ne.
   std::unique_ptr<ArbreRenduINF2990> arbre_{ nullptr };
   
   std::unique_ptr<EtatAbstrait> etat_{ nullptr };
   std::unique_ptr<ModeAbstrait> mode_{ nullptr };
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
inline EtatAbstrait* FacadeModele::obtenirEtat()
{
	return etat_.get();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline std::shared_ptr<ModeAbstrait> FacadeModele::obtenirMode()
///
/// Cette fonction retourne le mode dans lequel se trouve pr�sentement
/// le mod�le.
///
/// @return le mode courant.
///
////////////////////////////////////////////////////////////////////////
inline ModeAbstrait* FacadeModele::obtenirMode()
{
	return mode_.get();
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
inline vue::Vue* FacadeModele::obtenirVue()
{
   return vue_.get();
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
inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
{
   return arbre_.get();
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
inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
{
   return arbre_.get();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn  bool obtenirAutorisationInput()
///
/// Retourne si oui ou non le modele prend pr�sentement les entr�es claviers utilisateurs
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline bool FacadeModele::obtenirAutorisationInputClavier() const
{
	return autorisationInputClavier_; 
}

////////////////////////////////////////////////////////////////////////
///
/// @fn  bool obtenirAutorisationInput()
///
/// Assigne la valeur autorisation � la variable autorisationInputClavier_.
///
/// @param[in] autorisation : Si vrai, permet au modele de prendre les entr�es claviers utilisateurs.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void FacadeModele::assignerAutorisationInputClavier(const bool& autorisation)
{ 
	autorisationInputClavier_ = autorisation;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn  bool obtenirAutorisationInput()
///
/// Retourne si oui ou non le modele prend pr�sentement les entr�es souris sourisutilisateurs
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
bool FacadeModele::obtenirAutorisationInputSouris() const 
{ 
	return autorisationInputSouris_; 
}

////////////////////////////////////////////////////////////////////////
///
/// @fn  void assignerAutorisationInputSouris(bool autorisation)
///
/// Assigne la valeur autorisation � la variable autorisationInputSouris_.
///
/// @param[in] autorisation : Si vrai, permet au modele de prendre les entr�es souris utilisateurs.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::assignerAutorisationInputSouris(const bool& autorisation)
{ 
	autorisationInputSouris_ = autorisation; 
}

#endif // __APPLICATION_FACADEMODELE_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
