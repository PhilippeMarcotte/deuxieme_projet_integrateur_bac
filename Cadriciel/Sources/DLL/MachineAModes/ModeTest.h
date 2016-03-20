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

#include <memory>
#include "glm\glm.hpp"

#include "ModeAbstrait.h"
#include "ControleRobot.h"
#include <unordered_map>
#include <array>

class ProfilUtilisateur;

//////////////////////////////////////////////////////////////////////////
/// @class ModeTest
/// @brief Classe qui repr�sente le mode test de notre machine � modes
///
///        Cette classe s'occupe d'impl�menter les fonctions du mode test
///
/// @author Simon-Pierre Desjardins
/// @date 2016-02-14
///////////////////////////////////////////////////////////////////////////

class ModeTest : public ModeAbstrait
{
private:
	std::unique_ptr<ControleRobot> controleRobot_;
	ProfilUtilisateur* profil_{ nullptr };
	static std::array<char, 9> touchesNonConfigurable_;

	bool lumiereAmbiante{ true };
	bool lumiereDirectionnelle{ true };
	bool lumiereSpot{ true };

public:

	//Constructeur par d�faut
	ModeTest();
	//Destructeur
	virtual ~ModeTest();
	
	void preChangementDeProfil();
	void postChangementDeProfil();

	void inverserLumiereAmbiante();
	void inverserLumiereDirectionnelle();
	void inverserLumiereSpot();

	//Gestion des entr�es utilisateur
	void gererMessage(UINT msg, WPARAM wParam, LPARAM lParam);

	inline static std::array<char, 9>* getTouchesNonConfigurable();
};

std::array<char, 9>* ModeTest::getTouchesNonConfigurable()
{
	return &touchesNonConfigurable_;
}
#endif /// MODE_TEST_H

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////