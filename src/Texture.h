
#ifndef TEXTURE_H
#define TEXTURE_H

#include<bits/stdc++.h>
#include "rsdl.hpp"

const int DIM = 30;

class Texture
{
public:
  void draw(Window& win, Rectangle camera, Rectangle pos);

  void add_state(std::string state_name, int frames);
  void set_state(std::string state_name);

  void add_dir(std::string name, std::string dr);
  void set_dir(std::string name);

  void set_name(std::string str);
private:
  std::string current_state;
  std::string current_dir;
  std::map<std::string,int> state_cache_frames;
  std::map<std::string,std::string> dir_address_cache;
  std::string name;
};

#endif
