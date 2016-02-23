////////////////////////////////////////////////
/// @file   ProfilUtilisateur.h
/// @author Philippe Marcotte
/// @date   2016-02-22
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "CommandeRobot.h"

///////////////////////////////////////////////////////////////////////////
/// @class ProfilUtilisateur
/// @brief Classe qui repr�sente le profil d'un utilisateur.
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
		ProfilUtilisateur(std::string nomProfil, bool* options);
		~ProfilUtilisateur();
		void sauvegarder();
		void modifierToucheCommande(const uint8_t& touche, const TypeCommande& controle);
		void chargerProfilParDefaut();
private:
		void ouvrirFichierProfil();

		std::string nomProfil_;
		const int NOMBRE_OPTIONS{ 11 };
		FILE* profil_;
		const std::string CHEMIN_PROFIL = "./../../Donnees";

		//TODO: Assigner les 
		std::vector<bool> options_;
		std::vector<unsigned char> touches_;
		// Utilisation d'une unordered map pour un temps d'acces constant.
		std::unordered_map<unsigned char, std::unique_ptr<CommandeRobot>> commandes_;
		//TODO: Mapping de l'affichage debugage.
};
////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////