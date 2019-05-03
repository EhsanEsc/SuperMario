#include "src/Game.h"
using namespace std;

const int FPS = 60;
const int DELAY_TIME = 1000/FPS;

int find_height(string map_address)
{
  ifstream fl(map_address);
  int txt_h=0;
  string str;

  while(getline(fl,str))
  {
    txt_h++;
  }
  fl.close();
  return txt_h;
}

int main(int argc, char** argv)
{
  string map_address = argv[1];
  int txt_height = find_height(map_address);
  int screen_h = txt_height*DIM;
  int screen_w = screen_h*2;

  Game game(screen_w,screen_h,"MyGame!");

  game.init(map_address);

  while(game.is_running())
  {
    int starting_time = SDL_GetTicks();

    game.handle_event();
    game.update();
    game.render();

    int elapsed_time = SDL_GetTicks() - starting_time;
    if(DELAY_TIME - elapsed_time > 0)
      delay(DELAY_TIME - elapsed_time);
  }
  game.clean();

  return 0;
}
