#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <array>
#include <iterator>
#include "../includes/plateau.hpp"
#include "../includes/unite.hpp"
#include "../includes/soldat.hpp"
#include "../includes/archer.hpp"
#include "../includes/catapulte.hpp"

class Soldat;
class Archer;
class Catapulte;

// ********************** CONSTRUCTEUR ************************

Plateau::Plateau(int i){
    if(i==1 || i ==2){
        for(auto c = m_cases.begin(); c != m_cases.end(); c++){
            *c = nullptr;
        }
        m_J1 = new Joueur(0,100,this);
        m_J1->setPlateau(this);
        m_J1->setBase(0);
        m_J2 = new Joueur(0,100,this);
        m_J2->setPlateau(this);
        m_J2->setBase(getTaille()-1);
    }else if(i==3){
        chargerPartie(this);
        this->m_J1->setPlateau(this);
        this->m_J1->setBase(0);
        this->m_J2->setPlateau(this);
        this->m_J2->setBase(getTaille()-1);
        this->m_J1->afficherJoueur();
        this->m_J2->afficherJoueur();
    }
}

Plateau::~Plateau(){
    for(auto c = m_cases.begin(); c != m_cases.end(); c++)
        delete *c;
}

// ******************* AFFICHAGE ***************

void Plateau::afficherPlateau() const {
    std::cout << "\nRappel: Arc = ARCHER, Slt = SOLDAT, SpSlt = SUPER SOLDAT, Cat = CATAPULTE " << std::endl;
    std::cout << "JOUEUR 1: \t\t" << "JOUEUR 2: \n" << "Pt de vie:" << m_J1->getPtDeVie()
    << "\t\t" << "Pt de vie:" << m_J2->getPtDeVie() << "\nArgent:" << m_J1->getArgent()
    << "\t\t" << "Argent:" << m_J2->getArgent() << std::endl;

    std::cout << std::endl;
        std::cout << "Plateau: \n|";

    // Ligne 1
    for(int i = 0; i < TAILLE_PLATEAU; i++) {
        std::cout << "\tCase " << i << "\t|";
    }
    std::cout << std::endl;

    // Ligne 2
    std::cout << "|\tBase J1 |\t";
    for(int i = 0; i < TAILLE_PLATEAU - 2; i++) {
        std::cout << "\t|\t";
    }
    std::cout << "Base J2 |\n";

    // Ligne 3
    std::cout << "|";
    for(int i = 0; i < TAILLE_PLATEAU; i++) {
        if(jeuContrejoueur)
            std::cout << "\t" << ((m_cases[i]==nullptr)? "Vide": (m_cases[i]->getJoueur()->getBase()== 0) ? "J1":"J2") << "\t|";
        else
            std::cout << "\t" << ((m_cases[i]==nullptr)? "Vide": (m_cases[i]->getJoueur()->getBase()== 0) ? "J1":"IA") << "\t|";
    }
    std::cout << std::endl;

    // Ligne 4
    std::cout << "|";
    for(auto c = m_cases.begin(); c != m_cases.end(); c++) {
        std::cout << "\t" << ((*c == nullptr) ? "" : ((*c)->typeUnite())) << "\t|";
    }
    std::cout << std::endl;

    // Ligne 5
    std::cout << "|";
    for(auto c = m_cases.begin(); c != m_cases.end(); c++) {
        std::cout << "\tPV:" << ((*c == nullptr) ? 0 : ((*c)->getPtsDeVie())) << "\t|";
    }
    std::cout << std::endl;

    // Ligne 6
    std::cout << "|";
    for(auto c = m_cases.begin(); c != m_cases.end(); c++) {
        std::cout << "\tPA:" << ((*c == nullptr)? 0 : (*c)->getAttaque()) << "\t|";
    }

    std::cout << "\n" << std::endl;
}

//******************** FONCTION *******************

