#ifndef NMC_IMAGECHECKBOX_HPP
#define NMC_IMAGECHECKBOX_HPP

#include "guichan.hpp"

#include <string>

namespace nmc
{
    class ImageCheckBox: public gcn::CheckBox
    {
    public:
        ImageCheckBox(const std::string& filename);
        ~ImageCheckBox();
        void draw(gcn::Graphics* graphics);
        void drawBorder(gcn::Graphics* graphics);

    protected:
        gcn::Image* mImage;
    };
}
#endif