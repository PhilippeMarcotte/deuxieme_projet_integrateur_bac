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

///////////////////////////////////////////////////////////////////////////
/// @class ModeAbstrait
/// @brief Classe qui repr�sente le mode abstrait de notre machine � modes
///
///        Cette classe s'occupe de d�clarer les fonctions qui seront impl�ment�s 
///	       dans les �tats d�riv�s.
/// @author Simon-Pierre Desjardins
/// @date 2016-02-14
///////////////////////////////////////////////////////////////////////////

enum Mode
{
	MENU_PRINCIPAL,
	SIMULATION,
	EDITION,
	CONFIGURE,
	TEST
};

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

	//Gestion des diff�rentes touches et de leur effet selon le mode choisi
	virtual void gererTouchePlus();
	virtual void gererToucheMoins();

	virtual void gererToucheEchappe();

	virtual void gererToucheB();
	virtual void gererToucheC();
	virtual void gererToucheD();
	virtual void gererToucheE();
	virtual void gererToucheJ();
	virtual void gererToucheK();
	virtual void gererToucheL();
	virtual void gererToucheR();
	virtual void gererToucheS();
	virtual void gererToucheT();
	virtual void gererToucheZ();

	virtual void gererToucheCTRLavecS();
	virtual void gererToucheCTRLavecN();
	virtual void gererToucheCTRLavecO();

	virtual void gererTouche1();
	virtual void gererTouche2();
	virtual void gererTouche3();

	virtual void gererFlecheGauche();
	virtual void gererFlecheBas();
	virtual void gererFlecheHaut();
	virtual void gererFlecheDroit();

	// Gestion des touches de modification
	virtual void gererBarreDespacement();
	virtual void gererToucheArriere();
	virtual void gererToucheControlEnfoncee();
	virtual void gererToucheControlRelachee();

	virtual void gererToucheSupprimer();

	// Gestion de la souris
	virtual void gererClicDroitEnfonce(const int& x, const int& y);
	virtual void gererClicDroitRelache(const int& x, const int& y);
	virtual void gererClicGaucheEnfonce(const int& x, const int& y);
	virtual void gererClicGaucheRelache(const int& x, const int& y);
	virtual void gererMouvementSouris(const int & x, const int& y);
	virtual void gererMoletteSouris(const int & delta);

	inline int obtenirTypeMode();

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