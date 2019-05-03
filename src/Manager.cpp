
#include "Manager.h"

using namespace std;

const int TRIGGER_SENSITIVITY_PIXEL = 5;
const int SHRINK_GUARD_TIME = 60;
const int REVIVE_GUARD_TIME = 60;
const int DIE_JUMP_SPEED = 15;
const int KILL_SENSITIVITY_PIXEL = 20;
const int FIRE_COOLDOWN = 20;
const int GOOMBA_DEAD_BODY_TIME = 20;
const int MAX_HEIGHT = 600;
const int START_ROLLING_GUARD_TIME = 30;

Manager::Manager()
: mario_starting_point(Rectangle(0,0,0,0))
{}

void Manager::init(string map_address, Window* win)
{
  add_creatures_from_map(map_address);
  add_sounds(win);
  set_ui();
  is_finish = false;
  timer = 0;
  coins = 0;
}

void Manager::update(Window& win, Rectangle& camera)
{
  timer++;

  mario.check_guard(timer);
  handle_fires();
  remove_dead_goombas();
  handle_goombas_kill();
  handle_troopas_kill();
  handle_rolling_kill();
  handle_mario_kill(win, camera);
  handle_hitted_amazing_bricks();

  vector<int> hitted_bricks_id = find_hitted_normal_bricks();
  move(mario.get_shape());
  mario.fix_pos(camera);
  trigger_normal_bricks(hitted_bricks_id);

  mario.update_texture();

  handle_powerups_actions();
  handle_objects_moving(Shape(camera));

  update_camera(win, camera);
  handle_ending(win);
}

void Manager::handle_hitted_amazing_bricks()
{
  Shape s = mario.get_shape();
  s.move_y();

  for(auto& u:obs)
    if(cooler.is_coll_up(s,u.get_shape())>TRIGGER_SENSITIVITY_PIXEL && u.get_powerop() != PoweropsType::NA)
      trigger_amazing_brick(u);

  s.undo_move_y();
}

vector<int> Manager::find_hitted_normal_bricks()
{
  Shape s = mario.get_shape();
  s.move_y();

  vector<int> ids;
  for(int i=0 ; i<obs.size() ; i++)
    if(cooler.is_coll_up(s,obs[i].get_shape())>TRIGGER_SENSITIVITY_PIXEL && obs[i].get_type() == ObstaclesType::BRICK)
      ids.push_back(i);

  s.undo_move_y();
  return ids;
}

void Manager::trigger_amazing_brick(Obstacles& u)
{
  if(u.get_powerop() == PoweropsType::COIN)
  {
    coins++;
    sound.play_sound_effect("coin");
  }
  else
  {
    sound.play_sound_effect("powerup-appears");
  }

  int xpos = u.get_shape().get_rect().x;
  int ypos = u.get_shape().get_rect().y;
  Powerops w(xpos,ypos-DIM-1,u.get_powerop());

  if(w.get_type() == PoweropsType::RED_MUSHROOM && mario.is_normal()==false)
    w.transform_flower();

  powerops.push_back(w);

  u.break_tile();
}

void Manager::trigger_normal_bricks(vector<int> hitted_bricks)
{
  reverse(hitted_bricks.begin(), hitted_bricks.end());
  for(auto i:hitted_bricks)
  {
    for(auto& u:goombas)
      if(cooler.is_stick_down(u.get_shape() , obs[i].get_shape()))
        u.die(timer);
    for(auto &u:troopas)
      if(cooler.is_stick_down(u.get_shape() , obs[i].get_shape()))
        u.die();

    if(mario.is_normal() == false)
      obs.erase(obs.begin()+i);
  }
  if(hitted_bricks.empty() == false)
    sound.play_sound_effect("brick-smash");
}

void Manager::move(Shape& s)
{
  s.update_speed();
  move_x(s);
  move_y(s);
}

