#ifndef PLAYER_H
#define PLAYER_H

#include <vector>


class Game;
class Carta;

class Player {
public:
    Player(int n, Game* j) : numero(n), juego(j) {};

    void setTurno(bool t);

    bool getTurno();

    bool procesaTurno();

    void reset(int ganador);

    bool sigueJugando();

    int getPuntos();

    void render();
    
private:
    Game* juego;
    int numero;
    bool plantado = false;
    bool enTurno = false;
    std::vector<Carta*> mano;
    int puntos = 0;
    int victorias = 0;
    

    void pideCarta();
    void colocaCartas(Carta* nuevaCarta);
};

#endif    