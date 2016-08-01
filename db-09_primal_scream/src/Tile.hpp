#pragma once

class Tile
{
public:
	Tile(BITMAP* aTilemap, int aX, int aY, int aH, int aW);

	Tile();	

	void onDraw(
		BITMAP* aBuffer,
		int		aX,
		int		aY);

	int	 getWidth();

	int	 getHeight();

	void setCollide(bool aCollide);

	bool getCollide();

	void setDangerous(bool aDangerous);

	bool getDangerous();

private:
	BITMAP*		mTilemap;
	int			mX;
	int			mY;
	int			mW;
	int			mH;

	//Properties
	bool mCollide;
	bool mDangerous;
};