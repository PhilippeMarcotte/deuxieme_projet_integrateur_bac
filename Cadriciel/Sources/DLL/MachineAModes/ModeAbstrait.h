///////////////////////////////////////////////////////////////////////////
/// @file ModeAbstrait.h
/// @author Fr�d�ric Gr�goire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef MODE_ABSTRAIT_H
#define MODE_ABSTRAIT_H

#include <memory>
#include "glm\glm.hpp"
#include <Windows.h>
#include <Windowsx.h>


enum Mode
{
	MENU_PRINCIPAL,
	SIMULATION,
	EDITION,
	CONFIGURE,
	TEST
};

///////////////////////////////////////////////////////////////////////////
/// @class ModeAbstrait
/// @brief Classe qui repr�sente le mode abstrait de notre machine � modes
///
///        Cette classe s'occupe de d�clarer les fonctions qui seront impl�ment�s 
///	       dans les �tats d�riv�s.
/// @author Simon-Pierre Desjardins
/// @date 2016-02-14
///////////////////////////////////////////////////////////////////////////
class ModeAbstrait
{
public:
	//Constructeur par d�faut
	ModeAbstrait();
	//Destructeur
	virtual ~ModeAbstrait();

	//Gestion du syst�me de chargement et de sauvegarde
	virtual void sauvegarder();
	virtual void charger();

	virtual void gererMessage(UINT msg, WPARAM wParam, LPARAM lParam);

	inline int obtenirTypeMode();

	void assignerSymboleCurseur();

protected:
	int typeMode_;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn inline int ModeAbstrait::obtenirTypeMode()
///
/// Cette fonction retourne le type de mode de l'attribut typeMode_.
///
///
/// @return int typeMode_.
///
////////////////////////////////////////////////////////////////////////
inline int ModeAbstrait::obtenirTypeMode()
{
	return typeMode_;
}

#endif /// MODE_ABSTRAIT_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////