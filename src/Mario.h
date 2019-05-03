
#ifndef MARIO_H
#define MARIO_H

#include<bits/stdc++.h>
#include "rsdl.hpp"
#include "Texture.h"
#include "Shape.h"

enum class MarioState
{
  NORMAL,
  BIG,
  WHITE
};

class Mario
{
public:
  Mario();
  void draw(Window& win, Rectangle camera);
  void set_all(std::string address, Shape sh);
  void update_texture();
  int get_x();
  int get_lives();
  void death();
  Shape& get_shape();
  MarioState get_state();
  void get_health();

  void transform_normal();
  void transform_big();
  void transform_white();

  void start_move_x(Dir dir);
  void jump();
  void small_jump();
  void stop_move(Dir dir);
  void get_guard(int timer, int dur);
  bool has_guard();
  void check_guard(int timer);

  bool is_normal();
  bool is_big();
  bool is_white();
  void fix_pos(Rectangle camera);

  Dir get_last_dir();
private:
  Texture texture;
  Shape shape;
  bool running;

  bool guard;
  int time_guard;
  int guard_duration;
  int lives;

  MarioState state;
  Dir last_dir;
};

#endif
