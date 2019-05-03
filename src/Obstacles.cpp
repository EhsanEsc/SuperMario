
#include "Obstacles.h"
using namespace std;

void Obstacles::draw(Window& win, Rectangle camera)
{
  texture.draw(win, camera, shape.get_rect());
}

Obstacles::Obstacles(string address, Shape sh, char c, int type_num)
: starting_point(0,0)
{
  set_all(address, sh, c, type_num);
}

void Obstacles::set_all(string address,  Shape sh, char c, int type_num)
{
  texture.add_dir("origin", address);
  texture.set_dir("origin");

  powerop = PoweropsType::NA;

  shape = sh;
  texture.add_state("normal",1);
  starting_point.x = sh.get_rect().x;
  starting_point.y = sh.get_rect().y;

  type = determine_type(c);
  if(type == ObstaclesType::BRICK){
    texture.set_name("brick");
    texture.add_state("broken",1);
  } else if(type == ObstaclesType::PIPE){
    if(type_num==0)
      texture.set_name("pipe-0");
    else if(type_num==1)
      texture.set_name("pipe-1");
    else if(type_num==2)
      texture.set_name("pipe-2");
    else if(type_num==3)
      texture.set_name("pipe-3");
  }else if(type == ObstaclesType::AMAZING_BRICK){
    texture.set_name("amazing_brick");
    texture.add_state("normal",3);
    texture.add_state("broken",1);
    if(c == '?')
      powerop = PoweropsType::COIN;
    else if(c == 'm')
      powerop = PoweropsType::RED_MUSHROOM;
    else if(c == 'h')
      powerop = PoweropsType::HEALTH_MUSHROOM;
  }else if(type == ObstaclesType::BLOCK){
    texture.set_name("block");
  }else if(type == ObstaclesType::CLAY){
    texture.set_name("clay");
  }else if(type == ObstaclesType::FLAG){
    if(type_num==0)
      texture.set_name("flag-head");
    else if(type_num==1)
      texture.set_name("flag-body");
  }

  texture.set_state("normal");

  type_number = type_num;
}

ObstaclesType Obstacles::determine_type(char c)
{
  if(c == 'b')
    return ObstaclesType::BRICK;
  if(c == '|')
    return ObstaclesType::PIPE;
  if(c == '?' || c == 'm' || c == 'h')
    return ObstaclesType::AMAZING_BRICK;
  if(c == '@')
    return ObstaclesType::BLOCK;
  if(c == '#')
    return ObstaclesType::CLAY;
  if(c == 'f')
    return ObstaclesType::FLAG;
  cout << c << endl;
  return ObstaclesType::NA;
}

ObstaclesType Obstacles::get_type()
{
  return type;
}

PoweropsType Obstacles::get_powerop()
{
  return powerop;
}

Shape& Obstacles::get_shape()
{
  return shape;
}

void Obstacles::break_tile()
{
  if(type != ObstaclesType::AMAZING_BRICK)
    return;
  texture.set_state("broken");
  powerop = PoweropsType::NA;
}
