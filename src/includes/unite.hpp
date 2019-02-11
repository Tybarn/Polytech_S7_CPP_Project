#ifndef UNITE_HPP_
#define UNITE_HPP_

#include <vector>
#include <string>
#include "joueur.hpp"
#include "plateau.hpp"

class Joueur;
class Plateau;

class Unite {
private:

protected:
    //ATTRIBUT
	int m_prix, m_ptsDeVie, m_ptsAttaque, m_position;
	Joueur* m_joueur;
    bool m_veutEvoluer;
    //FONCTION ABSTRAITE
    virtual int ennemiAPorte()=0;

public:
    //CONSTRUCTEUR ET DESTRUCTEUR
    Unite();
    Unite(Joueur* j);
    virtual ~Unite();
    //FONCTION CONCRETE
    void avancer();
    bool attaquer(int posCible);
    virtual bool peutEvoluer() {return false;}
    virtual Unite* evolution() {return nullptr;}
    //FONCTION ABSTRAITE
    virtual void afficher()=0; // virtuel pure, je force la redefinition dans la classe fille
	virtual void action1()=0;
	virtual void action2()=0;
	virtual void action3()=0;
	virtual std::string typeUnite()=0;
    //GETTER ET SETTER
    Joueur* getJoueur() const;
    int getPosition()const;
    bool setVie(int i);
    int getAttaque()const;
    int getPtsDeVie()const;
    int getPrix()const;
    void setPosition(int i);
    bool souhaiteEvoluer() {return m_veutEvoluer;}
    // GETTERS SPECIAUX (PAS DES ATTRIBUTS, JUSTE DES SIMPLIFICATIONS DU CODE)
    int getBase() const;
    Plateau* getPlateau() const;
};

#endif
