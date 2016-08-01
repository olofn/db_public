using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace DB.Gui
{
    public class Graphics : SpriteBatch
    {
        struct ClipRectangle
        {
            public readonly int X, Y, Width, Height, XOffset, YOffset;

            public ClipRectangle(int x, int y, int width, int height)
            {
                X = x;
                Y = y;
                Width = width;
                Height = height;
                XOffset = 0;
                YOffset = 0;
            }

            private ClipRectangle(int x, int y, int width, int height, int xOffset, int yOffset)
            {
                X = x;
                Y = y;
                Width = width;
                Height = height;
                XOffset = xOffset;
                YOffset = yOffset;
            }

            public ClipRectangle Intersect(Rectangle r)
            {
                int xOffset = XOffset + r.X;
                int yOffset = YOffset + r.Y;
                int x1 = Math.Max(X, X + r.X);
                int y1 = Math.Max(Y, Y + r.Y);
                int x2 = Math.Min(X + Width, X + r.X + r.Width);
                int y2 = Math.Min(Y + Height, Y + r.Y + r.Height);
                int w = x2 - x1;
                int h = y2 - y1;
                return new ClipRectangle(x1, y1, w, h, xOffset, yOffset);
            }
        }

        Stack<ClipRectangle> clipStack = new Stack<ClipRectangle>();
        Rectangle orignalScissorRectangle;
        bool originalScissorEnabled;

        Point Offset { get { return new Point(clipStack.Peek().XOffset, clipStack.Peek().YOffset); } }

        public Graphics(GraphicsDevice graphicsDevice) : base(graphicsDevice)
        {
        }

        public void BeginClip()
        {
            originalScissorEnabled = GraphicsDevice.RenderState.ScissorTestEnable;
            orignalScissorRectangle = GraphicsDevice.ScissorRectangle;
            clipStack.Push(new ClipRectangle(0, 0, GraphicsDevice.Viewport.Width, GraphicsDevice.Viewport.Height));            
            UpdateScissor();
            GraphicsDevice.RenderState.ScissorTestEnable = true;
        }

        public void EndClip()
        {
            clipStack.Clear();
            GraphicsDevice.RenderState.ScissorTestEnable = originalScissorEnabled;
            GraphicsDevice.ScissorRectangle = orignalScissorRectangle;
        }

        private Rectangle ApplyOffset(Rectangle r)
        {
            return new Rectangle(r.X + Offset.X, r.Y + Offset.Y, r.Width, r.Height);
        }

        private Vector2 ApplyOffset(Vector2 r)
        {
            return new Vector2(r.X + Offset.X, r.Y + Offset.Y);
        }

        private Vector2 ApplyOffset(Point r)
        {
            return new Vector2(r.X + Offset.X, r.Y + Offset.Y);
        }

        public new void Draw(Texture2D texture, Rectangle destinationRectangle, Color color)
        {
            base.Draw(texture, ApplyOffset(destinationRectangle), color);
        }

        public void Draw(Texture2D texture, Point position, Color color)
        {
            base.Draw(texture, ApplyOffset(position), color);
        }

        public new void Draw(Texture2D texture, Vector2 position, Color color)
        {
            base.Draw(texture, ApplyOffset(position), color);
        }

        public new void Draw(Texture2D texture, Rectangle destinationRectangle, Rectangle? sourceRectangle, Color color)
        {
            base.Draw(texture, ApplyOffset(destinationRectangle), sourceRectangle, color);
        }

        public void Draw(Texture2D texture, Point position, Rectangle? sourceRectangle, Color color)
        {
            base.Draw(texture, ApplyOffset(position), sourceRectangle, color);
        }

        public new void Draw(Texture2D texture, Vector2 position, Rectangle? sourceRectangle, Color color)
        {
            base.Draw(texture, ApplyOffset(position), sourceRectangle, color);
        }

        public new void Draw(Texture2D texture, Rectangle destinationRectangle, Rectangle? sourceRectangle, Color color, float rotation, Vector2 origin, SpriteEffects effects, float layerDepth)
        {
            base.Draw(texture, ApplyOffset(destinationRectangle), sourceRectangle, color, rotation, origin, effects, layerDepth);
        }

        public new void Draw(Texture2D texture, Vector2 position, Rectangle? sourceRectangle, Color color, float rotation, Vector2 origin, float scale, SpriteEffects effects, float layerDepth)
        {
            base.Draw(texture, ApplyOffset(position), sourceRectangle, color, rotation, origin, scale, effects, layerDepth);
        }

        public new void Draw(Texture2D texture, Vector2 position, Rectangle? sourceRectangle, Color color, float rotation, Vector2 origin, Vector2 scale, SpriteEffects effects, float layerDepth)
        {
            base.Draw(texture, ApplyOffset(position), sourceRectangle, color, rotation, origin, scale, effects, layerDepth);
        }

        public void DrawString(SpriteFont spriteFont, string text, Point position, Color color)
        {
            base.DrawString(spriteFont, text, ApplyOffset(position), color);
        }

        public void DrawString(SpriteFont spriteFont, string text, Rectangle destinationRectangle, TextAlignment alignment, Color color)
        {
            Point position = Point.Zero;
            Vector2 textSize = spriteFont.MeasureString(text);

            switch (alignment)
            {
                case TextAlignment.TopLeft:
                case TextAlignment.TopCenter:
                case TextAlignment.TopRight:
                    position.Y = 0;
                    break;
                case TextAlignment.CenterLeft:
                case TextAlignment.Center:
                case TextAlignment.CenterRight:
                    position.Y = (int)((destinationRectangle.Height - textSize.Y) / 2);
                    break;
                case TextAlignment.BottomLeft:
                case TextAlignment.BottomCenter:
                case TextAlignment.BottomRight:
                    position.Y = (int)(destinationRectangle.Height - textSize.Y);
                    break;
            }

            switch (alignment)
            {
                case TextAlignment.TopLeft:
                case TextAlignment.CenterLeft:
                case TextAlignment.BottomLeft:
                    position.X = 0;
                    break;
                case TextAlignment.TopCenter:
                case TextAlignment.Center:
                case TextAlignment.BottomCenter:
                    position.X = (int)((destinationRectangle.Width - textSize.X) / 2);
                    break;
                case TextAlignment.TopRight:
                case TextAlignment.CenterRight:
                case TextAlignment.BottomRight:
                    position.X = (int)(destinationRectangle.Width - textSize.X);
                    break;
            }            

            DrawString(spriteFont, text, new Point(position.X + destinationRectangle.X, position.Y + destinationRectangle.Y), color);
        }

        public void DrawStringShadowed(SpriteFont spriteFont, string text, Rectangle destinationRectangle, TextAlignment alignment, Color color)
        {
            DrawString(spriteFont,
                       text,
                       new Rectangle(destinationRectangle.X + 1,
                                     destinationRectangle.Y + 1,
                                     destinationRectangle.Width,
                                     destinationRectangle.Height),
                       alignment,
                       Color.Black);
            DrawString(spriteFont,
                       text,
                       destinationRectangle,
                       alignment,
                       color);
        }

        public new void DrawString(SpriteFont spriteFont, string text, Vector2 position, Color color, float rotation, Vector2 origin, float scale, SpriteEffects effects, float layerDepth)
        {
            base.DrawString(spriteFont, text, ApplyOffset(position), color, rotation, origin, scale, effects, layerDepth);
        }

        public new void DrawString(SpriteFont spriteFont, string text, Vector2 position, Color color, float rotation, Vector2 origin, Vector2 scale, SpriteEffects effects, float layerDepth)
        {
            base.DrawString(spriteFont, text, ApplyOffset(position), color, rotation, origin, scale, effects, layerDepth);
        }

        public void PushClipRectangle(Rectangle r)
        {
            clipStack.Push(clipStack.Peek().Intersect(r));
            UpdateScissor();
        }

        public void PopClipRectangle()
        {
            clipStack.Pop();
            UpdateScissor();
        }

        private void UpdateScissor()
        {
            ClipRectangle c = clipStack.Peek();
            GraphicsDevice.ScissorRectangle = new Rectangle(c.X, c.Y, c.Width, c.Height);
        }
    }
}
