#ifndef DBSH07_DIALOG_HPP
#define DBSH07_DIALOG_HPP

#include "guichan.hpp"
#include <allegro.h>

class Dialog : public gcn::Widget, public gcn::KeyListener, public gcn::MouseListener
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

    void mousePressed(gcn::MouseEvent& mouseEvent);

    void mouseReleased(gcn::MouseEvent& mouseEvent);

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

    SAMPLE* mBeepSample;

    gcn::Image* mBomb;
    gcn::Image* mFluffyLove;
    gcn::Image* mFluffyLoveAngry;
    gcn::Image* mCuddelz;
    gcn::Image* mDoctorMad;

    enum
    {
        NONE,
        BOMB,
        FLUFFY_LOVE,
        CUDDELZ,
        DOCTOR_MAD,
        FLUFFY_LOVE_ANGRY
    };

    unsigned int mCharacter;
};

#endif
