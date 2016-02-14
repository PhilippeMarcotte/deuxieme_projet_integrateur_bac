///////////////////////////////////////////////////////////////////////////
/// @file ModeTest.h
/// @author Fr�d�ric Gr�goire
/// @date 2016-02-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef MODE_TEST_H
#define MODE_TEST_H

#include "ModeAbstrait.h"
#include <memory>
#include "glm\glm.hpp"

//////////////////////////////////////////////////////////////////////////
/// @class ModeTest
/// @brief Classe qui repr�sente le mode test de notre machine � modes
///
///        Cette classe s'occupe d'impl�menter les fonctions du mode test

/// @author Simon-Pierre Desjardins
/// @date 2016-02-14
///////////////////////////////////////////////////////////////////////////

class ModeTest : public ModeAbstrait
{
public:

	//Constructeur par d�faut
	ModeTest();
	//Destructeur
	virtual ~ModeTest();


protected:

};


#endif /// MODE_TEST_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////