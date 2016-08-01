#ifndef NMC_CRACKINTRO_HPP
#define NMC_CRACKINTRO_HPP

#include <allegro.h>
#include <vector>

namespace nmc
{
    class CrackIntro
    {
    public:
        CrackIntro();
		~CrackIntro();
        void logic();
        void draw(BITMAP* dest);
        bool isDrawingDone();
    protected:
		void rotoZoom(BITMAP *dest, float angle, float scale, int ystart);
		void drawLogo();
		void drawScroller();
		void drawString(char *s, int x, int y);
		void drawLetter(char letter, int x, int y);
        int mFrameCounter;

		BITMAP *mBuffer;
		BITMAP *mRotoZoom;
		BITMAP *mLogo;
		BITMAP *mFont;

		std::vector<int> mStarX;
		std::vector<int> mStarY;
    };
}
#endif