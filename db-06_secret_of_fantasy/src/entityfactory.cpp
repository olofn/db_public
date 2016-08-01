#include "entityfactory.hpp"
#include "exception.hpp"
#include "entities/slime.hpp"
#include "entities/bat.hpp"
#include "entities/chest.hpp"
#include "entities/introcutscene.hpp"
#include "entities/dialogtile.hpp"
#include "entities/paintingcutscene.hpp"
#include "items/cure.hpp"
#include "items/bomb.hpp"
#include "items/calciumcrystal.hpp"
#include "entities/explodable.hpp"
#include "entities/dirt.hpp"
#include "entities/eye.hpp"
#include "entities/vapor.hpp"
#include "entities/milkcutscene.hpp"
#include "entities/shopkeeper.hpp"
#include "entities/friendlyvapor.hpp"
#include "entities/endingcutscene.hpp"
#include "items/energydrink.hpp"
#include "items/windsword.hpp"
#include "items/magicgun.hpp"
#include "entities/plancutscene.hpp"
#include "entities/towerdoor.hpp"
#include "entities/citizen.hpp"
#include "random.hpp"
#include <iostream>

Entity* createEntity(char id, int x, int y, Random &random)
{
	switch (id)
	{
	case '1':
		return new Door(x, y, true, "towndungeon.txt", 0, false);
	case '2':
		return new Door(x, y, true, "dungeon1.txt", 0, false);
	case '3':
		return new Door(x, y, true, "dungeon2.txt", 0, false);
	case '4':
		return new Door(x, y, true, "dungeon3.txt", 0, false);
	case '5':
		return new Door(x, y, true, "dungeon4.txt", 0, false);
	case '6':
		return new Door(x, y, true, "dungeon5.txt", 0, false);
	case 'a':
		return new Slime(x, y, 0, 0);
	case 'b':
		return new Slime(x, y, 1, 1);
	case 'c':
		return new Slime(x, y, 2, 2);
	case 'd':
		return new Bat(x, y, 0, 0);
	case 'e':
		return new Bat(x, y, 1, 1);
	case 'f':
		return new Bat(x, y, 2, 2);
	case 'g':
		return new Bat(x, y, 3, 3);
	case 'h':
		return new Bat(x, y, 4, 4);
	case 'i':
		return new Bat(x, y, 5, 5);
	case 'j':
		return new Eye(x, y, 3);
	case 'k':
		return new Vapor(x, y);
	case '<':
		return new Door(x, y, true, "", -1, false);
	case '>':
		return new Door(x, y, false, "", -1, false);
	case '[':
		return new Door(x, y, true, "", -1, true);
	case ']':
		return new Door(x, y, false, "", -1, true);
	case 'A':
		{
			Item *i = 0;
			int r = random.getInt(100);
			if (r >= 97)
				i = new EnergyDrink();
			else if (r >= 72)
				i = new Bomb();
			else
				i = new Cure();
				
			Chest* chest = new Chest(x, y, i, false);
			return chest;
		}
	case 'B':
		{
			IntroCutScene* e = new IntroCutScene();
			return e;
		}
	case 'C':
		{
			DialogTile* e = new DialogTile(x, y, true, "standdown", false);
			e->addDialog("Mom: Are you touching that video game again?");
			e->addDialog("Ted: Eh... no mom... I will go and get milk now.");
			return e;
		}
	case 'D':
		{
			PaintingCutScene* e = new PaintingCutScene(x, y);
			return e;
		}
	case 'E':
		{
			Explodable* e = new Explodable(x, y);
			return e;
		}
	case 'F':
		{
			Dirt* e = new Dirt(x, y);
			return e;
		}
	case 'G':
		{
			ShopKeeper* e = new ShopKeeper(x, y);
			return e;
		}
	case 'H':
		{
			FriendlyVapor* e = new FriendlyVapor(x, y);
			return e;
		}
		
	case 'I':
		{
			return new MilkCutScene(x, y);
		}
	case 'J':
		{
			return new EndingCutScene();
		}
	case 'K':
		{
			Chest* e = new Chest(x, y, new EnergyDrink(), false);
			return e;
		}
	case 'L':
		{
			return new PlanCutScene();
		}
	case 'M':
		{
			return new TowerDoor(x, y, "olof", 1);
		}
	case 'N':
		{
			Citizen* c = new Citizen(x, y, false);
			c->addDialog("Citizen: Our village has been completely drained on milk.");
			c->addDialog("Citizen: I should not talk about this, but Lord Vapor is going to use milk to power his doomsday device...");
			c->addDialog("Citizen: Maybe you can help us so our children can have milk on their table?");
			c->addDialog("Ted: No no no. I need just a bottle for my mom.");
			c->addDialog("Ted: Why does this always happen to me when I buy milk?.");
			return c;
		}
	case 'O':
		{
			Citizen* c = new Citizen(x, y);
			c->addDialog("Citizen: You might have met my brother, he looks just like me.");
			c->addDialog("Citizen: He is obsessed with the milk shortage in our village and talks about nothing else.");
			return c;
		}
   case 'P':
		{
			Chest* e = new Chest(x, y, new CalciumCrystal(), false);
			return e;
		}
   case 'Q':
	   {
		   Chest* e = new Chest(x, y, new WindSword(), false);
		   return e;
	   }
   case 'R':
	   {
		   Chest* e = new Chest(x, y, new MagicGun(), false);
		   return e;
	   }
	case 'S':
	{
		Citizen* c = new Citizen(x, y);
		c->addDialog("Major: You have fallen from Lord Vapors Tower.");
		c->addDialog("Ted: Yeah, whatever... Do you know where I can get milk?");
		c->addDialog("Major: Milk! Are you nuts?!");
		c->addDialog("Ted: ...");
		c->addDialog("Major: Milk is the most powerful substance in the galaxy.");
		c->addDialog("Major: Only Lord Vapor possesses it in his tower.");
		c->addDialog("Major: Lord Vapor has tormented us as long as I can remember... I once...");
		c->addDialog("Ted: Dont care, dont care...");
		c->addDialog("Major: ...anyway. You can only enter the tower if you have calcium crystals.");
		return c;
	}
	  case 'T':
		{
			Citizen* c = new Citizen(x, y);
			c->addDialog("Falstaf: There is a legend of a great weapons called magic guns.");
			c->addDialog("Falstaf: But I for one have never seen one.");
			return c;
		}
	case 'U':
		{
			Citizen* c = new Citizen(x, y);
			c->addDialog("X-G: Quit bugging me, Im trying to make a game here!");
			return c;
		}
	case 'V':
		{
			Citizen* c = new Citizen(x, y);
			c->addDialog("Matthew: Hmmm... perhaps these blocks with four squares can fit together...");
			return c;
		}
	case 'W':
		{
			Citizen* c = new Citizen(x, y);
			c->addDialog("Elias: I am a farmer, but I can't work because i lost my shovel...");
			return c;
		}
	case 'X':
		{
			Citizen* c = new Citizen(x, y);
			c->addDialog("Ted: Michael Jackson? Seriously?");
			c->addDialog("Jeff: Hey, whats wrong with Michael?");
			c->addDialog("Ted: ...");
			c->addDialog("Jeff: Perhaps I should rethink this...");
			return c;
		}
	case 'Y':
		{
			Citizen* c = new Citizen(x, y);
			c->addDialog("Bruce: Mwuhahaha! Im invincible!");
			return c;
		}
	case 'Z':
		{
			Citizen* c = new Citizen(x, y);
			c->addDialog("Onewing: We dont go down here anymore...");
			return c;
		}
	case '@':
		{
			Citizen* c = new Citizen(x, y);
			c->addDialog("Zorn: Remember that you can press the i key to access your inventory!!");
			return c;
		}
	default:
		throw DB_EXCEPTION("Unknown entity!");
	}
}
