
#ifndef SOUND_H
#define SOUND_H

#include <bits/stdc++.h>
#include "rsdl.hpp"

class Sound
{
public:
  void add_sound_effect(std::string name, std::string address);
  void add_sound_track(std::string name, std::string address);
  void play_sound_effect(std::string name);
  void play_sound_track(std::string name);
  void pause_track();
  void resume_track();
  void set_win(Window* ww);
private:
  std::map<std::string,std::string> sound_effect_cache;
  std::map<std::string,std::string> sound_track_cache;
  Window* win;
};

#endif
