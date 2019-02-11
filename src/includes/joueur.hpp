#ifndef JOUEUR_HPP_
#define JOUEUR_HPP_

#include "plateau.hpp"
#include "unite.hpp"

class Plateau;
class Unite;

class Joueur {
private:
    //ATTRIBUT
    Plateau* m_plateau;
	int m_argent, m_ptDeVie, m_base;
    //FONCTION
    void creationUniteIA();
    void creerUnite(Unite *u);
    void action1();
    void action2();
    void action3();
    void addArgent(int i);

public:
    //CONSTRUCTEUR
    Joueur();
    Joueur(int newargent,int newptDeVie);
    Joueur(int argent, int ptDeVie, Plateau* plt);
    ~Joueur();
    //AFFICHAGE
    void afficherJoueur()const;
    //FONCTION
    void ajouterArgent(int i);
    bool enleverArgent(int i);
    void jouer();
    void jouerIASimple();
    void creationUnite();
    void creerSoldat();
    void creerArcher();
    void creerCatapulte();
    //GETTER ET SETTER
    int getBase()const;
    void setBase(int i);
    int getArgent()const;
    int getPtDeVie()const;
    void perdrePointDeVie(int i);
    Plateau* getPlateau()const;
    void setPlateau(Plateau* plt);
};

#endif


