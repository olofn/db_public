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
    public partial class GeneratorClipValueView : UserControl
    {
        #region Properties
        private GeneratorClip generatorClip;
        public GeneratorClip GeneratorClip
        {
            get
            {
                return generatorClip;
            }
            set
            {
                if (generatorClip != null)
                {
                    generatorClip.StateChanged -= clipStateChanged;
                }

                generatorClip = value;
                if (generatorClip != null)
                {
                    generatorClip.StateChanged += clipStateChanged;
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
        private Clip.EventHandler clipStateChanged;
        #endregion

        #region Constructors
        public GeneratorClipValueView()
        {
            InitializeComponent();
            DoubleBuffered = true;
            clipStateChanged = new Clip.EventHandler(this.clip_StateChanged);
        }
        #endregion

        #region Event Handlers
        private void GeneratorClipValueView_Paint(object sender, PaintEventArgs e)
        {
            PaintGrid(e);
            PaintGraph(e);
        }
        private void GeneratorClipValueView_Load(object sender, EventArgs e)
        {
            UpdateSize();
        }
        private void clip_StateChanged(Clip clip)
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
            if (generatorClip == null)
                return;

            int ticks = generatorClip.Dimension.Width * Metronome.TicksPerBeat;
            int middle = Height / 2 - 1;
            float v = generatorClip.GetValue(0);
            int lastX = 0;
            int lastY = (int)(middle - v * middle);
            Pen p = new Pen(Color.FromArgb(45, 45, 255), 2.0f);
            for (int x = 1; x < Width; x++)
            {
                int beat = (int)((x / (float)Width) * ticks);
                float value = generatorClip.GetValue(beat);
                int y = (int)(middle - value * middle) + 1;
                e.Graphics.DrawLine(p, lastX, lastY, x, y);
                lastX = x;
                lastY = y;
            }
            p.Dispose();
        }
        private void UpdateSize()
        {
            if (generatorClip == null)
                return;

            int width = beatWidth * generatorClip.Dimension.Width * 4;

            if (Parent == null)
                return;

            int height = (int)(Parent.ClientRectangle.Height * yZoom);

            Width = width;
            Height = height;
            Invalidate();
        }
        #endregion
    }
}
