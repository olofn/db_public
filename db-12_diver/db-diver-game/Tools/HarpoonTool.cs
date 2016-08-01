using System;
using System.Collections.Generic;
using System.Text;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using DB.DoF.Entities;
using DB.Gui;

namespace DB.DoF.Tools
{
    public class HarpoonTool : ITool
    {
        enum Action
        {
            None,
            Shooting,
            Pulling,
            Retracting
        };

        Texture2D icon;
        Texture2D texture;
        public Texture2D Icon { get { return icon; } }
        Action action;
        int length;
        int direction;
        const int maxLength = 80;
        const int shootSpeed = 8;
        const int pullSpeed = 4;

        public HarpoonTool()
        {
            icon = DiverGame.DefaultContent.Load<Texture2D>("iconharpoon");
            texture = DiverGame.DefaultContent.Load<Texture2D>("harpoon");
        }

        public void Update(Diver diver, Room room, State s)
        {
            switch (action)
            {
                case Action.Shooting:
                    if (direction != diver.FacingDirection)
                    {
                        action = Action.Retracting;
                        break;
                    }

                    length += shootSpeed;
                    int tipX = diver.X + diver.Width / 2 + length * direction;
                    int tipY = diver.Y + diver.Height - 12;
                    if (room.TileMap.IsSolid(tipX / 16, tipY / 16))
                    {
                        diver.Freeze = true;
                        action = Action.Pulling;
                    } 
                    else if (length > maxLength)
                    {
                        action = Action.Retracting;
                    }
                    break;

                case Action.Pulling:
                    length -= pullSpeed;
                    diver.Velocity = new Point(direction * pullSpeed * Diver.Resolution, 0);
                    diver.MoveWithCollision(room);
                    diver.JumpVelocity = 0;
                    if (length <= 0 || diver.Velocity.X == 0)
                    {
                        action = Action.None;
                        diver.Freeze = false;
                    }
                    break;

                case Action.Retracting:
                    length -= pullSpeed;
                    if (length <= 0)
                    {
                        action = Action.None;
                        diver.Freeze = false;
                    }
                    break;

                case Action.None:
                    break;
            }
        }

        public void OnUse(Diver diver, Room room)
        {
            if (action == Action.None)
            {
                action = Action.Shooting;
                length = 0;
                direction = diver.FacingDirection;
            }
        }

        public void Draw(Graphics graphics, Diver diver)
        {
            if (action != Action.None)
            {
                int tipX = diver.X + diver.Width / 2 + length * direction;
                int tipY = diver.Y + diver.Height - 12;

                if (direction < 0)
                {
                    graphics.Begin();
                    graphics.Draw(texture, new Point(tipX, tipY - 4), new Rectangle(0, action == Action.Pulling ? 8 : 0, length, 8), Color.White);
                    graphics.End();
                }
                else
                {
                    graphics.Begin();
                    graphics.Draw(texture, new Rectangle(diver.X + diver.Width / 2, tipY - 4, length, 8), new Rectangle(0, action == Action.Pulling ? 8 : 0, length, 8), Color.White, 0.0f, Vector2.Zero, SpriteEffects.FlipHorizontally, 0.0f);
                    graphics.End();
                }
            }
        }
    }
}
