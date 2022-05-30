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
    pideCarta();
    pideCarta();
    enTurno = true;
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
    Carta nueva = juego->getCarta();
    Texture* carbalo = &sdlutils().images().at("setCartas");
    Carta* nuevaFina = new Carta(nueva.getPalo(), nueva.getValor(),
                            carbalo, carbalo,
                            Vector2D(sdlutils().width()/2, sdlutils().height()/2),
                            Vector2D(100.0f,150.0f), 0);

    int valor = nueva.getValor();
    if(valor > 10) valor = 10;
    puntos += valor;
    mano.push_back(nuevaFina);

    enTurno = false;

    if(puntos >= 21)
        plantado = true;

    std::cout << numero << " " << puntos << std::endl;
}


bool Player::sigueJugando() { return !plantado; }

int Player::getPuntos() { return puntos; }

void Player::setTurno(bool t) { enTurno = t;}

bool Player::getTurno() { return enTurno; };
