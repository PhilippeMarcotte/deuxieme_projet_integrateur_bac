///////////////////////////////////////////////////////////////////////////
/// @file ModeSimulation.h
/// @author Fr�d�ric Gr�goire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef MODE_SIMULATION_H
#define MODE_SIMULATION_H

#include "ModeAbstrait.h"
#include <memory>
#include "glm\glm.hpp"
#include "ControleRobot.h"

//////////////////////////////////////////////////////////////////////////
/// @class ModeSimulation
/// @brief Classe qui repr�sente le mode simulation de notre machine � modes
///
///        Cette classe s'occupe d'impl�menter les fonctions du mode simulation
///
/// @author Simon-Pierre Desjardins
/// @date 2016-02-14
///////////////////////////////////////////////////////////////////////////
class ModeSimulation : public ModeAbstrait
{
public:

	//Constructeur par d�faut
	ModeSimulation();

	//Destructeur
	virtual ~ModeSimulation();

	void gererMessage(UINT msg, WPARAM wParam, LPARAM lParam);

private:
	std::unique_ptr<ControleRobot> controleRobot_;
};


#endif /// MODE_SIMULATION_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////