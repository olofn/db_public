#include "Precompiled.hpp"

#include "EntityFactory.hpp"

#include "Hero.hpp"
#include "EnemyDragon.hpp"
#include "Background.hpp"
#include "Powerup.hpp"
#include "GameState.hpp"
#include "Savepoint.hpp"
#include "MovableBox.hpp"
#include "EnemyBoss.hpp"
#include "MusicPlayer.hpp"
#include "Shooter.hpp"
#include "ParticleSystem.hpp"
#include "Resource.hpp"
Entity* EntityFactory::create( int id )
{
	switch(id)
	{
	case 0:
		return new Hero();
	case 1:
		return new EnemyDragon(true,float2(20.0f,40.f));
	case 3:
		return new Shooter(float2(0.f,-40.f));
	case 6:
		return new EnemyBoss();
	case 7:
		return new Savepoint();
	case 10:
		return new EnemyDragon(false,float2(0.f,40.f));
	case 11:
		return new EnemyDragon(false,float2(30.0f,40.f));
	case 20:
		return new Background("data/images/bg_blocky_h1.png", "data/images/bg_blocky_2.png", 0);
	case 21:
		return new Background("data/images/bg_outside_1.png", "data/images/bg_outside_2.png", 0);
	case 22:
		return new Background("data/images/bg_cave_h1.png", "data/images/bg_cave_3.png", 0);
	case 23:
		return new Background("data/images/bg_blocky_h1.png", "data/images/bg_blocky_2.png", 0);
	case 24:
		return new Background("data/images/bg_outside_1.png", "data/images/bg_outside_2.png", 0);
	case 25:
		return new Background("data/images/bg_cave_v1.png", "data/images/bg_cave_3.png", 0);

	case 30:
		return new Powerup(GameState::POWERUP_GRENADE);
	case 31:
		return new Powerup(GameState::POWERUP_HIJUMP);
	case 32:
		return new Powerup(GameState::POWERUP_GUN);
	case 40:
		return new MovableBox();

	case 50:
		return new MusicPlayer("data/music/ruins.xm");
	case 51:
		return new MusicPlayer("data/music/outside.xm");
	case 52:
		return new MusicPlayer("data/music/caves.xm");
	case 53:
		return new MusicPlayer("data/music/boss.xm");
	}

	std::cout << "Unknown entity id: " << id << std::endl;
	//throw std::string("Unknown entity id!");

	return 0;
}
