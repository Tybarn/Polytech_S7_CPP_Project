#ifndef ARCHER_HPP_
#define ARCHER_HPP_
#include "unite.hpp"
#include "joueur.hpp"
#include <string>

class Archer : public Unite {
protected:
	//FONCTION
	int ennemiAPorte();

public:
    //CONSTRUCTEUR
    Archer();
	Archer(Joueur* j1);
	Archer(Joueur* j1,int vie,int pos);
	~Archer();
	//AFFICHAGE
    void afficher();
    //FONCTION
	void action1();
	void action2();
	void action3();
    std::string typeUnite();
};

#endif
