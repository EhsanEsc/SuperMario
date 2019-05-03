
#include "Goomba.h"
using namespace std;

Goomba::Goomba()
{
}

void Goomba::draw(Window& win, Rectangle camera)
{
  texture.draw(win, camera, shape.get_rect());
}

void Goomba::set_all(std::string address, Shape sh)
{
  shape = sh;

  texture.set_name("Goomba");

  texture.add_dir("origin", address);
  texture.set_dir("origin");

  texture.add_state("dead",1);
  texture.add_state("walking",2);

  texture.set_state("walking");

  shape.set_ay(0.5);
  shape.set_vx(-2);
  dir = Dir::LEFT;
  active = false;
  alive = true;
  shape.run();
}

void Goomba::run()
{
  active = true;
}

Shape& Goomba::get_shape()
{
  return shape;
}

void Goomba::turn_around()
{
  if(dir == Dir::LEFT)
    dir = Dir::RIGHT , shape.set_vx(2);
  else
    dir = Dir::LEFT , shape.set_vx(-2);
  shape.run();
}

void Goomba::die(int time)
{
  time_death = time;
  alive = false;
  active = false;
  texture.set_state("dead");
}

int Goomba::get_time_death()
{
  return time_death;
}

bool Goomba::is_active() { return active; }
bool Goomba::is_alive() { return alive; }