void Manager::move_x(Shape& s)
{
  s.move_x();
  for(auto u:obs)
  {
    if(u.get_type() != ObstaclesType::FLAG && cooler.is_coll_x(s,u.get_shape()))
    {
      s.undo_move_x();
      s.full_stop_x();
      return;
    }
  }
}

void Manager::move_y(Shape& s)
{
  s.move_y();
  for(auto u:obs)
  {
    if(u.get_type() != ObstaclesType::FLAG && cooler.is_coll_y(s,u.get_shape()))
    {
      s.undo_move_y();
      s.full_stop_y();
      return;
    }
  }
}

void Manager::update_camera(Window& win, Rectangle &camera)
{
  camera.x = max(camera.x,mario.get_x()-(win.get_width()/2)) ;
  camera.x = max(camera.x , 0);
  camera.x = min(camera.x , map_width - win.get_width());
}

void Manager::draw(Window& win, Rectangle& camera)
{
    Rectangle bg_rect = Rectangle(0,0,win.get_width(),win.get_height());
    for(int i=0; i-camera.x<=win.get_width() ; i+=win.get_width())
    {
      bg_rect.x = i-camera.x ;
      win.draw_img("assets/background_image.png" , bg_rect , NULL_RECT);
    }

    for(auto u:obs)
      u.draw(win, camera);
    for(auto u:troopas)
      u.draw(win, camera);
    for(auto u:goombas)
      u.draw(win, camera);
    for(auto u:powerops)
      u.draw(win, camera);
    for(auto u:fires)
      u.draw(win, camera);
    mario.draw(win, camera);

    ui_camera_x.draw(win, camera.x);
    ui_lives.draw(win, mario.get_lives());
    ui_speed_x.draw(win, mario.get_shape().get_speed().x);
    ui_speed_y.draw(win, mario.get_shape().get_speed().y);
    ui_coins.draw(win, coins);
}

void Manager::add_creatures_from_map(string map_address)
{
  vector<string> lines = get_map(map_address);
  int txt_height = lines.size();
  int txt_width = lines[0].size();
  map_width = DIM*txt_width;

  for(int i=0 ; i<txt_height ; i++)
  {
    for(int j=0 ; j<txt_width ; j++)
    {
      if(lines[i][j]=='M'){
        add_mario(i,j);
      }else if(lines[i][j]=='l'){
        add_goomba(i,j);
      }else if(lines[i][j]=='k'){
        add_troopa(i,j);
      } else if(lines[i][j]=='.'){
      } else {
        if(lines[i][j]=='|' && (lines[i][j-1]=='|' || lines[i-1][j]=='|'))
          continue;
        if(lines[i][j]=='f' && lines[i-1][j]=='f')
          continue;
        if(lines[i][j]=='|')
        {
          add_obs(j, i, lines[i][j], 0);
          add_obs(j+1, i, lines[i][j], 1);
          for(int w=i+1 ; w<txt_height && lines[w][j]=='|'; w++)
          {
            add_obs(j, w, lines[i][j], 2);
            add_obs(j+1, w, lines[i][j], 3);
          }
        } else if(lines[i][j] == 'f') {
          add_obs(j, i, lines[i][j], 0);
          for(int w=i+1 ; w<txt_height && lines[w][j]=='f'; w++)
          {
            add_obs(j, w, lines[i][j], 1);
          }
        } else {
          add_obs(j, i, lines[i][j], 0);
        }
      }
    }
  }
}

int Manager::convert_x(int x)
{
  return x*DIM;
}

int Manager::convert_y(int y)
{
  return y*DIM;
}

void Manager::add_obs(int x, int y, char c, int type_num)
{
  string address = "assets/sprites/objects/bricks_blocks";
  Shape sh(Rectangle(convert_x(x),convert_y(y),DIM,DIM));
  Obstacles u(address, sh, c, type_num);
  obs.push_back(u);
}

