#include "UI.h"
#include "sdlutils/Texture.h"
#include "sdlutils/SDLUtils.h"
#include "utils/Vector2D.h"
#include "Game.h"
#include "Player.h"
#include "sdlutils/Font.h"


UI::UI(Game* j)
{
    /*tr.pos = Vector2D(0,0);
    tr.scale = Vector2D(sdlutils().width(), sdlutils().height());
    tr.rot = 0;*/
    juego = j;

}

void UI::render()
{
    renderPuntosActuales();
    renderVictoriasActuales();
    renderTurno();
}

void UI::renderPuntosActuales()
{
    // PUNTOS DEL PLAYER 1
    int puntos = juego->getPlayer1()->getPuntos();
    Texture puntosMensaje(
        sdlutils().renderer(),
        "PUNTOS ACTUALES:" + std::to_string(puntos),
        sdlutils().fonts().at("ARIAL24"),
        build_sdlcolor(0xffffffff)
    );
    puntosMensaje.render(sdlutils().width()/10, sdlutils().height()/10 * 9);

    // PUNTOS DEL PLAYER 2
    puntos = juego->getPlayer2()->getPuntos();
    Texture puntosMensaje2(
        sdlutils().renderer(),
        "PUNTOS ACTUALES:" + std::to_string(puntos),
        sdlutils().fonts().at("ARIAL24"),
        build_sdlcolor(0xffffffff)
    );
    puntosMensaje2.render(sdlutils().width()/10, sdlutils().height()/10 - 20);
}

void UI::renderVictoriasActuales()
{
    // VICTORIAS DEL PLAYER 1
    int victorias = juego->getPlayer1()->getVictorias();
    Texture victoriasMensaje(
        sdlutils().renderer(),
        "VICTORIAS:" + std::to_string(victorias),
        sdlutils().fonts().at("ARIAL24"),
        build_sdlcolor(0xffffffff)
    );
    victoriasMensaje.render(sdlutils().width()/2, sdlutils().height()/10 * 9);

    // VICTORIAS DEL PLAYER 2
    victorias = juego->getPlayer2()->getVictorias();
    Texture victoriasMensaje2(
        sdlutils().renderer(),
        "VICTORIAS:" + std::to_string(victorias),
        sdlutils().fonts().at("ARIAL24"),
        build_sdlcolor(0xffffffff)
    );
    victoriasMensaje2.render(sdlutils().width()/2, sdlutils().height()/10 - 20 );
}

void UI::renderTurno()
{
    std::string numeroJugador = "";
    // SI ES EL TURNO DE PLAYER 1
    if(juego->getPlayer1()->getTurno())
        numeroJugador = "1";
    // SI ES EL TURNO DE PLAYER 2
    else
        numeroJugador = "2";

    Texture turnoMensaje(
        sdlutils().renderer(),
        "TURNO DEL JUGADOR " + numeroJugador,
        sdlutils().fonts().at("ARIAL24"),
        build_sdlcolor(0xffffffff)
    );
    turnoMensaje.render(sdlutils().width()/4, sdlutils().height()/2);

    
}

