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
    Uint8 state = juego->getState();
    renderPuntosActuales();
    renderVictoriasActuales();
    if(state == Game::GameState::PLAYING)
        renderTurno();
    else if(state == Game::GameState::ROUNDEND)
        renderFinRonda();
    renderNombres();
}

void UI::renderPuntosActuales()
{
    // PUNTOS DEL PLAYER 1
    int puntos = juego->getPlayer1()->getPuntos();
    Texture puntosMensaje(
        sdlutils().renderer(),
        "PUNTOS ACTUALES:" + std::to_string(puntos),
        sdlutils().fonts().at("ARIAL16"),
        build_sdlcolor(0xffffffff)
    );
    puntosMensaje.render(sdlutils().width()/3, sdlutils().height()/10 * 9.5);

    // PUNTOS DEL PLAYER 2
    /*puntos = juego->getPlayer2()->getPuntos();
    Texture puntosMensaje2(
        sdlutils().renderer(),
        "PUNTOS ACTUALES:" + std::to_string(puntos),
        sdlutils().fonts().at("ARIAL16"),
        build_sdlcolor(0xffffffff)
    );
    puntosMensaje2.render(sdlutils().width()/10, sdlutils().height()/10 - 20);*/
}

void UI::renderVictoriasActuales()
{
    // VICTORIAS DEL PLAYER 1
    int victorias = juego->getPlayer1()->getVictorias();
    Texture victoriasMensaje(
        sdlutils().renderer(),
        "VICTORIAS:" + std::to_string(victorias),
        sdlutils().fonts().at("ARIAL16"),
        build_sdlcolor(0xffffffff)
    );
    victoriasMensaje.render(sdlutils().width()/8, sdlutils().height()/10 * 9.2);

    // VICTORIAS DEL PLAYER 2
    victorias = juego->getPlayer2()->getVictorias();
    Texture victoriasMensaje2(
        sdlutils().renderer(),
        "VICTORIAS:" + std::to_string(victorias),
        sdlutils().fonts().at("ARIAL16"),
        build_sdlcolor(0xffffffff)
    );
    victoriasMensaje2.render(sdlutils().width()/8, sdlutils().height()/10 - 35);
}

void UI::renderTurno()
{
    std::string nombreJugador = "";
    // SI ES EL TURNO DE PLAYER 1
    if(juego->getPlayer1()->getTurno())
        nombreJugador = juego->getPlayer1()->getNombre();
    // SI ES EL TURNO DE PLAYER 2
    else
        nombreJugador = juego->getPlayer2()->getNombre();

    Texture turnoMensaje(
        sdlutils().renderer(),
        "TURNO DE " + nombreJugador,
        sdlutils().fonts().at("ARIAL24"),
        build_sdlcolor(0xffffffff)
    );
    turnoMensaje.render(sdlutils().width()/3.5, sdlutils().height()/2); 
}

void UI::renderNombres()
{
    // VICTORIAS DEL PLAYER 1
    std::string nombre = juego->getPlayer1()->getNombre();
    Texture nombreMensaje(
        sdlutils().renderer(),
        nombre,
        sdlutils().fonts().at("ARIAL24"),
        build_sdlcolor(0xffffffff)
    );
    nombreMensaje.render(sdlutils().width()/3, sdlutils().height()/10 * 9);

    // VICTORIAS DEL PLAYER 2
    nombre = juego->getPlayer2()->getNombre();
    Texture nombreMensaje2(
        sdlutils().renderer(),
        nombre,
        sdlutils().fonts().at("ARIAL24"),
        build_sdlcolor(0xffffffff)
    );
    nombreMensaje2.render(sdlutils().width()/3, sdlutils().height()/10 - 30 );
}
void UI::renderFinRonda()
{
    int ganador = juego->getGanador();
    std::string mensajeFinal;

    if(ganador == 0)
        mensajeFinal = "EMPATE";
    else if(ganador == 1)
        mensajeFinal = "GANA " + juego->getPlayer1()->getNombre();
    else
        mensajeFinal = "GANA " + juego->getPlayer2()->getNombre();

    Texture textoFin(
        sdlutils().renderer(),
        mensajeFinal,
        sdlutils().fonts().at("ARIAL24"),
        build_sdlcolor(0xffffffff)
    );

    textoFin.render(sdlutils().width()/4, sdlutils().height()/2);
}