void Manager::move_mario(char ch)
{
  if(ch == 'd'){
    mario.start_move_x(Dir::RIGHT);
  } else if(ch == 'a'){
    mario.start_move_x(Dir::LEFT);
  } else if(ch == 'w'){
    if(check_ground())
    {
      mario.jump();
      sound.play_sound_effect("jump-super");
    }
  }
}

void Manager::stop_mario(char ch)
{
  if(ch == 'd'){
    mario.stop_move(Dir::RIGHT);
  } else if(ch == 'a'){
    mario.stop_move(Dir::LEFT);
  }
}

void Manager::kill_mario(Window& win, Rectangle& camera)
{
  if(mario.has_guard())
    return;
  if(mario.is_normal() == false)
  {
    mario.transform_normal();
    mario.get_guard(timer,SHRINK_GUARD_TIME);
    return;
  }

  show_mario_death(win, camera);
  reposition_mario(camera);
  if(mario.get_lives() == 0)
    finish_lost(win);
}

void Manager::reposition_mario(Rectangle& camera)
{
  mario.get_guard(timer, REVIVE_GUARD_TIME);
  mario.transform_normal();
  mario.get_shape().set_rect(mario_starting_point);
  camera.x = camera.y = 0;
}

void Manager::show_mario_death(Window& win, Rectangle& camera)
{
    mario.death();
    sound.pause_track();
    sound.play_sound_effect("mario-death");
    mario.get_shape().set_vy(-DIE_JUMP_SPEED);

    while(mario.get_shape().get_rect().y <= win.get_height())
    {
      win.clear();
      draw(win, camera);
      win.update_screen();

      mario.get_shape().update_speed();
      mario.get_shape().move_y();
    }

    mario.get_shape().set_vy(0);
    delay(3000);
    sound.resume_track();
}

void Manager::finish_win(Window& win)
{
  is_finish = true;
  is_win = true;

  sound.pause_track();
  sound.play_sound_effect("level-clear");

  cout << "YOU WIN" << endl;

  win.clear();
  win.draw_img("assets/win.png");
  win.update_screen();

  delay(6000);
}

void Manager::finish_lost(Window& win)
{
  is_finish = true;
  is_win = false;

  sound.pause_track();
  sound.play_sound_effect("gameover");

  cout << "YOU LOSE" << endl;

  win.clear();
  win.draw_img("assets/lose.png");
  win.update_screen();

  delay(4000);
}

void Manager::add_sounds(Window* win)
{
  sound.set_win(win);

  sound.add_sound_track("theme music", "assets/sounds/Super_Mario_Bros_theme_music.mp3");
  sound.play_sound_track("theme music");

  sound.add_sound_effect("jump-super", "assets/sounds/sound_effects/jump-super.wav");
  sound.add_sound_effect("jump-small", "assets/sounds/sound_effects/jump-small.wav");
  sound.add_sound_effect("powerup-appears", "assets/sounds/sound_effects/powerup-appears.wav");
  sound.add_sound_effect("powerup", "assets/sounds/sound_effects/powerup.wav");
  sound.add_sound_effect("mario-death", "assets/sounds/sound_effects/mario-death.wav");
  sound.add_sound_effect("gameover", "assets/sounds/sound_effects/gameover.wav");
  sound.add_sound_effect("coin", "assets/sounds/sound_effects/coin.wav");
  sound.add_sound_effect("fireball", "assets/sounds/sound_effects/fireball.wav");
  sound.add_sound_effect("brick-smash", "assets/sounds/sound_effects/brick-smash.wav");
  sound.add_sound_effect("level-clear", "assets/sounds/sound_effects/level-clear.wav");
}

bool Manager::is_running() { return !is_finish; }

bool Manager::is_wining() { return is_win; }

bool Manager::check_ground()
{
  for(auto u:obs)
    if(cooler.is_stick_down(mario.get_shape(),u.get_shape()))
      return true;
  return false;
}

