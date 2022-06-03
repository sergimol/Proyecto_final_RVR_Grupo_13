#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <cstring>
#include "Serializable.h"

class Game;
class Carta;

const static int MAX_NAME = 80;

class PlayerMessage : public Serializable {
public:
    static const size_t MESSAGE_SIZE = sizeof(uint8_t) + MAX_NAME * sizeof(char);

    enum MessageType
    {
        LOGIN = 0,
        LOGOUT = 1,
        ACCEPT = 2
    };

    PlayerMessage(){};

    PlayerMessage(const char * n) {
        strncpy(nombre, n, MAX_NAME);
    };

    ~PlayerMessage(){};

    uint8_t type;

    char nombre[MAX_NAME];

    void to_bin() override;

    int from_bin(char * dt) override;
};

class Player {
public:
    Player(int n, Game* j, const char * no) : numero(n), juego(j) {
        strncpy(nombre, no, MAX_NAME);
    };
    ~Player(){};

    void setTurno(bool t);

    bool getTurno();

    bool procesaTurno();

    bool procesaTurnoMensaje(bool sigue, int p);

    void reset(int ganador);

    bool sigueJugando();

    int getPuntos();

    void setPlantado(bool p);
    
    inline int getVictorias(){return victorias;};
    char * getNombre(){return nombre;};

    void render();
    
    void setName(const char * no);
private:
    Game* juego;
    int numero;
    bool plantado = false;
    bool enTurno = false;
    std::vector<Carta*> mano;
    int puntos = 0;
    int victorias = 0;
    char nombre[MAX_NAME];
    

    void pideCarta();
    void colocaCartas(Carta* nuevaCarta);
};

#endif    