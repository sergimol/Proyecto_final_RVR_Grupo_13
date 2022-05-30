#ifndef CARTA_H
#define CARTA_H
#pragma once

#include "utils/Vector2D.h"
#include "SDL2/SDL.h"

class Texture;
enum Palo
{
	CORAZONES, PICAS, DIAMANTES, TREBOLES
};

struct miTransform
{
	Vector2D pos;
	Vector2D scale;
	float rot;
};


class Carta {
public:

	Carta(Palo p, int v);
	Carta(Palo p, int v, Texture* mt, Texture* rt, Vector2D ps, Vector2D sc, float r);
	~Carta(){};

	void render();

	inline Palo getPalo(){return palo;};
	inline int getValor(){return valor;};

private:
	Palo palo;
	int valor;
	miTransform tr;
	bool seMuestra = true; 
	bool visible = true;

	// Para la imagen
	Texture* muestraTex; 
	Texture* ocultaTex;
	SDL_Rect muestraSrc;
	SDL_Rect ocultaSrc;
	SDL_Texture *texture_;

	int fils = 4;	
    int cols = 15;

	Vector2D calculaCasillaTextura();

};

#endif