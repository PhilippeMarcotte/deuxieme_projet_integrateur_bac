///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.h
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_ARBRERENDUINF2990_H__
#define __ARBRE_ARBRERENDUINF2990_H__


#include "ArbreRendu.h"
#include <map>
#include <string>
#include "rapidjson\document.h"

class VisiteurAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class ArbreRenduINF2990
/// @brief Classe qui repr�sente l'arbre de rendu sp�cifique au projet de
///        INF2990.
///
///        Cette classe s'occupe de configurer les usines des noeuds qui
///        seront utilis�s par le projet.
///
/// @author Martin Bisson
/// @date 2007-03-23
///////////////////////////////////////////////////////////////////////////
class ArbreRenduINF2990 : public ArbreRendu
{
public:
   /// Constructeur par d�faut.
   ArbreRenduINF2990();
   /// Destructeur.
   virtual ~ArbreRenduINF2990();

   /// Initialise l'arbre de rendu � son �tat initial.
   void initialiser();

   void chargerZone();
	/// La cha�ne repr�sentant le type des araign�es.
   static const std::string NOM_ARAIGNEE;
	/// La cha�ne repr�sentant le type des cones-cubes.
   static const std::string NOM_CONECUBE;
   /// La cha�ne repr�sentant le type du robot.
   static const std::string NOM_ROBOT;
   /// La cha�ne repr�sentant le type de la table.
   static const std::string NOM_TABLE;
   /// La cha�ne repr�sentant le type des poteaux.
   static const std::string NOM_POTEAU;
   /// La cha�ne repr�sentant le type des murs.
   static const std::string NOM_MUR;
   /// La cha�ne repr�sentant le type des lignes.
   static const std::string NOM_LIGNENOIRE;
   /// La cha�ne repr�sentant le type des segments.
   static const std::string NOM_SEGMENT;
   /// La cha�ne repr�sentant le type des duplications. 
   static const std::string NOM_DUPLICATION;

private:
	void chargerZone(rapidjson::Value::ConstValueIterator noeudJSON, shared_ptr<NoeudAbstrait> parent);
   /// La cha�ne repr�sentant le type du point de d�part. 
   static const std::string NOM_DEPART;
};

#endif // __ARBRE_ARBRERENDUINF2990_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
