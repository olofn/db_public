#include "Game.hpp"

#include "Input.hpp"
#include "Music.hpp"
#include "Resource.hpp"
#include "ScreenManager.hpp"
#include "Sound.hpp"
#include "Time.hpp"

Game::Game(const std::string& aTitle, bool windowed)
	: myRunning(true)
	, mySlowMotion(false)
	, myVSync(true)
    , myWindowed(windowed)
	, myTitle(aTitle)
	, myWideScreen(false)
{
    allegro_init();
	
	Sound::init();
	Input::init();
	Resource::init();
	Music::init();
	Time::init();
	ScreenManager::init();
	
	initGraphics(windowed);
}

Game::~Game()
{
	ScreenManager::destroy();
	Resource::destroy();

	destroy_bitmap(myScreenBuffer);
}

void Game::initGraphics(bool windowed)
{
	privChangeResolution(windowed);

	myScreenBuffer = create_bitmap(320, 240);
	rectfill(myScreenBuffer, 0, 0, 320, 240, 0);
	setTitle(myTitle.c_str());
}

void Game::run()
{
#ifndef _DEBUG
 	try
 	{
#endif
		long frame = Time::getTick();
		int second = Time::getTick() / Time::TicksPerSecond;
		int framesPerSecond = 0;

		while (myRunning != false) 
		{
			static int tmp = 0;
			tmp++;
			if (tmp % 5 == 0 || !mySlowMotion)
			{
				Input::onLogic();
				ScreenManager::onLogic();
				onLogic();
				Music::onLogic();
				Sound::onLogic();
			}

			if (Time::getTick() - frame > 20)
			{
				frame = Time::getTick();
				std::cout << "Logic frame drop! =(" << std::endl;
			}

			frame++;

			if (frame > Time::getTick())
			{
				ScreenManager::draw(myScreenBuffer);
				if (myVSync)
				{
					vsync();
				}
				if (!myWindowed && myWideScreen)
				{
 					int x = myResolutionWidth / 2 - (int)(myResolutionHeight * 4.0f / 3.0f) / 2;				
 					stretch_blit(myScreenBuffer, screen, 0, 0, 320, 240, x, 0, myResolutionWidth - x*2, myResolutionHeight);
				}
				else
				{
					stretch_blit(myScreenBuffer, screen, 0, 0, 320, 240, 0, 0, myResolutionWidth, myResolutionHeight);
				}
				

				framesPerSecond++;
			}

			while (frame > Time::getTick()) 
			{
				rest(frame - Time::getTick());
			}

			if (second != Time::getTick() / Time::TicksPerSecond) 
			{	
				second = Time::getTick() / Time::TicksPerSecond;
				std::cout << "FPS=" << framesPerSecond << std::endl;
				framesPerSecond = 0;
			}
		}
#ifndef _DEBUG
	}
	catch (std::string e)
	{
		std::string str;
        std::ostringstream os(str);
		os << "An exception occured: \"" << e << "\".";
        allegro_message(e.c_str());
	}
	catch (std::exception e)
	{
        std::string str;
        std::ostringstream os(str);
		os << "An STD exception occured: \"" << e.what() << "\".";
        allegro_message(os.str().c_str());
	}
    catch (...)
	{
        std::string error = "An unknown exception occured (this is generally very bad).";
        allegro_message(error.c_str());
	}
#endif
}

void Game::halt()
{
	myRunning = false;
}

void Game::setTitle(const char*	format, ...)
{
	char buffer[4096];

	va_list lst;
	va_start(lst, format);
	vsprintf_s(buffer, 4096, format, lst);
	va_end(lst);

	set_window_title(buffer);
}

void Game::toggleSlowMotion()
{
	mySlowMotion = !mySlowMotion;
}

void Game::toggleVSync()
{
	myVSync = !myVSync;

	if (myVSync)
	{
		setTitle("%s | vsync", myTitle.c_str());
	}
	else
	{
		setTitle("%s", myTitle.c_str());
	}
}

void Game::toggleFullscreen()
{
	privChangeResolution(!myWindowed);

	myScreenBuffer = create_bitmap(320, 240);
}

void Game::toggleWideScreen()
{
	myWideScreen = !myWideScreen;

	privChangeResolution(myWindowed);

	myScreenBuffer = create_bitmap(320, 240);
}

void Game::privChangeResolution( bool aWindowed )
{
	myWindowed = aWindowed;
	int driver;

	if (myWindowed)
	{
		driver = GFX_AUTODETECT_WINDOWED;
		myResolutionWidth = 640;
		myResolutionHeight = 480;
	}
	else
	{
		driver = GFX_AUTODETECT_FULLSCREEN;
		if (myWideScreen)
		{
			myResolutionWidth = 1280;
			myResolutionHeight = 720;
		}
		else
		{
			myResolutionWidth = 640;
			myResolutionHeight = 480;
		}
	}

	set_color_depth(32);
	if (set_gfx_mode(driver, myResolutionWidth, myResolutionHeight, 0, 0) < 0) {
		set_color_depth(24);
		if (set_gfx_mode(driver, myResolutionWidth, myResolutionHeight, 0, 0) < 0) {
			set_color_depth(16);
			if (set_gfx_mode(driver, myResolutionWidth, myResolutionHeight, 0, 0) < 0) {
				set_color_depth(15);
				if (set_gfx_mode(driver, myResolutionWidth, myResolutionHeight, 0, 0) < 0) 
				{
					throw std::string("Unable to set graphics mode.");
				}
			}
		}
	}
}
