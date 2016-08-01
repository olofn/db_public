using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using VerkstanEditor.Logic;

namespace VerkstanEditor.Gui
{
    public partial class SplineClipValueView : UserControl
    {
        #region Properties
        private SplineClip splineClip;
        public SplineClip SplineClip
        {
            get
            {
                return splineClip;
            }
            set
            {
                if (splineClip != null)
                {
                    splineClip.StateChanged -= clipStateChangedHandler;
                    splineClip.Added -= splineClipAddedHandler;
                    splineClip.Removed -= splineClipRemovedHandler;
                    splineClip.Moved -= splineClipMovedHandler;
                    splineClip.ControlPointStateChanged -= splineClipControlPointStateChangedHandler;
                }

                splineClip = value;
                if (splineClip != null)
                {
                    splineClip.StateChanged += clipStateChangedHandler;
                    splineClip.Added += splineClipAddedHandler;
                    splineClip.Removed += splineClipRemovedHandler;
                    splineClip.Moved += splineClipMovedHandler;
                    splineClip.ControlPointStateChanged += splineClipControlPointStateChangedHandler;
                }
                UpdateSize();
            }
        }
        private int beatWidth = 31;
        public int BeatWidth
        {
            get
            {
                return beatWidth;
            }
            set
            {
                beatWidth = value;
                UpdateSize();
            }
        }
        private float yZoom = 1.0f;
        public float YZoom
        {
            get
            {
                return yZoom;
            }
            set
            {
                yZoom = value;
                if (yZoom < 1.0f)
                    yZoom = 1.0f;
                UpdateSize();
            }
        }
        #endregion

        #region Private Variables
        private int controlPointSize = 9;
        private bool inMove = false;
        private Clip.EventHandler clipStateChangedHandler;
        private SplineClip.EventHandler splineClipAddedHandler;
        private SplineClip.EventHandler splineClipRemovedHandler;
        private SplineClip.EventHandler splineClipMovedHandler;
        private SplineClip.EventHandler splineClipControlPointStateChangedHandler;
        #endregion

        #region Constructors
        public SplineClipValueView()
        {
            InitializeComponent();
            DoubleBuffered = true;
            clipStateChangedHandler = new Clip.EventHandler(this.clip_StateChanged);
            splineClipAddedHandler = new SplineClip.EventHandler(this.splineClip_Added);
            splineClipRemovedHandler = new SplineClip.EventHandler(this.splineClip_Removed);
            splineClipMovedHandler = new SplineClip.EventHandler(this.splineClip_Moved);
            splineClipControlPointStateChangedHandler = new SplineClip.EventHandler(this.splineClip_ControlPointStateChanged);
        }
        #endregion

        #region Event Handlers
        private void SplineClipValueView_Paint(object sender, PaintEventArgs e)
        {
            PaintGrid(e);
            PaintGraph(e);
            PaintControlPoints(e);
        }
        private void SplineClipValueView_Load(object sender, EventArgs e)
        {
            UpdateSize();
        }
        private void clip_StateChanged(Clip clip)
        {
            Invalidate();
        }
        private void SplineClipValueView_KeyDown(object sender, KeyEventArgs e)
        {
            if (splineClip == null)
                return;

            if (e.KeyCode == Keys.Delete)
                splineClip.RemoveSelected();
        }
        private void SplineClipValueView_MouseDown(object sender, MouseEventArgs e)
        {
            if (splineClip == null)
                return;

            if (e.Button == MouseButtons.Right)
            {
                splineClip.Add(new ControlPoint(), PixelXToControlPointX(e.X), PixelYToControlPointY(e.Y));
                return;
            }

            if (e.Button == MouseButtons.Left)
            {
                splineClip.Select(PixelXToControlPointX(e.X),
                                  PixelYToControlPointY(e.Y),
                                  (int)((float)controlPointSize / beatWidth / 8 * Metronome.TicksPerBeat),
                                  (float)controlPointSize / Height);
                if (splineClip.Selected != null)
                    inMove = true;
            }
        }
        private void SplineClipValueView_MouseMove(object sender, MouseEventArgs e)
        {
            if (splineClip == null)
                return;

            if (!inMove)
                return;

            splineClip.MoveSelected(PixelXToControlPointX(e.X), PixelYToControlPointY(e.Y));
        }
        private void SplineClipValueView_MouseUp(object sender, MouseEventArgs e)
        {
            inMove = false;
        }
        private void splineClip_ControlPointStateChanged(SplineClip.EventArgs e)
        {
            foreach (ControlPoint controlPoint in e.ControlPoints)
                Invalidate(ControlPointDimensionToPixelDimension(controlPoint));
        }
        private void splineClip_Added(SplineClip.EventArgs e)
        {
            Invalidate();
        }
        private void splineClip_Removed(SplineClip.EventArgs e)
        {
            Invalidate();
        }
        private void splineClip_Moved(SplineClip.EventArgs e)
        {
            Invalidate();
        }
        #endregion

