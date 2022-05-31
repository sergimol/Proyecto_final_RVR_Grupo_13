#include "Player.h"
#include "Game.h"
#include "Carta.h"
#include "sdlutils/InputHandler.h"
#include <vector>
#include "sdlutils/SDLUtils.h"

using namespace std;

bool Player::procesaTurno()
{
    if(ih().getKeyDown(SDL_SCANCODE_SPACE))
    {
        pideCarta();
        //std::cout << "nova";
    }
    else if(ih().getKeyDown(SDL_SCANCODE_R))
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
    // SI ES JUGADOR 2
    else
    {
        // Colocamos la carta actual en el medio
        nuevaCarta->setPos(Vector2D(sdlutils().width()/2 - nuevaCarta->getTransform().scale.getX()/2,
                           sdlutils().height()/2 - (sdlutils().height()/2)/2 - nuevaCarta->getTransform().scale.getY()/2));
        // La hacemos inivisible
        nuevaCarta->setMuestra(false);

        //Desplazamos el vector de cartas a la izquierda
        for(Carta* c : mano)
        {
            c->setPos(Vector2D(c->getTransform().pos.getX() - 100,  c->getTransform().pos.getY()));

            // Las hacemos visibles
            c->setMuestra(true);
        }
    }
}

bool Player::sigueJugando() { return !plantado; }

int Player::getPuntos() { return puntos; }

void Player::setTurno(bool t) { enTurno = t;}

bool Player::getTurno() { return enTurno; };

void PlayerMessage::to_bin()
{
    alloc_data(MESSAGE_SIZE);
    
    memset(_data, 0, MESSAGE_SIZE);

    char* buffer = _data;
    memcpy(buffer, &type, sizeof(uint8_t));
    buffer += sizeof(uint8_t);
    nombre[nombre.size() + 1] = '\0';
    memcpy(buffer, nombre.c_str(), Player::MAX_NAME * sizeof(char));
}

int PlayerMessage::from_bin(char * dt)
{
    alloc_data(MESSAGE_SIZE);

    memcpy(static_cast<void *>(_data), dt, MESSAGE_SIZE);

    char * buffer = _data;
    memcpy(&type, buffer, sizeof(uint8_t));
    buffer += sizeof(uint8_t);
    memcpy(&nombre[0], buffer, Player::MAX_NAME * sizeof(char));
    return 0;
}
