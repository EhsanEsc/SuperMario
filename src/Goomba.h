
#ifndef GOOMBA_H
#define GOOMBA_H

#include<bits/stdc++.h>
#include "rsdl.hpp"
#include "Texture.h"
#include "Shape.h"

class Goomba
{
public:
  Goomba();
  void draw(Window& win, Rectangle camera);
  void set_all(std::string address, Shape sh);
  void run();
  void turn_around();
  Shape& get_shape();
  void die(int time);

  int get_time_death();
 
  bool is_active();
  bool is_alive();
private:
  Shape shape;
  Texture texture;
  bool alive;
  bool active;
  Dir dir;
  int time_death;
};

#endif
