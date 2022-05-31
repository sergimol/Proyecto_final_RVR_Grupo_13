#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "sdlutils/InputHandler.h"
#include "sdlutils/Texture.h"
#include "sdlutils/SDLUtils.h"
#include "Carta.h"
#include "Player.h"
#include "Fondo.h"
#include "UI.h"

#include <vector>

Game::Game(char * dir, char * port, char * host) : socket(dir, port)
{
    state_ = NEWGAME;
    if(host[0] == '1'){
        eresHost = true;
    }
}

Game::~Game(){
 
    SDL_Quit();
}

void Game::init(int w, int h)
{
    // PREGUNTAR AL JUGADOR POR EL NOMBRE
    std::cout << "INTRODUCE TU NOMBRE: ";
    std::cin >> nombre;

    // INICIAMOS LA VENTANA DE SDL
    SDLUtils::init("Jacobo Negro", 800, 600,
    "resources/config/resources.json");

    if(eresHost){
        createServer();
    }

    // CREAMOS LOS OBJETOS DE LA ESCENA
    cartaTexture = &sdlutils().images().at("setCartas");
    fondo = new Fondo(&sdlutils().images().at("tapete"), cartaTexture, this);
    player1 = new Player(1, this, nombre);

    ui = new UI(this);
}

void Game::start()
{
    bool exit = false;
    SDL_Event event;

    while(!exit)
    {
        Uint32 startTime = sdlutils().currRealTime();

        ih().clearState();
        while(SDL_PollEvent(&event))
            ih().update(event);

        if(ih().isKeyDown(SDL_SCANCODE_ESCAPE))
        {
            exit = true;
            continue;
        }

        // UPDATE DE LAS COSAS
        update();

        sdlutils().clearRenderer();        
        // RENDER DE LAS COSAS
        render();
        //mngr_->render();
        sdlutils().presentRenderer();

        Uint32 frameTime = sdlutils().currRealTime() - startTime;

        if(frameTime < 20)
            SDL_Delay(20 - frameTime);
    }
}

void Game::update()
{
    switch (state_)
    {
    case NEWGAME:
        if(eresHost)
        {
            createGame();
            sendHostInfo();
        }
        else {
            joinGame();
        }
        break;
    case WAITINGFORHOST:
        receiveHostInfo();
        break;
    case ROUNDEND:
        if(ih().getKeyDown(SDL_SCANCODE_RETURN))
            inicioDePartida();
        break;
    case PLAYING:
        // TURNOS
        // JUGADOR 1
        if(player1->sigueJugando() && player1->getTurno())
        {
            if(!player1->procesaTurno()){
                player1->setTurno(!player2->sigueJugando());
                player2->setTurno(player2->sigueJugando() && player1->getPuntos() <= 21);
            }        
        }
        // JUGADOR 2
        else if(player2->sigueJugando() && player2->getTurno())
        {
            if(!player2->procesaTurno()){
                player1->setTurno(player1->sigueJugando() && player2->getPuntos() <= 21);
                player2->setTurno(!player1->sigueJugando());
            }
        }
        else 
            finDePartida();
            break;
    
    default:
        break;
    }
    
}

void Game::inicioDePartida()
{
    limpiarBaraja();
    generaBaraja();

    player1->reset(ultimoGanador_);
    player2->reset(ultimoGanador_);

    state_ = PLAYING;
}

void Game::finDePartida()
{
    int puntos1 = player1->getPuntos();
    int puntos2 = player2->getPuntos();

    if((puntos1 > puntos2 && puntos1 <= 21) || puntos2 > 21)
        ultimoGanador_ = 1;
    else if((puntos2 > puntos1 && puntos2 <= 21) || puntos1 > 21)
        ultimoGanador_ = 2;
    else
        ultimoGanador_ = 0;

    state_ = ROUNDEND;
}

void Game::render()
{
    //carta->render();
    fondo->render();
    player1->render();
    player2->render();
    ui->render();
}

Carta* Game::getCarta()
{
    //std::cout <<  "bro?";
    if(!baraja.empty())
    {
        Carta* c = baraja.top();
        baraja.pop();
        return c;
    }
    else
        return nullptr;
}

void Game::limpiarBaraja()
{
    while(!baraja.empty())
        baraja.pop();
}

void Game::generaBaraja()
{
    // Creamos la baraja en un vector
    vector<Carta*> barajaAux;

    // 52 CARTAS
    // Por palo
    for (int i = 0; i < NUM_PALOS; i++)
    {
        // Por numero
        for (int j = 1; j <= NUM_CARTAS/NUM_PALOS; j++)
        {
            //Carta nuevaCarta(Palo(i), j);
            Carta* nuevaCarta = new Carta(Palo(i), j,
                            cartaTexture, cartaTexture,
                            Vector2D(sdlutils().width()/2, sdlutils().height()/2),
                            Vector2D(100.0f,150.0f),
                            0,
                            false);

            // Añadimos la carta a la baraja auxiliar
            barajaAux.push_back(nuevaCarta);
        }
    }

    // Barajamos las cartas en el mazo de verdad
    int indicesRestantes = NUM_CARTAS;
    while (indicesRestantes > 0)
    {
        // Elegimos un indice aleatorio
        int indiceRandom = sdlutils().rand().nextInt(0, indicesRestantes);

        // Anadimos la carta a la baraja buena
        baraja.push(barajaAux[indiceRandom]);

        // Eliminamos la carta de la baraja auxiliar y restamos los indices
        auto carta = barajaAux.begin() + indiceRandom;
        barajaAux.erase(carta);
        indicesRestantes--;
    }
}

void Game::createServer()
{
    socket.bind();

    state_ = NEWGAME;
}

void Game::createGame()
{
    // Recibe la info del cliente
    PlayerMessage msg;
    Socket* client;
    if(socket.recv(msg, client) == 0 && msg.type == PlayerMessage::LOGIN){
        std::cout << msg.nombre.c_str() << " se ha conectado.\n"; 
        player2 = new Player(2, this, msg);
        // Crea la partida
        inicioDePartida();
    }
}

void Game::sendHostInfo()
{
    if(player2 != nullptr){
        // Manda la información de su jugador al cliente
        PlayerMessage msg(nombre);
        msg.type = PlayerMessage::ACCEPT;
        socket.send(msg, socket);
    }
}

void Game::joinGame() 
{
    PlayerMessage msg(nombre);
    msg.type = PlayerMessage::LOGIN;
    socket.send(msg, socket);
    state_ = WAITINGFORHOST;
}

void Game::logOutGame() 
{
    PlayerMessage msg;
    msg.type = PlayerMessage::LOGOUT;
    socket.send(msg, socket);
}

void Game::receiveHostInfo()
{
    // Recibe la info del cliente
    PlayerMessage msg;
    Socket* host;
    if(socket.recv(msg, host) == 0 && msg.type == PlayerMessage::ACCEPT){
        player2 = new Player(2, this, msg);
        std::cout << "Te has conectado a " << msg.nombre << "\n"; 
        // Crea la partida
        inicioDePartida();
    }
}

Uint8 Game::getState()
{
    return state_;
}

int Game::getGanador()
{
    return ultimoGanador_;
}