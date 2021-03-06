//////////////////////////////////////////////////////////////////////////////
/// @file Utilitaire.h
/// @author Martin Bisson
/// @date 2007-03-11
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_UTILITAIRE_H__
#define __UTILITAIRE_UTILITAIRE_H__

#include "glm\glm.hpp"

#include <sstream>
#include <vector>

template <typename T> class aiMatrix4x4t;	/// D�claration avanc�e d'une classe
using aiMatrix4x4 = aiMatrix4x4t<float>;	//  template

struct aiColor3D;

namespace modele{
	class Modele3D;
	class Noeud;
}

namespace utilitaire {


   /// D�finition d'un type d'entier non sign�.
	using uint = unsigned int;

	/// Constante pour la diff�rence entre deux nombres r�els.
	static const double EPSILON{ 0.00000001 };
	/// Constante PI.
	static const double PI{ 3.1415926535897932384626433832795 };

	/// Le vecteur i (dirig� vers l'axe des X positifs et unitaire).
	static glm::dvec3 vi{ 1.0, 0.0, 0.0 };
	/// Le vecteur j (dirig� vers l'axe des Y positifs et unitaire).
	static glm::dvec3 vj{ 0.0, 1.0, 0.0 };
	/// Le vecteur k (dirig� vers l'axe des Z positifs et unitaire).
	static glm::dvec3 vk{ 0.0, 0.0, 1.0 };

   /// Fonction globale pour l'affichage d'erreur.
   void afficherErreur(const std::string& message);

   /// Pour convertir les angles de radians en degr�s.
   double RAD_TO_DEG( double AngleRad );
   /// Pour convertir les angles de degr�s en radians.
   double DEG_TO_RAD( double AngleDeg );

   /// Pour convertir les km/h en m/s.
   float KMH_TO_MS( float kmh );
   /// Pour convertir les m/s en km/h.
   float MS_TO_KMH( float ms );

   /// Fonction pour conna�tre le signe d'un nombre.
   float SIGN( float nombre );

   /// Fonction pour savoir si un double est �gal � z�ro.
   bool EGAL_ZERO(double Nombre);

   /// Pour savoir si un nombre est dans l'intervalle: [BorneMin, BorneMax].
   bool DANS_INTERVALLE( double Valeur, double BorneMin, double BorneMax );
   /// Fonction pour v�rifier si un Point 2d est dans un carr�.
   bool DANS_LIMITESXY( double x, double xMin, double xMax,
                        double y, double yMin, double yMax );

   /// Calcule le rapport d'�crasement
   double ecrasement( double a, double b);

   /// V�rification de l'existance d'un fichier
   bool fichierExiste( const std::string& nomDuFichier );

   /// Applique une matrice de transformation � un point.
   glm::dvec3 appliquerMatrice( const glm::dvec3& point, const double mat[] );

   /// Conversion d'une matrice Assimp vers glm
   glm::mat4x4 ai_To_glm(aiMatrix4x4 const& m);
   /// Conversion d'une couleur Assimp vers glm
   glm::vec3 ai_To_glm(aiColor3D const& c);

   void time_in_HH_MM_SS_MMM();

   /// Structure contenant les donn�es pour une sph�re englobante
   struct SphereEnglobante{
	   double rayon;
   };

   /// Structure contenant les donn�es pour un cylindre englobant
   struct CylindreEnglobant{
	   double rayon;
	   double bas;
	   double haut;
   };

   /// Structure contenant les donn�es pour une boite englobante
   struct BoiteEnglobante{
	   glm::dvec3 coinMin;
	   glm::dvec3 coinMax;
   };

   struct QuadEnglobant
   {
	  static const int N_COINS = 4;
	  glm::dvec3 coins[N_COINS];
   };

   /// Calcule la sph�re englobante
   SphereEnglobante calculerSphereEnglobante(modele::Modele3D const& modele);

   /// Calcule le cylindre englobant
   CylindreEnglobant calculerCylindreEnglobant(modele::Modele3D const& modele);

   /// Calcule la boite englobante
   BoiteEnglobante calculerBoiteEnglobante(modele::Modele3D const& modele);

   /// Permet de r�cup�rer les points extr�mes d'un noeud (r�cursivement)
   void obtenirPointsExtremes(modele::Noeud const& noeud, 
	   glm::dvec3& xMin, glm::dvec3& xMax, 
	   glm::dvec3& yMin, glm::dvec3& yMax, 
	   glm::dvec3& zMin, glm::dvec3& zMax);

   
	double calculerAngleRotation(glm::dvec3& pointUn, glm::dvec3& pointDeux);

	double calculerDistanceHypothenuse(glm::dvec3& pointUn, glm::dvec3& pointDeux);

	glm::dvec3 calculerPositionEntreDeuxPoints(glm::dvec3& pointUn, glm::dvec3& pointDeux);

	void calculerPositionApresRotation(glm::dvec3 positionInitiale, 
                                       glm::dvec3&       positionFinale, 
                                       const double&     theta);

	bool calculerPointEstDansQuad(const glm::dvec3& point, 
                                  const QuadEnglobant& quad);

