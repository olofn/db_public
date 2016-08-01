#ifndef RESOURCEHANLDER_HPP
#define RESOURCEHANLDER_HPP

#include <allegro.h>
#include <map>
#include <string>

class ResourceHandler
{
public:
    static ResourceHandler* getInstance();
    void destroy();
    BITMAP* getBitmap(const std::string& filename);
	SAMPLE* getSample(const std::string& filename);
    std::string getRealFilename(const std::string& filename);
    
private:
    ResourceHandler();
    static ResourceHandler* mInstance;
    std::map<std::string, BITMAP*> mBitmaps;
	std::map<std::string, SAMPLE*> mSamples;
};
#endif

