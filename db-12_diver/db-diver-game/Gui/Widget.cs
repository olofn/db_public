using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace DB.Gui
{
    public abstract class Widget
    {
        List<Widget> children = new List<Widget>();
        Widget parent;
        GuiManager guiManager;
        
        public Rectangle Dimension = Rectangle.Empty;
        public bool IsVisible = true;
        public bool IsOpaque = true;
        public SpriteFont Font;

        public SpriteFont InheritedFont
        {
            get { return Font == null ? ( parent == null ? null : parent.InheritedFont ) : Font; }
        }

        public int X
        {
            get { return Dimension.X; }
            set { Dimension.X = value; }
        }

        public int Y
        {
            get { return Dimension.Y; }
            set { Dimension.Y = value; }
        }

        public int Width
        {
            get { return Dimension.Width; }
            set { Dimension.Width = value; }
        }

        public int Height
        {
            get { return Dimension.Height; }
            set { Dimension.Height = value; }
        }

        public Point Position
        {
            get { return new Point(Dimension.X, Dimension.Y); }
            set { Dimension.X = value.X; Dimension.Y = value.Y; }
        }

        public Point Size
        {
            get { return new Point(Dimension.Width, Dimension.Height); }
            set { Dimension.Width = value.X; Dimension.Height = value.Y; }
        }

        public Point AbsolutePosition
        {
            get { return (Parent == null) ? Position : new Point(Dimension.X + Parent.Dimension.X, Dimension.Y + Parent.Dimension.Y); }
        }

        public IList<Widget> Children { get { return children.AsReadOnly(); } }

        public Widget Parent { get { return parent; } }

        public bool HasMouse { get { return guiManager.WidgetWithMouse == this; } }

        public GuiManager GuiManager
        {
            get { return guiManager; }
            set {
                guiManager = value;
                foreach (Widget c in children) {
                    c.GuiManager = value;
                }
            }
        }

        public void MoveToTop(Widget c)
        {
            if (!children.Remove(c))
            {
                throw new Exception("No such child exists");
            }

            children.Add(c);
        }

        public void MoveToTop()
        {
            parent.MoveToTop(this);
        }

        public void Add(Widget c)
        {
            if (c.parent != null)
            {
                c.parent.Remove(c);
            }

            children.Add(c);
            c.parent = this;
            c.guiManager = guiManager;
        }

        public void Remove(Widget c)
        {
            if (!children.Remove(c))
            {
                throw new Exception("No such child exists");
            }

            c.parent = null;
            c.guiManager = null;
        }

        public abstract void Draw(Graphics g, GameTime gameTime);

        public virtual void Update(GameTime gameTime) { }


        // Mouse Events

        public delegate void MouseMovedHandler(Widget sender, int x, int y);

        public event MouseMovedHandler MouseMoved;

        internal void OnMouseMoved(int x, int y)
        {
            if (MouseMoved != null)
            {
                MouseMoved(this, x, y);
            }
        }

        public delegate void MousePressedHandler(Widget sender, int x, int y, MouseButton button);

        public event MousePressedHandler MousePressed;

        internal void OnMousePressed(int x, int y, MouseButton button)
        {
            if (MousePressed != null)
            {
                MousePressed(this, x, y, button);
            }
        }

        public delegate void MouseReleasedHandler(Widget sender, int x, int y, MouseButton button);

        public event MouseReleasedHandler MouseReleased;

        internal void OnMouseReleased(int x, int y, MouseButton button)
        {
            if (MouseReleased != null)
            {
                MouseReleased(this, x, y, button);
            }
        }

        public delegate void MouseEnteredHandler(Widget sender);

        public event MouseEnteredHandler MouseEntered;

        internal void OnMouseEntered()
        {
            if (MouseEntered != null)
            {
                MouseEntered(this);
            }
        }

        public delegate void MouseLeftHandler(Widget sender);

        public event MouseLeftHandler MouseLeft;

        internal void OnMouseLeft()
        {
            if (MouseLeft != null)
            {
                MouseLeft(this);
            }
        }
    }
}
