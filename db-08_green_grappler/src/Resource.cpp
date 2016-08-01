#include "Precompiled.hpp"
#include "Resource.hpp"
#include "Util.hpp"
#include "Font.hpp"
#include "Animation.hpp"

std::map<std::string, BITMAP*> Resource::mBitmaps;
std::map<std::string, SAMPLE*> Resource::mSamples;
std::map<std::string, Font*> Resource::mFonts;
std::map<std::string, Animation*> Resource::myAnimations;

Resource::Resource()
{

}

void Resource::init()
{

}

void Resource::destroy()
{
    std::map<std::string, BITMAP*>::iterator it;
    for (it = mBitmaps.begin(); it != mBitmaps.end(); it++)
    {
        destroy_bitmap((*it).second);
    }

	std::map<std::string, SAMPLE*>::iterator it2;
    for (it2 = mSamples.begin(); it2 != mSamples.end(); it2++)
    {
        destroy_sample((*it2).second);
    }

	std::map<std::string, Font*>::iterator it3;
	for (it3 = mFonts.begin(); it3 != mFonts.end(); it3++)
	{
		delete (*it3).second;
	}

	std::map<std::string, Animation*>::iterator it4;
	for (it4 = myAnimations.begin(); it4 != myAnimations.end(); it4++)
	{
		delete (*it4).second;
	}
}

BITMAP* Resource::getBitmap(const std::string &filename) {
	return getBitmap(filename, makecol(255, 255, 255));
}

BITMAP* Resource::getBitmap(const std::string &filename, unsigned int color)
{
	std::string key = filename + toString(color);

	if (mBitmaps.find(key) == mBitmaps.end())
    {
	    BITMAP* bitmap = load_bitmap(getRealFilename(filename).c_str(), NULL);
		
		if (bitmap == NULL) 
		{
			throw std::string("Unable to load: ") + getRealFilename(filename);
		}

		unsigned int colorR = getr(color);
		unsigned int colorG = getg(color);
		unsigned int colorB = getb(color);
		unsigned int magicPink = makecol(255, 0, 255);

		for(int y = 0; y < bitmap->h; ++y) {
			for(int x = 0; x < bitmap->w; ++x) {
				unsigned int c = getpixel(bitmap, x, y);
				if(c != magicPink) {
					unsigned int r = getr(c);
					unsigned int g = getg(c);
					unsigned int b = getb(c);

					r = (colorR * r) / 255;
					g = (colorG * g) / 255;
					b = (colorB * b) / 255;
					c = makecol(r, g, b);

					putpixel(bitmap, x, y, c);
				}
			}
		}



        mBitmaps[key] = bitmap;
    }

    return mBitmaps[key];
}


SAMPLE* Resource::getSample(const std::string& filename)
{
    if (mSamples.find(filename) == mSamples.end())
    {
	    SAMPLE* sample = load_sample(getRealFilename(filename).c_str());
	    
        if (sample == NULL) 
        {
			throw std::string("Unable to load: " + getRealFilename(filename));
	    }

        mSamples[filename] = sample;
    }

    return mSamples[filename];
}

std::string Resource::getRealFilename(const std::string& filename)
{
    return filename;
}

Font* Resource::getFont( const std::string& filename ) {
	return getFont(filename, makecol(255, 255, 255));
}

Font* Resource::getFont( const std::string& filename, unsigned int textColor )
{
	std::string key = filename + toString(textColor);
	if (mFonts.find(key) == mFonts.end())
	{
		Font* font = new Font(getBitmap(filename, textColor), ' ', 'z');

		mFonts[key] = font;
	}

	return mFonts[key];
}

Animation* Resource::getAnimation( const std::string& filename, int aFrames )
{
	std::string key = filename + toString(aFrames);
	if(myAnimations.find(key) == myAnimations.end()) {
		Animation* animation = new Animation(filename, aFrames);
		myAnimations[key] = animation;
	}

	return myAnimations[key];
}

Animation* Resource::getAnimation( const std::string& filename )
{
	std::string key = filename;
	if(myAnimations.find(key) == myAnimations.end()) {
		Animation* animation = new Animation(filename);
		myAnimations[key] = animation;
	}

	return myAnimations[key];
}
