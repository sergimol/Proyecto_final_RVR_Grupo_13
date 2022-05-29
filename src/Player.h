#ifndef PLAYER_H
#define PLAYER_H

#include "ecs/Component.h"
#include "components/Carta.h"
#include "Game.h"

class Player : public Component {
public:
    Player(int n, Game* j) : numero(n), juego(j) {};

private:
    Game* juego;
    int numero;
    bool plantado = false;
    std::vector<Carta> mano;
    int puntos = 0;
    int victorias = 0;

    void PideCarta(){
        Carta nueva = juego->getCarta();

        puntos += nueva.getValor();

        if(puntos != 21)
            mano.push_back(nueva);
    }

    void Reset(int ganador){
        mano.clear();
        puntos = 0;
        plantado = false;
        if(ganador == numero)
            victorias++;
    }
};

#endif