
#include "Troopa.h"
using namespace std;

const int TROOPA_BASE_SPEED = 2;
const int TROOPA_ROLLING_SPEED = 5;

Troopa::Troopa()
{
}

void Troopa::draw(Window& win, Rectangle camera)
{
  texture.draw(win, camera, shape.get_rect());
}

void Troopa::set_all(std::string address, Shape sh)
{
  shape = sh;

  texture.set_name("Troopa");

  texture.add_dir("origin", address);
  texture.set_dir("origin");

  texture.add_state("dead",1);
  texture.add_state("walking-right",2);
  texture.add_state("walking-left",2);

  texture.set_state("walking-right");

  base_speed = TROOPA_BASE_SPEED;

  shape.set_ay(0.5);
  shape.set_vx(-base_speed);
  dir = Dir::LEFT;
  active = false;
  alive = true;
  rooling = false;
  shape.run();
}

void Troopa::run()
{
  active = true;
}

Shape& Troopa::get_shape()
{
  return shape;
}

void Troopa::turn_around()
{
  if(dir == Dir::LEFT)
    dir = Dir::RIGHT , shape.set_vx(base_speed);
  else
    dir = Dir::LEFT , shape.set_vx(-base_speed);
  shape.run();
}

void Troopa::update_texture()
{
  if(alive == false)
    return;
  if(dir == Dir::LEFT)
    texture.set_state("walking-left");
  else
    texture.set_state("walking-right");
}

bool Troopa::is_active() { return active; }
bool Troopa::is_alive() { return alive; }

void Troopa::die()
{
  alive = false;
  texture.set_state("dead");
  base_speed = 0;
  shape.set_vx(0);
  shape.stop();
}

bool Troopa::is_rolling()
{
  return rooling;
}

void Troopa::start_rolling(Dir d)
{
  base_speed = TROOPA_ROLLING_SPEED;
  if(d == Dir::LEFT)
    shape.set_vx(-base_speed);
  else
    shape.set_vx(base_speed);
  rooling = true;
  shape.run();
}
