#ifndef NMC_DIALOG_HPP
#define NMC_DIALOG_HPP

#include "guichan.hpp"
#include <allegro.h>

namespace nmc
{
    class Dialog : public gcn::Widget, public gcn::KeyListener
    {
    public:
	    Dialog();
        ~Dialog();

	    void draw(gcn::Graphics *graphics);

	    void setText(const std::string &text);

	    const std::string &getText();

        void logic();

        void keyPressed(gcn::KeyEvent& keyEvent);

        void keyReleased(gcn::KeyEvent& keyEvent);

        void setVisible(bool visible);

    private:
    	std::string mText;
    	int mLettersWritten;
        gcn::Image* mImage; 
        int mFrameCounter;
        int mWriteSpeed;
        bool mWriteFast;

        gcn::Image* mCornerUL;
        gcn::Image* mCornerUR;
        gcn::Image* mCornerDL;
        gcn::Image* mCornerDR;
        gcn::Image* mHorizontal;
        gcn::Image* mVertical;
        gcn::ImageFont* mFont;
    };
}

#endif
