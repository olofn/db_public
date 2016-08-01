#include <cmath>

#include "crackintro.hpp"
#include "resourcehandler.hpp"

namespace nmc
{
	CrackIntro::CrackIntro() :
        mFrameCounter(0)
    {
		mRotoZoom = ResourceHandler::getInstance()->getBitmap("cracktro/rotozoom.bmp");
		mLogo = ResourceHandler::getInstance()->getBitmap("cracktro/darkbits.bmp");
		mFont = ResourceHandler::getInstance()->getBitmap("cracktro/font.bmp");
		mBuffer = create_bitmap(160, 120);

		int i;

		for (i = 0; i < 100; i++)
		{
			mStarX.push_back(rand() % 160);
			mStarY.push_back(rand() % 85 + 17);
		}
    }

	CrackIntro::~CrackIntro()
	{
		destroy_bitmap(mBuffer);
	}

    void CrackIntro::logic()
    {
        mFrameCounter++;
    }

    void CrackIntro::draw(BITMAP* dest)
    {
		clear_to_color(mBuffer, makecol(0,0,0));

		float angle = mFrameCounter / 80.0f;
		float scale = 1 / (sin(mFrameCounter / 17.0f) + 2);
		rotoZoom(mBuffer, angle, scale, 0);
		rotoZoom(mBuffer, angle, scale, 104);
		drawLogo();

		int i;
		int starcolor = makecol(rand() % 256, rand() % 256, rand() % 256);
		for (i = 0; i < 100; i++)
		{
			int x = mStarX[i];
			int y = mStarY[i];
			if (i < 20)
			{
				x += mFrameCounter / 3;
			}
			else if (i < 50)
			{
				x += mFrameCounter / 2;
			}
			else
			{
				x += mFrameCounter;
			}

			if (getpixel(mBuffer, x % 160, y) == 0)
			{
				putpixel(mBuffer, x % 160, y, starcolor);
			}
		}

		drawString("PRESENTS", 56, 48);
		drawString("NODAJOS MECHANICAL CASTLE", 5, 62);

		drawScroller();

		stretch_blit(mBuffer, dest, 0, 0, 160, 120, 0, 0, 640, 480);
    }

	void CrackIntro::drawScroller()
	{
		std::string text("TIME FOR ANOTHER DARKBITS RELEASE"
			             "   ..:NODAJOS MECHANICAL CASTLE:..   "
		                 "AN EPIC ADVENTURE GAME CRACKED BY THE ELITE DARKBITS TEAM.   "
						 "VISIT HTTP://WWW.DARKBITS.ORG/ FOR MORE QUALITY WAREZ.   "
                         "GREETZ FLY OUT TO :: ASTROLITE :: PEEKABOO :: MACCAN :: KB :: HAIKO :: OMENDREC :: "
                         "THE ATOMDELTA CREW :: "
                         "ALL COOL PEOPLEZ AT ALLEGRO.CC :: TED STEEN :: ARCHMIFFO :: FIGUREHEAD :: T. HARJE :: "
                         "AND OF COURSE NODAJO ::   ........................   "
						 "ENJOY THE GAME                                                                                  "
						 "YEAH I KNOW. THIS INTRO IS IMPRESSIVE...");

		unsigned int i;
		int start = (mFrameCounter - 180) / 7;

		if (start < 0)
		{
			start = 0;
		}

		for (i = start; i < text.size(); i++)
		{
			int x = 180 - mFrameCounter + i * 7;
			
			if (x > 160)
			{
				break;
			}

			int y = 96 - std::abs(sin(x / 20.0 - mFrameCounter / 17.0)) * 18;
			drawLetter(text[i], x, y);
		}
	}

    bool CrackIntro::isDrawingDone()
    {
        return key[KEY_ESC] || key[KEY_SPACE] || key[KEY_ALT] || key[KEY_ENTER];
    }

