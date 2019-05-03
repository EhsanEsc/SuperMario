
#include "UI_box.h"
using namespace std;

UI_box::UI_box()
: src(Point(0,0)),
  color(RGB(0,0,0))
{

}

void UI_box::set_all(string str,Point pt,
    RGB col, string font_add, int sz)
{
  name = str;
  src = pt;
  color = col;
  font_address = font_add;
  size = sz;
}
void UI_box::draw(Window& win, int var)
{
  win.show_text(name + "  " + to_string(var), src, color, font_address, size);
}
