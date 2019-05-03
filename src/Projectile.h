
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include<bits/stdc++.h>
#include "rsdl.hpp"
#include "Texture.h"
#include "Shape.h"

class Projectile
{
public:
  Projectile(Rectangle pos, Dir dir, int time);
  Shape& get_shape();
  bool out_of_time(int timer);
  void draw(Window& win, Rectangle camera);
private:
  Texture texture;
  Shape shape;

  int btime;
};

#endif
