#pragma once

class LevelDesc
{
public:
	LevelDesc()
	{}
	LevelDesc( std::string aName, std::string aLevelFile, int aFrameIndex, std::string aMusicFile)
		: myName(aName), myLevelFile(aLevelFile), myFrameIndex(aFrameIndex), myMusicFile(aMusicFile)
	{}
	std::string myName;
	std::string myLevelFile;
	int myFrameIndex;
	std::string myMusicFile;
};