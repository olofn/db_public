#ifndef DBSH07_ANIMATION_HPP
#define DBSH07_ANIMATION_HPP

#include <string>
#include <vector>
#include <allegro.h>

class Animation
{
public:
	Animation(const std::string& filename);

	Animation(const std::string& filename, int frames);

	~Animation();

	enum Blending 
    {
		NONE, 
		ADD,
		FROZEN,
		LIGHTEN
	};

	BITMAP *getFrame(int frame) const;

	int getFrameCount() const;

	int getFrameWidth() const;

	int getFrameHeight() const;

	void drawFrame(BITMAP *dest, int frame, int x, int y, bool hflip = false, bool vflip = false, Blending blending = NONE) const;

	void drawRotatedFrame(BITMAP *dest, int frame, int x, int y, int angle, bool vflip = false) const;

protected:
	void fillFramesList(BITMAP *allFrames, int count);

	int mFrameWidth, mFrameHeight;
	std::vector<BITMAP *> mFrames;
};


#endif