    bool calculerIntersectionDeuxQuads(const QuadEnglobant& quad1, 
                                       const QuadEnglobant& quad2);


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn T borneSuperieure(T const& valeur, T const& borne)
   ///
   /// Cette fonction s'assure que la valeur ne d�passe pas la borne.
   ///
   /// @param[in] valeur : La valeur de l'expression � borner.
   /// @param[in] borne  : La borne sup�rieure.
   ///
   /// @return La valeur born�e.
   ///
   ////////////////////////////////////////////////////////////////////////
   template <class T>
   T borneSuperieure(T const& valeur, T const& borne)
   {
	   return valeur > borne ? borne : valeur;
   }

   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn T borneInferieure(T const& valeur, T const& borne)
   ///
   /// Cette fonction s'assure que la valeur d�passe la borne.
   ///
   /// @param[in,out] valeur : La valeur de l'expression � borner.
   /// @param[in]     borne  : La borne inf�rieure.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   template <class T>
   T borneInferieure(T const& valeur, T const& borne)
   {
	   return valeur < borne ? borne : valeur;
   }

   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn T borne(T const& valeur, T const& min, T const& max)
   ///
   /// Cette fonction s'assure que la valeur ne d�passe pas les bornes.
   ///
   /// @param[in] valeur	: La valeur de l'expression � borner.
   /// @param[in] min		: La borne inf�rieure.
   /// @param[in] max		: La borne sup�rieure.
   ///
   /// @return la valeur born�e.
   ///
   ////////////////////////////////////////////////////////////////////////
   template <class T>
   T borne(T const& valeur, T const& min, T const& max)
   {
	   return borneSuperieure(borneInferieure(valeur, min), max);
   }

   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn static std::string convertirEnChaine(const T& valeur)
   ///
   /// @brief Conversion d'un type g�n�rique vers une cha�ne de caract�res.
   ///
   /// Cette fonction convertit un type g�n�rique en une cha�ne de
   /// caract�res.  Comme elle se sert de l'op�rateur << appliqu� sur
   /// un ostringstream, elle devrait fonctionner pour toutes les classes
   /// qui d�finissent cet op�rateur pour les ostream&.
   ///
   /// @param[in] valeur    : Valeur template � convertir en cha�ne de
   ///                        caract�res.
   /// @param[in] modifieur : Fonction utilis�e pour la conversion de type
   ///                        particulier, par exemple std::hex ou std::oct
   ///                        pour les entiers.
   ///
   /// @return Cha�ne repr�sentant le type.
   ///
   ////////////////////////////////////////////////////////////////////////
   template<typename T> static std::string convertirEnChaine(
      const T& valeur,
      std::ios_base& (*modifieur)(std::ios_base&) = 0
      )
   {
      std::ostringstream oss;

      // Application du modifieur s'il est sp�cifi�.
      if (modifieur)
         oss << modifieur;

      oss << valeur;
      return oss.str();
   }

   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn static bool convertirEnType(const std::string& chaine, T& valeur, std::ios_base& (*modifieur)(std::ios_base&) = 0)
   ///
   /// @brief Conversion d'une cha�ne de caract�res vers un type g�n�rique.
   ///
   /// Cette fonction convertit une cha�ne de caract�res en un type g�n�rique.
   /// Comme elle se sert de l'op�rateur >> appliqu� sur un istringstream,
   /// elle devrait fonctionner pour toutes les classes qui d�finissent cet
   /// op�rateur pour les istream&.
   ///
   /// @param[in] chaine    : Cha�ne � convertir.
   /// @param[in] valeur    : Valeur template qui contiendra la valeur contenu
   ///                        dans la cha�ne.  Ne sera pas modifi�e si la
   ///                        cha�ne n'est pas valide.
   /// @param[in] modifieur : Fonction utilis�e pour la conversion de type
   ///                        particulier, par exemple std::hex ou std::oct
   ///                        pour les entiers.
   ///
   /// @return Vrai si la conversion a r�ussi.
   ///
   ////////////////////////////////////////////////////////////////////////
   template<typename T> static bool convertirEnType(
      const std::string& chaine,
      T& valeur,
      std::ios_base& (*modifieur)(std::ios_base&) = 0
      )
   {
	   std::istringstream iss{ chaine };

      // Application du modifieur s'il est sp�cifi�.
      if (modifieur)
         iss >> modifieur;

      // Lecture de la valeur
      T temp;
	  iss >> temp;

	  // Pour que la conversion soit un succ�s, toute la cha�ne doit avoir �t�
	  // convertie.  On ajoute donc le second test pour �viter qu'une cha�ne
	  // comme "123bidon" puisse �tre accept�e et que toute la cha�ne soit
	  // utilis�e pour que la conversion soit consid�r�e comme r�ussie.
	  const bool succes{ ((!iss.fail()) && (iss.peek() == EOF)) };

      if (succes)
         valeur = temp;

      return succes;
   }

} // Fin du namespace utilitaire.


#endif // __UTILITAIRE_UTILITAIRE_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
