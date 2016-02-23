///////////////////////////////////////////////////////////////////////////////
/// @file ComportementBalayage.h
/// @author Olivier St-Amour
/// @date 2016-02-16
/// @version 2.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef COMPORTEMENT_BALAYAGE
#define COMPORETMENT_BALAYAGE

#include "ComportementAbstrait.h"

///////////////////////////////////////////////////////////////////////////
/// @class ComportementBalayage
/// @brief Classe qui impl�mente le comportement de balayage du robot.
///
/// @author Olivier St-Amour
/// @date 2016-02-16
///////////////////////////////////////////////////////////////////////////
class ComportementBalayage : public ComportementAbstrait
{
public:
	ComportementBalayage();
	virtual ~ComportementBalayage();

	void initialiser();

	void mettreAJour();
};

#endif // COMPORTEMENT_BALAYAGE

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////