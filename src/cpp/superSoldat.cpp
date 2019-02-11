#include <iostream>
#include "../includes/superSoldat.hpp"

// ********************** CONSTRUCTEUR ************************

SuperSoldat::SuperSoldat():Soldat::Soldat(){}

SuperSoldat::SuperSoldat(Soldat s):Soldat::Soldat(){
	m_joueur = s.getJoueur();
    m_prix = s.getPrix();
    m_ptsDeVie = s.getPtsDeVie();
    m_ptsAttaque = s.getAttaque();
    m_position = s.getPosition();
}

SuperSoldat::~SuperSoldat(){}

// ********************** AFFICHAGE ************************

void SuperSoldat::afficher(){
    std::cout << "SuperSoldat: " << std::endl;
    if(m_joueur != nullptr) {
        if(Plateau::jeuContrejoueur)
        std::cout << "(Joueur " << ((m_joueur->getBase() == 0)? "1" : "2") << ")" << std::endl;
        else
        std::cout << "(" << ((m_joueur->getBase() == 0)? "Joueur 1" : "IA") << ")" << std::endl;

        std::cout << "Prix: " << m_prix << std::endl;
        std::cout << "Points de Vie: " << m_ptsDeVie << std::endl;
        std::cout << "Points d attaque: " << m_ptsAttaque << std::endl;
        std::cout << "Position: " << m_position << std::endl << std::endl;
    }
}

// ********************** FONCTIONS ************************

// L'action 3 d'un superSoldat est d'attaquer
void SuperSoldat::action3() {
	std::cout << typeUnite() << " en position " << m_position << " veut attaquer " << std::endl;
    int cible = ennemiAPorte();
    if(cible != -1){
        std::cout << typeUnite() << " en position " << m_position << " attaque la cible en position " << cible << std::endl;
        attaquer(cible);
    }
    else if(getBase() == 0 && m_position == getPlateau()->getTaille() - 2) {
        std::cout << typeUnite() << " en position " << m_position << " attaque le joueur " << (getBase()==0?"2":"1") << std::endl;
        getPlateau()->attaquerJoueur(this, getPlateau()->getJ2());
        m_dejaAttaque = true;
    }
    else if(getBase() == getPlateau()->getTaille() - 1 && m_position == 1) {
        std::cout << typeUnite() << " en position " << m_position << " attaque le joueur " << (getBase()==0?"2":"1") << std::endl;
        getPlateau()->attaquerJoueur(this, getPlateau()->getJ1());
        m_dejaAttaque = true;
    }
    else
       std::cout << typeUnite() << " en position " << m_position << " n'a pas de cible a attaquer" << std::endl;
}

std::string SuperSoldat::typeUnite(){
    return "SpSdt";
}
