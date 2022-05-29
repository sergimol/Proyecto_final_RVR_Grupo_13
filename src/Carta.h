#ifndef CARTA_H
#define CARTA_H

#include "sdlutils/SDLUtils.h"
#include "sdlutils/Texture.h"
#include "utils/Vector2D.h"

enum Palo
{
	CORAZONES, PICAS, DIAMANTES, TREBOLES
};

struct miTransform{
	Vector2D pos;
	Vector2D scale;
	float rot;
};


class Carta {

public:

	Carta(Palo p, int v)
	{
		palo = p;
		valor = v;
	}
	Carta(Palo p, int v, Texture* mt, Texture* rt, Vector2D ps, Vector2D sc, float r)
	{
		palo = p;
		valor = v;
		muestraTex = mt;
		ocultaTex = rt;

		tr.pos = ps;
		tr.scale = sc;
		tr.rot = r;

		auto w = muestraTex->width() / cols;
		auto h = muestraTex->height() / fils;

		// Calcular la posicion de la textua
		Vector2D casilla = calculaCasillaTextura();
		muestraSrc = { w * int(casilla.getX()), h * int(casilla.getY()), w, h };
		ocultaSrc = { 0, 0, w, h };


	}

	void render()
	{
		if(visible)
		{
			if(seMuestra)
			{
				SDL_Rect dest = build_sdlrect(tr.pos, tr.scale.getX(), tr.scale.getY());
				muestraTex->render(muestraSrc, dest, tr.rot);
			}
			else
			{
				SDL_Rect dest = build_sdlrect(tr.pos, tr.scale.getX(), tr.scale.getY());
				ocultaTex->render(ocultaSrc, dest, tr.rot);
			}
		}
		
	}

	Palo getPalo() { return palo; }
	int getValor() { return valor; }

private:
	Palo palo;
	int valor;
	miTransform tr;
	bool seMuestra = false; 
	bool visible = true;

	// Para la imagen
	Texture* muestraTex; 
	Texture* ocultaTex;
	SDL_Rect muestraSrc;
	SDL_Rect ocultaSrc;

	int fils = 4;
    int cols = 15;

	Vector2D calculaCasillaTextura()
	{
		int x = 0;

		int y = 0;

		y = int(palo);

		if(valor == 1)
			x = 13;
		else
			x = valor - 1;

		return Vector2D(x,y);
	} 

};

#endif