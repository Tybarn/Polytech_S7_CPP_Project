#include <iostream>
#include "../includes/unite.hpp"

// ********************** CONSTRUCTEUR ************************

Unite::Unite(){
    m_prix = 0;
    m_ptsDeVie= 0;
    m_ptsAttaque= 0;
    m_position= -1;
    m_joueur= nullptr;
    m_veutEvoluer = false;
}

Unite::Unite(Joueur* j){
    m_joueur = j;
    m_prix = 0;
    m_ptsDeVie= 0;
    m_ptsAttaque= 0;
    m_position= j->getBase();
    m_veutEvoluer = false;
}

Unite::~Unite(){}

//******************** FONCTION *******************

// Avancement d'une unite
void Unite::avancer(){
    if(getBase()==0){
        getPlateau()->deplacerUnite(m_position, 1);
    }
    else if(getBase()==(getPlateau()->getTaille() - 1)){
        getPlateau()->deplacerUnite(m_position, -1);
    }
}

// Attaque d'une unite sur une cible
bool Unite::attaquer(int posCible){
    return getPlateau()->attaqueUnite(this, posCible);
}


//******************** GETTER ET SETTER ***********

// change la m_position d'une unite
void Unite::setPosition(int i){
    if(i > 0 && i<getPlateau()->getTaille())
        this->m_position=i;
}

//renvoie true si l'unite n a plus de vie (=<0)
bool Unite::setVie(int i){
    m_ptsDeVie=m_ptsDeVie-i;
    if(m_ptsDeVie<=0){
        return true;
    }else return false;
}

Joueur* Unite::getJoueur() const{
    return m_joueur;
}

int Unite::getPosition()const{
    return m_position;
}

int Unite::getAttaque()const{
    return m_ptsAttaque;
}

 int Unite::getPtsDeVie()const{
    return m_ptsDeVie;
 }

 int Unite::getPrix()const{
    return m_prix;
 }

// *********************** GETTERS SPECIAUX **************************

int Unite::getBase() const {
    if(this->m_joueur != nullptr)
        return m_joueur->getBase();
    return -1;
}

Plateau* Unite::getPlateau() const {
    if(this->m_joueur == nullptr)
        return nullptr;
    return m_joueur->getPlateau();
}
