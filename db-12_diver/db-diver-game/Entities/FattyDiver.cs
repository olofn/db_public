using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using DB.Gui;

namespace DB.DoF.Entities
{
    public class FattyDiver: Diver
    {
        public FattyDiver(ITool tool1, ITool tool2, int x, int y) :
            base(tool1, tool2, x, y)
        {
            Size = new Point(16, 40);
            StandingGrid = new SpriteGrid("tiny_standing", 2, 1);
            WalkingGrid = new SpriteGrid("tiny_walking", 12, 1);
            JumpingGrid = new SpriteGrid("tiny_jumping", 6, 1);
            ClimbingGrid = new SpriteGrid("fatty_climbing", 2, 1);
            Name = "Fatty";
            originalBoatPosition = new Point(200, 224 - Height);
            Strength = 20;
        }

        public FattyDiver() :
            this(null, null, 50, 50)
        {            
        }

        public override void Update(State s, Room room)
        {
            base.Update(s, room);
        }
    }
}
