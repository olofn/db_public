using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace DB.Gui
{
    public class GuiManager
    {
        Widget top = null;
        public Widget WidgetWithMouse;
        private Widget mouseFocus;

        private MouseState lastMouseState = new MouseState(-1, -1, 0, ButtonState.Released, ButtonState.Released, ButtonState.Released, ButtonState.Released, ButtonState.Released);

        public Widget Top
        {
            get { return top; }
            set { top = value; top.GuiManager = this; }
        }

        public void Draw(Graphics g, GameTime gameTime)
        {                   
            DrawWidgets(g, gameTime, Top);
        }

        private void DrawWidgets(Graphics g, GameTime gameTime, Widget w)
        {
            if (!w.IsVisible)
            {
                return;
            }

            g.PushClipRectangle(w.Dimension);

            if (w.IsOpaque)
            {
                g.Begin(SpriteBlendMode.AlphaBlend, SpriteSortMode.Deferred, SaveStateMode.SaveState);
                w.Draw(g, gameTime);
                g.End();
            }

            foreach (Widget c in w.Children)
            {
                DrawWidgets(g, gameTime, c);
            }

            g.PopClipRectangle();
        }

        public Widget GetWidgetAt(int x, int y)
        {
            return GetWidgetAt(new Point(x, y));
        }
        
        public Widget GetWidgetAt(Point p)
        {
            if (top.Dimension.Contains(p))
            {
                return GetWidgetAt(p, top);
            }
            return null;
        }

        private Widget GetWidgetAt(Point p, Widget w)
        {
            if (!w.IsVisible)
            {
                return null;
            }

            p = new Point(p.X - w.Dimension.X, p.Y - w.Dimension.Y);
            Widget found = w.IsOpaque ? w : null;

            foreach (Widget c in w.Children)
            {
                if (c.IsVisible && c.Dimension.Contains(p))
                {
                    Widget g = GetWidgetAt(p, c);
                    if (g != null)
                    {
                        found = g;
                    }
                }
            }
            return found;
        }

        private void DispatchMouseInput(MouseState mouseState)
        {
            Widget newWidgetWithMouse = GetWidgetAt(mouseState.X, mouseState.Y);
            if (newWidgetWithMouse != WidgetWithMouse)
            {
                if (WidgetWithMouse != null)
                {
                    WidgetWithMouse.OnMouseLeft();
                }

                WidgetWithMouse = newWidgetWithMouse;

                if (newWidgetWithMouse != null)
                {
                    newWidgetWithMouse.OnMouseEntered();
                }
            }

            if (mouseFocus == null)
            {
                mouseFocus = WidgetWithMouse;
            }

            if (mouseFocus == null)
            {
                return;
            }

            Point absPos = mouseFocus.AbsolutePosition;
            int x = mouseState.X - absPos.X;
            int y = mouseState.Y - absPos.Y;

            if (mouseState.X != lastMouseState.X || mouseState.Y != lastMouseState.Y)
            {
                mouseFocus.OnMouseMoved(x, y);
            }

            if (mouseState.LeftButton == ButtonState.Pressed && lastMouseState.LeftButton == ButtonState.Released)
            {
                mouseFocus.OnMousePressed(x, y, MouseButton.Left);
            }

            if (mouseState.RightButton == ButtonState.Pressed && lastMouseState.RightButton == ButtonState.Released)
            {
                mouseFocus.OnMousePressed(x, y, MouseButton.Right);
            }

            if (mouseState.MiddleButton == ButtonState.Pressed && lastMouseState.MiddleButton == ButtonState.Released)
            {
                mouseFocus.OnMousePressed(x, y, MouseButton.Middle);
            }

            if (mouseState.LeftButton == ButtonState.Released && lastMouseState.LeftButton == ButtonState.Pressed)
            {
                mouseFocus.OnMouseReleased(x, y, MouseButton.Left);
            }

            if (mouseState.RightButton == ButtonState.Released && lastMouseState.RightButton == ButtonState.Pressed)
            {
                mouseFocus.OnMouseReleased(x, y, MouseButton.Right);
            }

            if (mouseState.MiddleButton == ButtonState.Released && lastMouseState.MiddleButton == ButtonState.Pressed)
            {
                mouseFocus.OnMouseReleased(x, y, MouseButton.Middle);
            }

            if (mouseState.LeftButton == ButtonState.Released && mouseState.RightButton == ButtonState.Released && mouseState.MiddleButton == ButtonState.Released)
            {
                mouseFocus = null;
            }
        }

        public void Update(GameTime gameTime)
        {
            MouseState mouseState = Mouse.GetState();
            if (mouseState != lastMouseState)
            {
                DispatchMouseInput(mouseState);
            }
            lastMouseState = mouseState;

            UpdateWidgets(gameTime, top);
        }

        private void UpdateWidgets(GameTime gameTime, Widget w)
        {
            w.Update(gameTime);

            foreach (Widget c in w.Children)
            {
                UpdateWidgets(gameTime, c);
            }
        }
    }
}
