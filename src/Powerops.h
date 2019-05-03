
#ifndef POWEROPS_H
#define POWEROPS_H

#include<bits/stdc++.h>
#include "rsdl.hpp"
#include "Texture.h"
#include "Shape.h"
using namespace std;

enum class PoweropsType
{
  COIN,
  RED_MUSHROOM,
  FLOWER,
  HEALTH_MUSHROOM,
  NA
};

class Powerops
{
public:
  Powerops(int xpos, int ypos, PoweropsType tp);
  void draw(Window& win, Rectangle camera);
  Shape& get_shape();
  PoweropsType get_type();
  void transform_flower();

  void turn_around();
private:
  Shape shape;
  Texture texture;
  PoweropsType type;
  Dir dir;
  bool active;
  int base_vx;
};


#endif
