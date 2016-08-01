#include "Dialogue.hpp"
#include "Resource.hpp"

#include "Animation.hpp"
#include "Util.hpp"
#include "Sound.hpp"
#include "GameState.hpp"
#include "Room.hpp"
#include "Hero.hpp"

Dialogue::Dialogue(std::string aFile)
: myCurrentLine(0)
, myCurrentCharacter(0)
, myFrameCounter(0)
, myFile(aFile)
, myDone(false)
, myRunning(false)
, myRunWithoutHero(false)
{
	myFont = Resource::getFont("data/images/font.bmp");
	myBackground = Resource::getAnimation("data/images/dialogue.bmp", 1);
	myTedPortrait = Resource::getAnimation("data/images/ted_portrait.bmp", 1);
	myDoctorGreenPortrait = Resource::getAnimation("data/images/doctor_green_portrait.bmp", 1);

	std::string key = "dialogue_";
	key += myFile;
	if (GameState::getInt(key) == 1)
	{
		myDone = true;
		remove();
	}

	load(aFile);

	setSize(float2(10, 10 * 200));
}

void Dialogue::draw( BITMAP *buffer, int offsetX, int offsetY, int layer )
{	
	//Entity::draw(buffer, offsetX, offsetY, layer);

	if (myDone)
		return;

	if (!myRunning)
		return;

	myBackground->drawFrame(buffer, 0, 0, 240 - myBackground->getFrameHeight());
	CharacterPortrait portrait = myLines[myCurrentLine].myPortrait;
	std::string line = myLines[myCurrentLine].myLine;

	int pX = 4;
	int pY = 240 - myTedPortrait->getFrameHeight() - 3;
	if (portrait == CharacterPortrait_Ted)
		myTedPortrait->drawFrame(buffer, 0, pX, pY);
	if (portrait == CharacterPortrait_DoctorGreen)
		myDoctorGreenPortrait->drawFrame(buffer, 0, pX, pY);

	myFont->drawWrap(buffer, line, 55, 240 - 16, 300, myCurrentCharacter);
}

void Dialogue::update()
{
	if (myDone)
		return;

	if (!myRunWithoutHero)
	{
		if (Collides(mRoom->getHero()->getCollisionRect(), getCollisionRect()))
		{
			myRunning = true;
		}
	}

	if (!myRunning)
		return;

	myFrameCounter++;

	Line line = myLines[myCurrentLine];

	if (myFrameCounter > 2
		&& myCurrentCharacter < (int)line.myLine.size())
	{
		myCurrentCharacter++;
		myFrameCounter = 0;
		Sound::playSample("data/sounds/beep.wav");
	}

	if (myFrameCounter > 90
		&& (int)myLines.size() > myCurrentLine)
	{
		myCurrentLine++;
		myCurrentCharacter = 0;
		myFrameCounter = 0;

		if (myLines.size() == myCurrentLine)
		{
			myLines.clear(); // We are done!
			std::string key = "dialogue_";
			key += myFile;
			GameState::put(key, 1);
			myDone = true;
			if (!myRunWithoutHero)
				remove();
		}
	}
}

void Dialogue::addLine( CharacterPortrait aCharacterPortrait, std::string aLine )
{
	Line line;
	line.myLine = aLine;
	line.myPortrait = aCharacterPortrait;
	myLines.push_back(line);
}

void Dialogue::load( std::string aFile )
{
	std::string dialogueFileString = loadFile(aFile);
	std::vector<std::string> lines = tokenize(dialogueFileString, "\n", true);

	for (unsigned int i = 0; i < lines.size(); i++)
	{
		char character = lines[i].at(0);
		CharacterPortrait portrait;
		if (character == 'D')
			portrait = CharacterPortrait_DoctorGreen;
		else if (character == 'T')
			portrait = CharacterPortrait_Ted;
		else
			throw std::string("Unknown portrait! ") + std::string(""+character);

		std::string line = lines[i].substr(2, lines[i].size());
		addLine(portrait, line);
	}
}

void Dialogue::setRunWithoutHero()
{
	myRunWithoutHero = true;
	myRunning = true;
}
