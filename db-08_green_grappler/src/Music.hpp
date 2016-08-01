#pragma once

class Music
{
public:
	static void init();

	static void pushSong();
	static bool popSong();
	static void playSong(const std::string& file);
	static void registerSong(const std::string& file, float volume);
	static void stop();
	static void onLogic();

private:
	Music();

	static DUH* myPlaying;
	static AL_DUH_PLAYER* myPlayer;
	static std::string myPlayingFile;
	static std::map<std::string, float> mySongVolumes;
	class Song
	{
	public:
		 DUH* myPlaying;
		 AL_DUH_PLAYER* myPlayer;
	};
	static std::stack<Song> mySongStack;
};