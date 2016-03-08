///////////////////////////////////////////////////////////////////////////////
/// @file ComporterDeviation.h
/// @author Olivier St-Amour
/// @date 20016-02-16
/// @version 2.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////

#ifndef COMPORTEMENT_DEVIATION
#define COMPORTEMENT_DEVIATION

#include "ComportementAbstrait.h"

///////////////////////////////////////////////////////////////////////////
/// @class ComportementDeviation
/// @brief Classe qui impl�mente le comportement de deviation du robot.
///
/// @author Olivier St-Amour
/// @date 2016-02-16
///////////////////////////////////////////////////////////////////////////
class ComportementDeviation : public ComportementAbstrait
{
public:
	ComportementDeviation();
	virtual ~ComportementDeviation();

	void initialiser();

	void mettreAJour();

	void setAngleMaxRotation(double angle);

private:
	// La variation relative d'angle maximale que la d�viation doit atteindre
	double maxAngle_;

	// L'angle que doit atteindre le robot pour que la d�viation soit consid�r�e accomplie.
	double angleCible_;

	// D�finit si la d�viation doit se faire vers la gauche ou bien vers la droite
	bool gauche;

	// Flag dictant au comportement d'ignorer la ligne
	bool ignorerLigne_;
};

#endif // COMPORTEMENT_DEVIATION

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////
