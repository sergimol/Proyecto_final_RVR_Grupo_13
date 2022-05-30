#include "Player.h"
#include "Game.h"
#include "Carta.h"
#include "sdlutils/InputHandler.h"
#include <vector>
#include "sdlutils/SDLUtils.h"



bool Player::procesaTurno()
{
    if(ih().isKeyDown(SDLK_SPACE))
    {
        pideCarta();
        std::cout << "nova";
    }
    else if(ih().isKeyDown(SDLK_r))
    {
        plantado = true;
        enTurno = false;
    }

    return enTurno;
}

void Player::reset(int ganador)
{
    mano.clear();
    puntos = 0;
    plantado = false;
    if(ganador == numero)
        victorias++;
}

void Player::render()
{
    for(Carta* c : mano)
    {
        c->render();
    }
}


void Player::pideCarta()
{
    Carta* nueva = juego->getCarta();

    puntos += nueva->getValor();
    mano.push_back(nueva);

    enTurno = false;

    if(puntos >= 21)
        plantado = true;
}


bool Player::sigueJugando() { return !plantado; }

int Player::getPuntos() { return puntos; }

void Player::setTurno(bool t) { enTurno = t;}

bool Player::getTurno() { return enTurno; };
