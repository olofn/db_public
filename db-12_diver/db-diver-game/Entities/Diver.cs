using System;
using System.Collections.Generic;
using System.Text;
using DB.Gui;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace DB.DoF.Entities
{
    public abstract class Diver: PersistentEntity
    {
        public const int MaxOxygen = 10000;
        protected int MaxSpeed = 1 * Resolution;
        protected int GroundAcceleration = Resolution;
        protected int AirAcceleration = Resolution / 16;
        protected int JumpPower = (9 * Resolution) / 2;
        protected int MaxJumpSpeed = (5 * Resolution) / 2;
        protected int MaxFallSpeed = (6 * Resolution) / 2;
        protected int WalkAnimationSpeed = Resolution * 3;
        protected int ClimbAnimationSpeed = Resolution * 12;
        protected int Strength = 10;

        public Point AppliedForce;
        protected SpriteGrid StandingGrid;
        protected SpriteGrid WalkingGrid;
        protected SpriteGrid JumpingGrid;
        protected SpriteGrid ClimbingGrid;
        protected String Name;
        protected Point originalBoatPosition;

        public int FacingDirection;
        SpriteEffects spriteEffects = SpriteEffects.None;
        SpriteFont font;

        public ITool Tool1;
        public ITool Tool2;

        public bool IsDead = false;
        int climbingGridFrame = 0;
        int walkingGridFrame = 3;
        int standingGridFrame = 0;
        int jumpingGridFrame = 0;
        public int JumpVelocity;
        bool isOnGround = true;
        public bool OxygenDecrease = true;
        public bool OxygenIncrease = false;
        public bool Freeze = false;
        public bool JumpEnabled = true;
        bool disabledThisFrame;
        bool enabled;
        bool climbing = false;
        int frameCounter = 0;

        public bool Enabled
        {
            set { enabled = value; if (!enabled) disabledThisFrame = true; }
            get { return enabled; }
        }

        bool collisionWithDiver = false;

        public int Oxygen = MaxOxygen;

        public Diver(ITool tool1, ITool tool2, int x, int y)
        {
            font = DiverGame.DefaultContent.Load<SpriteFont>("Font");
            X = x;
            Y = y;
        }


        protected override string[] GetConstructorArguments()
        {
            string t1 = Tool1 != null ? "new " + Tool1.GetType().Name + "()" : "null";
            string t2 = Tool2 != null ? "new " + Tool2.GetType().Name + "()" : "null";
            return new string[] { t1, t2, X.ToString(), Y.ToString() };
        }

        public override void Update(State s, Room room)
        {
            frameCounter++;
            if (!Enabled)
            {
                collisionWithDiver = Dimension.Intersects(room.Diver.Dimension);

                if (collisionWithDiver 
                    && s.Input.WasPressed(Input.Action.Select)
                    && !disabledThisFrame)
                {
                    int x = X;
                    X = room.Diver.X;
                    room.Diver.X = x;
                    room.Diver.Enabled = false;
                    Enabled = true;
                    OxygenDecrease = false;
                    OxygenIncrease = true;
                    JumpEnabled = false;
                    room.OnDiverChange(this);
                }

                disabledThisFrame = false;
                return;
            }

            isOnGround = IsTileSolidBelow(room) || IsSpecialLadderCase(room) ;

            
            if (frameCounter % 60 == 0)
                standingGridFrame++;
 
            if (!Freeze && climbing)
            {
                UpdateClimbingMovement(s, room);
            }
            else if (!Freeze)
            {
                UpdateNormalMovement(s, room);
            }

            if (Tool1 != null)
            {
                Tool1.Update(this, room, s);
            }

            if (Tool2 != null)
            {
                Tool2.Update(this, room, s);
            }

            if (OxygenDecrease)
            {
                Oxygen--;

                if (Oxygen < 0)
                    Oxygen = 0;

                if (s.Time.TotalGameTime.Seconds % 4 == 1 && s.Time.TotalGameTime.Milliseconds % 1000 < 500)
                {
                    if (DiverGame.Random.Next(10) == 0)
                    {
                        room.AddEntity(Particle.MakeBigBubble(new Point(X + Width / 2, Y)));
                    }

                    if (DiverGame.Random.Next(5) == 0)
                    {
                        room.AddEntity(Particle.MakeSmallBubble(new Point(X + Width / 2, Y)));
                    }

                    if (DiverGame.Random.Next(4) == 0)
                    {
                        room.AddEntity(Particle.MakeTinyBubble(new Point(X + Width / 2, Y)));
                    }
                }
            }

            if (OxygenIncrease)
                Oxygen += 5;

            if (Oxygen < 0)
            {
                Freeze = true;
                IsDead = true;
            }

            if (Oxygen > MaxOxygen)
                Oxygen = MaxOxygen;
        }

        public void UpdateClimbingMovement(State s, Room room)
        {
            Velocity.X = 0;

            if (s.Input.WasPressed(Input.Action.Jump))
            {
                climbing = false;
                JumpVelocity = -JumpPower / 2;
            }
            else if (s.Input.IsHeld(Input.Action.Up) 
                && !s.Input.IsHeld(Input.Action.Down)
                && room.TileMap.IsLadder(TopCenter.X / 16, TopCenter.Y / 16))
            {
                Velocity.Y = -MaxSpeed;
                X = Center.X - Center.X % 16;
            }
            else if (s.Input.IsHeld(Input.Action.Down) 
                && !s.Input.IsHeld(Input.Action.Up)
                && room.TileMap.IsLadder(BottomCenter.X / 16, BottomCenter.Y / 16))
            {
                Velocity.Y = MaxSpeed;
                X = Center.X - Center.X % 16;
            }
            else if (s.Input.IsHeld(Input.Action.Left) && !IsTileSolidLeft(room))
            {
                climbing = false;
                Velocity.Y = 0;
                JumpVelocity = 0;
            }
            else if (s.Input.IsHeld(Input.Action.Right) && !IsTileSolidRight(room))
            {
                climbing = false;
                Velocity.Y = 0;
                JumpVelocity = 0;
            }
            else
            {
                Velocity.Y = 0;
                JumpVelocity = 0;
            }

            MoveWithCollision(room);

            climbingGridFrame += Math.Abs(Velocity.Y);

            if (IsTileSolidBelow(room) && Velocity.Y == 0)
            {
                climbing = false;
                return;
            }
        }

        public void UpdateNormalMovement(State s, Room room)
        {
            int acceleration = isOnGround ? GroundAcceleration : AirAcceleration;

            if (room.TileMap.IsLadder(Center.X / 16, Center.Y / 16)
                && s.Input.WasPressed(Input.Action.Up)
                && Velocity.Y >= 0)
            {
                climbing = true;
                Velocity.Y = 0;
                return;
            }

            if (room.TileMap.IsLadder(Center.X / 16, Center.Y / 16)
                && s.Input.WasPressed(Input.Action.Down)
                && Velocity.Y >= 0
                && !room.TileMap.IsSolid(BottomCenter.X / 16, BottomCenter.Y / 16 + 1))
            {
                climbing = true;
                Velocity.Y = 0;
                return;
            }

            if (s.Input.IsHeld(Input.Action.Right) && !s.Input.IsHeld(Input.Action.Left))
            {
                AppliedForce.X = Strength;
                Velocity.X = Math.Min(Velocity.X + acceleration, MaxSpeed);
            }
            else if (s.Input.IsHeld(Input.Action.Left) && !s.Input.IsHeld(Input.Action.Right))
            {
                AppliedForce.X = -Strength;
                Velocity.X = Math.Max(Velocity.X - acceleration, -MaxSpeed);
            }
            else
            {
                AppliedForce.X = 0;
                if (Velocity.X > 0)
                {
                    Velocity.X = Math.Max(Velocity.X - acceleration, 0);
                }
                else if (Velocity.X < 0)
                {
                    Velocity.X = Math.Min(Velocity.X + acceleration, 0);
                }
            }

            if (Velocity.X == 0)
            {
                walkingGridFrame = 3 * WalkAnimationSpeed;
            }
            else
            {
                walkingGridFrame += Math.Abs(Velocity.X);
                spriteEffects = Velocity.X > 0 ? SpriteEffects.None : SpriteEffects.FlipHorizontally;
            }

            if (s.Input.WasPressed(Input.Action.Jump) && isOnGround && JumpEnabled)
            {
                JumpVelocity = -JumpPower;
                isOnGround = false;
            }

            if ((s.Input.WasReleased(Input.Action.Jump) && JumpVelocity < 0) || isOnGround)
            {
                JumpVelocity = 0;
                jumpingGridFrame = 0;
            }

            if (JumpVelocity < 0 && JumpVelocity + Resolution / 8 >= 0)
                jumpingGridFrame = 3;

            JumpVelocity += Resolution / 8;

            Velocity.Y = Math.Max(Math.Min(JumpVelocity, isOnGround?0:MaxFallSpeed), -MaxJumpSpeed);

            MoveWithCollision(room);

            if (Velocity.Y < 0 && jumpingGridFrame < 3 && frameCounter % 6 == 0)
            {
                jumpingGridFrame++;
            }

            if (Velocity.Y > 0 && jumpingGridFrame < 5 && frameCounter % 6 == 0)
            {
                if (jumpingGridFrame < 4)
                    jumpingGridFrame = 4;
                else
                    jumpingGridFrame++;
            }

            if (Velocity.Y == 0 && isOnGround)
            {
                jumpingGridFrame = 0;
            }

            // Bumped head
            if (Velocity.Y == 0)
            {
                JumpVelocity = 0;
            }

            FacingDirection = spriteEffects == SpriteEffects.None ? 1 : -1;

            if (s.Input.WasPressed(Input.Action.Item1) && Tool1 != null)
            {
                Tool1.OnUse(this, room);
            }
            else if (s.Input.WasPressed(Input.Action.Item2) && Tool2 != null)
            {
                Tool2.OnUse(this, room);
            }
        }

        public override void Draw(Graphics g, GameTime gameTime, Room.Layer layer)
        {
            if (layer == Room.Layer.Player)
            {
                if (Tool1 != null) Tool1.Draw(g, this);
                if (Tool2 != null) Tool2.Draw(g, this);
                  
                g.Begin();
                Point pos = new Point(Position.X - 2, Position.Y);

                if (climbing)
                    ClimbingGrid.Draw(g, new Point(pos.X, pos.Y - (ClimbingGrid.FrameSize.Y - Height)), climbingGridFrame / ClimbAnimationSpeed, spriteEffects);
                else if (isOnGround && Velocity.X != 0)
                    WalkingGrid.Draw(g, new Point(Center.X - WalkingGrid.FrameSize.X / 2, pos.Y - (WalkingGrid.FrameSize.Y - Height)), walkingGridFrame / WalkAnimationSpeed, spriteEffects);
                else if (isOnGround)
                    StandingGrid.Draw(g, new Point(Center.X - StandingGrid.FrameSize.X / 2, pos.Y - (StandingGrid.FrameSize.Y - Height)), standingGridFrame, spriteEffects);
                else
                    JumpingGrid.Draw(g, new Point(Center.X - JumpingGrid.FrameSize.X / 2, pos.Y - (JumpingGrid.FrameSize.Y - Height) + 5), jumpingGridFrame, spriteEffects);
                g.End();
            }

            if (layer == Room.Layer.Foreground)
            {
                g.Begin();
                if (collisionWithDiver && !Enabled)
                {
                    g.DrawStringShadowed(font,
                                        "Press Space to select " + Name,
                                        new Rectangle(0, 100, 400, 20),
                                        TextAlignment.Center,
                                        Color.White);
                }
                g.End();
            }
        }

        public void kill()
        {
            Oxygen = 0;
        }

        bool IsSpecialLadderCase(Room room)
        {
            return Velocity.Y == 0
                && BottomCenter.Y % 16 == 15
                && room.TileMap.IsLadder(BottomCenter.X / 16, BottomCenter.Y / 16 + 1)
                && (room.TileMap.IsSolid(BottomCenter.X / 16 - 1, BottomCenter.Y / 16 + 1)
                    || room.TileMap.IsSolid(BottomCenter.X / 16 + 1, BottomCenter.Y / 16 + 1));
        }
    }
}
