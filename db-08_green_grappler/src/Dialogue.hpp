#pragma once

#include "Font.hpp"
#include "Entity.hpp"

class Animation;

enum CharacterPortrait
{
	CharacterPortrait_DoctorGreen,
	CharacterPortrait_Ted
};

class Dialogue
	: public Entity
{
public:
	Dialogue(std::string aFile);
	virtual int getLayer(){return 3;}
	void update();
	void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
	void setRunWithoutHero();

private:
	Font* myFont;
	Animation* myBackground;
	Animation* myDoctorGreenPortrait;
	Animation* myTedPortrait;
	struct Line
	{
		CharacterPortrait myPortrait;
		std::string myLine;
	};
	std::vector<Line> myLines;
	int myCurrentLine;
	int myCurrentCharacter;
	int myFrameCounter;
	std::string myFile;
	bool myDone;
	bool myRunning;
	bool myRunWithoutHero;
	
	void load(std::string aFile);
	void addLine(CharacterPortrait aCharacterPortrait, std::string aText);
};