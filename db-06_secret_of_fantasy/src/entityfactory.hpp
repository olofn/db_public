#ifndef DB_ENTITYFACTORY_HPP
#define DB_ENTITYFACTORY_HPP
#include "room.hpp"
class Entity;
class Random;
Entity* createEntity(char id, int x, int y, Random &random);

#endif