
#ifndef TROOPA_H
#define TROOPA_H

#include<bits/stdc++.h>
#include "rsdl.hpp"
#include "Texture.h"
#include "Shape.h"

class Troopa
{
public:
  Troopa();
  void draw(Window& win, Rectangle camera);
  void set_all(std::string address, Shape sh);

  void run();
  void turn_around();
  Shape& get_shape();
  void update_texture();

  bool is_active();
  bool is_alive();

  void die();
  void start_rolling(Dir d);
  bool is_rolling();
private:
  Shape shape;
  Texture texture;

  bool active;
  Dir dir;

  bool alive;
  bool rooling;
  int base_speed;
};

#endif
