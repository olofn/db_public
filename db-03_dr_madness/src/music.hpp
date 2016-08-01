#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <string>

void initMusic();

void playMusic(std::string file, float volume = 0.5f);

void pollMusic();

void stopMusic();

#endif
