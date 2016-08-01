#include "util.h"
#include "core/externals.hpp"

float expFalloff(float current, float target, float rate, float dt)
{
	return target + (current - target) * powf(2.0f, -dt * rate);
}