// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <array>
#include <vector>
#include <stack>
#include <string>

#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

class Transform;
using namespace std;

enum Palo
{
	DIAMANTES, CORAZONES, TREBOLES, PICAS
};
struct Carta
{
	Palo palo;
	int num;
	bool descubierta;
};

//MANEJA LOS ESTADOS DEL JUEGO
class GameManager : public Component {
public:


	GameManager() 
	{
	}

	virtual ~GameManager() {
	}

	//POR DEFECTO A NEWGAME
	void init() override {
		generaBaraja();
	}

	void update() override {
		
	}

	//DEPENDIENDO DEL ESTADO SE MUESTRA UN MENSAJE U OTRO EN PANTALLA
	void render() override {
		
	}

	// Genera un nuevo mazo barajado
	void generaBaraja()
	{
		// Creamos la baraja en un vector
		vector<Carta> barajaAux;

		// 52 CARTAS
		// Por palo
		for (int i = 0; i < NUM_PALOS; i++)
		{
			Carta nuevaCarta;
			nuevaCarta.palo = Palo(i);

			// Por numero
			for (int j = 1; j <= NUM_CARTAS/NUM_PALOS; j++)
			{
				nuevaCarta.num = j;
				nuevaCarta.descubierta = false;

				// A�adimos la carta a la baraja auxiliar
				barajaAux.push_back(nuevaCarta);
			}
		}

		// Barajamos las cartas en el mazo de verdad
		int indicesRestantes = NUM_CARTAS;
		while (indicesRestantes > 0)
		{
			// Elegimos un indice aleatorio
			int indiceRandom = sdlutils().rand().nextInt(0, indicesRestantes);

			// Anadimos la carta a la baraja buena
			baraja.push(barajaAux[indiceRandom]);

			// Eliminamos la carta de la baraja auxiliar y restamos los indices
			auto carta = barajaAux.begin() + indiceRandom;
			barajaAux.erase(carta);
			indicesRestantes--;
		}

		// Debug
		if (debug)
		{
			for (int i = 0; i < NUM_CARTAS; i++)
			{
				string p;
				switch (baraja.top().palo)
				{
				case DIAMANTES:
					p = "D";
					break;
				case CORAZONES:
					p = "C";
					break;
				case TREBOLES:
					p = "T";
					break;
				case PICAS:
					p = "P";
					break;
				}
				cout << p << " " << baraja.top().num << "\n";

				baraja.pop();
			}
		}
	}

	// Vacia la baraja para una nueva partida o lo quesea
	void limpiarBaraja()
	{
		while(!baraja.empty())
			baraja.pop();
	}

	// Devuelve al jugador que lo pida, la siguiente carta del mazo
	Carta getCarta()
	{
		Carta c = baraja.top();
		baraja.pop();
		return c;
	}

private:

	const int NUM_CARTAS = 52;
	const int NUM_PALOS = 4;
	stack<Carta> baraja;
	bool debug = false;

	
};

