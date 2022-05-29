#include <SDL2/SDL.h>
#include "ecs/Manager.h"
#include <stack>

using namespace std;
class GameObject;
class SDL_Renderer;
class Carta;
class Game{
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

private:
    std::unique_ptr<Manager> mngr_;

    const int NUM_CARTAS = 52;
	const int NUM_PALOS = 4;
	stack<Carta> baraja;
	bool debug = false;
};