        #region Private Methods
        private void PaintGrid(PaintEventArgs e)
        {
            if (beatWidth == 0)
                return;

            Pen p1 = new Pen(Color.FromArgb(60, 60, 60), 1);
            Pen p2 = new Pen(Color.FromArgb(30, 30, 30), 1);

            int w = Width / beatWidth + 1;

            for (int i = 0; i < w; i++)
            {
                Rectangle rect = new Rectangle(i * beatWidth, 0, 1, Size.Height);
                e.ClipRectangle.Intersect(rect);

                if (rect.IsEmpty)
                    continue;

                if (i % 4 == 0)
                    e.Graphics.DrawLine(p1, rect.X, rect.Y, rect.X, rect.Y + rect.Height);
                else
                    e.Graphics.DrawLine(p2, rect.X, rect.Y, rect.X, rect.Y + rect.Height);
            }

            for (int i = 0; i < 10; i++)
            {
                Rectangle rect = new Rectangle(0, i * Height / 10, Size.Width, 1);
                e.ClipRectangle.Intersect(rect);

                if (rect.IsEmpty)
                    continue;

                if (i == 5)
                    e.Graphics.DrawLine(p1, rect.X, rect.Y, rect.X + rect.Width, rect.Y);
                else
                    e.Graphics.DrawLine(p2, rect.X, rect.Y, rect.X + rect.Width, rect.Y);
            }

            p1.Dispose();
            p2.Dispose();
        }
        private void PaintGraph(PaintEventArgs e)
        {
            if (splineClip == null)
                return;

            int ticks = splineClip.Dimension.Width * Metronome.TicksPerBeat;
            int middle = Height / 2 - 1;
            float v = splineClip.GetValue(0);
            int lastX = 0;
            int lastY = (int)(middle - v * middle);
            Pen p = new Pen(Color.FromArgb(45, 45, 255));
            for (int x = 1; x < Width; x++)
            {
                int beat = (int)((x / (float)Width) * ticks);
                float value = splineClip.GetValue(beat);
                int y = (int)(middle - value * middle) + 1;
                e.Graphics.DrawLine(p, lastX, lastY, x, y);
                lastX = x;
                lastY = y;
            }
            p.Dispose();
        }
        private void PaintControlPoints(PaintEventArgs e)
        {
            if (splineClip == null)
                return;

            foreach (ControlPoint point in splineClip.ControlPoints)
            {
                Rectangle dim = ControlPointDimensionToPixelDimension(point);

                if (!e.ClipRectangle.IntersectsWith(dim))
                    continue;

                if (point.IsSelected)
                    e.Graphics.FillRectangle(Brushes.Red, dim);
                else
                    e.Graphics.DrawRectangle(Pens.Red, new Rectangle(dim.X, dim.Y, dim.Width - 1, dim.Height - 1));
                Point p = ControlPointPointToPixelPoint(point.X, point.Y);
                e.Graphics.DrawLine(Pens.Yellow, p.X, p.Y, p.X + 1, p.Y);
            }
        }
        private void UpdateSize()
        {
            if (splineClip == null)
                return;

            int width = beatWidth * splineClip.Dimension.Width * 4;

            if (Parent == null)
                return;

            int height = (int)(Parent.ClientRectangle.Height * yZoom);

            Width = width;
            Height = height;
            Invalidate();
        }
        private Rectangle ControlPointDimensionToPixelDimension(ControlPoint point)
        {
            Point p = ControlPointPointToPixelPoint(point.X, point.Y);
            return new Rectangle(p.X - controlPointSize / 2, p.Y - controlPointSize / 2, controlPointSize + 1, controlPointSize + 1);
        }
        private int PixelXToControlPointX(int x)
        {
            return (int)((x / (float)beatWidth / 4) * Metronome.TicksPerBeat);
        }
        private float PixelYToControlPointY(int y)
        {
            int middlei = Height / 2;
            float middlef = Height / 2;

            if (y > middlei)
            {
                return 1.0f - y / middlef;
            }
            else if (y == middlei)
            {
                return 0.0f;
            }
            else
            {
                return -((y - middlef) / middlef);
            }
        }
        private int PixelWidthToConrolPointWidth(int width)
        {
            return (int)((width / (float)beatWidth / 4) * Metronome.TicksPerBeat);
        }
        private float PixelHeightToControlPointHeight(int height)
        {
            return height / (float)Height;
        }
        private Point ControlPointPointToPixelPoint(int x, float y)
        {
            int newX = (int)(x / (float)Metronome.TicksPerBeat * beatWidth * 4) + 1;
            int newY = 0;
            if (y < 0)
                newY = (int)(-y * Height / 2 + Height / 2) - 1;
            else if (y == 0)
                newY = Height / 2 - 1;
            else if (y > 0)
                newY = (int)((1.0f - y) * Height / 2) - 1;

            return new Point(newX, newY);
        }
        #endregion
    }
}