void Plateau::chargerPartie(Plateau * pt){
    std::ifstream fichier("src/Ressource/partieEnregistre.txt", std::ios::in);
    if(fichier){
        //Parseur
        Joueur *J1=nullptr,*J2=nullptr;
        int argent, ptDeVie;
        int joueurCourant;
        int caseActuelle;
        std::string uniteCourant;
        int baseUnite,vieUnite;
        int nbtour;
        std::cout << "FICHIER OUVERT EN LECTURE " << std::endl;
        //enregistre les donnees des joueurs 1 et 2
        //J1
		int modejeu=0;
		fichier >> modejeu;
		if(modejeu==1)
			Plateau::jeuContrejoueur = true;
		else if(modejeu==2)
			Plateau::jeuContrejoueur = false;
        fichier >> argent;
        fichier >> ptDeVie;

        J1 = new Joueur(argent,ptDeVie);


        std::cout << "CHARGEMENT DE JOUEUR 1 TERMINE " << std::endl;
        //J2
        fichier >> argent;
        fichier >> ptDeVie;
        J2 = new Joueur(argent,ptDeVie);

        std::cout << "CHARGEMENT DE JOUEUR 2 TERMINE " << std::endl;

        //enregistrer le numero du joueur courant
        fichier >> joueurCourant;
        std::cout << "CHARGEMENT DE JOUEUR COURANT TERMINE " << std::endl;

        pt->m_J1=J1;
        pt->m_J2=J2;

        //enregistrer les m_cases du plateaux
        for(int i=0; i < 12; i++){
            fichier >> caseActuelle;
            std::cout << "CHARGEMENT CASE ACTUELLE " << i << std::endl;

            if(caseActuelle != -1){
                fichier >> uniteCourant >> baseUnite >> vieUnite;
                if(uniteCourant == "Sdt"){
                   pt->m_cases[i] =new Soldat(((baseUnite==0)? pt->getJ1():pt->getJ2()), vieUnite,i);
                }else if(uniteCourant == "Arc"){
                    pt->m_cases[i] =new Archer(((baseUnite==0)? pt->getJ1():pt->getJ2()), vieUnite,i);
                }else if(uniteCourant == "Cat"){
                    pt->m_cases[i] =new Catapulte(((baseUnite==0)? pt->getJ1():pt->getJ2()), vieUnite,i);
                }
                pt->m_cases[i]->afficher();
            }else{
                pt->m_cases[i]=nullptr;
                std::cout << "CHARGEMENT DE LA CASE TERMINE (VIDE)" << std::endl;
            }
        }

        fichier >> nbtour;
        //pt->getCase(1)->afficher();
        Plateau::nombreTour = nbtour;
        Plateau::joueurActuelle= joueurCourant;
        std::cout << "CHARGEMENT DU PLATEAU TERMINE " << std::endl;

        fichier.close();
    }else
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;

}

bool Plateau::sauvegarderPartie(Joueur* j){
    int choixJoueur=0;

    if(chercherFichier()){
        std::cout << "Attention vous allez supprimer le fichier de sauvegarde qui existe, voulez vous vraiment faire ca ?\n1 - Oui\n2 - Annuler" << std::endl;

        if(!(std::cin >> choixJoueur)) {
            std::cerr << "Information entree incorrecte. Veuillez entrer uniquement un chiffre.\n";
            std::cin.clear();
            std::cin.ignore(1);
        }
        while(choixJoueur != 2 && choixJoueur != 1) {
            std::cerr << "Choix entre impossible" << std::endl;
            std::cout << "Votre choix (numero): ";
            if(!(std::cin >> choixJoueur)) {
                std::cerr << "Information entree incorrecte. Veuillez entrer uniquement un chiffre.\n";
                std::cin.clear();
                std::cin.ignore(1);
            }
        }
    }
	if(choixJoueur == 2)
        return false;


    std::ofstream fichier("src/Ressource/partieEnregistre.txt", std::ios::out | std::ios::trunc);
    if(fichier){

    std::cout << "FICHIER OUVERT EN ECRITURE " << std::endl;
    //enregistre le mode de jeu
    fichier << ((jeuContrejoueur == true)? "1" : "2");
    fichier << "\n" ;
    //enregistre les donnees des joueurs 1 et 2
    //m_J1
    fichier << m_J1->getArgent() << " " << m_J1->getPtDeVie() << "\n";
    std::cout << "ENREGISTREMENT DE JOUEUR 1 TERMINE " << std::endl;
    //m_J2
    fichier << m_J2->getArgent() << " " << m_J2->getPtDeVie() << "\n";
    std::cout << "ENREGISTREMENT DE JOUEUR 2 TERMINE " << std::endl;
    //enregistrer le numero du joueur courant
    fichier << j->getBase() << "\n";
    std::cout << "ENREGISTREMENT DE JOUEUR COURANT TERMINE " << std::endl;

    //enregistrer les m_cases du plateaux
    for(int i=0; i < 12; i++){
        if(getCase(i)!=nullptr){
            fichier << i << " " <<getCase(i)->typeUnite() << " " << getCase(i)->getBase() << " " << getCase(i)->getPtsDeVie() << std::endl;
            std::cout << "ENREGISTREMENT DE LA CASE " << i << " TERMINE " << std::endl;
        }else{
            fichier << -1 << std::endl;
            std::cout << "ENREGISTREMENT DE LA CASE TERMINE (VIDE)" << std::endl;
        }
    }
    fichier<< nombreTour << std::endl;

    std::cout << "ENREGISTREMENT DU PLATEAU TERMINE " << std::endl;
    //enregistrer d'autre information si besoin


    fichier.close();

    exit(0);
    }else
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
    return false;
}

