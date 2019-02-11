#include <iostream>
#include <cstdlib>
#include "../includes/joueur.hpp"
#include "../includes/unite.hpp"
#include "../includes/soldat.hpp"
#include "../includes/archer.hpp"
#include "../includes/catapulte.hpp"

class Soldat;
class Archer;
class Catapulte;
// ********************** CONSTRUCTEUR ************************

Joueur::Joueur(){
    m_argent=-1;
    m_ptDeVie=-1;
    m_base=-1;
    m_plateau = nullptr;
}

Joueur::Joueur(int newargent,int newptDeVie){
    m_argent= newargent;
    m_ptDeVie= newptDeVie;
    m_plateau=nullptr;
}

Joueur::Joueur(int newargent, int newptDeVie, Plateau* pt){
    m_argent= newargent;
    m_ptDeVie= newptDeVie;
    m_plateau = pt;
    if(pt!=nullptr){
        if(pt->getJ1() == nullptr && pt->getJ2() == nullptr){
            pt->setJ1(this);
            m_base = 0;
        }else if(pt->getJ1() != nullptr && pt->getJ2() == nullptr){
            pt->setJ2(this);
            m_base = Plateau::TAILLE_PLATEAU - 1;
        }else{
            m_base = -1;
        }
    }
}

Joueur::~Joueur(){

}

//********************** AFFICHAGE *********************

void Joueur::afficherJoueur()const{
    std::cout << "Joueur "<< ((m_base==0)? "1" : (m_base==m_plateau->getTaille()-1)?"2" : " ") << ":\n" << "Point de vie: " << m_ptDeVie << "\nArgent:" << m_argent << "\n"<<std::endl;
}

// ************************ FONCTION ***********************

void Joueur::addArgent(int i){
    m_argent= m_argent+i;
}

void Joueur::ajouterArgent(int i){
    if(i>0)
        addArgent(i);
}

bool Joueur::enleverArgent(int i){
    if(i>0 && i<=m_argent ){
        addArgent(-i);
        return true;
    }
    return false;
}

void Joueur::creerUnite(Unite* u){
	std::cout << "\n\n************************* PHASE CREATION UNITE ****************************\n\n" << std::endl;
    m_plateau->creerUnite(u,m_base);
}

//Deroulement de la partie
void Joueur::jouer(){
    if(m_base == 0)
        std::cout << "\n\n*********************** JOUEUR 1 *************************\n\n";
    else
        std::cout << "\n\n*********************** JOUEUR 2 *************************\n\n";
    action1();
    action2();
    action3();
    std::cout << "\n\n************************* AFFICHAGE DU PLATEAU APRES LES PHASES DU JOUEUR " << ((m_base==0)? "1":"2") << " ****************************\n\n" << std::endl;
    m_plateau->afficherPlateau();
	creationUnite();
}

// Jeu contre IA (simple)
void Joueur::jouerIASimple(){
    if(m_base ==0)
        std::cout << "\n\n*********************** JOUEUR 1 *************************\n\n";
    else
        std::cout << "\n\n***********************    IA    *************************\n\n";

    action1();
    action2();
    action3();
    if(m_base==0)
        std::cout << "\n\n************************* AFFICHAGE DU PLATEAU APRES LES PHASES DU JOUEUR 1 ****************************\n\n" << std::endl;
    else
        std::cout << "\n\n*************************   AFFICHAGE DU PLATEAU APRES LES PHASES DE L'IA   ****************************\n\n" << std::endl;
    m_plateau->afficherPlateau();
    creationUniteIA();
}

