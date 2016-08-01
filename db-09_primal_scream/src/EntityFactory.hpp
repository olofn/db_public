#pragma once

class Entity;

class EntityFactory
{
public:
	static Entity* create(int id);
};