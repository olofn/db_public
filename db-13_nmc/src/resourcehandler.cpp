/*
 * Copyright (c) 2007, Olof Naessen and Per Larsson
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 *    * Redistributions of source code must retain the above copyright notice, 
 *      this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright notice, 
 *      this list of conditions and the following disclaimer in the documentation 
 *      and/or other materials provided with the distribution.
 *    * Neither the name of the Darkbits nor the names of its contributors may be 
 *      used to endorse or promote products derived from this software without 
 *      specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "resourcehandler.hpp"

#include "exception.hpp"
#include "os.hpp"
#include "stringutil.hpp"
#include "tilemap.hpp"

#include <iostream>

namespace nmc
{
    ResourceHandler* ResourceHandler::mInstance = 0;

    ResourceHandler::ResourceHandler()
    {
        loadRooms();
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

        std::map<int, BITMAP*>::iterator it3;

        for (it3 = mRoomEntitiesBitmaps.begin(); it3 != mRoomEntitiesBitmaps.end(); it3++)
        {
            destroy_bitmap((*it3).second);
        }

        for (it3 = mRoomTilesBitmaps.begin(); it3 != mRoomTilesBitmaps.end(); it3++)
        {
            destroy_bitmap((*it3).second);
        }
    }

    BITMAP* ResourceHandler::getBitmap(const std::string& filename)
    {
        if (mBitmaps.find(filename) == mBitmaps.end())
        {
            set_color_conversion(COLORCONV_KEEP_ALPHA | COLORCONV_KEEP_TRANS);
	        BITMAP* bitmap = load_bitmap(getRealFilename(filename).c_str(), NULL);
    	    
            if (bitmap == NULL) 
            {
                throw NMC_EXCEPTION("Unable to load: " + getRealFilename(filename));
	        }

            mBitmaps[filename] = bitmap;
        }

        return mBitmaps[filename];
    }

    BITMAP* ResourceHandler::getRawBitmap(const std::string& filename)
    {
        if (mBitmaps.find(filename) == mBitmaps.end())
        {
            set_color_conversion(COLORCONV_NONE);
	        BITMAP* bitmap = load_bitmap(getRealFilename(filename).c_str(), NULL);
    	    
            if (bitmap == NULL) 
            {
                throw NMC_EXCEPTION("Unable to load: " + getRealFilename(filename));
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
                throw NMC_EXCEPTION("Unable to load: " + getRealFilename(filename));
	        }

            mSamples[filename] = sample;
        }

        return mSamples[filename];
    }

    std::string ResourceHandler::getRealFilename(const std::string& filename)
    {
        return std::string(NMC_DATA_PREFIX) + "/" + filename;
    }

    BITMAP* ResourceHandler::getRoomEntitiesBitmap(int roomNumber)
    {
        if (mRoomEntitiesBitmaps.find(roomNumber) == mRoomEntitiesBitmaps.end())
        {
            throw NMC_EXCEPTION("Cannot find room entities bitmap for room number : " + toString(roomNumber) + ".");
        }

        return mRoomEntitiesBitmaps[roomNumber];
    }

    BITMAP* ResourceHandler::getRoomTilesBitmap(int roomNumber)
    {
        if (mRoomTilesBitmaps.find(roomNumber) == mRoomTilesBitmaps.end())
        {
            throw NMC_EXCEPTION("Cannot find room tiles bitmap for room number : " + toString(roomNumber) + ".");
        }

        return mRoomTilesBitmaps[roomNumber];
    }

    std::string ResourceHandler::getRoomName(int roomNumber)
    {
        if (mRoomNames.find(roomNumber) == mRoomNames.end())
        {
            throw NMC_EXCEPTION("Cannot find room name for room number : " + toString(roomNumber) + ".");
        }

        return mRoomNames[roomNumber];
    }

    std::string ResourceHandler::getRoomTilesBitmapFilename(int roomNumber)
    {
        std::string name = getRoomName(roomNumber);
        
        return "rooms/"+roomNumberToString(roomNumber)+"-tiles-"+convertSpaces(name)+".bmp";
    }

    std::string ResourceHandler::getRoomEntitiesBitmapFilename(int roomNumber)
    {
        std::string name = getRoomName(roomNumber);
        
        return "rooms/"+roomNumberToString(roomNumber)+"-entities-"+convertSpaces(name)+".bmp";
    }

    int ResourceHandler::newRoomBitmap(int width, int height, const std::string& name)
    {
        struct al_ffblk info;

        std::string pattern = NMC_DATA_PREFIX 
                            + std::string("rooms/") 
                            + "*.bmp";

        int roomNumber = -1;
        int lastRoomNumber = -1;

        if (al_findfirst(pattern.c_str(), &info, FA_ALL))
		{
			al_findclose(&info);
			roomNumber = 0;
		}
		else
		{
			do
			{
				std::string foundName = std::string(info.name);
				std::string roomNumberString = foundName.substr(0, 3);
				lastRoomNumber = fromString<int>(roomNumberString);

				if (lastRoomNumber > roomNumber)
				{
					roomNumber = lastRoomNumber;
				}

			} while (al_findnext(&info) == 0);
		}
       
        al_findclose(&info);

        BITMAP* newRoomTilesBitmap = create_bitmap_ex(24, width * 20, height * 15);
        clear(newRoomTilesBitmap);
        mRoomTilesBitmaps[roomNumber + 1] = newRoomTilesBitmap;
        
        BITMAP* newRoomEntitiesBitmap = create_bitmap_ex(24, width * 20, height * 15);
        clear(newRoomEntitiesBitmap);
        mRoomEntitiesBitmaps[roomNumber + 1] = newRoomEntitiesBitmap;

        BITMAP* humanReadableRoomBitmap = create_bitmap(newRoomTilesBitmap->w, newRoomTilesBitmap->h);
        mHumanReadableRoomBitmaps[roomNumber + 1] = humanReadableRoomBitmap;
        mRoomNames[roomNumber + 1] = name;
        mRoomNumbers.push_back(roomNumber + 1);
        
        return roomNumber + 1;
    }

    void ResourceHandler::loadRooms()
    {
        struct al_ffblk info;
        std::string pattern = NMC_DATA_PREFIX 
                            + std::string("rooms/") 
                            + "*-entities-*.bmp";

        int roomNumber = -1;
		if (al_findfirst(pattern.c_str(), &info, FA_ALL)) {
			al_findclose(&info);
			return;
		}

        do
        {
            std::string foundName = std::string(info.name);
            std::string roomNumberString = foundName.substr(0, 3);
            // Remove room number and string -entities- from name.
            std::string roomName = foundName.substr(13, foundName.size() - 13);
            // Remove trailing .bmp from name.
            roomName = roomName.substr(0, roomName.length() - 4);
            roomNumber = fromString<int>(roomNumberString);
            mRoomNumbers.push_back(roomNumber);
           
            set_color_conversion(COLORCONV_NONE);
            std::string roomEntitiesBitmapFilename = getRealFilename(std::string("rooms/") 
                                                     + roomNumberString
                                                     + "-entities-"
                                                     + roomName
                                                     + ".bmp");
            BITMAP* roomEntitiesBitmap = load_bitmap(roomEntitiesBitmapFilename.c_str(), NULL);

            if (roomEntitiesBitmap == NULL)
            {
                throw NMC_EXCEPTION("Cannot load bitmap " + roomEntitiesBitmapFilename + ".");
            }

            mRoomEntitiesBitmaps[roomNumber] = roomEntitiesBitmap;  

            std::string roomTilesBitmapFilename = getRealFilename(std::string("rooms/") 
                                                    + roomNumberString
                                                    + "-tiles-"
                                                    + roomName
                                                    + ".bmp");

            BITMAP* roomTilesBitmap = load_bitmap(roomTilesBitmapFilename.c_str(), NULL);

            if (roomTilesBitmap == NULL)
            {
                throw NMC_EXCEPTION("Cannot load bitmap " + roomTilesBitmapFilename + ".");
            }

            mRoomTilesBitmaps[roomNumber] = roomTilesBitmap;  
        
            BITMAP* humanReadableRoomBitmap = create_bitmap(roomTilesBitmap->w, roomTilesBitmap->h);
            newHumanReadableRoomBitmap(roomTilesBitmap, humanReadableRoomBitmap);
            mHumanReadableRoomBitmaps[roomNumber] =  humanReadableRoomBitmap;

            mRoomNames[roomNumber] = convertUnderscores(roomName);

        } while (al_findnext(&info) == 0);
       
        al_findclose(&info);
    }

    std::string ResourceHandler::roomNumberToString(int roomNumber)
    {
        if (roomNumber < 10)
        {
            return std::string("00") + toString(roomNumber); 
        }
        else if (roomNumber < 100)
        {
            return std::string("0") + toString(roomNumber); 
        }
        else if (roomNumber < 1000)
        {
            return toString(roomNumber); 
        }
        else
        {
            throw NMC_EXCEPTION("Illegal room number: " + toString(roomNumber) + "."); 
        }
    }

    void ResourceHandler::saveRoomBitmap(int roomNumber)
    {
        // TODO add check here!
        save_bmp(getRealFilename(getRoomTilesBitmapFilename(roomNumber)).c_str(),
                 getRoomTilesBitmap(roomNumber),
                 NULL);
        save_bmp(getRealFilename(getRoomEntitiesBitmapFilename(roomNumber)).c_str(),
                 getRoomEntitiesBitmap(roomNumber),
                 NULL);

        newHumanReadableRoomBitmap(mRoomTilesBitmaps[roomNumber], mHumanReadableRoomBitmaps[roomNumber]);
    }

    const std::vector<int>& ResourceHandler::getRoomNumberList()
    {
        return mRoomNumbers;
    }

    BITMAP* ResourceHandler::getHumanReadableRoomBitmap(int roomNumber)
    {
        if (mHumanReadableRoomBitmaps.find(roomNumber) == mHumanReadableRoomBitmaps.end())
        {
            throw NMC_EXCEPTION("Cannot find human readable room bitmap for room number : " 
                + toString(roomNumber) + ".");
        }

        return mHumanReadableRoomBitmaps[roomNumber];
    }

    void ResourceHandler::newHumanReadableRoomBitmap(BITMAP* roomBitmap, BITMAP* humanReadableRoomBitmap)
    {      
        int y;
        int x;
        for (y = 0; y < humanReadableRoomBitmap->h; y++)
        {
            for (x = 0; x < humanReadableRoomBitmap->w; x++)
            {
                 int pixel = _getpixel24(roomBitmap, x, y);

                 if (getb24(pixel) & TileMap::SOLID)
                 {
                    int newPixel = makecol(0, 0, 0);
                    putpixel(humanReadableRoomBitmap, x, y, newPixel); 
                 }
				 else if (getb24(pixel) & TileMap::PLATFORM)
				 {
					int newPixel = makecol(120, 120, 120);
                    putpixel(humanReadableRoomBitmap, x, y, newPixel); 
				 }
                 else
                 {
                    int newPixel = makecol(255, 0, 255);
                    putpixel(humanReadableRoomBitmap, x, y, newPixel); 
                 }
            }
        }
    }
}
