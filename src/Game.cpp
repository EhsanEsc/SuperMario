
#include "Game.h"
using namespace std;

Game::Game(int screen_w, int screen_h, string title)
: win(screen_w,screen_h,title),
  camera(0,0,screen_w,screen_h)
{
  screen_width = screen_w;
  screen_height = screen_h;
}

void Game::init(string map_address)
{
  cout << "INIT" << endl;
  running = true;
  manager.init(map_address,&win);
}

void Game::handle_event()
{
  while(win.has_pending_event())
  {
    Event ev = win.poll_for_event();
    Event::EventType ev_type = ev.get_type();

    if(ev_type == Event::KEY_PRESS)
    {
      char ch = ev.get_pressed_key();
      if(ch == 'q')
        running = false;
      else if(ch == 'x'){
        manager.shoot();
      } else if (ch == 'd' || ch == 'a' || ch == 'w'){
        manager.move_mario(ch);
      }
    }
    else if(ev_type == Event::KEY_RELEASE){
      char ch = ev.get_pressed_key();
      if (ch == 'd' || ch == 'a' || ch == 'w'){
        manager.stop_mario(ch);
      }
    } else if(ev_type == Event::QUIT){
      running = false;
    }
  }
}

void Game::update()
{
  manager.update(win, camera);
}

void Game::render()
{
  win.clear();
  manager.draw(win , camera);
  win.update_screen();
}

bool Game::is_running()
{
  return running && manager.is_running();
}

void Game::clean()
{
  cout << "THE END" << endl;
}
