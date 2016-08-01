#ifndef NMC_CANDELABRA_HPP
#define NMC_CANDELABRA_HPP

#include "entities/animatedentity.hpp"

namespace nmc
{
	class Candelabra : public AnimatedEntity
	{
	public:
		Candelabra(int x, int y);

		bool drawInLayer(unsigned int layer);

		void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);
	};
}

#endif