#ifndef DB_ACTOR_HPP
#define DB_ACTOR_HPP

#include "entity.hpp"
#include "animation.hpp"
#include <string>
#include <map>

class Actor: public Entity
{
public:
	Actor(Entity::Type type,
		  int x,
		  int y,
		  int width,
		  int height,
		  bool coollidable);
	~Actor();
	bool move();
	bool move(int x, int y);
	void draw(BITMAP *dest, int scrollx, int scrolly);
	void setState(const std::string& name); 
	std::string getCurrentStateName();
	void setCheckForCollisions(bool check);
	Direction getDirection();
	void flash(int frames = 6);
	void blink(int frames = 6);
	void setVisible(bool visible);

protected:
	void addState(const std::string& name,
			      Animation* animation,
				  int x,
				  int y,
				  int delay,
				  Direction direction,
				  bool hflip,
				  bool vflip);
private:
	class State
	{
	public:
		Animation* animation;
		int x;
		int y;
		int delay;
		Direction direction;
		bool hflip;
		bool vflip;
	};
	State* mState;
	std::map<std::string, State> mStates;
	int mAnimationFrame;
	int mFrameCounter;
	bool mCheckForCollisions;
	Direction mDirection;
	int mFlashFrames;
	int mBlinkFrames;
	std::string mCurrentStateName;
	bool mVisible;
};

#endif
