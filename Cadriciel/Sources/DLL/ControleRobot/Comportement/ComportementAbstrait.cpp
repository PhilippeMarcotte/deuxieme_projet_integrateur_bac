///////////////////////////////////////////////////////////////////////////////
/// @file ComporterAbstrait.cpp
/// @author Olivier St-Amour
/// @date 20016-02-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "ComportementAbstrait.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementAbstrait::ComportementAbstrait()
///
/// Constructeur
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementAbstrait::ComportementAbstrait()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementAbstrait::~ComportementAbstrait()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ComportementAbstrait::~ComportementAbstrait()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementAbstrait::~ComportementAbstrait()
///
/// Assigne au comportement le comportement qui devrait le suivre lorsque la condition de fin est atteinte.
///
/// @param[in] prochainComportement: Valeur enum indiquant le prochain comportement a adopter.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ComportementAbstrait::assignerComportementSuivant(eComportement comportementSuivant){
	comportementSuivant_ = comportementSuivant;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ComportementAbstrait::~ComportementAbstrait()
///
/// Assigne au comportement le comportement qui devrait le suivre lorsque la condition de fin est atteinte.
///
/// @return le comportement suivant a adopter.
///
////////////////////////////////////////////////////////////////////////
eComportement ComportementAbstrait::obtenirComportementSuivant(){
	return comportementSuivant_;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////