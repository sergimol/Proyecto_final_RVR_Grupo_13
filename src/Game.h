#include <vector>
#include <SDL2/SDL.h>
#include "ecs/Manager.h"

class GameObject;
class SDL_Renderer;

class Game{
public:
     Game();
     virtual ~Game();
     void init(int w, int h);
     void start();
private:
    std::unique_ptr<Manager> mngr_;
};