bool Manager::can_kill(Shape s1, Shape s2)
{
  Rectangle r1(s1.get_rect());
  Rectangle r2(s2.get_rect());

  if(r1.y+r1.h-KILL_SENSITIVITY_PIXEL > r2.y)
    return false;
  if(cooler.is_coll_down(s1,s2) == 0)
    return false;
  return true;
}

Dir Manager::find_dir_for_rolling(Shape s1, Shape s2)
{
  Rectangle r1(s1.get_rect());
  Rectangle r2(s2.get_rect());

  if(r1.x < r2.x)
    return Dir::RIGHT;
  else
    return Dir::LEFT;
}

void Manager::shoot()
{
  if(mario.is_white() == false)
    return;
  if(timer-last_fire_time<FIRE_COOLDOWN)
    return;
  last_fire_time = timer;
  Projectile fr(mario.get_shape().get_rect(), mario.get_last_dir() ,timer);
  fires.push_back(fr);
  sound.play_sound_effect("fireball");
}

void Manager::set_ui()
{
  ui_coins.set_all("Coins",Point(100,0),RGB(255, 0, 255),"assets/FreeSans.ttf",24);
  ui_lives.set_all("lives",Point(250,0),RGB(200, 157, 30),"assets/FreeSans.ttf",24);
  ui_speed_x.set_all("x speed",Point(400,0),RGB(250,150,0),"assets/FreeSans.ttf",24);
  ui_speed_y.set_all("y speed",Point(550,0),RGB(28, 57, 187),"assets/FreeSans.ttf",24);
  ui_camera_x.set_all("Camera X pos",Point(700,0),RGB(0, 255, 255),"assets/FreeSans.ttf",24);
}

vector<string> Manager::get_map(string map_address)
{
  ifstream fl(map_address);
  vector<string> lines;
  string str;

  while(getline(fl,str))
  {
    lines.push_back(str);
  }
  fl.close();
  return lines;
}

void Manager::add_mario(int i, int j)
{
  mario_starting_point.x = convert_x(j);
  mario_starting_point.y = convert_y(i);
  mario_starting_point.w = mario_starting_point.h = DIM;
  Shape sh(mario_starting_point);

  mario.set_all("assets/sprites/mario", sh);
}

void Manager::add_goomba(int i,int j)
{
  Shape sh(Rectangle(convert_x(j),convert_y(i),DIM,DIM));
  Goomba gm;
  gm.set_all("assets/sprites/enemies/goomba", sh);
  goombas.push_back(gm);
}

void Manager::add_troopa(int i,int j)
{
  Shape sh(Rectangle(convert_x(j),convert_y(i),DIM,DIM));
  Troopa tp;
  tp.set_all("assets/sprites/enemies/troopa", sh);
  troopas.push_back(tp);
}

void Manager::handle_fires()
{
  for(auto u=fires.begin() ; u!=fires.end() ; u++)
  {
    bool alive = true;
    if(u->out_of_time(timer) || u->get_shape().get_speed().x == 0)
      alive = false;
    for(auto& w:goombas)
      if(alive && cooler.is_coll(u->get_shape(), w.get_shape()) && w.is_alive())
      {
        w.die(timer);
        alive = false;
      }
    for(auto& w:troopas)
      if(alive && cooler.is_coll(u->get_shape(), w.get_shape()) && w.is_alive())
      {
        w.die();
        alive = false;
      }
    if(!alive)
    {
      fires.erase(u);
      u--;
    }
  }
}

void Manager::remove_dead_goombas()
{
  for(auto u=goombas.begin() ; u!=goombas.end() ; u++)
    if(u->is_alive() == false && timer- u->get_time_death() >= GOOMBA_DEAD_BODY_TIME)
    {
      goombas.erase(u);
      u--;
    }
}

void Manager::handle_goombas_kill()
{
  for(auto& u:goombas)
  {
    if(u.is_alive() && can_kill(mario.get_shape(), u.get_shape()))
    {
      mario.small_jump();
      sound.play_sound_effect("jump-small");
      u.die(timer);
    }
    if(u.is_alive() && u.get_shape().get_rect().y >= MAX_HEIGHT)
      u.die(timer);
  }
}

