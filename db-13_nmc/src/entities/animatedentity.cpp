#include "entities/animatedentity.hpp"	

namespace nmc
{
	AnimatedEntity::AnimatedEntity(int x, int y, const std::string& filename, int speed, int layer, bool once, Animation::Blending blending)
        : Entity(x, y),
          mAnimation(filename),
          mSpeed(speed),
          mFrameCounter(0),
		  mLayer(layer),
		  mOnce(once),
		  mBlending(blending)
    {
		
    }

	AnimatedEntity::AnimatedEntity(int x, int y, const std::string& filename, int framecount, int speed, int layer, bool once, Animation::Blending blending)
        : Entity(x, y),
          mAnimation(filename, framecount),
          mSpeed(speed),
          mFrameCounter(0),
		  mLayer(layer),
		  mOnce(once),
		  mBlending(blending)
    {
		
    }

    void AnimatedEntity::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
    {
        mAnimation.drawFrame(dest, mFrameCounter / mSpeed, mX - scrollx, mY - scrolly, false, false, mBlending);
    }

    void AnimatedEntity::logic(Room *room)
    {
        mFrameCounter++;
    }
	
	bool AnimatedEntity::isToBeDeleted()
	{
		return mOnce && mAnimation.getFrameCount() <= (mFrameCounter / mSpeed);
	}

	bool AnimatedEntity::drawInLayer(unsigned int layer)
	{ 
		return layer == mLayer;
	}
}