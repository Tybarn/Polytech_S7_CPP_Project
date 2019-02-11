#ifndef PLATEAU_HPP_
#define PLATEAU_HPP_

#include <array>
#include "joueur.hpp"
#include "unite.hpp"
class Joueur;
class Unite;

class Plateau {
public:
    //ATTRIBUT
    static bool jeuContrejoueur;
    static constexpr int TAILLE_PLATEAU = 12;
private:
	// STATIC
    static bool partieCharge;
    static int nombreTour;
    static int joueurActuelle;
    //ATTRIBUT
	Joueur* m_J1;
	Joueur* m_J2;
	std::array<Unite*, TAILLE_PLATEAU> m_cases;
public:
    //CONSTRUCTEUR

	Plateau(int i);
	~Plateau();
	//AFFICHAGE
    void afficherPlateau()const;
    //FONCTION
    void chargerPartie(Plateau *pt);
    bool sauvegarderPartie(Joueur *j);
    static bool chercherFichier();
    void donnerArgentDebutTour();
    bool attaqueUnite(Unite* u, int i);
    void attaquerJoueur(Unite* u, Joueur* j);
    bool deplacerUnite(int position, int deplacement);
	void jeuJoueurContreJoueur();
	void jeuJoueurContreIA();
	void jeu(int i);
	bool creerUnite(Unite* u, int position);
	bool detruireUnite(int position);
	bool faireEvoluerUnite(Unite* unite);
	//GETTER ET SETTER
	int getTaille() const;
	Unite* getCase(int i) const;
	const std::array<Unite*, TAILLE_PLATEAU>& getCases() const;
	Joueur* getJ1()const;
	Joueur* getJ2()const;
	void setJ1(Joueur* j1);
	void setJ2(Joueur* j2);

};

#endif
