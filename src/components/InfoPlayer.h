
#pragma once
#include <array>
#include <vector>
#include <stack>
#include <string>

#include "../ecs/Component.h"
#include "../ecs/ecs.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"


class Transform;
class Carta;
using namespace std;


//MANEJA LOS ESTADOS DEL JUEGO
class InfoPlayer : public Component {
public:


	InfoPlayer() 
	{
	}

	virtual ~InfoPlayer() {
	}

	//POR DEFECTO A NEWGAME
	void init() override {
	}

	void update() override 
	{

		if(tuTurno && ih().keyDownEvent())
		{
			
		}

	}

	void render() override 
	{
		
	}

	void robarCarta()
	{
		// Llamar al GM y robar carta

	}
	


private:

	const int NUM_CARTAS = 52;
	const int NUM_PALOS = 4;
	//vector<Entity*> mano;
	bool tuTurno = false;
	int puntos;

	
};

