using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using DB.Gui;

namespace DB.DoF.Entities
{
    public class SpeedyDiver: Diver
    {
        public SpeedyDiver(ITool tool1, ITool tool2, int x, int y) :
            base(tool1, tool2, x, y)
        {
            Size = new Point(16, 40);
            StandingGrid = new SpriteGrid("tiny_standing", 2, 1);
            WalkingGrid = new SpriteGrid("tiny_walking", 12, 1);
            JumpingGrid = new SpriteGrid("tiny_jumping", 6, 1);
            ClimbingGrid = new SpriteGrid("speedy_climbing", 2, 1);
            Name = "Speedy";
            originalBoatPosition = new Point(150, 224 - Height);
        }

        public SpeedyDiver() :
            this(null, null, 50, 50)
        {            
        }

        public override void Update(State s, Room room)
        {
            base.Update(s, room);
        }
    }
}
