
#ifndef UI_BOX_H
#define UI_BOX_H

#include<bits/stdc++.h>
#include "rsdl.hpp"

class UI_box
{
public:
  UI_box();
  void set_all(std::string str, Point pt,
    RGB col, std::string font_add, int sz);
  void draw(Window& win, int var);
private:
  std::string name;
  Point src;

  RGB color;
  int size;
  std::string font_address;
};

#endif
