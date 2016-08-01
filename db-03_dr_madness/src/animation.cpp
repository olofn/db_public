#include <allegro.h>

#include "animation.hpp"
#include "resourcehandler.hpp"

Animation::Animation(const std::string& filename) {
	BITMAP *allFrames = ResourceHandler::getInstance()->getBitmap(filename);
	mFrameWidth = mFrameHeight = allFrames->h;
	int count = allFrames->w / mFrameWidth;
	
	fillFramesList(allFrames, count);
}

Animation::Animation(const std::string& filename, int frames) {
	BITMAP *allFrames = ResourceHandler::getInstance()->getBitmap(filename);
	mFrameWidth = allFrames->w / frames;
	mFrameHeight = allFrames->h;
	int count = frames;

	fillFramesList(allFrames, count);
}

Animation::~Animation() {
	unsigned int i;
	for (i = 0; i < mFrames.size(); i++) {
		destroy_bitmap(mFrames[i]);
	}
}

BITMAP *Animation::getFrame(int frame) {
	return mFrames[frame % mFrames.size()];
}

int Animation::getFrameCount() {
	return mFrames.size();
}

int Animation::getFrameWidth() {
	return mFrameWidth;
}

int Animation::getFrameHeight() {
	return mFrameHeight;
}

void Animation::drawFrame(BITMAP *dest, int frame, int x, int y, bool hflip, bool vflip)
{
	BITMAP *src = getFrame(frame);

	if (hflip && vflip) {
		draw_sprite_vh_flip(dest, src, x, y);
	} else if (hflip && !vflip) {
		draw_sprite_h_flip(dest, src, x, y);
	} else if (!hflip && vflip) {
		draw_sprite_v_flip(dest, src, x, y);
	} else {
		draw_sprite(dest, src, x, y);
	}
	return;
}

void Animation::drawRotatedFrame(BITMAP *dest, int frame, int x, int y, int angle, bool vflip)
{
	BITMAP *src = getFrame(frame);

	if (vflip) {
		rotate_sprite_v_flip(dest, src, x, y, itofix(angle));
	} else {
		rotate_sprite(dest, src, x, y, itofix(angle));
	}
}

void Animation::fillFramesList(BITMAP *allFrames, int count)
{
	mFrames.reserve(count);
	
	int i;
	for (i = 0; i < count; i++) {
		BITMAP *frame = create_sub_bitmap(allFrames, i * mFrameWidth, 0, mFrameWidth, mFrameHeight);
		mFrames.push_back(frame);
	}
}