bool Plateau::chercherFichier(){
    std::string monFichier = "src/Ressource/partieEnregistre.txt";
    std::ifstream fichier(monFichier.c_str(), std::ios::in);
    if(fichier){ fichier.close(); return true;}
    else return false;
}

void Plateau::donnerArgentDebutTour(){
    std::cout << "TOUS LES JOUEURS GAGNENT 8 PIECES d'OR " << std::endl;
    m_J1->ajouterArgent(8);
    m_J2->ajouterArgent(8);
}

// l unite u attaque l emplacement i du plateau, return true si la cible a ete detruite
bool Plateau::attaqueUnite(Unite* attaquant , int posCible){
    if(m_cases[posCible]!=nullptr){
       // std::cout << "L'UNITE " << attaquant->typeUnite() <<  " EN POSITION " << attaquant->getPosition() << " ATTAQUE L'UNITE " << m_cases[posCible]->typeUnite() << " EN CASE " << posCible << std::endl;
        if(m_cases[posCible]->setVie(attaquant->getAttaque())) {
            std::cout << "L'UNITE EST MORTE" << std::endl;
            if(attaquant->getJoueur()->getBase()==0)
                m_J1->ajouterArgent(m_cases[posCible]->getPrix()/2);
            else if(attaquant->getJoueur()->getBase() == (TAILLE_PLATEAU - 1))
                m_J2->ajouterArgent(m_cases[posCible]->getPrix()/2);
            detruireUnite(posCible);
            return true;
        }
        else {
            std::cout << "L'UNITE N'EST PAS MORTE" << std::endl;
        }
    }
    return false;
}

// l unite u attaque le joueur j
void Plateau::attaquerJoueur(Unite* u, Joueur* j){
    j->perdrePointDeVie(u->getAttaque());
}

void Plateau::jeuJoueurContreIA(){
    int limite =100;

    if(!partieCharge){
        nombreTour=0;
    }else{
        std::cout << "\n\n*******************  REPRISE DU JEU TOUR " << nombreTour << "**************************\n\n" << std::endl;

    }
    while(m_J1->getPtDeVie()>0 && m_J2->getPtDeVie()>0 && nombreTour<limite){

		if(Plateau::partieCharge== false){
			std::cout << "\n\n*************  TOUR " << nombreTour << "   **************\n\n" << std::endl;
			donnerArgentDebutTour();
			std::cout << "\n\n************************* AFFICHAGE DU PLATEAU AVANT LES PHASES DU JOUEUR 1 ****************************\n\n" << std::endl;
			this->afficherPlateau();
			m_J1->jouer();
			std::cout << "\n\n*************************   AFFICHAGE DU PLATEAU AVANT LES PHASES DE L'IA   ****************************\n\n" << std::endl;
			this->afficherPlateau();
			m_J2->jouerIASimple();
			nombreTour++;
		}
		if(Plateau::partieCharge && joueurActuelle==0){
			this->afficherPlateau();
            m_J1->creationUnite();
            partieCharge = false;
            std::cout << "\n\n*************************   AFFICHAGE DU PLATEAU AVANT LES PHASES DE L'IA   ****************************\n\n" << std::endl;
            this->afficherPlateau();
            m_J2->jouerIASimple();
		}


    }
    std::cout << "\n\nNombre de tour joue: " << nombreTour << std::endl;
    if(nombreTour == limite){
        std::cout << "Match null : Personne n a gagne " << std::endl;
    }else
        std::cout << "Le grand gagnant est :" << (m_J1->getPtDeVie() <=0 ? " IA(simple) " : " J1") << std::endl;
}

void Plateau::jeu(int i){
    if(i==1){
        jeuContrejoueur=true;
        partieCharge=false;
        jeuJoueurContreJoueur();
    }else if(i==2){
        jeuContrejoueur=false;
        jeuJoueurContreIA();
    }else if(i==3){
        partieCharge=true;
        if(jeuContrejoueur)
			jeuJoueurContreJoueur();
        else if(!jeuContrejoueur)
			jeuJoueurContreIA();
    }
}

