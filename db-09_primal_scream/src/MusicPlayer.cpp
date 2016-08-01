#include "Precompiled.hpp"

#include "MusicPlayer.hpp"
#include "Music.hpp"

MusicPlayer::MusicPlayer(std::string file)
	: mFile(file)
{
}

void MusicPlayer::update()
{
	Music::playSong(mFile);
	remove();
}