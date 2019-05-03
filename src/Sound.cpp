
#include "Sound.h"
using namespace std;

void Sound::add_sound_effect(string name, string address)
{
  sound_effect_cache[name] = address;
}
void Sound::add_sound_track(string name, string address)
{
  sound_track_cache[name] = address;
}
void Sound::play_sound_effect(string name)
{
  win->play_sound_effect(sound_effect_cache[name]);
}
void Sound::play_sound_track(string name)
{
  win->play_music(sound_track_cache[name]);
}

void Sound::set_win(Window* ww)
{
  win = ww;
}

void Sound::resume_track()
{
  win->resume_music();
}

void Sound::pause_track()
{
  win->pause_music();
}
