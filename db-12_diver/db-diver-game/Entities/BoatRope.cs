using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using DB.Gui;

namespace DB.DoF.Entities
{
    public class BoatRope: Entity
    {
        SpriteGrid ropeGrid;
        bool collisionWithDiverLastFrame;
        bool collisionWithDiver;
        bool diverFreezed;
        bool surface;
        SpriteFont font;
        int pullSpeed, offsetY, frameCounter;

        public BoatRope()
        {
            ropeGrid = new SpriteGrid("boat_rope", 2, 1);
            font = DiverGame.DefaultContent.Load<SpriteFont>("Font");
            Size.X = 16;
            Size.Y = 5;
            X = 190;
            Y = 170;
            Reset();
        }

        void Reset()
        {
            pullSpeed = 0;
            offsetY = 0;
            frameCounter = 0;
            diverFreezed = false;
            surface = false;
            collisionWithDiver = false;
            collisionWithDiverLastFrame = false;
        }
            
        public override void Draw(Graphics g, GameTime gameTime, Room.Layer layer)
        {
            if (layer == Room.Layer.Player)
            {
                g.Begin();
                ropeGrid.Draw(g, new Point(190, -20 + offsetY), diverFreezed?1:0);
                g.End();
            }

            if (layer == Room.Layer.Foreground)
            {
                g.Begin();
                if (collisionWithDiver && diverFreezed && !surface)
                {
                    g.DrawStringShadowed(font,
                                         "Press Space to surface",
                                         new Rectangle(0, 100, 400, 20),
                                         TextAlignment.Center,
                                         Color.White);
                }
                g.End();
            }
        }

        public override void Update(State s, Room room)
        {
            frameCounter++;

            if (surface)
            {
                room.LeaveRoomEnabled = false;

                offsetY += pullSpeed;
                room.Diver.Y += pullSpeed;

                if (frameCounter % 6 == 0)
                {
                    pullSpeed--;

                    if (pullSpeed <= 0)
                    {
                        room.AddEntity(Particle.MakeBigBubble(new Point(room.Diver.X + room.Diver.Width / 2, room.Diver.Y)));
                        room.AddEntity(Particle.MakeBigBubble(new Point(room.Diver.X + room.Diver.Width / 2, room.Diver.Y)));
                        room.AddEntity(Particle.MakeSmallBubble(new Point(room.Diver.X + room.Diver.Width / 2, room.Diver.Y)));
                        room.AddEntity(Particle.MakeSmallBubble(new Point(room.Diver.X + room.Diver.Width / 2, room.Diver.Y)));
                        room.AddEntity(Particle.MakeTinyBubble(new Point(room.Diver.X + room.Diver.Width / 2, room.Diver.Y)));
                        room.AddEntity(Particle.MakeTinyBubble(new Point(room.Diver.X + room.Diver.Width / 2, room.Diver.Y)));
                    }
                }

                if (frameCounter > 240)
                {
                    Reset();
                    room.Diver.Freeze = false;
                    room.SurfaceDiver();
                }

                return;
            }

            collisionWithDiver = Dimension.Intersects(new Rectangle(room.Diver.TopCenter.X,
                                                                    room.Diver.TopCenter.Y,
                                                                    1,
                                                                    1));

            if (collisionWithDiver && !collisionWithDiverLastFrame)
            {
                room.Diver.Freeze = true;
                diverFreezed = true;
            }

            if (collisionWithDiver && s.Input.WasPressed(Input.Action.Jump))
            {
                room.Diver.Velocity.Y = 0;
                room.Diver.JumpVelocity = 0;
                room.Diver.Freeze = false;
                diverFreezed = false;
            }

            if (collisionWithDiver && s.Input.WasPressed(Input.Action.Select))
            {
                surface = true;
                pullSpeed = 2;
                frameCounter = 0;
            }

            collisionWithDiverLastFrame = collisionWithDiver;

            base.Update(s, room);

        }
    }
}
