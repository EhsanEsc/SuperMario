
#ifndef GAME_H
#define GAME_H

#include<bits/stdc++.h>
#include "rsdl.hpp"
#include "Manager.h"

class Game
{
public:
  Game(int screen_w, int screen_h, std::string title);
  void init(std::string map_address);
  void handle_event();
  void update();
  void render();
  void clean();

  bool is_running();
private:
  Manager manager;

  Window win;
  Rectangle camera;

  int screen_width;
  int screen_height;
  bool running;
};


#endif
