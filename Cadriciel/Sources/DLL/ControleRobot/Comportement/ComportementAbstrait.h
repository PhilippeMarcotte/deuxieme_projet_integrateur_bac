///////////////////////////////////////////////////////////////////////////////
/// @file ComportementAbstrait.h
/// @author Olivier St-Amour
/// @date 20016-02-16
/// @version 2.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef COMPORTEMENT_ABSTRAIT
#define COMPORTEMENT_ABSTRAIT

#include <memory>

class ControleRobot;

enum eComportement {
	DEFAUT,
	SUIVIDELIGNE,
	BALAYAGE180,
	DEVIATIONVERSLAGAUCHE,
	DEVIATIONVERSLADROITE,
	EVITEMENTPARLAGAUCHE,
	EVITEMENTPARLADROITE
};

///////////////////////////////////////////////////////////////////////////
/// @class ComportementAbstrait
/// @brief Classe de base qui d�finit le comportement du robot.
///
///        Cette classe abstraite comprend l'interface de base que doivent
///        implanter tous les comportements que le robot peut adopter. 
///		   
///
/// @author Olivier St-Amour
/// @date 2016-02-16
///////////////////////////////////////////////////////////////////////////
class ComportementAbstrait
{
public:
	ComportementAbstrait(ControleRobot* controleRobot);
	virtual ~ComportementAbstrait();

	// Assure la reinitialisation du comportement avant son execution
	virtual void initialiser() = 0;

	// Traite l'execution du comportement
	virtual void mettreAJour() = 0;

	eComportement obtenirComportementSuivant();

	void assignerComportementSuivant(eComportement prochainComportement);

protected:
	// Le comportement a adopter une fois les conditions de fin de ce comportement sont atteintes.
	eComportement comportementSuivant_;

	std::shared_ptr<ControleRobot> controleRobot_;
};

#endif // COMPORTEMENT_ABSTRAIT

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////