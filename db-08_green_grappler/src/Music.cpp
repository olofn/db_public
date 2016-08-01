#include "Music.hpp"

#include "Resource.hpp"

DUH* Music::myPlaying = NULL;
AL_DUH_PLAYER* Music::myPlayer = NULL;
std::string Music::myPlayingFile;
std::map<std::string, float> Music::mySongVolumes;
std::stack<Music::Song> Music::mySongStack;

Music::Music()
{

}

void Music::init()
{
	atexit(&dumb_exit);
	dumb_register_stdfiles();
}

void Music::playSong(const std::string& file)
{
	if (myPlayingFile == file) 
	{
		return;
	}

	if (myPlaying != NULL) 
	{
		al_stop_duh(myPlayer);
		unload_duh(myPlaying);
		myPlaying = NULL;
		myPlaying = NULL;
	}

	std::string filename = Resource::getRealFilename(file);

	if (!exists(filename.c_str())) 
	{
		throw std::string("Unable to load ") + filename;
	}

	float volume = mySongVolumes[file];

	myPlaying = dumb_load_xm_quick(filename.c_str());
	myPlayer = al_start_duh(myPlaying, 2, 0, volume, 4096, 44100);
	myPlayingFile = file;

	onLogic();
}

void Music::stop() 
{
	if (myPlaying != NULL) 
	{
		al_stop_duh(myPlayer);
		unload_duh(myPlaying);
		myPlaying = NULL;
		myPlayer = NULL;
	}
	
	myPlayingFile = "";
}

void Music::onLogic() 
{
	if (myPlayer != NULL)
		al_poll_duh(myPlayer);
}

void Music::registerSong( const std::string& file , float volume)
{
	mySongVolumes[file] = volume;
}

void Music::pushSong()
{
	Song song;
	song.myPlayer = myPlayer;
	song.myPlaying = myPlaying;
	al_pause_duh(myPlayer);
	mySongStack.push(song);
	myPlayer = NULL;
	myPlaying = NULL;
	myPlayingFile = "";
}

bool Music::popSong()
{
	stop();
	
	if (mySongStack.empty())
	{
		return false;
	}

	Song song = mySongStack.top();
	mySongStack.pop();
	myPlayer = song.myPlayer;
	myPlaying = song.myPlaying;
	al_resume_duh(myPlayer);

	return true;
}
