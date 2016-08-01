#ifndef DBSH07_DECORATEDCONTAINER_HPP
#define DBSH07_DECORATEDCONTAINER_HPP

#include "guichan.hpp"

class DecoratedContainer: public gcn::Container
{
public:
    DecoratedContainer();
    ~DecoratedContainer();
    void draw(gcn::Graphics* graphics);
    gcn::Rectangle getChildrenArea();

protected:
    gcn::Image* mCornerUL;
    gcn::Image* mCornerUR;
    gcn::Image* mCornerDL;
    gcn::Image* mCornerDR;
    gcn::Image* mHorizontal;
    gcn::Image* mVertical;
};

#endif