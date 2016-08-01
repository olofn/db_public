#include "Speedhack11Game.hpp"

#include "Constants.hpp"
#include "Input.hpp"
#include "Music.hpp"
#include "ScreenManager.hpp"
#include "Sound.hpp"
#include "Level.hpp"
#include "Title.hpp"
#include "LevelSelect.hpp"
#include "SplashScreen.hpp"
#include "End.hpp"

Speedhack11Game::Speedhack11Game()
:Game("db - Green Grappler", true)
{
	Input::registerKey(Button_ToggleFullscreen, KEY_F);
	Input::registerKey(Button_ToggleSlowMotion, KEY_S);
	Input::registerKey(Button_Exit, KEY_ESC);
	Input::registerKey(Button_ToggleVSync, KEY_V);
	Input::registerKey(Button_ToggleWideScreen, KEY_W);
	Input::registerKey(Button_Fire, KEY_LCONTROL);
	Input::registerKey(Button_Fire, KEY_X);
	Input::registerKey(Button_Fire, KEY_Z);
	Input::registerKey(Button_Fire, KEY_C);
	Input::registerKey(Button_Fire, KEY_RCONTROL);
	Input::registerKey(Button_Fire, KEY_SPACE);
	Input::registerKey(Button_Fire, KEY_ENTER);
	Input::registerKey(Button_Jump, KEY_UP);
	Input::registerKey(Button_Up, KEY_UP);
	Input::registerKey(Button_Down, KEY_DOWN);
	Input::registerKey(Button_Left, KEY_LEFT);
	Input::registerKey(Button_Right, KEY_RIGHT);
	//Input::registerKey(Button_ForceQuit, KEY_Q);
	// Xbox 360 controller
	//Input::registerJoypadButton(Button_Action, 0, 7);
	Input::registerJoypadButton(Button_Exit,  0, 6);
	Input::registerJoypadButton(Button_Jump,  0, 1);
	Input::registerJoypadButton(Button_Jump,  0, 0);
	Input::registerJoypadButton(Button_Fire,  0, 2);
	Input::registerJoypadButton(Button_Fire,  0, 3);
	Input::registerJoypadStick(Button_Left,   0, 0, 0, -1);
	Input::registerJoypadStick(Button_Right,  0, 0, 0, 1);
	Input::registerJoypadStick(Button_Up,     0, 0, 1, -1);
	Input::registerJoypadStick(Button_Down,   0, 0, 1, 1);
	Input::registerJoypadStick(Button_Left,   0, 1, 0, -1);
	Input::registerJoypadStick(Button_Right,  0, 1, 0, 1);
	Input::registerJoypadStick(Button_Up,     0, 1, 1, -1);
	Input::registerJoypadStick(Button_Down,   0, 1, 1, 1);

	Sound::registerSample("data/sounds/start.wav", 255);
	Sound::registerSample("data/sounds/beep.wav", 50);
	Sound::registerSample("data/sounds/select.wav", 150);
	Sound::registerSample("data/sounds/jump.wav", 255);
	Sound::registerSample("data/sounds/hook.wav", 255);
	Sound::registerSample("data/sounds/rope.wav", 100);
	Sound::registerSample("data/sounds/land.wav", 255);
	Sound::registerSample("data/sounds/no_hook.wav", 150);
	Sound::registerSample("data/sounds/damage.wav", 255);
	Sound::registerSample("data/sounds/coin.wav", 100);
	Sound::registerSample("data/sounds/alarm.wav", 200);
	Sound::registerSample("data/sounds/reactor_explosion.wav", 255);
	Sound::registerSample("data/sounds/time.wav", 255);
	Sound::registerSample("data/sounds/timeout.wav", 100);
	Sound::registerSample("data/sounds/hurt.wav", 255);
	Sound::registerSample("data/sounds/boot.wav", 255);
	Sound::registerSample("data/sounds/boss_saw.wav", 200);
	Sound::registerSample("data/sounds/green_peace.wav", 255);

	float masterVolume = 1.0f;
	Music::registerSong("data/music/splash.xm", 1.0f * masterVolume);
	Music::registerSong("data/music/intro2.xm", 2.0f * masterVolume);
	Music::registerSong("data/music/olof3.xm", 1.0f * masterVolume);
	Music::registerSong("data/music/olof9.xm", 1.0f * masterVolume);
	Music::registerSong("data/music/olof8.xm", 1.0f * masterVolume);
	Music::registerSong("data/music/olof12.xm", 1.5f * masterVolume);
	Music::registerSong("data/music/olof2-rmx.xm", 1.0f * masterVolume);
	Music::registerSong("data/music/spooky.xm", 2.5f * masterVolume);
	Music::registerSong("data/music/level_select.xm", 1.0f * masterVolume);
	Music::registerSong("data/music/level_completed.xm", 1.0f * masterVolume);
	
	ScreenManager::add(new Title());
	ScreenManager::add(new SplashScreen());
}

void Speedhack11Game::onLogic()
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
