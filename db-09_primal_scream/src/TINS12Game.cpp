#include "Precompiled.hpp"

#include "TINS12Game.hpp"

#include "Constants.hpp"
#include "Input.hpp"
#include "Music.hpp"
#include "ScreenManager.hpp"
#include "Sound.hpp"
#include "Level.hpp"
#include "Title.hpp"
#include "SplashScreen.hpp"
#include "RoomLoader.hpp"
#include "Room.hpp"
#include "World.hpp"
#include "GameState.hpp"
#include "End.hpp"
#include "Outro.hpp"

TINS12Game::TINS12Game()
:Game("db - Primal Scream", true)
{
	register_png_file_type();

	Input::registerKey(Button_ToggleFullscreen, KEY_F);
	Input::registerKey(Button_ToggleSlowMotion, KEY_S);
	Input::registerKey(Button_Exit, KEY_ESC);
	Input::registerKey(Button_ToggleVSync, KEY_V);
	Input::registerKey(Button_ToggleWideScreen, KEY_W);
	//Input::registerKey(Button_Fire, KEY_LCONTROL);
	Input::registerKey(Button_Fire, KEY_X);
	//Input::registerKey(Button_Fire, KEY_RCONTROL);
	Input::registerKey(Button_Fire, KEY_SPACE);
	Input::registerKey(Button_Fire, KEY_ENTER);
	Input::registerKey(Button_Fire, KEY_ALT);
	Input::registerKey(Button_ToggleWeapon, KEY_LCONTROL);
	Input::registerKey(Button_ToggleWeapon, KEY_RCONTROL);
	Input::registerKey(Button_ToggleWeapon, KEY_Z);
	Input::registerKey(Button_Jump, KEY_UP);
	Input::registerKey(Button_Up, KEY_UP);
	Input::registerKey(Button_Down, KEY_DOWN);
	Input::registerKey(Button_Left, KEY_LEFT);
	Input::registerKey(Button_Right, KEY_RIGHT);
#ifdef _DEBUG	
	Input::registerKey(Button_ForceQuit, KEY_Q);
#endif
	// Xbox 360 controller
	//Input::registerJoypadButton(Button_Action, 0, 7);
	Input::registerJoypadButton(Button_Exit,  0, 6);
	//Input::registerJoypadButton(Button_Jump,  0, 1);
	Input::registerJoypadButton(Button_Jump,  0, 0);
	Input::registerJoypadButton(Button_ToggleWeapon,  0, 2);
	Input::registerJoypadButton(Button_Fire,  0, 1);
	Input::registerJoypadStick(Button_Left,   0, 0, 0, -1);
	Input::registerJoypadStick(Button_Right,  0, 0, 0, 1);
	Input::registerJoypadStick(Button_Up,     0, 0, 1, -1);
	Input::registerJoypadStick(Button_Down,   0, 0, 1, 1);
	Input::registerJoypadStick(Button_Left,   0, 1, 0, -1);
	Input::registerJoypadStick(Button_Right,  0, 1, 0, 1);
	Input::registerJoypadStick(Button_Up,     0, 1, 1, -1);
	Input::registerJoypadStick(Button_Down,   0, 1, 1, 1);

	Sound::registerSample("data/sounds/start.wav", 150);
	Sound::registerSample("data/sounds/beep.wav", 50);
	Sound::registerSample("data/sounds/select.wav", 150);

	Sound::registerSample("data/sounds/jump.wav", 255);
	Sound::registerSample("data/sounds/land.wav", 128);
	Sound::registerSample("data/sounds/hurt.wav", 255);
	Sound::registerSample("data/sounds/unknown.wav", 255);
	
	Sound::registerSample("data/sounds/bossdeath.wav", 255);
	Sound::registerSample("data/sounds/coin.wav", 100);
	Sound::registerSample("data/sounds/dragondeath.wav", 128);
	Sound::registerSample("data/sounds/grenadeexplode.wav", 100);
	Sound::registerSample("data/sounds/shoot.wav", 255);
	Sound::registerSample("data/sounds/throwgrenade.wav", 150);
	Sound::registerSample("data/sounds/portal.wav", 80);

	//float masterVolume = 0.0f;
	float masterVolume = 0.7f;
	Music::registerSong("data/music/ruins.xm", 1.0f * masterVolume);
	Music::registerSong("data/music/caves.xm", 0.8f * masterVolume);
	Music::registerSong("data/music/outside.xm", 0.7f * masterVolume);
	Music::registerSong("data/music/title.xm", 0.7f * masterVolume);
	Music::registerSong("data/music/boss.xm", 0.8f * masterVolume);
	Music::registerSong("data/music/powerup.xm", 0.8f * masterVolume);
	Music::registerSong("data/music/splash.xm", 1.0f * masterVolume);
	
	ScreenManager::add(new Title());
	//ScreenManager::add(new End());
	//ScreenManager::add(new Outro());
	ScreenManager::add(new SplashScreen());

	RoomLoader::Initialize();

	//ScreenManager::add(world);
}

void TINS12Game::onLogic()
{
	if (Input::isPressed(Button_ToggleFullscreen))
	{
		toggleFullscreen();
	}

	if (Input::isPressed(Button_ToggleSlowMotion))
	{
		toggleSlowMotion();
	}

	if (Input::isPressed(Button_ToggleVSync))
	{
		toggleVSync();
	}

	if (Input::isPressed(Button_ToggleWideScreen))
	{
		toggleWideScreen();
	}

	if (Input::isPressed(Button_ForceQuit) || ScreenManager::isEmpty())
	{
		halt();
	}
}
