#include <SDL2/SDL.h>
#include <stack>

using namespace std;
class GameObject;
class SDL_Renderer;
class Carta;
class Player;
class Texture;
class Fondo;
class UI;


class Game {
public:
    Game();
    virtual ~Game();
    void init(int w, int h);
    void start();
    
    enum GameState : Uint8 {
        NEWGAME,
        PLAYING,
        ROUNDEND,
        GAMEOVER
    };

    // Devuelve al jugador que lo pida, la siguiente carta del mazo
	Carta* getCarta();

    // Vacia la baraja para una nueva partida o lo quesea
	void limpiarBaraja();

    // Genera un nuevo mazo barajado
	void generaBaraja();

    // Update de los objetos
    void update();

    // Render de los objetos
    void render();

    // Inicia una nueva partida
    void inicioDePartida();

    // Comprobaciones al terminar una partida
    void finDePartida();

    Player* getPlayer1(){return player1;};
    Player* getPlayer2(){return player2;};

    int getNumCartas(){return baraja.size();};

    Uint8 getState();

    int getGanador();

private:
    const int NUM_CARTAS = 52;
	const int NUM_PALOS = 4;
	stack<Carta*> baraja;
	bool debug = false;

    Player* player1;
    Player* player2;

    Fondo* fondo;

    UI* ui;

    // TRUE = 1 FALSE = 2 
    bool turno;

    // 0 empate / 1 player1 / 2 player2
    int ultimoGanador_ = 0;
    GameState state_;

    Texture* cartaTexture;

    bool eresJugador1 = true;
};