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
        //std::cout << "nova";
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
    Carta* nueva = juego->getCarta();
    colocaCartas(nueva);

    int valor = nueva->getValor();
    if(valor > 10) valor = 10;
    puntos += valor;
    mano.push_back(nueva);

    enTurno = false;

    if(puntos >= 21)
        plantado = true;

}

void Player::colocaCartas(Carta* nuevaCarta)
{
    // SI ES JUGADOR 1
    if(numero == 1)
    {
        // Colocamos la carta actual en el medio
        nuevaCarta->setPos(Vector2D(sdlutils().width()/2 - nuevaCarta->getTransform().scale.getX()/2,
                           sdlutils().height()/2 + (sdlutils().height()/2)/2 - nuevaCarta->getTransform().scale.getY()/2));


        //Desplazamos el vector de cartas a la izquierda
        for(Carta* c : mano)
        {
            c->setPos(Vector2D(c->getTransform().pos.getX() - 100,  c->getTransform().pos.getY()));
        }
    }
    else
    {
        // Colocamos la carta actual en el medio
        nuevaCarta->setPos(Vector2D(sdlutils().width()/2 - nuevaCarta->getTransform().scale.getX()/2,
                           sdlutils().height()/2 - (sdlutils().height()/2)/2 - nuevaCarta->getTransform().scale.getY()/2));

        //Desplazamos el vector de cartas a la izquierda
        for(Carta* c : mano)
        {
            c->setPos(Vector2D(c->getTransform().pos.getX() - 100,  c->getTransform().pos.getY()));
        }
    }
}


bool Player::sigueJugando() { return !plantado; }

int Player::getPuntos() { return puntos; }

void Player::setTurno(bool t) { enTurno = t;}

bool Player::getTurno() { return enTurno; };
