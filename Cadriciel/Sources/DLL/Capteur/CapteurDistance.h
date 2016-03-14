///////////////////////////////////////////////////////////////////////////
/// @file CapteurDistance.h
/// @author Olivier St-Amour
///
/// version 2.1
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef CAPTEUR_DISTANCE_H
#define CAPTEUR_DISTANCE_H

#include "ComportementAbstrait.h"
#include "rapidjson\writer.h"
#include "rapidjson\document.h"

namespace rapidjson {
	class FileWriteStream;
}

///////////////////////////////////////////////////////////////////////////
/// @class CapteurDistance
/// @brief Classe qui repr�sente un capteur de distance du robot.  
///
///        Cette classe s'occupe de g�rer la d�tection des poteaux et des murs. 
///
/// @author Olivier St-Amour
/// @date 2016-02-23
///////////////////////////////////////////////////////////////////////////
class CapteurDistance
{
public:
	//Constructeur par d�faut
	CapteurDistance();

	//Constructeur par param�tre
	CapteurDistance(bool estActif, TypeComportement comportementDanger, double distanceDanger, TypeComportement comportementSecuritaire, double distanceSecuritaire);

	//Constructeur par param�tre
	CapteurDistance(const rapidjson::Value& capteurJSON);

	//Destructeur
	~CapteurDistance();

	void assignerActif(bool estActif);

	void assignerParametreZoneDanger(TypeComportement comportement, double distance);

	void assignerParametreZoneSecuritaire(TypeComportement comportement, double distance);

	void toJSON(rapidjson::Writer<rapidjson::FileWriteStream>& writer);

private:
	bool estActif_{ true };
};

#endif // CAPTEUR_DISTANCE_H