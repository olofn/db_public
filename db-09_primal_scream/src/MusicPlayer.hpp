#pragma once

#include "Entity.hpp"

class MusicPlayer : public Entity
{
private:
	std::string mFile;

public:
	MusicPlayer(std::string file);
	virtual int getLayer() { return 1; };
	virtual void update();
};