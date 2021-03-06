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
	Carta(Palo p, int v, Texture* mt, Texture* rt, Vector2D ps, Vector2D sc, float r, bool vi);
	~Carta(){};

	void render();

	// GETTERS
	inline Palo getPalo(){return palo;};
	inline int getValor(){return valor;};
	inline miTransform getTransform(){return tr;};

	// SETTERS
	inline void setPos(Vector2D newPos){tr.pos = newPos;};
	inline void setScale(Vector2D newSc){tr.scale = newSc;};
	inline void setPos(float newRot){tr.rot = newRot;};
	inline void setVisible(bool v){visible = v;};
	inline void setMuestra(bool m){seMuestra = m;};

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