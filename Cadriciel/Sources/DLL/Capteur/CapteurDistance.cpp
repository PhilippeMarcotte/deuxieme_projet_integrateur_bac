#include "CapteurDistance.h"


CapteurDistance::CapteurDistance()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn CapteurDistance::CapteurDistance(bool estActif, TypeComportement comportementDanger, double distanceDanger, TypeComportement comportementSecuritaire, double distanceSecuritaire)
///
/// Constructeur par param�tre
///
/// @param[in] estActif: repr�sente si le capteur est actif ou non
/// @param[in] comportementDanger : repr�sente le comportement � adapter dans une zone de danger
/// @param[in] distanceDanger : la distance minimal pour que le robot soit en danger
/// @param[in] comportementSecuritaire : repr�sente le comportement � adapter dans une zone s�curitaire
/// @param[in] distanceSecuritaire : la distance minimal pour que le robot soit en s�curit�
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
CapteurDistance::CapteurDistance(bool estActif, TypeComportement comportementDanger, double distanceDanger, TypeComportement comportementSecuritaire, double distanceSecuritaire){
	/*
	this->estActif = estActif;
	this->comportementDanger = comportementDanger;
	this->distanceDanger = distanceDanger;
	this->comportementSecuritaire = comportementSecuritaire;
	this->distanceSecuritaire = distanceSecuritaire;
	*/
}

////////////////////////////////////////////////////////////////////////
///
/// @fn CapteurDistance::CapteurDistance(rapidjson::Value::ConstValueIterator capteurJSON)
///
/// Constructeur par param�tre
///
/// @param[in] capteurJSON: le capteur en format JSON
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
CapteurDistance::CapteurDistance(const rapidjson::Value& capteurJSON)
{
	/*
	rapidjson::Value::ConstMemberIterator itr = capteurJSON.MemberBegin();

	this->estActif = itr->value.GetBool();

	itr++;
	this->comportementDanger = itr->value.GetInt();

	itr++;
	this->distanceDanger = itr->value.GetDouble();

	itr++;
	this->comportementSecuritaire = itr->value.GetInt();

	itr++;
	this->distanceSecuritaire = itr->value.GetDouble();
	*/
}


CapteurDistance::~CapteurDistance()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void CapteurDistance::toJson(rapidjson::Writer<rapidjson::FileWriteStream>& writer)
///
/// Cette fonction obtient les valeurs � sauvegarder pour le capteur en JSON
///
/// @param[in] writer : Le stream dans lequel le JSON est �crit
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void CapteurDistance::toJSON(rapidjson::Writer<rapidjson::FileWriteStream>& writer){
	/*
	writer.Key("estActif");
	writer.Bool(estActif);
	writer.Key("comportementDanger");
	writer.Int(comportementDanger);
	writer.Key("distanceDanger");
	writer.Double(distanceDanger);
	writer.Key("comportementSecuritaire");
	writer.Int(comportementSecuritaire);
	writer.Key("distanceSecuritaire");
	writer.Double(distanceSecuritaire);
	*/
}