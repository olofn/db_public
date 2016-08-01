#ifndef NMC_FIRESHOT_HPP
#define NMC_FIRESHOT_HPP

#include "shot.hpp"

namespace nmc {

	class FireShot : public Shot {
	public:
		FireShot(int x, 
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