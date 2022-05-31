#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <cstring>
#include "Serializable.h"

class Game;
class Carta;

class Player {
public:
    const static size_t MAX_NAME = 80;

    Player(int n, Game* j, const char * no) : numero(n), juego(j) {
        strncpy(nombre, no, MAX_NAME);
    };

    Player(int n, Game* j, PlayerMessage msg) : numero(n), juego(j) {
        strncpy(nombre, msg.nombre.c_str(), MAX_NAME);
    };

    void setTurno(bool t);

    bool getTurno();

    bool procesaTurno();

    void reset(int ganador);

    bool sigueJugando();

    int getPuntos();

    inline int getVictorias(){return victorias;};
    char * getNombre(){return nombre;};

    void render();
    
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

class PlayerMessage : public Serializable {
public:
    static const size_t MESSAGE_SIZE = sizeof(char) * Player::MAX_NAME + sizeof(uint8_t);

    enum MessageType
    {
        LOGIN = 0,
        LOGOUT = 1
    };

    PlayerMessage(){};

    PlayerMessage(const std::string& n) : nombre(n){};

    uint8_t type;

    std::string nombre;

    void to_bin() override;

    int from_bin(char * dt) override;
};

#endif    