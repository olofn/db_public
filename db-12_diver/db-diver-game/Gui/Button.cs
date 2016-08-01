using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace DB.Gui
{
    public class Button : Widget
    {
        bool isMouseDown = false;

        public string Caption;
        public Box AreaDefault;
        public Box AreaHover;
        public Box AreaPressed;
        public TextAlignment TextAlignment = TextAlignment.Center;

        public bool IsPressed
        {
            get { return isMouseDown && HasMouse; }
        }

        public Button(string caption, Box areaDefault, Box areaPressed, Box areaHover)
        {
            Caption = caption;
            AreaDefault = areaDefault;
            AreaPressed = areaPressed;
            AreaHover = areaHover;

            MousePressed += new MousePressedHandler(Button_MousePressed);
            MouseReleased += new MouseReleasedHandler(Button_MouseReleased);
        }

        public delegate void ClickedHandler(Button sender, int x, int y, MouseButton button);
        public event ClickedHandler Clicked;

        void Button_MouseReleased(Widget sender, int x, int y, MouseButton button)
        {
            if (button != MouseButton.Left)
            {
                return;
            }

            if (IsPressed && Clicked != null)
            {
                Clicked(this, x, y, button);
            }

            isMouseDown = false;
        }

        void Button_MousePressed(Widget sender, int x, int y, MouseButton button)
        {
            isMouseDown = (button == MouseButton.Left);
        }

        public override void Draw(Graphics g, GameTime gameTime)
        {
            Box area = null;

            if (HasMouse)
            {
                area = AreaHover;
            }

            if (IsPressed)
            {
                area = AreaPressed;
            }

            if (area == null)
            {
                area = AreaDefault;
            }

            DrawButton(g, area, gameTime);
        }

        protected virtual void DrawButton(Graphics g, Box area, GameTime gameTime)
        {
            area.Draw(g, Size);

            g.DrawString(InheritedFont, Caption, new Rectangle(1, 1, Width, Height), TextAlignment, Color.Black);
            g.DrawString(InheritedFont, Caption, new Rectangle(0, 0, Width, Height), TextAlignment, Color.White);
            /*
            g.DrawString(InheritedFont, "Top\nLeft", new Rectangle(0, 0, Width, Height), TextAlignment.TopLeft, Color.Red);
            g.DrawString(InheritedFont, "TopCenter", new Rectangle(0, 0, Width, Height), TextAlignment.TopCenter, Color.Green);
            g.DrawString(InheritedFont, "TopRight", new Rectangle(0, 0, Width, Height), TextAlignment.TopRight, Color.Blue);
            g.DrawString(InheritedFont, "CenterLeft", new Rectangle(0, 0, Width, Height), TextAlignment.CenterLeft, Color.BlueViolet);
            g.DrawString(InheritedFont, "Center\nCent\tererer\nRecente\tr", new Rectangle(0, 0, Width, Height), TextAlignment.Center, Color.Yellow);
            g.DrawString(InheritedFont, "CenterRight", new Rectangle(0, 0, Width, Height), TextAlignment.CenterRight, Color.Orange);
            g.DrawString(InheritedFont, "BottomLeft", new Rectangle(0, 0, Width, Height), TextAlignment.BottomLeft, Color.NavajoWhite);
            g.DrawString(InheritedFont, "BottomCenter", new Rectangle(0, 0, Width, Height), TextAlignment.BottomCenter, Color.Purple);
            g.DrawString(InheritedFont, "Bottom\nRight", new Rectangle(0, 0, Width, Height), TextAlignment.BottomRight, Color.Sienna);*/
        }

        public virtual void AutoResize()
        {
            Vector2 size = InheritedFont.MeasureString(Caption);
            Size = new Point((int)(size.X) + 16, (int)(size.Y) + 8);
        }
    }
}
