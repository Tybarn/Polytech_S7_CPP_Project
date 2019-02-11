#ifndef SUPERSOLDAT_HPP_
#define SUPERSOLDAT_HPP_

#include <string>
#include "unite.hpp"
#include "soldat.hpp"
#include "joueur.hpp"

class Unite;

class SuperSoldat : public Soldat {
public:
	// CONSTRUCTEUR ET DESTRUCTEUR
	SuperSoldat();
	SuperSoldat(Soldat s);
	~SuperSoldat();
	// FONCTION
	void afficher();
	Unite* evolution() {return nullptr;}
	void action3();
	std::string typeUnite();
};

#endif