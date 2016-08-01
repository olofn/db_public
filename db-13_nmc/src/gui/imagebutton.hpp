#ifndef NMC_IMAGEBUTTON_HPP
#define NMC_IMAGEBUTTON_HPP

#include "guichan.hpp"

#include <string>

namespace nmc
{
    class ImageButton : public gcn::Button
    {
    public:
        ImageButton(const std::string& filename);
        ~ImageButton();
        void draw(gcn::Graphics* graphics);

    protected:
        gcn::Image* mImage;
    };
}
#endif