#include <iostream>
#include "../includes/plateau.hpp"
#include "../includes/joueur.hpp"
#include "../includes/unite.hpp"

bool Plateau::jeuContrejoueur=false;
int Plateau::nombreTour=0;
int Plateau::joueurActuelle=0;
bool Plateau::partieCharge=false;

int main() {
	// Menu principal - choix entre JcJ ou JcIA
	int choixJoueur = 0;
    bool partieEnregistrer = Plateau::chercherFichier();
	std::cout << "A quel mode de jeu souhaitez-vous jouer ? :\n1 - Joueur contre Joueur\n2 - Joueur contre IA\n" << ((partieEnregistrer==true)? "3 - Reprendre la partie enregistree" : "")
	<<"\nVotre choix (numero): ";
	if(!(std::cin >> choixJoueur)) {
		std::cerr << "Information entree incorrecte. Veuillez entrer uniquement un chiffre.\n";
		std::cin.clear();
		std::cin.ignore(1);
	}
	while(choixJoueur != 1 && choixJoueur != 2 && choixJoueur != 3) {
		std::cerr << "Choix entre impossible" << std::endl;
		std::cout << "Votre choix (numero): ";
		if(!(std::cin >> choixJoueur)) {
			std::cerr << "Information entree incorrecte. Veuillez entrer uniquement un chiffre.\n";
			std::cin.clear();
			std::cin.ignore(1);
		}
	}

    Plateau plate(choixJoueur);
    plate.jeu(choixJoueur);

	return 0;
}
