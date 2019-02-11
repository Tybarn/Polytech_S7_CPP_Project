#include <iostream>
#include "../includes/archer.hpp"
#include "../includes/joueur.hpp"

// ********************** CONSTRUCTEUR ************************

Archer::Archer():Unite::Unite(){}

Archer::Archer(Joueur* j):Unite::Unite(j){
    m_prix = 12;
    m_ptsDeVie = 8;
    m_ptsAttaque = 3;
    m_position = j->getBase();
}

Archer::Archer(Joueur* j,int vie, int pos):Unite::Unite(j){
    m_prix = 12;
    m_ptsDeVie = vie;
    m_ptsAttaque = 3;
    m_position = pos;

}

Archer::~Archer(){}

// ********************** AFFICHAGE **********************

void Archer::afficher(){
    std::cout << "Archer: " << std::endl;
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

// un archer peut attaquer si il est a porte d'attaque (distance 1,2 et 3)
int Archer::ennemiAPorte(){
    if(getBase() == 0){
        Unite* uniteDevant = getPlateau()->getCase(m_position + 1);
        if(uniteDevant != nullptr && uniteDevant->getBase() != getBase()){
            return uniteDevant->getPosition();
        }else{
            uniteDevant = getPlateau()->getCase(m_position + 2);
            if(uniteDevant != nullptr && uniteDevant->getBase() != getBase()){
                return uniteDevant->getPosition();
            }else{
                uniteDevant = getPlateau()->getCase(m_position + 3);
                if(uniteDevant != nullptr && uniteDevant->getBase() != getBase()){
                    return uniteDevant->getPosition();
                }
            }
        }
    }
    else if(getBase() == getPlateau()->getTaille() - 1){
        Unite* uniteDevant = getPlateau()->getCase(m_position - 1);
        if(uniteDevant != nullptr && uniteDevant->getBase() != getBase()){
            return uniteDevant->getPosition();
        }else{
            uniteDevant = getPlateau()->getCase(m_position - 2);
            if(uniteDevant != nullptr && uniteDevant->getBase() != getBase()){
                return uniteDevant->getPosition();
            }else if(uniteDevant == nullptr){
                uniteDevant = getPlateau()->getCase(m_position - 3);
                if(uniteDevant != nullptr && uniteDevant->getBase() != getBase()){
                    return uniteDevant->getPosition();
                }
            }
        }
    }
    return -1;
}

// L'action 1 d'un archer est d'attaquer
void Archer::action1(){
    std::cout << typeUnite() << " en position " << m_position << " veut attaquer " << std::endl;
    int cible = ennemiAPorte();
    if(cible != -1){
        std::cout << typeUnite() << " en position " << m_position << " attaque la cible en position " << cible << std::endl;
        attaquer(cible);
    }
    else if(getBase() == 0 && (m_position == getPlateau()->getTaille() - 2
            || m_position == getPlateau()->getTaille() - 3 || m_position == getPlateau()->getTaille() - 4)) {
        std::cout << typeUnite() << " en position " << m_position << " attaque le joueur " << (getBase()==0?"2":"1") << std::endl;
        getPlateau()->attaquerJoueur(this, getPlateau()->getJ2());
    }
    else if(getBase() == getPlateau()->getTaille() - 1 && (m_position == 1 || m_position == 2 || m_position == 3)) {
        std::cout << typeUnite() << " en position " << m_position << " attaque le joueur " << (getBase()==0?"2":"1") << std::endl;
        getPlateau()->attaquerJoueur(this, getPlateau()->getJ1());
    }
    else
        std::cout << typeUnite() << " en position " << m_position << " n'a pas de cible a attaquer" << std::endl;
}

// l'action 2 d'un archer est d'avancer
void Archer::action2(){
    std::cout << typeUnite() << " en position " << m_position << " veut d'avancer " << std::endl;
    if((getBase() == 0 && m_position != getPlateau()->getTaille() - 2 && getPlateau()->getCase(m_position+1) == nullptr)
        || (getBase() == (Plateau::TAILLE_PLATEAU - 1) && m_position != 1 && getPlateau()->getCase(m_position-1) == nullptr)){
        std::cout << typeUnite() << " en position " << m_position << " avance a la case suivante " << std::endl;
        avancer();
    }else
        std::cout << typeUnite() << " en position " << m_position << " ne peut pas avancer (case occupee ou base ennemie)" << std::endl;
}

void Archer::action3(){}

std::string Archer::typeUnite(){
    return "Arc";
}
