#ifndef BALLZ_BALLZSCROLLAREA_HPP
#define BALLZ_BALLZSCROLLAREA_HPP

#include <guichan.hpp>

class DbScrollArea : public gcn::ScrollArea
{
public:
	DbScrollArea();
	void draw(gcn::Graphics *graphics);
};

#endif
