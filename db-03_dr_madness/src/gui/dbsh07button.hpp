#ifndef DBSH07_BUTTON_HPP
#define DBSH07_BUTTON_HPP

#include "guichan.hpp"

class DBSH07Button : public gcn::Button
{
public:
    DBSH07Button(const std::string& caption);
    void draw(gcn::Graphics* graphics);
protected:
    gcn::ImageFont* mNormalFont;
    gcn::ImageFont* mHighLightFont;
};

#endif