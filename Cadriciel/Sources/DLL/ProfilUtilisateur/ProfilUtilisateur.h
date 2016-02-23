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
#include "ComportementAbstrait.h"

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
		void sauvegarder();
		void ouvrirFichierProfil(std::string nomProfil);
		void assignerComportement(eComportement typeComportement, std::unique_ptr<ComportementAbstrait> comportement);
	private:
		std::vector<std::unique_ptr<ComportementAbstrait>> options_;
		void modifierToucheCommande(const uint8_t& touche, const TypeCommande& controle);
		void chargerProfilParDefaut();
		void ouvrirFichierProfil();
		std::string nomProfil_;
		const int NOMBRE_OPTIONS{ 11 };
		FILE* profil_;
		const std::string CHEMIN_PROFIL = "./../../Donnees/";

		//TODO: Assigner les 
		std::vector<unsigned char> touches_;
		// Utilisation d'une unordered map pour un temps d'acces constant.
		std::unordered_map<unsigned char, std::unique_ptr<CommandeRobot>> commandes_;
		//TODO: Mapping de l'affichage debugage.
};
////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////