// pour la phase un, ce sont les unites du joueur courant les plus pres de la base qui jouer en premier
void Joueur::action1(){
    std::cout << "\n\n************************* PHASE 1 ****************************\n\n" << std::endl;
    const std::array<Unite*, Plateau::TAILLE_PLATEAU>& pt = m_plateau->getCases();
    if(m_base==0){
        for(int i=0;i<=Plateau::TAILLE_PLATEAU - 1;i++){
            if(pt[i]!=nullptr) {
                Unite* unite = pt[i];
                if(unite->getJoueur()->getBase()==this->m_base){
                    unite->action1();
                    if(unite->souhaiteEvoluer())
                        m_plateau->faireEvoluerUnite(unite);
                }
            }
        }
    }
    else if(m_base==Plateau::TAILLE_PLATEAU - 1){
        for(int i=m_base;i>=0;i--){
            if(pt[i]!=nullptr) {
                Unite* unite = pt[i];
                if(unite->getJoueur()->getBase()==this->m_base){
                    unite->action1();
                    if(unite->souhaiteEvoluer())
                        m_plateau->faireEvoluerUnite(unite);
                }
            }
        }
    }
}

// pour les phases deux, c'est les unites du joueur courant le plus loin de sa base qui commence
void Joueur::action2(){
    std::cout << "\n\n************************* PHASE 2 ****************************\n\n" << std::endl;
    const std::array<Unite*, Plateau::TAILLE_PLATEAU>& pt = m_plateau->getCases();
    if(m_base==0){
        for(int i=Plateau::TAILLE_PLATEAU - 1;i>=0;i--){
            if(pt[i]!=nullptr) {
                Unite* unite = pt[i];
                if(unite->getJoueur()->getBase()==this->m_base){
                    unite->action2();
                    if(unite->souhaiteEvoluer())
                        m_plateau->faireEvoluerUnite(unite);
                }
            }
        }
    }
    else if(m_base==Plateau::TAILLE_PLATEAU-1){
        for(int i=0;i<=m_base;i++){
            if(pt[i]!=nullptr) {
                Unite* unite = pt[i];
                if(unite->getJoueur()->getBase()==this->m_base){
                    unite->action2();
                    if(unite->souhaiteEvoluer())
                        m_plateau->faireEvoluerUnite(unite);
                }
            }
        }
    }
}

// pour les phases trois, c'est les unites du joueur courant le plus loin de sa base qui commence
void Joueur::action3(){
    std::cout << "\n\n************************* PHASE 3 ****************************\n\n" << std::endl;
    const std::array<Unite*, Plateau::TAILLE_PLATEAU>& pt = m_plateau->getCases();
    if(m_base==0){
        for(int i=Plateau::TAILLE_PLATEAU-1;i>=0;i--){
            if(pt[i]!=nullptr) {
                Unite* unite = pt[i];
                if(unite->getJoueur()->getBase()==this->m_base){
                    unite->action3();
                    if(unite->souhaiteEvoluer())
                        m_plateau->faireEvoluerUnite(unite);
                }
            }
        }
    }
    else if(m_base==Plateau::TAILLE_PLATEAU-1){
        for(int i=0;i<=m_base;i++){
            if(pt[i]!=nullptr) {
                Unite* unite = pt[i];
                if(unite->getJoueur()->getBase()==this->m_base){
                    unite->action3();
                    if(unite->souhaiteEvoluer())
                        m_plateau->faireEvoluerUnite(unite);
                }
            }
        }
    }
}

// creer un soldat dans la base du joueur
void Joueur::creerSoldat(){
    Unite* s;
    s= new Soldat(this);
    creerUnite(s);
}

// creer un archer dans la base du joueur
void Joueur::creerArcher(){
    Unite* s;
    s= new Archer(this);
    creerUnite(s);
}

// creer une catapulte dans la base du joueur
void Joueur::creerCatapulte(){
    Unite* s;
    s= new Catapulte(this);
    creerUnite(s);
}

// Creation d'une unite par l'IA
void Joueur::creationUniteIA(){
    bool peutCreer = (m_argent >= 10 &&
        ((m_base==(getPlateau()->getTaille() - 1) && this->getPlateau()->getCases()[getPlateau()->getTaille() - 1]==nullptr)
        || (m_base==0 && this->getPlateau()->getCases()[0]==nullptr)));
    if(peutCreer){
        if(m_argent>=20){
            std::cout << "IA CREE UNE CATAPULTE" << std::endl;
            creerCatapulte();
        }else if(m_argent>=12){
            std::cout << "IA CREE UN ARCHER" << std::endl;
            creerArcher();
        }else if(m_argent>=10){
            std::cout << "IA CREE UN SOLDAT" << std::endl;
            creerSoldat();
        }
    }


}

