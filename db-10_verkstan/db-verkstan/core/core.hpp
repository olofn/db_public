#pragma once

#include "core/clip.hpp"
#include "core/externals.hpp"
#include "core/operator.hpp"

#define DB_MAX_CLIPS 4096
#define DB_MAX_OPERATORS 4096
#define DB_TICKS_PER_BEAT 256
#define DB_MAX_LIGHTS 9

extern Clip* coreClips[DB_MAX_CLIPS];
extern Operator* coreOperators[DB_MAX_OPERATORS];
extern short coreNumberOfOperators;
extern D3DLIGHT9* coreLights[DB_MAX_LIGHTS];
extern short coreNumberOfLights;
