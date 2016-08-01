#include <list>
#include "entities/cutscene.hpp"
#include "room.hpp"
#include "actor.hpp"
#include "exception.hpp"

namespace nmc
{
	CutScene::CutScene(bool disablePlayer) 
        : mInitialized(false), 
          mDone(false),
          mDisablePlayer(disablePlayer)
	{
	}

    void CutScene::draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer)
    {

    }

    void CutScene::logic(Room *room)
    {
		if (!mInitialized)
		{
            if (mDisablePlayer)
            {
			    room->disablePlayer();
            
			    room->addEntity(Actor::createPlayerActor(room->getPlayer()->getX(),
													     room->getPlayer()->getY()));
			    room->setKeysDisabled(true);
            }

			mInitialized = true;
		}

        if (room->getDialog()->isVisible())
        {
            return;
        }

		if (mSceneEvents.empty() && !mDone)
		{
			// Replace the player actor with the real player and restore control
            if (mDisablePlayer)
            {
			    room->setKeysDisabled(false);
			    Actor *playerActor = getActor(room, "player");
			    room->getPlayer()->setPosition(playerActor->getX(), playerActor->getY());
			    playerActor->remove();
			    room->enablePlayer();
            }

			mDone = true;
		}

        while (!mSceneEvents.empty())
        {
            SceneEvent &evnt = mSceneEvents.front();

			switch(evnt.type)
			{
			case WAIT:
                evnt.frames--;
                
                if (evnt.frames <= 0)
                {
                    mSceneEvents.pop();
                }
                else
                {
                    return;
                }
				break;
			case DIALOG:            
                room->getDialog()->setText(evnt.text);
                room->getDialog()->setVisible(true);
                mSceneEvents.pop();
                return;
			case ANIMATION_SIMPLE:
				getActor(room, evnt.actor)->playAnimation(evnt.text,
					                                      evnt.frames,
														  evnt.hflip,
														  evnt.vflip,
														  evnt.looped);
				mSceneEvents.pop();
				break;
			case ANIMATION_ADVANCED:
				getActor(room, evnt.actor)->playAnimation(evnt.text,
														  evnt.frames,
														  evnt.x, // From frame
														  evnt.y, // To frame
														  evnt.hflip,
														  evnt.vflip,
														  evnt.looped);
				mSceneEvents.pop();
				break;
			case MOVE_XY:
				getActor(room, evnt.actor)->move(evnt.x, evnt.y, evnt.frames, evnt.absolute);
				mSceneEvents.pop();
				break;
			case MOVE_X:
				getActor(room, evnt.actor)->moveX(evnt.x, evnt.frames, evnt.absolute);
				mSceneEvents.pop();
				break;
			case MOVE_Y:
				getActor(room, evnt.actor)->moveY(evnt.y, evnt.frames, evnt.absolute);
				mSceneEvents.pop();
				break;
            case TEXT:
                evnt.frames--;

                if (evnt.frames <= 0)
                {
                    room->getTextBox()->setVisible(false);
                    mSceneEvents.pop();
                }
                else if (!room->getTextBox()->isVisible())
                {
                    room->getTextBox()->setText(evnt.text);
                    room->getTextBox()->setVisible(true);
                    room->getTextBox()->setPosition(160 - room->getTextBox()->getWidth() / 2,
                                                    120 - room->getTextBox()->getHeight() / 2);
                    return;
                }
                else
                {
                    return;
                }

                break;
			}
        }
    }

    bool CutScene::isToBeDeleted()
    {
        return mDone;
    }

    void CutScene::addDialog(const std::string& dialog)
    {
        SceneEvent sceneEvent;
        sceneEvent.type = DIALOG;
        sceneEvent.text = dialog;
        mSceneEvents.push(sceneEvent);
    }

    void CutScene::addText(const std::string& text, int time)
    {
        SceneEvent sceneEvent;
        sceneEvent.type = TEXT;
        sceneEvent.text = text;
        sceneEvent.frames = time;
        mSceneEvents.push(sceneEvent);
    }

    void CutScene::addWait(int time)
    {
        SceneEvent sceneEvent;
        sceneEvent.type = WAIT;
        sceneEvent.frames = time;
        mSceneEvents.push(sceneEvent);
    }

	void CutScene::addAnimation(const std::string& actor,
	                  const std::string& animation,
		              int frameDelay,
					  bool hflip,
					  bool vflip,
					  bool looped)
	{
		SceneEvent e;
		e.type = ANIMATION_SIMPLE;
		e.actor = actor;
		e.text = animation;
		e.frames = frameDelay;
		e.hflip = hflip;
		e.vflip = vflip;
		e.looped = looped;
		mSceneEvents.push(e);
	}

	void CutScene::addAnimation(const std::string& actor,
			          const std::string& name,
                      int frameDelay,
					  int fromFrame,
					  int toFrame,
					  bool hflip,
					  bool vflip,
					  bool looped)
	{
		SceneEvent e;
		e.type = ANIMATION_ADVANCED;
		e.actor = actor;
		e.text = name;
		e.frames = frameDelay;
		e.x = fromFrame;
		e.y = toFrame;
		e.hflip = hflip;
		e.vflip = vflip;
		e.looped = looped;
		mSceneEvents.push(e);
	}

	void CutScene::addMove(const std::string& actor, int destinationX, int destinationY, int frames, bool absolute, bool autoWait)
	{
		SceneEvent e;
		e.type = MOVE_XY;
		e.actor = actor;
		e.x = destinationX;
		e.y = destinationY;
		e.frames = frames;
		e.absolute = absolute;
		mSceneEvents.push(e);

		if (autoWait)
		{
			addWait(frames + 1);
		}
	}

	void CutScene::addMoveX(const std::string& actor, int destinationX, int frames, bool absolute, bool autoWait)
	{
		SceneEvent e;
		e.type = MOVE_X;
		e.actor = actor;
		e.x = destinationX;
		e.y = 0;
		e.frames = frames;
		e.absolute = absolute;
		mSceneEvents.push(e);

		if (autoWait)
		{
			addWait(frames + 1);
		}
	}

	void CutScene::addMoveY(const std::string& actor, int destinationY, int frames, bool absolute, bool autoWait)
	{
		SceneEvent e;
		e.type = MOVE_Y;
		e.actor = actor;
		e.x = 0;
		e.y = destinationY;
		e.frames = frames;
		e.absolute = absolute;
		mSceneEvents.push(e);

		if (autoWait)
		{
			addWait(frames + 1);
		}
	}

	Actor *CutScene::getActor(Room *room, const std::string &id)
	{
		std::list<Entity *>::const_iterator it;

		for (it = room->getEntityList().begin(); it != room->getEntityList().end(); it++)
		{
			Actor *a = dynamic_cast<Actor *>(*it);

			if (a != NULL && a->getId() == id)
			{
				return a;
			}
		}

		throw NMC_EXCEPTION("No actor found with id '" + id + "'");
	}
}