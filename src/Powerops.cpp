
#include "Powerops.h"
using namespace std;

const int POWEROPS_BASE_SPEED = 1;
const int COIN_JUMP_SPEED = 5;

void Powerops::draw(Window& win, Rectangle camera)
{
  texture.draw(win, camera, shape.get_rect());
}

Shape& Powerops::get_shape()
{
  return shape;
}

Powerops::Powerops(int xpos, int ypos, PoweropsType tp)
{
  shape.set_rect(Rectangle(xpos, ypos, DIM, DIM));
  base_vx = POWEROPS_BASE_SPEED;
  shape.set_ay(0.5);
  shape.set_vx(base_vx);
  dir = Dir::RIGHT;
  shape.run();


  texture.add_dir("origin","assets/sprites/objects");
  texture.set_dir("origin");

  type = tp;
  if(type == PoweropsType::COIN) {
    texture.set_name("coin");
    shape.set_vx(0);
    shape.set_vy(-COIN_JUMP_SPEED);
    shape.set_ay(0.2);
    base_vx = 0;
  } else if(type == PoweropsType::FLOWER) {
    texture.set_name("flower");
    shape.set_vx(0);
    base_vx = 0;
  } else if(type == PoweropsType::RED_MUSHROOM) {
    texture.set_name("red-mushroom");
  } else if(type == PoweropsType::HEALTH_MUSHROOM) {
    texture.set_name("health-mushroom");
  }

  texture.add_state("normal",1);
  texture.set_state("normal");
}

void Powerops::turn_around()
{
  if(dir == Dir::LEFT)
    dir = Dir::RIGHT , shape.set_vx(base_vx);
  else
    dir = Dir::LEFT , shape.set_vx(-base_vx);
  shape.run();
}

PoweropsType Powerops::get_type()
{
  return type;
}

void Powerops::transform_flower()
{
  type = PoweropsType::FLOWER;
  texture.set_name("flower");
  shape.set_vx(0);
  base_vx = 0;
}