void Manager::handle_troopas_kill()
{
  for(auto& u:troopas)
    if(can_kill(mario.get_shape(), u.get_shape()))
    {
      if(u.is_alive())
      {
        mario.small_jump();
        sound.play_sound_effect("jump-small");
        u.die();
      }
      else if(u.is_rolling() == false)
      {
        mario.small_jump();
        sound.play_sound_effect("jump-small");
        mario.get_guard(timer, START_ROLLING_GUARD_TIME);
        u.start_rolling(find_dir_for_rolling(mario.get_shape(), u.get_shape()));
      }
    }
}

void Manager::handle_rolling_kill()
{
  vector<int>dead_troopas;
  for(auto& u:troopas)
  {
    if(u.is_rolling() == false)
      continue;
    for(auto& w:goombas)
      if(cooler.is_coll(u.get_shape(), w.get_shape()))
        w.die(timer);
    for(int i=0 ; i<troopas.size() ; i++)
      if(cooler.is_coll(u.get_shape(), troopas[i].get_shape()) && troopas[i].is_alive())
        dead_troopas.push_back(i);
  }
  reverse(dead_troopas.begin(),dead_troopas.end());
  for(auto u:dead_troopas)
    troopas.erase(troopas.begin()+u);
}

void Manager::handle_mario_kill(Window& win, Rectangle& camera)
{
  for(auto u:goombas)
    if(u.is_alive() && cooler.is_coll(mario.get_shape(), u.get_shape()))
      kill_mario(win, camera);
  for(auto u:troopas)
    if(cooler.is_coll(mario.get_shape(), u.get_shape()))
      if(u.is_alive() || u.is_rolling())
        kill_mario(win, camera);
  if(mario.get_shape().get_rect().y >= win.get_height())
    kill_mario(win, camera);
}

void Manager::handle_powerups_actions()
{
  for(auto u=powerops.begin() ; u != powerops.end() ; u++)
    if(u->get_shape().get_speed().y==0 && u->get_type() == PoweropsType::COIN)
    {
      powerops.erase(u);
      u--;
    }

  for(auto u=powerops.begin() ; u != powerops.end() ; u++)
  {
    if(cooler.is_coll(mario.get_shape(), u->get_shape()))
    {
      if(u->get_type() == PoweropsType::HEALTH_MUSHROOM)
        mario.get_health();
      else if(u->get_type() == PoweropsType::RED_MUSHROOM)
        mario.transform_big();
      else if(u->get_type() == PoweropsType::FLOWER)
        mario.transform_white();
      powerops.erase(u);
      sound.play_sound_effect("powerup");
      break;
    }
  }
}

void Manager::handle_objects_moving(Shape cam)
{
  for(auto& u:goombas)
  {
    if(cooler.is_coll_right(cam, u.get_shape()) && u.is_active()==false && u.is_alive())
      u.run();
    if(u.is_active())
      move(u.get_shape());
    if(u.get_shape().get_speed().x==0)
      u.turn_around();
  }
  for(auto& u:troopas)
  {
    if(cooler.is_coll_right(cam, u.get_shape()) && u.is_active()==false)
      u.run();
    if(u.is_active())
      move(u.get_shape());
    if(u.get_shape().get_speed().x==0)
      u.turn_around();
    u.update_texture();
  }

  for(auto& u:powerops)
  {
    move(u.get_shape());
    if(u.get_shape().get_speed().x==0)
      u.turn_around();
  }

  for(auto& u:fires)
    move(u.get_shape());
}

void Manager::handle_ending(Window& win)
{
  for(auto u:obs)
    if(is_running() && u.get_type() == ObstaclesType::FLAG && mario.get_shape().get_rect().x>=u.get_shape().get_rect().x)
      finish_win(win);
}
