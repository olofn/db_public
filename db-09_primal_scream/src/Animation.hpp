#pragma once

#include "Blending.hpp"

class Animation
{
public:
	Animation(const std::string& aFilename);
	Animation(const std::string& aFilename, int aNumberOfFrames);
	~Animation();

	BITMAP *getFrame(int aFrame) const;
	int getFrameCount() const;
	int getFrameWidth() const;
	int getFrameHeight() const;
	void drawFrame(BITMAP *aBuffer, int aFrame, int aX, int aY, bool aHFlip = false, bool aVFlip = false, Blending aBlending = Blending_None) const;
	//void drawFrame(BITMAP *dest, int frame, int x, int y, bool aHFlip, int aFillColor) const;
	void drawRotatedFrame(BITMAP *aBuffer, int aFrame, int aX, int aY, int aAngle, bool aVFlip = false) const;

protected:
	void privFillFramesList(BITMAP *aAllFrames, int aCount);

	int myFrameWidth;
	int myFrameHeight;
	std::vector<BITMAP *> myFrames;
};