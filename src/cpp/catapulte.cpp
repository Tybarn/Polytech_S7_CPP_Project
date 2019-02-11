#include <iostream>
#include "../includes/catapulte.hpp"
#include "../includes/joueur.hpp"

// ********************** CONSTRUCTEUR ************************

Catapulte::Catapulte():Unite::Unite(){}

Catapulte::Catapulte(Joueur* j1):Unite::Unite(j1){
    m_prix = 20;
    m_ptsDeVie = 12;
    m_ptsAttaque = 6;
    m_dejaAttaque=false;
}

Catapulte::Catapulte(Joueur* j1, int vie,int pos):Unite::Unite(j1){
    m_prix = 20;
    m_ptsDeVie = vie;
    m_ptsAttaque = 6;
    m_dejaAttaque=false;
    m_position= pos;
}

Catapulte::~Catapulte(){}

// ********************** AFFICHAGE **********************

void Catapulte::afficher(){
    std::cout << "Catapulte: " << std::endl;
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

//******************** FONCTION *******************

// une catapulte peut attaquer si il est a porte d'attaque (distance 2,3 ou 3,4)
int Catapulte::ennemiAPorte(){
    if(getBase() == 0){
            Unite* uniteDevant = getPlateau()->getCase(m_position + 2);
            if(uniteDevant != nullptr && uniteDevant->getBase() != getBase()){
                return uniteDevant->getPosition();
            }else {
                uniteDevant = getPlateau()->getCase(m_position + 3);
                if(uniteDevant != nullptr && uniteDevant->getBase() != getBase()){
                    return uniteDevant->getPosition();
                }else {
                    uniteDevant = getPlateau()->getCase(m_position + 4);
                    if(uniteDevant != nullptr && uniteDevant->getBase() != getBase()){
                        return uniteDevant->getPosition();
                    }
                }
            }
    }
    else if(getBase() == getPlateau()->getTaille() - 1){
            Unite* uniteDevant = getPlateau()->getCase(m_position - 2);
            if(uniteDevant != nullptr && uniteDevant->getBase() != getBase()){
                return uniteDevant->getPosition();
            }else{
                uniteDevant = getPlateau()->getCase(m_position - 3);
                if(uniteDevant != nullptr && uniteDevant->getBase() != getBase()){
                    return uniteDevant->getPosition();
                }else {
                    uniteDevant = getPlateau()->getCase(m_position - 4);
                    if(uniteDevant != nullptr && uniteDevant->getBase() != getBase()){
                        return uniteDevant->getPosition();
                    }
                }
            }
    }
    return -1;
}

// L'action 1 d'une catapulte est d'attaquer
void Catapulte::action1(){
    m_dejaAttaque=false;
    std::cout << typeUnite() << " en position " << m_position << " veut attaquer " << std::endl;
    int cible = ennemiAPorte();
    if(cible != -1){
		std::cout << typeUnite() << " en position " << m_position << " attaque la cible en position " << cible << std::endl;
        attaquer(cible);
        m_dejaAttaque=true;
        if(cible-m_position==2 || cible - m_position==-2){
            if(getBase()==0){
                if(getPlateau()->getCase(cible+1) != nullptr){
                    attaquer(cible+1);
                    std::cout << typeUnite() << " en position " << m_position << " attaque la cible en position " << cible+1 << std::endl;
                }
            }else if(getBase()==getPlateau()->getTaille()-1){
                if(getPlateau()->getCase(cible-1) != nullptr){
                    attaquer(cible-1);
                    std::cout << typeUnite() << " en position " << m_position << " attaque la cible en position " << cible-1 << std::endl;
                }
            }
        }else if(cible - m_position==3 || cible - m_position==-3){
            if(getBase()==0){
                if(getPlateau()->getCase(cible+1) != nullptr){
                    attaquer(cible+1);
                    std::cout << typeUnite() << " en position " << m_position << " attaque la cible en position " << cible+1 << std::endl;
                }else if(getPlateau()->getCase(cible+1) == nullptr && cible+1==getPlateau()->getTaille()-1){
					std::cout << typeUnite() << " en position " << m_position << " attaque le joueur " << (getBase()==0?"2":"1") << std::endl;
					getPlateau()->attaquerJoueur(this, getPlateau()->getJ2());
				}
            }else if(getBase()==getPlateau()->getTaille()-1){
                if(getPlateau()->getCase(cible-1) != nullptr){
                    attaquer(cible-1);
                    std::cout << typeUnite() << " en position " << m_position << " attaque la cible en position " << cible-1 << std::endl;
                }else if(getPlateau()->getCase(cible+1) == nullptr && cible+1==getPlateau()->getTaille()-1){
					std::cout << typeUnite() << " en position " << m_position << " attaque le joueur " << (getBase()==0?"2":"1") << std::endl;
					getPlateau()->attaquerJoueur(this, getPlateau()->getJ1());
				}
            }
        }else if(cible-m_position==4 || cible - m_position==-4){
            if(getBase()==0){
                if(getPlateau()->getCase(cible-1) != nullptr){
                    attaquer(cible-1);
                    std::cout << typeUnite() << " en position " << m_position << " attaque la cible en position " << cible-1 << std::endl;
                }
            } else if(getBase()==getPlateau()->getTaille()-1){
                if(getPlateau()->getCase(cible+1) != nullptr){
                    attaquer(cible+1);
                    std::cout << typeUnite() << " en position " << m_position << " attaque la cible en position " << cible+1 << std::endl;
                }
            }
        }
    }
    else if(getBase() == 0 && m_position == getPlateau()->getTaille() - 5) {
        m_dejaAttaque=true;
        std::cout << typeUnite() << " en position " << m_position << " attaque le joueur " << (getBase()==0?"2":"1") << std::endl;
        getPlateau()->attaquerJoueur(this, getPlateau()->getJ2());
        if(getPlateau()->getCase(getPlateau()->getTaille() - 2)!= nullptr){
            attaquer(getPlateau()->getTaille() - 2);
            std::cout << typeUnite() << " en position " << m_position << " attaque l'unite en position 10 "<< std::endl;
        }
    }
    else if(getBase() == getPlateau()->getTaille() - 1 && m_position == 4) {
        m_dejaAttaque=true;
        std::cout << typeUnite() << " en position " << m_position << " attaque le joueur " << (getBase()==0?"2":"1") << std::endl;
        getPlateau()->attaquerJoueur(this, getPlateau()->getJ1());
        if(getPlateau()->getCase(1)!= nullptr){
            attaquer(1);
            std::cout << typeUnite() << " en position " << m_position << " attaque l'unite en position 1"<< std::endl;
        }
    }
    else
        std::cout << typeUnite() << " en position " << m_position << " n'a pas de cible a attaquer" << std::endl;
}

// l'action 2 d'une catapulte ne fait rien pas
void Catapulte::action2(){}

// si l'action 1 n'a pas ete faite , alors la catapulte peut avancer a l'action 3
void Catapulte::action3(){
    std::cout << typeUnite() << " en position " << m_position << " veut d'avancer " << std::endl;
    if(((getBase() == 0 && m_position != getPlateau()->getTaille()-5 && getPlateau()->getCase(m_position+1) == nullptr)
        || (getBase() == getPlateau()->getTaille()-1 && m_position != 4 && getPlateau()->getCase(m_position-1) == nullptr)) && m_dejaAttaque==false){
        std::cout << typeUnite() << " en position " << m_position << " avance a la case suivante " << std::endl;
        avancer();
    }else
         std::cout << typeUnite() << " en position " << m_position << " ne peut pas avancer (case occupee ou base ennemie ou a deja attaque)" << std::endl;
}

std::string Catapulte::typeUnite(){
    return "Cat";
}


