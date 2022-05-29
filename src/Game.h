#include <SDL2/SDL.h>
#include <stack>

using namespace std;
class GameObject;
class SDL_Renderer;
class Carta;
class Player;

class Game {
public:
     Game();
     virtual ~Game();
     void init(int w, int h);
     void start();

     // Devuelve al jugador que lo pida, la siguiente carta del mazo
	Carta getCarta();

    // Vacia la baraja para una nueva partida o lo quesea
	void limpiarBaraja();

    // Genera un nuevo mazo barajado
	void generaBaraja();

    // Update de todos los componentes
    void update();

private:
    const int NUM_CARTAS = 52;
	const int NUM_PALOS = 4;
	stack<Carta> baraja;
	bool debug = false;

    Player* player1;
    Player* player2;

    // TRUE = 1 FALSE = 2 
    bool turno;
};