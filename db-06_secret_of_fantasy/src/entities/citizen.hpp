#ifndef DB_CITIZEN_HPP
#define DB_CITIZEN_HPP

#include "tilealignedentity.hpp"
#include "animation.hpp"
#include <vector>
#include <string>

class Citizen: public TileAlignedEntity
{
public:
	Citizen(int x, int y, bool dialogAtTop = true);
	~Citizen();
	void logic();
	void draw(BITMAP *dest, int scrollx, int scrolly);
	void addDialog(const std::string& text);
private:
	Animation mAnimation;
	int mFrameCounter;
	bool mInitialized;
	std::vector<std::string> mDialogs;
	bool mDialogAtTop;
};
#endif