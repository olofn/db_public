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

	void setCollide(
		bool aCollide);

	bool getCollide();

	void setHook(
		bool aHook);

	bool getHook();

private:
	BITMAP*		mTilemap;
	int			mX;
	int			mY;
	int			mW;
	int			mH;

	//Properties
	bool mCollide;
	bool mHook;
};