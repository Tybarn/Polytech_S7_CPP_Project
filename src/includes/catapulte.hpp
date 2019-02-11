#ifndef CATAPULTE_HPP_
#define CATAPULTE_HPP_
#include "unite.hpp"
#include "joueur.hpp"
#include <string>

class Catapulte : public Unite {
protected:
    //ATTRIBUT
	bool m_dejaAttaque;
	//FONCTION
	int ennemiAPorte();

public:
    //CONSTRUCTEUR
    Catapulte();
	Catapulte(Joueur* j1);
	Catapulte(Joueur* j1, int vie,int pos);
	~Catapulte();
	//AFFICHAGE
    void afficher();
    //FONCTION
	void action1();
	void action2();
	void action3();
    std::string typeUnite();
};

#endif
