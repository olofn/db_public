#ifndef DB_DIALOGTILE_HPP
#define DB_DIALOGTILE_HPP

#include "tilealignedentity.hpp"
#include <string>
#include <vector>

class DialogTile: public TileAlignedEntity
{
public:
	DialogTile(int x, int y, bool solid, const std::string& stateBeforeDialog, bool atTop = true);
	void logic();
	void draw(BITMAP *dest, int scrollx, int scrolly) {}
	void drawForeground(BITMAP *dest, int scrollx, int scrolly);
	void addDialog(const std::string& text);
private:
	bool mInitialized;
	bool mSolid;
	bool mAtTop;
	std::vector<std::string> mDialogs;
	std::string mStateBeforeDialog;
};
#endif