// permet de faire choisir quelle unite creer
void Joueur::creationUnite(){
    bool peutCreer = (m_argent >= 10 &&
        ((m_base==m_plateau->getTaille()-1 && this->getPlateau()->getCases()[m_plateau->getTaille()-1]==nullptr)
        || (m_base==0 && this->getPlateau()->getCases()[0]==nullptr)));
    bool actionReussie = true;
    int choix=0;
    std::cout << "\n\n************************* PHASE CREATION D'UNITE ****************************\n\n" << std::endl;
    do{
        std::cout << "VOUS AVEZ " << m_argent << " PIECES "<< std::endl;
        if(peutCreer){
                std::cout << "Veuillez choisir une unite a creer: " << std::endl;
                if(m_argent>=20)
                std::cout << "1-Soldat (10 pieces)\n" << "2-Archer (12 pieces)\n" << "3-Catapulte (20 pieces)" << std::endl;
                else if(m_argent>=12)
                    std::cout << "1-Soldat (10 pieces)\n" << "2-Archer (12 pieces)\n" << std::endl;
                else if(m_argent>=10)
                    std::cout << "1-Soldat (10 pieces)\n" << std::endl;
        }
        else{
            if(m_argent <10)
                std::cout << "VOUS N'AVEZ PAS SUFFISAMENT D'ARGENT POUR CREER UNE UNITE\n";
            if((m_base==m_plateau->getTaille()-1 && this->getPlateau()->getCases()[m_plateau->getTaille()-1]!=nullptr)
                    || (m_base==0 && this->getPlateau()->getCases()[0]!=nullptr))
                std::cout << "VOTRE BASE CONTIENT DEJA UNE UNITE\n";
            }
        std::cout << "4-Ne rien faire\n";
        std::cout << "5-Sauvegarder votre partie et quitter\nVotre choix: ";
        if(!(std::cin >> choix)) {
            std::cerr << "\nCHOIX INCORRECT ! Vous devez choisir un chiffre parmi les choix disponibles. RECOMMENCEZ !\n" << std::endl;
            std::cin.clear();
            std::cin.ignore(1);
            actionReussie = false;
        }else{
            actionReussie=true;
        }

        if(actionReussie){
            if(peutCreer && choix == 1 && m_argent>=8) {
                creerSoldat();
                actionReussie = true;
            }
            else if(peutCreer && choix == 2 && m_argent >=12) {
                creerArcher();
                actionReussie = true;
            }
            else if(peutCreer && choix == 3 && m_argent >=20) {
                creerCatapulte();
                actionReussie = true;
            }else if(choix == 5){
                actionReussie = true;
                if(this->getPlateau()->sauvegarderPartie(this)){
                    std::cout << "Merci d'avoir joue, nous avons sauvegarde votre partie pour une prochaine fois";
                    exit(0);
                }
            }else if(choix == 4)
                actionReussie = true;
            else{
                std::cerr << "\nChoix incorrect ! Vous devez choisir un chiffre parmi les choix disponibles. Recommencez !\n" << std::endl;
                actionReussie=false;
            }
        }
	}while(!actionReussie);
}

//********************* GETTER ET SETTER ********************

int Joueur::getBase()const{
    return m_base;
}

void Joueur::setBase(int i){
    if(i==0 || i==m_plateau->getTaille()-1)
        m_base=i;
}

int Joueur::getArgent()const{
    return m_argent;

}

int Joueur::getPtDeVie()const{
    return m_ptDeVie;
}

void Joueur::perdrePointDeVie(int i){
    m_ptDeVie= m_ptDeVie-i;
}

Plateau* Joueur::getPlateau()const{
    return m_plateau;
}

void Joueur::setPlateau(Plateau* plt){
    m_plateau=plt;
}

