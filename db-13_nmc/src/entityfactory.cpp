#include "entityfactory.hpp"

#include "exception.hpp"
#include "stringutil.hpp"
#include "entities/animatedentity.hpp"
#include "entities/area.hpp"
#include "entities/bubbles.hpp"
#include "entities/candelabra.hpp"
#include "entities/ceilingdrop.hpp"
#include "entities/cutscene.hpp"
#include "entities/eyeball.hpp"
#include "entities/fly.hpp"
#include "entities/imagebackground.hpp"
#include "entities/gradientbackground.hpp"
#include "entities/outsidecastlebackground.hpp"
#include "entities/parallaxscroll.hpp"
#include "entities/player.hpp"
#include "entities/savepoint.hpp"
#include "entities/shootabletile.hpp"
#include "entities/snowentity.hpp"
#include "entities/spider.hpp"
#include "entities/teleport.hpp"
#include "entities/text.hpp"
#include "entities/trigger.hpp"
#include "entities/rat.hpp"


namespace nmc
{
	EntityFactory *EntityFactory::mInstance = NULL;

	EntityFactory::EntityFactory()
	{
	}

	EntityFactory * EntityFactory::getInstance()
	{
		if (mInstance == NULL)
		{
			mInstance = new EntityFactory();
		}

		return mInstance;
	}

	Entity *EntityFactory::createEntity(int type, int x, int y)
	{
		switch(type) {
            // Case 1 is the player and is handled by the class Room.
			case 2:
				return new SavePoint(x, y);
			case 3:
				return new EyeBall(x, y);
            case 4:
                return new AnimatedEntity(x, y, "star.bmp", 5);
            case 5:
                return new SnowEntity();
            case 6:
                return new GradientBackground(236, 94, 96, 40, 40, 20);
            case 7:
                return new Rat(x, y);
            case 8:
                return new AnimatedEntity(x, y, "crystal.bmp", 10);
            case 9:
                return new CeilingDrop(x, y);
            case 10:
            {
                ParallaxScroll* cave = new ParallaxScroll();
                cave->setBackgroundFloor("cave-background-floor.bmp");
                cave->setBackgroundCeiling("cave-background-ceiling.bmp");
                cave->setForegroundFloor("cave-foreground-floor.bmp");

                return cave;
            }
            case 11:
                return new ImageBackground("cave-background.bmp", 4);
            case 12:
                return new ImageBackground("corridor-background-curtains.bmp", 3);
            case 13:
                return new ImageBackground("corridor-background-wall.bmp", 4);
            case 14:
                return new ImageBackground("corridor-background-paintings.bmp", 4);
            case 15:
				return new Candelabra(x, y);
            case 16:
                return new ImageBackground("kitchen-background.bmp", 4);
            case 17:
            {
                ParallaxScroll* dishes = new ParallaxScroll();
                dishes->setBackgroundFloor("kitchen-background-floor.bmp");
                dishes->setForegroundFloor("kitchen-foreground-floor.bmp");

                return dishes;
            }
            case 18:
                return new Bubbles();
			case 19:
				return new ShootableTile(x, y);
            case 20:
                return new OutsideCastleBackground();
            case 21:
            {
                ParallaxScroll* outside = new ParallaxScroll();
                outside->setBackgroundFloor("outside-background-floor.bmp", 85);
                outside->setForegroundFloor("outside-foreground-floor.bmp");
                return outside;
            }
            case 22:
				return new Area("The caves");
			case 23:
			{
				CutScene* cutScene = new CutScene();

				cutScene->addAnimation("signs", "talking", 1, 0, 0);
				cutScene->addAnimation("player", "hurt", 5);
				cutScene->addMoveX("player", 4630, 20, true);
				cutScene->addAnimation("player", "standing", 10);
				cutScene->addAnimation("signs", "talking", 8);
				cutScene->addDialog("BIG SIGN: Hold it right there! Can't you read the signs?");
				cutScene->addAnimation("signs", "talking", 1, 0, 0);
				cutScene->addAnimation("player", "talking", 8);
				cutScene->addDialog("DANTE: What signs?");
				cutScene->addAnimation("player", "standing", 30);
				cutScene->addAnimation("signs", "talking", 8);
				cutScene->addDialog("BIG SIGN: Us of course!! It's strictly forbidden to go any further near the wizard Nodajo's castle!");
				cutScene->addAnimation("signs", "talking", 1, 0, 0);
				cutScene->addDialog("SMALL SIGN: No one can pass under any circumstances, this area is out of bounds.");
				cutScene->addAnimation("player", "talking", 8);
				cutScene->addDialog("DANTE: Forbidden? But I have unfinished business with Nodajo. He destroyed my house!");
				cutScene->addAnimation("player", "standing", 30);
				cutScene->addAnimation("signs", "talking", 8);
				cutScene->addDialog("BIG SIGN: Well, that's not our problem... We are just signs, you see.");
				cutScene->addAnimation("signs", "talking", 1, 0, 0);
				cutScene->addAnimation("player", "talking", 8);
				cutScene->addDialog("DANTE: Seems to me like you are stuck to the ground. I'll just carry on walking, then...");
				cutScene->addAnimation("player", "standing", 30);
				cutScene->addAnimation("signs", "talking", 8);
				cutScene->addDialog("BIG SIGN: We'll see about that!");
				cutScene->addAnimation("signs", "talking", 1, 0, 0);
                cutScene->addWait(150);
				cutScene->addAnimation("signs", "pressing-button", 80, false, false, false);
				cutScene->addWait(90);
				cutScene->addAnimation("player", "jumping", 10, 2, 2, false, false, false);
				cutScene->addWait(30);
				cutScene->addAnimation("player", "jumping", 3, 2, 6, false, false, false);
				cutScene->addMoveY("player", 72, 20, false, false);
				cutScene->addWait(40);
				cutScene->addAnimation("signs", "laughing", 5);
				cutScene->addWait(20);
				cutScene->addDialog("SMALL SIGN: Ha-ha-ha! Works every time!");
				cutScene->addDialog("BIG SIGN: Yes, I know. I love this job!");

                return new Trigger(cutScene, x, y, 16, 16, true);
			}
			case 24:
				return new Spider(x, y);
			case 25:
				return new AnimatedEntity(x - 2, 
                                          y, "lightray.bmp", 
                                          1, 
                                          1, 
                                          Entity::FOREGROUND_LAYER, 
                                          false, 
                                          Animation::ADD);
			case 26:
			{
				Actor *a = new Actor("signs", x, y-48);		

				a->insertAnimation("idle", "signs.bmp");
				a->insertAnimation("talking", "signs-talking.bmp");
				a->insertAnimation("pressing-button", "signs-pressing-button.bmp");
				a->insertAnimation("laughing", "signs-laughing.bmp");
				
				return a;
			}
            case 27:
            {
                CutScene* cutScene = new CutScene(false);
                cutScene->addWait(100);
                cutScene->addText("Darkbits presents", 150);
                cutScene->addWait(100);
                cutScene->addText("Nodajo's Mechanical Castle", 150);
                cutScene->addWait(100);               
                cutScene->addText("Olof Naessen\n    Programmer\n    Art director", 150);
                cutScene->addWait(100);
                cutScene->addText("Per Larsson\n    Programmer\n    Additional graphics", 150);
                Trigger* trigger = new Trigger(cutScene, x, y, 16, 16);
                return trigger;
            }
            case 28:
            {
                return new Fly(x, y);
            }
    		default:
				throw NMC_EXCEPTION("Invalid entity number: " + toString(type));
		}
	}
}
