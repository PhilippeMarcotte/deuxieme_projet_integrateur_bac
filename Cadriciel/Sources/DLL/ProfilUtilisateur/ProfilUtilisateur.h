////////////////////////////////////////////////
/// @file   ProfilUtilisateur.h
/// @author Philippe Marcotte
/// @date   2016-02-22
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#ifndef __PROFILUTILISATEUR_H__
#define __PROFILUTILISATEUR_H__

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "CommandeRobot.h"
#include "ComportementAbstrait.h"
#include "./../../Enum/ConfigureControlEnum.cs"
#include <deque>
#include <Windows.h>
#include "CapteurDistance.h"
#include "SuiveurLigne.h"
#include "NoeudRobot.h"
#include <array>


enum optionsDebogagesEnum
{
	ETAT_DEBOGAGE,
	DEBOGAGE_COMPORTEMENTS,
	DEBOGAGE_ECLAIRAGE,
	DEBOGAGE_CAPTEURS
};

///////////////////////////////////////////////////////////////////////////
/// @class ProfilUtilisateur
/// @brief Classe qui représente le profil d'un utilisateur.
///		   Celle-ci contient toutes options qu'un utilisateur peut changer et sauvegarder.
///
///
/// @author Philippe Marcotte
/// @date 2016-02-22
///////////////////////////////////////////////////////////////////////////
class ProfilUtilisateur
{
	public:
		ProfilUtilisateur();

		ProfilUtilisateur(std::string nomProfil);

		~ProfilUtilisateur();

		bool sauvegarder(std::string nomProfil);

		bool changerProfil(std::string nomProfil);

		void assignerComportement(TypeComportement typeComportement, std::unique_ptr<ComportementAbstrait> comportement);

		void modifierToucheCommande(const uint8_t& touche, const TypeCommande& controle);

		void chargerProfilParDefaut();

		CommandeRobot* obtenirCommandeRobot(unsigned char touche) const;

		void modifierToucheCommande(char touche, TypeCommande commande);

		bool toucheEstUtilise(char touche);

		char obtenirToucheCommande(int commande);

		void setConfigureHandles(HWND handle, ConfigureControl ctrl);

		std::string obtenirExtensionProfils();

		std::string obtenirCheminProfils();

		std::string obtenirNomProfilDefaut();

        inline SuiveurLigne* obtenirSuiveurLigne();
        inline NoeudRobot::ConteneurCapteursDistance* obtenirCapteursDistance();

		void supprimerProfil(std::string nomProfil);

		void assignerCapteurDistance(bool estActif, TypeComportement comportementDanger, double distanceDanger, TypeComportement comportementSecuritaire, double distanceSecuritaire, int indexCapteur);

		void assignerSuiveurLigne(bool estActif);

		void assignerOptionsDebogages(bool optionsDebogages[]);

		inline int obtenirDureeMaxComportement();
		inline int obtenirDureeMinComportement();

		inline int obtenirLargeurTotalDetectionDistance();

		std::vector<std::unique_ptr<ComportementAbstrait>>* obtenirVecteurComportements();

		bool obtenirOptionDebogage(optionsDebogagesEnum option);

		int* obtenirLimiteParametres();

	private:
		void changerDernierProfil(std::string nomProfil);

		void sauvegarder();

		bool ouvrirProfil(std::string readOrWrite);

		bool ouvrir(std::string nomFichier, std::string readOrWrite, FILE*& fichier);

		std::vector<std::unique_ptr<ComportementAbstrait>> comportements_;
		
		bool chargerProfil();

		std::string nomProfil_;

		const int NOMBRE_OPTIONS{ 11 };

		FILE* profil_;

		const std::string CHEMIN_PROFIL = "./../../Donnees/";

		const std::string EXTENSION_PROFIL = ".profil";

		const std::string PROFIL_DEFAUT = "defaut";

		const std::string DERNIER_PROFIL = "dernier_profil";

		const int DUREE_MAX_COMPORTEMENT = 2000;

		const int DUREE_MIN_COMPORTEMENT = 0;

		const int LARGEUR_TOTAL_DETECTION_DISTANCE = 30;

		const int LARGEUR_MIN_DETECTION_DISTANCE = 0;

		const int ANGLE_MAX_COMPORTEMENT = 360;

		const int ANGLE_MIN_COMPORTEMENT = 0;

		std::string dernierProfil;

		std::unordered_map<ConfigureControl, HWND> configureHandles;

		std::vector<char> touches_;

		// Utilisation d'une unordered map pour un temps d'acces constant.
		std::unordered_map<unsigned char, std::unique_ptr<CommandeRobot>> commandes_;

        NoeudRobot::ConteneurCapteursDistance capteursDistance_;

		SuiveurLigne suiveurLigne_;

        std::array<glm::dvec3, NoeudRobot::N_CAPTEURS_DISTANCE> positionsRelatives_;
        std::array<double, NoeudRobot::N_CAPTEURS_DISTANCE> anglesRelatifs_;

		std::array<bool, 4> optionsDebogages_;
};
#endif // __PROFILUTILISATEUR_H__

inline SuiveurLigne* ProfilUtilisateur::obtenirSuiveurLigne()
{
    return &suiveurLigne_;
}


inline NoeudRobot::ConteneurCapteursDistance* ProfilUtilisateur::obtenirCapteursDistance()
{
    return &capteursDistance_;
}
////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////