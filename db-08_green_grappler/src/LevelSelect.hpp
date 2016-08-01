#pragma once

#include "Screen.hpp"

#include "LevelDescription.hpp"

class Font;
class Animation;
class Dialogue;

class LevelSelect: public Screen
{
public:
	LevelSelect();
	~LevelSelect();
	void onEntered();
	void onDraw(BITMAP* aBuffer);
	void onLogic();
	void onExited();
	static bool myBossLevelCompleted;
private:
	Font* myFont;
	Animation* myBackground;
	Animation* mySelectedLevelBackground;
	Animation* myUnselectedLevelBackground;
	Animation* myIcons;
	Animation* myCompletedIconBackground;
	Dialogue* myFirstDialogue;
	Dialogue* myBossUnlockedDialogue;
	class Particle
	{
	public:
		Particle(float x_, float y_, float z_)
			:x(x_), y(y_),z(z_)
		{

		}

		float x;
		float y;
		float z;
	};

	std::vector<Particle> myParticles;


	LevelDesc myLevelDescs[9];	
	int mySelectedX;
	int mySelectedY;
	int myFrameCounter;
	bool myLevelSelected;
	int myLevelSelectedCounter;
	bool myPlayingBossLevel;
	bool myBossLevelUnlocked;
	bool myRunFirstDialogue;
	bool myRunBossUnlockedDialogue;
	void PrivSetLevelDesc(int aX, int aY, LevelDesc aLevelDesc);
};