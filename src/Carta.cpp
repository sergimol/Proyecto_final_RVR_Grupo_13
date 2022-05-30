#include "Carta.h"
#include "sdlutils/Texture.h"
#include "sdlutils/SDLUtils.h"

Carta::Carta(Palo p, int v)
{
	palo = p;
	valor = v;
}
Carta::Carta(Palo p, int v, Texture* mt, Texture* rt, Vector2D ps, Vector2D sc, float r)
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

void Carta::render()
{
	if(visible)
	{
		if(seMuestra)
		{
			SDL_Rect dest = build_sdlrect(tr.pos, tr.scale.getX(), tr.scale.getY());
			muestraTex->render(muestraSrc, dest, tr.rot);
			//std::cout << tr.scale.getX() << " " << tr.scale.getY() << "\n";
			//std::cout << dest.x << " " << dest.y << "\n";

		}
		else
		{
			SDL_Rect dest = build_sdlrect(tr.pos, tr.scale.getX(), tr.scale.getY());
			ocultaTex->render(ocultaSrc, dest, tr.rot);
		}
	}
	
}



Vector2D Carta::calculaCasillaTextura()
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

