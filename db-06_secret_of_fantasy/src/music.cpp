#include <allegro.h>
#include <aldumb.h>
#include <dumb.h>

#include "music.hpp"
#include "resourcehandler.hpp"
#include "exception.hpp"

static DUH *playing = NULL;
static AL_DUH_PLAYER *player;
static std::string playingFile;

void initMusic()
{
	atexit(&dumb_exit);
	dumb_register_stdfiles();
}

void playMusic(std::string file, float volume)
{
	if (playingFile == file) {
		return;
	}

	if (playing != NULL) {
		al_stop_duh(player);
		unload_duh(playing);
	}

	std::string fileName = ResourceHandler::getInstance()->getRealFilename(file);

	if (!exists(fileName.c_str())) {
		throw DB_EXCEPTION("Unable to load " + fileName);
	}

	playing = dumb_load_xm_quick(fileName.c_str());
	player = al_start_duh(playing, 2, 0, volume, 4096, 44100);
	playingFile = file;

	pollMusic();
}

void stopMusic() {
	if (playing != NULL) {
		al_stop_duh(player);
		unload_duh(playing);
	}
	
	playing = NULL;
	playingFile = "";
}

void pollMusic() {
	if (playing)
		al_poll_duh(player);
}
