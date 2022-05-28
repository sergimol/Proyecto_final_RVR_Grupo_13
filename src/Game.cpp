#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "Game.h"

#include "ecs/ecs.h"
#include "ecs/Entity.h"
#include "ecs/Manager.h"
#include "sdlutils/InputHandler.h"
#include "sdlutils/SDLUtils.h"
#include "components/GameManager.h"

Game::Game()
{
    mngr_->reset(new Manager());
}

Game::~Game(){
 
    SDL_Quit();
}

void Game::init(int w, int h)
{
    SDLUtils::init("Jacobo Negro", 800, 600,
    "resources/config/resources.json");

    // Creamos un gamemanager
    auto* gameManager = mngr_->addEntity();
    gameManager->addComponent<Transform>(
        Vector2D(sdlutils().width()/2, sdlutils().height()/2), // POS
        Vector2D(), // VEL
        1.0f, 1.0f, // SCALE
        0.0f // ROT 
    );
    gameManager->addComponent<GameManager>();
    
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



