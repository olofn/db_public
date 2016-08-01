#ifndef NMC_CUTSCENE_HPP
#define NMC_CUTSCENE_HPP

#include "entity.hpp"
#include "actor.hpp"

#include <queue>

namespace nmc
{
    class CutScene: public Entity
    {
    public:
		CutScene(bool disablePlayer = true);
 
		virtual void draw(BITMAP *dest, int scrollx, int scrolly, unsigned int layer);

		virtual void logic(Room *room);

		virtual bool isToBeDeleted();

        void addDialog(const std::string& dialog);

        void addText(const std::string& text, int time);

        void addWait(int time);

		void addAnimation(const std::string& actor,
		                  const std::string& animation,
			              int frameDelay,
						  bool hflip = false,
						  bool vflip = false,
						  bool looped = true);

		void addAnimation(const std::string& actor,
				          const std::string& name,
                          int frameDelay,
						  int fromFrame,
						  int toFrame,
						  bool hflip = false,
						  bool vflip = false,
						  bool looped = true);

		void addMove(const std::string& actor, int destinationX, int destinationY, int frames, bool absolute = false, bool autoWait = true);

		void addMoveX(const std::string& actor, int destinationX, int frames, bool absolute = false, bool autoWait = true);

		void addMoveY(const std::string& actor, int destinationY, int frames, bool absolute = false, bool autoWait = true);

    private:
		Actor *getActor(Room *room, const std::string &id);

        enum SceneEventType
        {
            DIALOG,
            WAIT,
			ANIMATION_SIMPLE,
			ANIMATION_ADVANCED,
			MOVE_XY,
			MOVE_X,
			MOVE_Y,
            TEXT
        };

        class SceneEvent
        {
        public:
            SceneEventType type;
            std::string text;
			std::string actor;
            int frames;
			int x, y;
			bool hflip, vflip, looped, absolute;
        };

        std::queue<SceneEvent> mSceneEvents;
		bool mInitialized, mDone, mDisablePlayer;
    };
}
#endif