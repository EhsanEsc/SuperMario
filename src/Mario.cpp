
#include "Mario.h"
using namespace std;

const int STARTING_LIFES = 3;
const int MAX_X_SPEED = 7;
const int MAX_Y_SPEED = 30;
const double X_STARTING_MOVE = 0.2;
const double X_STOP_MOVE = 0.3;
const double SMALL_JUMP_SPEED = 5;
const double SUPER_JUMP_SPEED = 13;

Mario::Mario()
{
}

void Mario::draw(Window& win, Rectangle camera)
{
  texture.draw(win, camera, shape.get_rect());
}

void Mario::set_all(std::string address, Shape sh)
{
  shape = sh;

  texture.set_name("mario");

  texture.add_dir("normal", address + "/normal");
  texture.add_dir("big", address + "/big");
  texture.add_dir("white", address + "/white");

  texture.set_dir("normal");

  texture.add_state("standing-right",1);
  texture.add_state("standing-left",1);
  texture.add_state("jumping-right",1);
  texture.add_state("jumping-left",1);
  texture.add_state("walking-right",3);
  texture.add_state("walking-left",3);
  texture.add_state("sliding-right",1);
  texture.add_state("sliding-left",1);
  texture.add_state("dead",1);

  texture.set_state("walking-right");

  shape.set_max_speed(MAX_X_SPEED,MAX_Y_SPEED);
  shape.set_ay(0.5);
  lives=STARTING_LIFES;
  state = MarioState::NORMAL;
  guard = false;
}

void Mario::update_texture()
{
  if(shape.is_static())
  {
    if(last_dir == Dir::RIGHT)
      texture.set_state("standing-right");
    else
      texture.set_state("standing-left");
  }
  else if(shape.is_running())
  {
    if(shape.get_dir_acc() == Dir::RIGHT && shape.get_dir_speed() == Dir::RIGHT)
      texture.set_state("walking-right");
    if(shape.get_dir_acc() == Dir::LEFT && shape.get_dir_speed() == Dir::LEFT)
      texture.set_state("walking-left");
    if(shape.get_dir_acc() == Dir::RIGHT && shape.get_dir_speed() == Dir::LEFT)
      texture.set_state("sliding-right");
    if(shape.get_dir_acc() == Dir::LEFT && shape.get_dir_speed() == Dir::RIGHT)
      texture.set_state("sliding-left");
  }
    else if(shape.is_running() == false)
  {
    if(shape.get_dir_speed() == Dir::RIGHT)
      texture.set_state("walking-right");
    else
      texture.set_state("walking-left");
  }
}

int Mario::get_x()
{
  return shape.get_rect().x;
}

int Mario::get_lives()
{
  return lives;
}

Shape& Mario::get_shape()
{
  return shape;
}

void Mario::start_move_x(Dir dir)
{
  last_dir = dir;
  if(dir == Dir::RIGHT)
    shape.set_ax(X_STARTING_MOVE);
  else
    shape.set_ax(-X_STARTING_MOVE);
  shape.run();
}
void Mario::jump()
{
  shape.set_vy(-SUPER_JUMP_SPEED);
}

void Mario::small_jump()
{
  shape.set_vy(-SMALL_JUMP_SPEED);
}

void Mario::stop_move(Dir dir)
{
  if(dir == Dir::RIGHT)
    shape.set_ax(-X_STOP_MOVE);
  else
    shape.set_ax(X_STOP_MOVE);
  shape.stop();
}

void Mario::death()
{
  lives--;
  texture.set_state("dead");
}

MarioState Mario::get_state()
{
  return state;
}

void Mario::transform_normal()
{
  if(!is_normal())
    shape.add(Rectangle(0,DIM,0,-DIM));
  state = MarioState::NORMAL;
  texture.set_dir("normal");
  texture.set_state("standing-right");
}

void Mario::transform_big()
{
  if(is_normal())
    shape.add(Rectangle(0,-DIM,0,DIM));
  state = MarioState::BIG;
  texture.set_dir("big");
}

void Mario::transform_white()
{
  if(is_normal())
    shape.add(Rectangle(0,-DIM,0,DIM));
  state = MarioState::WHITE;
  texture.set_dir("white");
}

void Mario::get_health()
{
  lives++;
}

bool Mario::is_normal()
{
  return state==MarioState::NORMAL;
}

bool Mario::is_big()
{
  return state==MarioState::BIG;
}

bool Mario::is_white()
{
  return state==MarioState::WHITE;
}

void Mario::fix_pos(Rectangle camera)
{
  int xx = shape.get_rect().x;
  if(xx<camera.x)
    shape.add(Rectangle(camera.x-xx,0,0,0));
}

void Mario::get_guard(int timer, int dur)
{
  time_guard = timer;
  guard_duration = dur;
  guard = true;
}

bool Mario::has_guard()
{
  return guard;
}

void Mario::check_guard(int timer)
{
  if(timer - time_guard > guard_duration)
    guard = false;
}

Dir Mario::get_last_dir()
{
  return last_dir;
}