	void CrackIntro::rotoZoom(BITMAP *dest, float angle, float scale, int ystart)
	{
		float co = std::cos(angle) * scale;
		float si = std::sin(angle) * scale;
		int x, y;
		for (y = ystart; y < 16 + ystart; y++)
		{
			for (x = 0; x < dest->w; x++)
			{
				float sx = (x - 80) * co - (y - 60) * si;
				float sy = (x - 80) * si + (y - 60) * co;
				int c = getpixel(mRotoZoom, (int)(sx + 100000) & 15, (int)(sy + 100000) & 15);
				putpixel(dest, x, y, c);
			}
		}
	}

	void CrackIntro::drawLogo()
	{

		int rasterPos;

		rectfill(mBuffer, 0, 16, 160, 47, makecol(16, 0, 0));

		rasterPos = sin((mFrameCounter - 16) / 10.0f) * 10 + 32;
		hline(mBuffer, 0, rasterPos - 3, 160, makecol(0, 64, 0));
		hline(mBuffer, 0, rasterPos - 2, 160, makecol(0, 128, 0));
		hline(mBuffer, 0, rasterPos - 1, 160, makecol(0, 192, 0));
		hline(mBuffer, 0, rasterPos, 160, makecol(0, 255, 0));
		hline(mBuffer, 0, rasterPos + 1, 160, makecol(0, 192, 0));
		hline(mBuffer, 0, rasterPos + 2, 160, makecol(0, 128, 0));
		hline(mBuffer, 0, rasterPos + 3, 160, makecol(0, 64, 0));

		rasterPos = sin((mFrameCounter - 8) / 10.0f) * 10 + 32;
		hline(mBuffer, 0, rasterPos - 3, 160, makecol(0, 0, 64));
		hline(mBuffer, 0, rasterPos - 2, 160, makecol(0, 0, 128));
		hline(mBuffer, 0, rasterPos - 1, 160, makecol(0, 0, 192));
		hline(mBuffer, 0, rasterPos, 160, makecol(0, 0, 255));
		hline(mBuffer, 0, rasterPos + 1, 160, makecol(0, 0, 192));
		hline(mBuffer, 0, rasterPos + 2, 160, makecol(0, 0, 128));
		hline(mBuffer, 0, rasterPos + 3, 160, makecol(0, 0, 64));

		rasterPos = sin(mFrameCounter / 10.0f) * 10 + 32;
		hline(mBuffer, 0, rasterPos - 3, 160, makecol(64, 0, 0));
		hline(mBuffer, 0, rasterPos - 2, 160, makecol(128, 0, 0));
		hline(mBuffer, 0, rasterPos - 1, 160, makecol(192, 0, 0));
		hline(mBuffer, 0, rasterPos, 160, makecol(255, 0, 0));
		hline(mBuffer, 0, rasterPos + 1, 160, makecol(192, 0, 0));
		hline(mBuffer, 0, rasterPos + 2, 160, makecol(128, 0, 0));
		hline(mBuffer, 0, rasterPos + 3, 160, makecol(64, 0, 0));

		draw_sprite(mBuffer, mLogo, 0, 16);
		hline(mBuffer, 0, 16, 159, makecol(154, 187, 204));
		hline(mBuffer, 0, 103, 159, makecol(154, 187, 204));
	}

	void CrackIntro::drawString(char *s, int x, int y)
	{
		while (*s)
		{
			drawLetter(*s, x, y);
			x+=6;
			s++;
		}
	}

	void CrackIntro::drawLetter(char letter, int x, int y)
	{
		int l;

		if (letter == '.')
		{
			l = 26;
		}
		else if (letter == '/')
		{
			l = 27;
		}
		else if (letter == ':')
		{
			l = 28;
		}
		else
		{
			l = letter - 'A';
		}

		if (l < 0 || l > 28)
		{
			return;
		}

		masked_blit(mFont, mBuffer, l * 6, 0, x, y, 6, 8);
	}
}