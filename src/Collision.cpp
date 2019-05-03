
#include "Collision.h"
using namespace std;

int Collision::is_coll_right(Shape s1, Shape s2)
{
  Rectangle r1(s1.get_rect());
  Rectangle r2(s2.get_rect());

  if(!(r1.x<r2.x && r2.x<r1.x+r1.w))
    return 0;

  int n1 = min(r1.y+r1.h, r2.y+r2.h);
  int n2 = max(r1.y, r2.y);

  return max(0,n1-n2);
}

int Collision::is_coll_down(Shape s1, Shape s2)
{
  Rectangle r1(s1.get_rect());
  Rectangle r2(s2.get_rect());

  if(!(r1.y<r2.y && r2.y<r1.y+r1.h))
    return 0;

  int n1 = min(r1.x+r1.w, r2.x+r2.w);
  int n2 = max(r1.x, r2.x);

  return max(0,n1-n2);
}

int Collision::is_coll_left(Shape s1, Shape s2)
{
  return is_coll_right(s2, s1);
}

int Collision::is_coll_up(Shape s1, Shape s2)
{
  return is_coll_down(s2, s1);
}

int Collision::is_coll_x(Shape s1,Shape s2)
{
  return max(is_coll_right(s1,s2),is_coll_left(s1,s2));
}
int Collision::is_coll_y(Shape s1,Shape s2)
{
  return max(is_coll_down(s1,s2),is_coll_up(s1,s2));
}

int Collision::is_coll(Shape s1,Shape s2)
{
  return max(is_coll_x(s1,s2), is_coll_y(s1,s2));
}

bool Collision::is_stick_down(Shape s1, Shape s2)
{
  Rectangle r1(s1.get_rect());
  Rectangle r2(s2.get_rect());

  if(r1.y+r1.h != r2.y)
    return false;

  int n1 = min(r1.x+r1.w, r2.x+r2.w);
  int n2 = max(r1.x, r2.x);

  return (n1-n2>0);
}
