#ifndef DB_DBCONTAINER_HPP
#define DB_DBCONTAINER_HPP

#include "guichan.hpp"
#include <allegro.h>

class DbContainer : public gcn::Container
{
public:
    DbContainer();
    ~DbContainer();

    void draw(gcn::Graphics *graphics);

private:
    gcn::Image* mCornerUL;
    gcn::Image* mCornerUR;
    gcn::Image* mCornerDL;
    gcn::Image* mCornerDR;
    gcn::Image* mHorizontal;
    gcn::Image* mVertical;
};

#endif
