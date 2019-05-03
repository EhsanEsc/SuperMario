
#ifndef SHAPE_H
#define SHAPE_H

#include<bits/stdc++.h>
#include "rsdl.hpp"

enum class Dir
{
  RIGHT,
  LEFT,
  DOWN,
  UP,
  NA
};

class Shape
{
public:
  Shape();
  Shape(Rectangle rect);
  void set_rect(Rectangle rect);
  Rectangle& get_rect();
  void add(Rectangle rect);

  void update_speed();
  void set_vx(double sp);
  void set_ax(double sp);
  void set_vy(double sp);
  void set_ay(double ac);
  void set_max_speed(double spx, double spy);

  void move_x();
  void undo_move_x();
  void move_y();
  void undo_move_y();

  void full_stop_x();
  void full_stop_y();

  bool is_running();
  bool is_static();
  Dir get_dir_acc();
  Dir get_dir_speed();

  void stop();
  void run();

  Point get_speed();
private:
  Rectangle pos;

  bool running;

  double speed_x;
  double speed_y;

  double acc_x;
  double acc_y;

  double max_speed_x;
  double max_speed_y;

  Dir last_dir;
};

#endif
