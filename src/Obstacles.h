
#ifndef OBSTACLES_H
#define OBSTACLES_H

#include<bits/stdc++.h>
#include "rsdl.hpp"
#include "Texture.h"
#include "Shape.h"
#include "Powerops.h"

enum class ObstaclesType
{
  BLOCK,
  CLAY,
  PIPE,
  BRICK,
  AMAZING_BRICK,
  FLAG,
  NA
};

class Obstacles
{
public:
  Obstacles(std::string address, Shape sh, char c, int type_num);
  void draw(Window& win, Rectangle camera);
  void set_all(std::string address, Shape sh, char c, int type_num);
  void break_tile();
  Shape& get_shape();
  ObstaclesType get_type();
  PoweropsType get_powerop();
  Texture texture;
private:
  Shape shape;
  int type_number;
  std::string texture_address;
  ObstaclesType type;
  PoweropsType powerop;
  int x;
  int y;
  Point starting_point ;
  ObstaclesType determine_type(char c);
};


#endif
