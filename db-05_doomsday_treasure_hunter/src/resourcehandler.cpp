#include "resourcehandler.hpp"
#include "os.hpp"
#include "exception.hpp"

ResourceHandler* ResourceHandler::mInstance = 0;

ResourceHandler::ResourceHandler()
{

}

ResourceHandler* ResourceHandler::getInstance()
{
    if (mInstance == 0)
    {
        mInstance = new ResourceHandler();
    }

    return mInstance;
}

void ResourceHandler::destroy()
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
}

BITMAP* ResourceHandler::getBitmap(const std::string &filename)
{
    if (mBitmaps.find(filename) == mBitmaps.end())
    {
	    BITMAP* bitmap = load_bitmap(getRealFilename(filename).c_str(), NULL);
	    
        if (bitmap == NULL) 
        {
			throw DB_EXCEPTION("Unable to load: " + getRealFilename(filename));
	    }

        mBitmaps[filename] = bitmap;
    }

    return mBitmaps[filename];
}


SAMPLE* ResourceHandler::getSample(const std::string& filename)
{
    if (mSamples.find(filename) == mSamples.end())
    {
	    SAMPLE* sample = load_sample(getRealFilename(filename).c_str());
	    
        if (sample == NULL) 
        {
            throw DB_EXCEPTION("Unable to load: " + getRealFilename(filename));
	    }

        mSamples[filename] = sample;
    }

    return mSamples[filename];
}

std::string ResourceHandler::getRealFilename(const std::string& filename)
{
    return std::string(DB_DATA_PREFIX) + filename;
}

