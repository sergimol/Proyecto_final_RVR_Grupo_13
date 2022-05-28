#ifndef CARTA_H
#define CARTA_H

#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

enum Palo
{
	DIAMANTES, CORAZONES, TREBOLES, PICAS
};

class Carta : public Component {

public:
	Carta(Palo p, int v){
		palo = p;
		valor = v;
	};

	Palo getPalo() { return palo; };
	int getValor() { return valor; };

private:
	Palo palo;
	int valor;
};

#endif