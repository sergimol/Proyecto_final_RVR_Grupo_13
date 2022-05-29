#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "Game.h"

#include "ecs/ecs.h"
#include "ecs/Entity.h"
#include "ecs/Manager.h"
#include "sdlutils/InputHandler.h"
#include "sdlutils/SDLUtils.h"
#include "components/Carta.h"

#include <vector>

Game::Game()
{
    mngr_.reset(new Manager());
}

Game::~Game(){
 
    SDL_Quit();
}

void Game::init(int w, int h)
{
    SDLUtils::init("Jacobo Negro", 800, 600,
    "resources/config/resources.json");

    generaBaraja();    
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

        mngr_->update();
        mngr_->refresh();

        sdlutils().clearRenderer();
        mngr_->render();
        sdlutils().presentRenderer();

        Uint32 frameTime = sdlutils().currRealTime() - startTime;

        if(frameTime < 20)
            SDL_Delay(20 - frameTime);
    }
}

Carta Game::getCarta()
{
    Carta c = baraja.top();
    baraja.pop();
    return c;
}

void Game::limpiarBaraja()
{
    while(!baraja.empty())
        baraja.pop();
}

void Game::generaBaraja()
{
    // Creamos la baraja en un vector
    vector<Carta> barajaAux;

    // 52 CARTAS
    // Por palo
    for (int i = 0; i < NUM_PALOS; i++)
    {
        // Por numero
        for (int j = 1; j <= NUM_CARTAS/NUM_PALOS; j++)
        {
            Carta nuevaCarta(Palo(i), j);

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



