#ifndef DBSH07_ANIMATION_HPP
#define DBSH07_ANIMATION_HPP

#include <vector>
#include <allegro.h>

class Animation
{
public:
	Animation(const std::string& filename);

	Animation(const std::string& filename, int frames);

	~Animation();

	BITMAP *getFrame(int frame);

	int getFrameCount();

	int getFrameWidth();

	int getFrameHeight();

	void drawFrame(BITMAP *dest, int frame, int x, int y, bool hflip = false, bool vflip = false);

	void drawRotatedFrame(BITMAP *dest, int frame, int x, int y, int angle, bool vflip = false);

protected:
	void fillFramesList(BITMAP *allFrames, int count);

	int mFrameWidth, mFrameHeight;
	std::vector<BITMAP *> mFrames;
};


#endif