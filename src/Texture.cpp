
#include "Texture.h"
using namespace std;

void Texture::draw(Window& win, Rectangle camera, Rectangle pos)
{
  int total_frames = state_cache_frames[current_state];
  int frame = ((SDL_GetTicks()/500)%total_frames);
  string texture_address;

  texture_address = current_dir + "/" + name + "_" + current_state + "_" + to_string(frame) + ".png";
 
  if(pos.y >= win.get_height())
    return;
  if(pos.x-camera.x>=win.get_width() || pos.x-camera.x+pos.w<=0)
    return;

  Rectangle xx(pos.x - camera.x , pos.y , pos.w , pos.h);
  win.draw_img(texture_address , xx , NULL_RECT);
}

void Texture::add_state(string state_name, int frames)
{
  state_cache_frames[state_name] = frames;
}

void Texture::set_state(string state_name)
{
  current_state = state_name;
}

void Texture::add_dir(std::string name, std::string dr)
{
  dir_address_cache[name] = dr;
}

void Texture::set_dir(std::string name)
{
  current_dir = dir_address_cache[name];
}

void Texture::set_name(std::string str)
{
  name = str;
}
