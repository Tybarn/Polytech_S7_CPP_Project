#include <iostream>
#include "../includes/soldat.hpp"
#include "../includes/joueur.hpp"
#include "../includes/superSoldat.hpp"

// ********************** CONSTRUCTEUR ************************

Soldat::Soldat():Unite::Unite(){}

Soldat::Soldat(Joueur* j):Unite::Unite(j){
    m_prix = 10;
    m_ptsDeVie = 10;
    m_ptsAttaque = 4;
    m_dejaAttaque=false;
}

Soldat::Soldat(Joueur* j,int ptDeVie, int pos):Unite::Unite(j){
    m_prix = 10;
    m_ptsDeVie = ptDeVie;
    m_ptsAttaque = 4;
    m_dejaAttaque=false;
    m_position = pos;
}

Soldat::~Soldat(){}

// ********************** AFFICHAGE **********************

void Soldat::afficher(){
    std::cout << "Soldat: " << std::endl;
    if(m_joueur != nullptr) {
        if(Plateau::jeuContrejoueur)
        std::cout << "(Joueur " << ((m_joueur->getBase() == 0)? "1" : "2") << ")" << std::endl;
        else
        std::cout << "(" << ((m_joueur->getBase() == 0)? "Joueur 1" : "IA") << ")" << std::endl;
        std::cout << "Prix: " << m_prix << std::endl;
        std::cout << "Points de Vie: " << m_ptsDeVie << std::endl;
        std::cout << "Points d attaque: " << m_ptsAttaque << std::endl;
        std::cout << "Position: " << m_position << std::endl;
        std::cout << std::endl;
    }
}

//******************** FONCTION *******************

// un soldat peut attaquer si il est a porte d'attaque (distance 1)
int Soldat::ennemiAPorte(){
    if(getBase() == 0){
        Unite* uniteDevant = getPlateau()->getCase(m_position + 1);
        if(uniteDevant != nullptr && uniteDevant->getBase() != getBase())
            return uniteDevant->getPosition();
    }
    else if(getBase() == getPlateau()->getTaille() - 1){
        Unite* uniteDevant = getPlateau()->getCase(m_position - 1);
        if(uniteDevant != nullptr && uniteDevant->getBase() != getBase())
            return uniteDevant->getPosition();
    }
    return -1;
}

// L'action 1 d'un soldat est d'attaquer
void Soldat::action1(){
    m_dejaAttaque=false;
    std::cout << typeUnite() << " en position " << m_position << " veut attaquer " << std::endl;
    int cible = ennemiAPorte();
    if(cible != -1){
        std::cout << typeUnite() << " en position " << m_position << " attaque la cible en position " << cible << std::endl;
        m_veutEvoluer = attaquer(cible);
        m_dejaAttaque=true;
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

// l'action 2 d'un soldat est d'avancer
void Soldat::action2(){
    std::cout << typeUnite() << " en position " << m_position << " veut d'avancer " << std::endl;
    if((getBase() == 0 && m_position != getPlateau()->getTaille()-2 && getPlateau()->getCase(m_position+1) == nullptr)
        || (getBase() == getPlateau()->getTaille()-1 && m_position != 1 && getPlateau()->getCase(m_position-1) == nullptr)){
        std::cout << typeUnite() << " en position " << m_position << " avance a la case suivante " << std::endl;
        avancer();
    }else
        std::cout << typeUnite() << " en position " << m_position << " ne peut pas avancer (case occupee ou base ennemie)" << std::endl;
}

// si l'action 1 n'a pas ete faite , alors le soldat peut attaquer dans l'action 3
void Soldat::action3(){
    if(m_dejaAttaque == true)
        return;
    std::cout << typeUnite() << " en position " << m_position << " veut attaquer " << std::endl;
    int cible = ennemiAPorte();
    if(cible != -1){
        std::cout << typeUnite() << " en position " << m_position << " attaque la cible en position " << cible << std::endl;
        attaquer(cible);
        m_dejaAttaque=true;
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

std::string Soldat::typeUnite(){
    return "Sdt";
}

//fait evoluer le soldat en superSoldat
Unite* Soldat::evolution() {
    return new SuperSoldat(*this);
}
