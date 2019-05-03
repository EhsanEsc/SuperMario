
#ifndef MANAGER_H
#define MANAGER_H

#include<bits/stdc++.h>
#include "rsdl.hpp"
#include "Obstacles.h"
#include "Mario.h"
#include "Texture.h"
#include "Shape.h"
#include "Troopa.h"
#include "Goomba.h"
#include "UI_box.h"
#include "Collision.h"
#include "Powerops.h"
#include "Sound.h"
#include "Projectile.h"

class Manager
{
public:
  Manager();
  void init(std::string map_address, Window* win);
  void update(Window& win, Rectangle& camera);
  void draw(Window& win, Rectangle& camera);

  void move_mario(char ch);
  void stop_mario(char ch);
  void shoot();

  bool is_running();
private:
  void add_creatures_from_map(std::string map_address);

  void kill_mario(Window& win, Rectangle& camera);
  void handle_fires();
  void remove_dead_goombas();
  void handle_goombas_kill();
  void handle_troopas_kill();
  void handle_rolling_kill();
  void handle_mario_kill(Window& win, Rectangle& camera);
  void handle_powerups_actions();
  void handle_objects_moving(Shape cam);
  void handle_ending(Window& win);
  void update_camera(Window& win, Rectangle &camera);

  void handle_hitted_amazing_bricks();
  void trigger_amazing_brick(Obstacles& u);
  vector<int> find_hitted_normal_bricks();
  void trigger_normal_bricks(vector<int> ids);

  void reposition_mario(Rectangle& camera);
  void show_mario_death(Window& win, Rectangle& camera);

  vector<std::string> get_map(std::string map_address);
  void set_ui();
  void add_obs(int x, int y, char c, int type_num);
  void add_sounds(Window* win);
  void add_mario(int i,int j);
  void add_goomba(int i,int j);
  void add_troopa(int i,int j);

  void move(Shape& s);
  void move_x(Shape& s);
  void move_y(Shape& s);

  void finish_win(Window& win);
  void finish_lost(Window &win);

  bool is_wining();

  int convert_x(int x);
  int convert_y(int y);

  bool check_ground();
  bool can_kill(Shape s1, Shape s2);
  Dir find_dir_for_rolling(Shape s1, Shape s2);

  Mario mario;
  std::vector<Obstacles> obs;
  std::vector<Goomba> goombas;
  std::vector<Troopa> troopas;
  std::vector<Powerops> powerops;
  std::vector<Projectile> fires;

  Collision cooler;
  Sound sound;

  UI_box ui_coins;
  UI_box ui_lives;
  UI_box ui_speed_x;
  UI_box ui_speed_y;
  UI_box ui_camera_x;

  Rectangle mario_starting_point;
  int map_width;
  bool is_finish;
  bool is_win;
  int coins;
  int timer;
  int last_fire_time=0;
};

#endif
