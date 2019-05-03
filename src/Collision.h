
#ifndef COLLISION_H
#define COLLISION_H

#include<bits/stdc++.h>
#include "rsdl.hpp"
#include "Shape.h"

class Collision
{
public:
  int is_coll_right(Shape s1, Shape s2);
  int is_coll_left(Shape s1, Shape s2);
  int is_coll_down(Shape s1, Shape s2);
  int is_coll_up(Shape s1, Shape s2);

  int is_coll_x(Shape s1,Shape s2);
  int is_coll_y(Shape s1,Shape s2);

  int is_coll(Shape s1,Shape s2);

  bool is_stick_down(Shape s1, Shape s2);
};

#endif