void Plateau::jeuJoueurContreJoueur(){
    if(!partieCharge){
        nombreTour=0;
    }else{
        std::cout << "\n\n*******************  REPRISE DU JEU TOUR " << nombreTour << "**************************\n\n" << std::endl;
    }
    int limite =100;


    while(m_J1->getPtDeVie()>0 && m_J2->getPtDeVie()>0 && nombreTour<limite){
        if(Plateau::partieCharge== false){
            std::cout << "\n\n*************  TOUR " << nombreTour << "   **************\n\n" << std::endl;
            donnerArgentDebutTour();
            std::cout << "\n\n************************* AFFICHAGE DU PLATEAU AVANT LES PHASES DU JOUEUR 1 ****************************\n\n" << std::endl;
            this->afficherPlateau();
            m_J1->jouer();
            std::cout << "\n\n************************* AFFICHAGE DU PLATEAU AVANT LES PHASES DU JOUEUR 2 ****************************\n\n" << std::endl;
            this->afficherPlateau();
            m_J2->jouer();
            nombreTour++;
        }
        if(Plateau::partieCharge && joueurActuelle==0){
            this->afficherPlateau();
            m_J1->creationUnite();
            partieCharge = false;
            this->afficherPlateau();
            m_J2->jouer();
        }else if(Plateau::partieCharge && joueurActuelle == (TAILLE_PLATEAU - 1)){
            m_J2->creationUnite();
            partieCharge=false;
        }
    }
    std::cout << "\n\nNombre de tour joue: " << nombreTour << std::endl;
    if(nombreTour == limite){
        std::cout << "Match null : Personne n a gagne " << std::endl;
    }else
        std::cout << "Le grand gagnant est : " << (m_J1->getPtDeVie() <=0 ? " J2 " : " J1") << std::endl;
}

bool Plateau::deplacerUnite(int position, int deplacement) {
    if(position < 0 || position >= getTaille() || m_cases[position] == nullptr)
        return false;
    int i = position;
    if(deplacement < 0) {
        while(deplacement < 0 && (i-1) != 0 && m_cases[i-1] == nullptr) {
            m_cases[i-1] = m_cases[i];
            m_cases[i] = nullptr;
            i = i - 1;
            deplacement++;
        }
        m_cases[i]->setPosition(i);
        return true;
    }
    else if(deplacement > 0) {
        while(deplacement > 0 && (i+1) != (getTaille()-1) && m_cases[i+1] == nullptr) {
            m_cases[i+1] = m_cases[i];
            m_cases[i] = nullptr;
            i = i + 1;
            deplacement--;
        }
        m_cases[i]->setPosition(i);
        return true;
    }
    return false;
}

// Permet a un joueur de creer une unite sur le plateau dans sa base
bool Plateau::creerUnite(Unite* unite, int position) {
	if((position != 0 && position != (getTaille() - 1)) || (position == (getTaille() - 1) && unite->getJoueur()->getBase() != (getTaille() - 1))
        || (position == 0 && unite->getJoueur()->getBase() != 0)
        || unite == nullptr || m_cases[position] != nullptr){
		//unite->afficher();
		return false;
	}
	if(position == (getTaille() - 1)){
        if(m_J2->enleverArgent(unite->getPrix())==false){
            return false;
        }
    }else if(position == 0){
        if(m_J1->enleverArgent(unite->getPrix())==false)
            return false;
    }
    if(jeuContrejoueur)
        std::cout << " Joueur " << ((unite->getJoueur()->getBase() == 0)? "Joueur 1":"Joueur 2") << " cree un(e)" << unite->typeUnite() << std::endl;
	else
        std::cout << ((unite->getJoueur()->getBase() == 0)? "Joueur 1":"IA") << " cree un(e)" << unite->typeUnite() << std::endl;
	m_cases[position] = unite;
	return true;
}

bool Plateau::detruireUnite(int position) {
	if(position < 0 || position >= getTaille())
		return false;
    delete m_cases[position];
	m_cases[position] = nullptr;
	return true;
}

bool Plateau::faireEvoluerUnite(Unite* unite) {
    if(!(unite->peutEvoluer()) || unite == nullptr)
        return false;

    Unite* nouvelleUnite = unite->evolution();
    if(nouvelleUnite == nullptr)
        return false;

    int position = unite->getPosition();
    delete unite;
    m_cases[position] = nouvelleUnite;
    nouvelleUnite->setPosition(position);
    return true;
}

// ******************** GETTER ET SETTER *******************

Unite* Plateau::getCase(int i) const {
    if(i >= 0 && i < getTaille() && m_cases[i]!=nullptr){
        return m_cases[i];
    }
    return nullptr;
}

const std::array<Unite*, Plateau::TAILLE_PLATEAU>& Plateau::getCases() const {
    return m_cases;
}

int Plateau::getTaille() const {return m_cases.size();}

Joueur* Plateau::getJ1() const{
    return m_J1;
}

Joueur* Plateau::getJ2() const{
    return m_J2;
}
void Plateau::setJ1(Joueur* j){
    m_J1=j;
}

void Plateau::setJ2(Joueur* j){
    m_J2=j;
}
