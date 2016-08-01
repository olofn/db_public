#ifndef NMC_ICESHOT_HPP
#define NMC_ICESHOT_HPP

#include "shot.hpp"

namespace nmc {

	class IceShot : public Shot {
	public:
		IceShot(int x, 
                int y, 
                const std::string &filename, 
                const std::string &hitFilename, 
                int size, 
                int dx, 
                int dy, 
                int ttl, 
                bool friendly);
	
		virtual void handleCollision(Entity *other, Room *room);

	};
}

#endif