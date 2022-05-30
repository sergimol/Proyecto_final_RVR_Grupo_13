#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>


class Game;
class Carta;

class Player {
public:
    Player(int n, Game* j, std::string no) : numero(n), juego(j), nombre(no) {};

    void setTurno(bool t);

    bool getTurno();

    bool procesaTurno();

    void reset(int ganador);

    bool sigueJugando();

    int getPuntos();

    inline int getVictorias(){return victorias;};
    inline std::string getNombre(){return nombre;};

    void render();
    
private:
    Game* juego;
    int numero;
    bool plantado = false;
    bool enTurno = false;
    std::vector<Carta*> mano;
    int puntos = 0;
    int victorias = 0;
    std::string nombre;
    

    void pideCarta();
    void colocaCartas(Carta* nuevaCarta);
};

#endif    