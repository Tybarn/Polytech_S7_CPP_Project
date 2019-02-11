#ifndef SOLDAT_HPP_
#define SOLDAT_HPP_
#include "unite.hpp"
#include "joueur.hpp"
#include <string>

class Soldat : public Unite {
protected:
    //ATTRIBUT
	bool m_dejaAttaque;
	//FONCTION
	int ennemiAPorte();

public:
    //CONSTRUCTEUR
    Soldat();
	Soldat(Joueur* j);
	Soldat(Joueur* j,int ptDeVie, int position);
	~Soldat();
	//AFFICHAGE
    void afficher();
    //FONCTION
    bool peutEvoluer() {return true;}
    Unite* evolution();
	void action1();
	void action2();
	void action3();
    std::string typeUnite();
};

#endif
