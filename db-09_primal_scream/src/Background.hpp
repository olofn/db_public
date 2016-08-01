#include "Entity.hpp"

class Background : public Entity
{
	int color;
	BITMAP *layer1;
	BITMAP *layer2;

public:
	Background(char *layer1Image, char *layer2Image, int color);

	virtual int getLayer() { return 0; };

	virtual void draw(BITMAP *buffer, int offsetX, int offsetY, int layer);
};