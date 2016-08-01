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

#ifndef NMC_RESOURCEHANLDER_HPP
#define NMC_RESOURCEHANLDER_HPP

#include <allegro.h>
#include <map>
#include <string>
#include <vector>

namespace nmc
{
    class ResourceHandler
    {
    public:
        static ResourceHandler* getInstance();
        void destroy();
        BITMAP* getBitmap(const std::string& filename);
        BITMAP* getRawBitmap(const std::string& filename);
        BITMAP* getRoomTilesBitmap(int roomNumber);
        BITMAP* getRoomEntitiesBitmap(int roomNumber);
        BITMAP* getHumanReadableRoomBitmap(int roomNumber);
	    SAMPLE* getSample(const std::string& filename);
        std::string getRealFilename(const std::string& filename);
        std::string getRoomTilesBitmapFilename(int roomNumber);
        std::string getRoomEntitiesBitmapFilename(int roomNumber);
        std::string getRoomName(int roomNumber);
        void saveRoomBitmap(int roomNumber);
        const std::vector<int>& getRoomNumberList();
        
        /**
         * @return the new room number.
         */
        int newRoomBitmap(int width, int height, const std::string& name);
 
    private:
        ResourceHandler();
        void loadRooms();
        void newHumanReadableRoomBitmap(BITMAP* roomBitmap, BITMAP* humanReadableRoomBitmap);

        static ResourceHandler* mInstance;
        std::string roomNumberToString(int roomNumber);
        std::map<std::string, BITMAP*> mBitmaps;
        std::map<int, BITMAP*> mRoomEntitiesBitmaps;
        std::map<int, BITMAP*> mRoomTilesBitmaps;
        std::map<int, BITMAP*> mHumanReadableRoomBitmaps;
        std::map<int, std::string> mRoomNames;
	    std::map<std::string, SAMPLE*> mSamples;
        std::vector<int> mRoomNumbers;
    };
}
#endif
