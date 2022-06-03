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


    if(eresHost)
    {
        createServer();
    }


    // CREAMOS LOS OBJETOS DE LA ESCENA
    cartaTexture = &sdlutils().images().at("setCartas");
    fondo = new Fondo(&sdlutils().images().at("tapete"), cartaTexture, this);
    if(eresHost){
        player1 = new Player(1, this, nombre);
        player2 = new Player(2, this, "Esperando");
    }
    else{
        player2 = new Player(2, this, nombre);
        player1 = new Player(1, this, "Esperando");
    }

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

          
        // RENDER DE LAS COSAS
        sdlutils().clearRenderer();      
        render();
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
            std::cout << "2. SOY HOST VOY A CREAR TO.\n";
            createGame();
            //sendHostInfo();
        }
        else 
        {
            std::cout << "4. SOY CLIENTE ME VOY A CONECTAR.\n";
            joinGame();
        }
        break;
    case WAITINGFORHOST:
        // A ESTE ESTADO SOLO LLEGA EL CLIENTE
        receiveHostInfo();
        break;
    case ROUNDEND:
        if(ih().getKeyDown(SDL_SCANCODE_RETURN) && eresHost){
            inicioDePartida();
            DeckMessage gmsg(indicesBaraja);
            gmsg.type = DeckMessage::START;
            socket.send(gmsg, *other);
        }
        else{
            DeckMessage gmsg;
            if(socket.recv(gmsg, other) == 0 && gmsg.type == DeckMessage::START){
            for(int i = 0; i < NUM_CARTAS; ++i)
                indicesBaraja.push_back(gmsg.indicesBaraja[i]);
            // Crea la partida
            inicioDePartida();
        }
        }
        break;
    case PLAYING:
        // TURNOS
        // JUGADOR 1
        if(player1->sigueJugando() && player1->getTurno())
        {
            if(eresHost){
                if(!player1->procesaTurno()){
                    player1->setTurno(!player2->sigueJugando());
                    player2->setTurno(player2->sigueJugando() && player1->getPuntos() <= 21);
                    TurnMessage tmsg(player1->sigueJugando(), player1->getPuntos());
                    socket.send(tmsg, *other);
                }            
            }
            else{
                TurnMessage tmsg;
                if(socket.recv(tmsg) != 0)
                    return;
                player1->procesaTurnoMensaje(tmsg.sigue, tmsg.puntos);
                player1->setTurno(!player2->sigueJugando());
                player2->setTurno(player2->sigueJugando() && player1->getPuntos() <= 21);                
            }

        }
        // JUGADOR 2
        else if(player2->sigueJugando() && player2->getTurno())
        {
            if(!eresHost){
                if(!player2->procesaTurno()){
                    player1->setTurno(player1->sigueJugando() && player2->getPuntos() <= 21);
                    player2->setTurno(!player1->sigueJugando());
                    TurnMessage tmsg(player2->sigueJugando(), player2->getPuntos());
                    socket.send(tmsg, *other);
                }
            }
            else{
                TurnMessage tmsg;
                if(socket.recv(tmsg) != 0)
                    return;
                player2->procesaTurnoMensaje(tmsg.sigue, tmsg.puntos);
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
    if(eresHost)
        barajeaHost();
    else
        barajeaCliente();
    
    player1->reset(ultimoGanador_);
    player2->reset(ultimoGanador_);

    state_ = PLAYING;
    std::cout << "Pasamos al estado PLAYING.\n";
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

    indicesBaraja.clear();
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
}

void Game::barajeaHost()
{
    // Barajamos las cartas en el mazo de verdad
    int indicesRestantes = NUM_CARTAS;
    while (indicesRestantes > 0)
    {
        // Elegimos un indice aleatorio
        int16_t indiceRandom = (int16_t)sdlutils().rand().nextInt(0, indicesRestantes);

        // Anadimos la carta a la baraja buena
        baraja.push(barajaAux[indiceRandom]);
        indicesBaraja.push_back(indiceRandom);
        std::cout << indiceRandom << " " << indicesBaraja[NUM_CARTAS - indicesRestantes] << std::endl;
        // Eliminamos la carta de la baraja auxiliar y restamos los indices
        auto carta = barajaAux.begin() + indiceRandom;
        barajaAux.erase(carta);
        indicesRestantes--;
    }
}

void Game::barajeaCliente()
{
    for(int i = 0; i < indicesBaraja.size(); ++i)
    {
        // Anadimos la carta a la baraja buena
        baraja.push(barajaAux[indicesBaraja[i]]);

        // Eliminamos la carta de la baraja auxiliar
        auto carta = barajaAux.begin() + indicesBaraja[i];
        barajaAux.erase(carta);
    }
}

void Game::createServer()
{
    // Enlazamos el socket a puerto y direccion
    socket.bind();

    state_ = NEWGAME;

    std::cout << "1. Creaste el server.\n";

}

void Game::createGame()
{
    std::cout << "3. Esperando que se conecte el cliente.\n"; 

    // Recibe la info del cliente
    PlayerMessage msg;
    Socket* clnt = new Socket(socket);

    // AQUI SE QUEDA BLOQUEADA LA APP DEL HOST HASTA QUE LLEGA EL MENSAJE DE LOGIN
    if(socket.recv(msg, clnt)==0)
    {
        if(msg.type == PlayerMessage::LOGIN)
            std::cout << "Recibidio mensaje de LOGIN \n";     

    }

    if(msg.type == PlayerMessage::LOGIN)
    {
        std::cout << "7. " << msg.nombre << " ha solicitado conectarse.\n"; 
        std::cout << "Fuera: " << *clnt << std::endl;
        other = clnt;
        player2->setName(msg.nombre);
        // Crea la partida
        std::cout << "8. El host inicializa su juego.\n";
        inicioDePartida();
        conectado = true;

        // LE DECIMOS AL CLIENTE QUE HEMOS ACEPTADO SU PETICION
        PlayerMessage msg(nombre);
        msg.type = PlayerMessage::ACCEPT; // Aceptamos la solicitud del cliente para conectarse
        socket.send(msg, *clnt);

        DeckMessage gmsg(indicesBaraja);
        gmsg.type = DeckMessage::START;
        socket.send(gmsg, *clnt);
    }
}

void Game::joinGame() 
{
    PlayerMessage msg(nombre);
    msg.type = PlayerMessage::LOGIN;
    socket.send(msg, socket);
    std::cout << "5. Soy "<< nombre << " me quiero conectar.\n";
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
    std::cout << "6. Esperando confirmacion del host.\n";
    PlayerMessage msg;
    Socket* host;
    
    if(socket.recv(msg, host) == 0 && msg.type == PlayerMessage::ACCEPT)
    {
        std::cout << "8. Llega la confirmacion del host: inicilizando partida del cliente.\n";
        other = host;
        player1->setName(msg.nombre);
        DeckMessage gmsg;
        if(socket.recv(gmsg, host) == 0 && gmsg.type == DeckMessage::START){
            std::cout << "9. Te has conectado a " << msg.nombre << "\n";
            for(int i = 0; i < NUM_CARTAS; ++i)
                indicesBaraja.push_back(gmsg.indicesBaraja[i]);
            // Crea la partida
            inicioDePartida();
        }
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

void DeckMessage::to_bin()
{
    alloc_data(MESSAGE_SIZE);

    memset(_data, 0, MESSAGE_SIZE);
    
    char* buffer = _data;
    memcpy(buffer, &type, sizeof(uint8_t));
    buffer += sizeof(uint8_t);

    for(int i = 0; i < NUM_CARTAS; ++i){
        memcpy(buffer, &indicesBaraja[i], sizeof(int16_t));
        buffer += sizeof(int16_t);
    }
}

int DeckMessage::from_bin(char * dt)
{
    alloc_data(MESSAGE_SIZE);
    memcpy(static_cast<void*>(_data), dt, MESSAGE_SIZE);

    char * buffer = _data;

    memcpy(&type, buffer, sizeof(uint8_t));
    buffer += sizeof(uint8_t);
    for(int i = 0; i < NUM_CARTAS; ++i){
        memcpy(&indicesBaraja[i], buffer, sizeof(int16_t));
        buffer += sizeof(int16_t);
    }
    return 0;
}

void TurnMessage::to_bin()
{
    alloc_data(MESSAGE_SIZE);

    memset(_data, 0, MESSAGE_SIZE);
    
    char* buffer = _data;
    memcpy(buffer, &sigue, sizeof(bool));
    buffer += sizeof(bool);
    
    memcpy(buffer, &puntos, sizeof(int));
}

int TurnMessage::from_bin(char * dt)
{
    alloc_data(MESSAGE_SIZE);
    memcpy(static_cast<void*>(_data), dt, MESSAGE_SIZE);

    char * buffer = _data;

    memcpy(&sigue, buffer, sizeof(bool));
    buffer += sizeof(bool);

    memcpy(&puntos, buffer, sizeof(int));
    return 0;
}