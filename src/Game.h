#include <SDL2/SDL.h>
#include <stack>

using namespace std;
class GameObject;
class SDL_Renderer;
class Carta;
class Player;
class Texture;

class Game {
public:
     Game();
     virtual ~Game();
     void init(int w, int h);
     void start();

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

    // Comprobaciones al terminar una partida
    void finDePartida();
private:
    const int NUM_CARTAS = 52;
	const int NUM_PALOS = 4;
	stack<Carta*> baraja;
	bool debug = false;

    Player* player1;
    Player* player2;

    Carta* carta;

    // TRUE = 1 FALSE = 2 
    bool turno;

    Texture* cartaTexture;
};