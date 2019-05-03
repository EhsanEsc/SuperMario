
#include "Shape.h"
using namespace std;

const int MAX_SPEED = 999;

Shape::Shape() : Shape(Rectangle(0,0,0,0)) {}

Shape::Shape(Rectangle rect)
: pos(rect)
{
  running = false;
  speed_x = speed_y = acc_x = acc_y = 0;
  last_dir = Dir::RIGHT;
  max_speed_x = max_speed_y = MAX_SPEED;
}

void Shape::set_rect(Rectangle rect) { pos = rect; }

Rectangle& Shape::get_rect(){ return pos; }

void Shape::add(Rectangle rect)
{
  pos.x += rect.x;
  pos.y += rect.y;
  pos.w += rect.w;
  pos.h += rect.h;
}


void Shape::update_speed()
{
  if(running)
  {
      speed_x += acc_x;
      speed_x = min(speed_x, max_speed_x);
      speed_x = max(speed_x, -max_speed_x);
  } else {
    if((acc_x<0 && speed_x<0) || (acc_x>0 && speed_x>0))
      acc_x *= -1;
    if(abs(acc_x)>abs(speed_x))
      speed_x=acc_x=0;
    speed_x += acc_x;
  }

  speed_y += acc_y;
  speed_y = max(speed_y, -max_speed_y);
  speed_y = min(speed_y, max_speed_y);
}


void Shape::set_vx(double sp) { speed_x = sp; }
void Shape::set_ax(double ac) { acc_x = ac; }
void Shape::set_vy(double sp) { speed_y = sp; }
void Shape::set_ay(double ac) { acc_y = ac; }
void Shape::set_max_speed(double spx, double spy) { max_speed_x = spx; max_speed_y = spy; }

void Shape::move_x() { pos.x += speed_x; }
void Shape::undo_move_x() { pos.x -= speed_x; }
void Shape::move_y() { pos.y += int(speed_y); }
void Shape::undo_move_y() { pos.y -= int(speed_y); }

void Shape::full_stop_x() { speed_x=0; running = false; }
void Shape::full_stop_y() { speed_y=0; }

bool Shape::is_running() { return running; }
bool Shape::is_static() { return speed_x == 0; }

void Shape::stop() { running = false; }
void Shape::run() { running = true; }

Dir Shape::get_dir_acc()
{
  if(acc_x>0)
    return Dir::RIGHT;
  else
    return Dir::LEFT;
}
Dir Shape::get_dir_speed()
{
  if(speed_x>0)
    return Dir::RIGHT;
  else
    return Dir::LEFT;
}

Point Shape::get_speed() { return Point(speed_x,speed_y); }
