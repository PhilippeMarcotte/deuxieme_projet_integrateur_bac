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
	//Destructeur
	~CapteurDistance();

private:
	bool estActif_{ true };
};

#endif // CAPTEUR_DISTANCE_H