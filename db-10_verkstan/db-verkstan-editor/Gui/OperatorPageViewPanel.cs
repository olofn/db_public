using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using VerkstanEditor.Util;
using VerkstanEditor.Logic;
using System.Xml;

namespace VerkstanEditor.Gui
{
    [ToolboxItem(true)]
    public partial class OperatorPageViewPanel : UserControl
    {
        #region Private Variables
        private bool inSelect = false;
        private bool inMove = false;
        private bool inResize = false;
        private Point selectMarkLocation;
        private Point markLocation;
        private Point mouseLocation;
        private Point addLocation;
        private Rectangle selectionRectangle;
        private Rectangle lastSelectionRectangle;
        private Rectangle moveRectangle;
        private Rectangle lastMoveRectangle;
        private Rectangle resizeRectangle;
        private Rectangle lastResizeRectangle;
        private Page.EventHandler addedHandler;
        private Page.EventHandler removedHandler;
        private Page.EventHandler movedHandler;
        private Page.EventHandler stateChangedHandler;
        private Page.EventHandler resizedHandler;
        #endregion

        #region Properties
        private Page page;
        public Page Page
        {
            get
            {
                return page;
            }
            set
            {
                if (page != null)
                {
                    page.Added -= addedHandler;
                    page.Removed -= removedHandler;
                    page.Moved -= movedHandler;
                    page.StateChanged -= stateChangedHandler;
                    page.Resized -= resizedHandler;
                }
                page = value;

                if (page != null)
                {
                    page.Added += addedHandler;
                    page.Removed += removedHandler;
                    page.Moved += movedHandler;
                    page.StateChanged += stateChangedHandler;
                    page.Resized += resizedHandler;
                }
                Invalidate();
            }
        }
        private Operator viewedOperator;
        public Operator ViewedOperator
        {
            set
            {
                Operator oldViewedOperator = viewedOperator;
                viewedOperator = value;
                OnViewedOperatorChanged();
                if (oldViewedOperator != viewedOperator && oldViewedOperator != null)
                    oldViewedOperator.IsViewed = false;

                if (viewedOperator != null)
                    viewedOperator.IsViewed = true;               
            }
            get
            {
                return viewedOperator;
            }
        }
        private Operator viewedOperatorProperties;
        public Operator ViewedOperatorProperties
        {
            set
            {
                viewedOperatorProperties = value;
                OnViewedOperatorPropertiesChanged();
            }
            get
            {
                return viewedOperatorProperties;
            }
        }
        #endregion

        #region Events
        public event EventHandler ViewedOperatorChanged;
        protected void OnViewedOperatorChanged()
        {
            if (ViewedOperatorChanged != null)
                ViewedOperatorChanged(this, new EventArgs());
        }
        public event EventHandler ViewedOperatorPropertiesChanged;
        protected void OnViewedOperatorPropertiesChanged()
        {
            if (ViewedOperatorPropertiesChanged != null)
                ViewedOperatorPropertiesChanged(this, new EventArgs());
        }
        #endregion

        #region Constructors
        public OperatorPageViewPanel()
        {
            this.DoubleBuffered = true;
            InitializeComponent();
            
            foreach (String category in OperatorFactory.GetCategories())
            {
                ToolStripMenuItem item = new ToolStripMenuItem();
                item.AutoSize = true;
                item.Name = category;
                item.Text = item.Name;
                menu.Items.Add(item);
                ICollection<String> names = OperatorFactory.GetNamesInCategory(category);
                foreach (String name in names)
                {
                    ToolStripMenuItem nestedItem = new ToolStripMenuItem();
                    nestedItem.AutoSize = true;
                    nestedItem.Name = name;
                    nestedItem.Text = nestedItem.Name;
                    String clickedName = name;
                    nestedItem.Click += delegate (object o, EventArgs e)
                    {
                        AddOperator(clickedName);
                    };
                    item.DropDownItems.Add(nestedItem);
                }            
            }

            addedHandler = new Page.EventHandler(this.page_Added);
            removedHandler = new Page.EventHandler(this.page_Removed);
            movedHandler = new Page.EventHandler(this.page_Moved);
            stateChangedHandler = new Page.EventHandler(this.page_StateChanged);
            resizedHandler = new Page.EventHandler(this.page_Resized);
        }
        #endregion

        #region Event Handlers
        private void OperatorPage_Paint(object sender, PaintEventArgs e)
        {
            if (page == null)
                return;

            foreach (Operator op in page.Operators)
            {
                if (e.ClipRectangle.IntersectsWith(op.Dimension))
                    PaintOperator(op, e);
            }
           
            if (inMove)
            {
                ICollection<Operator> selected = page.GetSelected();
                foreach (Operator op in selected)
                    PaintMovingOperator(op, e);
            }  

            if (inResize)
            {
                ICollection<Operator> selected = page.GetSelected();
                foreach (Operator op in selected)
                    PaintResizingOperator(op, e);
            }
            
            if (inSelect)
            {
                Pen p = new Pen(Color.Black, 1);
                p.DashStyle = DashStyle.Dash;
                e.Graphics.DrawRectangle(p, selectionRectangle.X, selectionRectangle.Y, selectionRectangle.Width - 1, selectionRectangle.Height - 1);
                p.Dispose();
            }      
        }
        private void OperatorPage_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                mouseLocation = new Point(e.X, e.Y);
                selectMarkLocation = mouseLocation;
                markLocation = selectMarkLocation;

                selectionRectangle = CalculateSelectionRectangle();
                ICollection<Operator> selected = page.GetIn(selectionRectangle);

                if (selected.Count == 0)
                {
                    inSelect = true;
                    page.Select(selectionRectangle);
                    Invalidate(selectionRectangle);
                }
                else
                {
                    Operator op = selected.First();

                    if (op != viewedOperatorProperties)
                        ViewedOperatorProperties = op;

                    if (!op.IsSelected)
                        page.Select(selectionRectangle);

                    if (op.GetAreaForResize().Contains(mouseLocation))
                    {
                        inResize = true;
                        resizeRectangle = CalculateResizeRectangle();
                        Invalidate(resizeRectangle);
                    }
                    else
                    {
                        inMove = true;
                        moveRectangle = CalculateMoveRectangle();
                        Invalidate(moveRectangle);
                    }
                }
            }
        }
        private void OperatorPage_DoubleClick(object sender, EventArgs e)
        {
            Operator op = page.GetAt(mouseLocation);

            if (op != null)
                ViewedOperator = op;
        }
        private void OperatorPage_MouseUp(object sender, MouseEventArgs e)
        {
            if (inSelect)
            {
                inSelect = false;
                Invalidate(selectionRectangle);
            }

            if (inMove)
            {
                inMove = false;
                Rectangle moveRectangle = CalculateMoveRectangle();
                Invalidate(moveRectangle);
                page.MoveSelected(CalculateMovePoint());
            }

     
            if (inResize)
            {
                inResize = false;
                Rectangle resizeRectangle = CalculateResizeRectangle();
                Invalidate(resizeRectangle);
                page.ResizeSelected(CalculateRelativeResizeWidth());
            }
        }
        private void OperatorPage_MouseMove(object sender, MouseEventArgs e)
        {
            mouseLocation = new Point(e.X, e.Y);

            if (inSelect)
            {
                lastSelectionRectangle = selectionRectangle;
                selectionRectangle = CalculateSelectionRectangle();
                page.Select(selectionRectangle);
                Invalidate(lastSelectionRectangle);
                Invalidate(selectionRectangle);
            }

            if (inMove)
            {
                lastMoveRectangle = moveRectangle;
                moveRectangle = CalculateMoveRectangle();
                Invalidate(lastMoveRectangle);
                Invalidate(moveRectangle);
            }

            if (inResize)
            {
                lastResizeRectangle = resizeRectangle;
                resizeRectangle = CalculateResizeRectangle();
                Invalidate(lastResizeRectangle);
                Invalidate(resizeRectangle);
            }
        }
        private void menu_Opened(object sender, EventArgs e)
        {
            addLocation = mouseLocation;
        }
        private void OperatorPage_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Delete)
                page.RemoveSelected();
        }
        private void OperatorPage_Load(object sender, EventArgs e)
        {
            UpdateSize();
        }
        private void page_Added(Page.EventArgs e)
        {
            foreach (Operator op in e.Operators)
                Invalidate(op.Dimension);
        }
        private void page_Removed(Page.EventArgs e)
        {
            foreach (Operator op in e.Operators)
            {
                if (ViewedOperator == op)
                    ViewedOperator = null;
                if (ViewedOperatorProperties == op)
                    ViewedOperatorProperties = null;
                Invalidate(op.Dimension);
            }
        }
        private void page_Moved(Page.EventArgs e)
        {
            foreach (Operator op in e.Operators)
            {
                Invalidate(op.LastDimension);
                Invalidate(op.Dimension);
            }

            UpdateSize();
        }
        private void page_Resized(Page.EventArgs e)
        {
            foreach (Operator op in e.Operators)
            {
                Invalidate(op.LastDimension);
                Invalidate(op.Dimension);
            }

            UpdateSize();
        }
        private void page_StateChanged(Page.EventArgs e)
        {
            foreach (Operator op in e.Operators)
                Invalidate(new Rectangle(op.Left, op.Top, op.Width + 1, op.Height + 1));
        }
        #endregion

        #region Private Methods
        private void PaintMovingOperator(Operator op, PaintEventArgs e)
        {
            Point p = CalculateMovePoint();
            Point opLocation = op.Location;
            opLocation.X += p.X;
            opLocation.Y += p.Y;
            opLocation = Operator.QuantizeLocation(opLocation);
            Pen pen = new Pen(Color.White);
            e.Graphics.DrawRectangle(pen, opLocation.X, opLocation.Y, op.Width - 1, op.Height - 1);
            pen.Dispose();
        }
        private void PaintResizingOperator(Operator op, PaintEventArgs e)
        {
            int width = CalculateResizeWidth(op.Width);
            Pen pen = new Pen(Color.White);
            e.Graphics.DrawRectangle(pen, op.Location.X, op.Location.Y, width - 1, op.Height - 1);
            pen.Dispose();
        }
        private void PaintOperator(Operator op, PaintEventArgs e)
        {
            Region clip = e.Graphics.Clip;
            e.Graphics.Clip = new Region(op.Dimension);
            
            double brightness = 1.0;
            if (op.IsSelected)
                brightness = 1.3;

            double saturation = 0.0;
            if (op.IsProcessable)
                saturation = 1.0;

            Color color = RGBHSL.ModifyBrightness(GetOperatorColor(op), brightness);
            color = RGBHSL.ModifySaturation(color, saturation);
            Color lightColor = RGBHSL.ModifyBrightness(color, 1.3);
            Color darkColor = RGBHSL.ModifyBrightness(color, 0.7);

            String displayName = op.Name;

            if (displayName == null || displayName == "")
                displayName = op.TypeName;

            Brush b = new SolidBrush(color);
            Pen lightPen = new Pen(lightColor);
            Pen darkPen = new Pen(darkColor);
            if (op.GetType() == typeof(CoreOperator) || op.GetType() == typeof(PropagateOperator))
            {
                e.Graphics.FillRectangle(b, op.Dimension);
                e.Graphics.Clip = new Region(new Rectangle(op.Left + 10, op.Top, op.Width - 20, op.Height));
                SizeF stringSize = e.Graphics.MeasureString(displayName, Font);
                e.Graphics.DrawString(displayName, Font, Brushes.Black, op.Left + op.Width / 2 - stringSize.Width / 2, op.Top + op.Height / 2 - stringSize.Height / 2);
                e.Graphics.Clip = new Region(op.Dimension);
                e.Graphics.DrawLine(lightPen, op.Left, op.Top, op.Left + op.Width, op.Top);
                e.Graphics.DrawLine(lightPen, op.Left, op.Top + 1, op.Left, op.Top + op.Height - 2);
                e.Graphics.DrawLine(darkPen, op.Left + 1, op.Top + op.Height - 1, op.Left + op.Width, op.Top + op.Height - 1);
                e.Graphics.DrawLine(darkPen, op.Left + op.Width - 1, op.Top + 1, op.Left + op.Width - 1, op.Top + op.Height - 2);
            }
            else if (op.GetType() == typeof(StoreOperator))
            {
                Point[] points1 = new Point[3];
                points1[0] = new Point(op.Left, op.Top);
                points1[1] = new Point(op.Left + 10, op.Top);
                points1[2] = new Point(op.Left + 10, op.Top + op.Height - 6);
                e.Graphics.FillPolygon(b, points1);
                Point[] points2 = new Point[3];
                points2[0] = new Point(op.Left + op.Width - 1, op.Top);
                points2[1] = new Point(op.Left + op.Width - 10, op.Top + op.Height - 6);
                points2[2] = new Point(op.Left + op.Width - 10, op.Top);
                e.Graphics.FillPolygon(b, points2);
                e.Graphics.FillRectangle(b, new Rectangle(op.Left + 10, op.Top, op.Width - 20, op.Height - 5));
                e.Graphics.Clip = new Region(new Rectangle(op.Left + 10, op.Top, op.Width - 20, op.Height - 5));
                SizeF stringSize = e.Graphics.MeasureString(displayName, Font);
                e.Graphics.DrawString(displayName, Font, Brushes.Black, op.Left + op.Width / 2 - stringSize.Width / 2, op.Top + (op.Height - 5) / 2 - stringSize.Height / 2);
                e.Graphics.Clip = new Region(op.Dimension);
                e.Graphics.DrawLine(darkPen, op.Left, op.Top, op.Left + 9, op.Top + op.Height - 6);
                e.Graphics.DrawLine(darkPen, op.Left + 10, op.Top + op.Height - 6 , op.Left + op.Width - 11, op.Top + op.Height - 6);
                e.Graphics.DrawLine(darkPen, op.Left + op.Width - 10, op.Top + op.Height - 6, op.Left + op.Width - 1, op.Top);
                e.Graphics.DrawLine(lightPen, op.Left, op.Top, op.Left + op.Width - 2, op.Top);
            }   
            else if (op.GetType() == typeof(LoadOperator))
            {
                Point[] points1 = new Point[3];
                points1[0] = new Point(op.Left, op.Top + op.Height);
                points1[1] = new Point(op.Left + 10, op.Top + op.Height);
                points1[2] = new Point(op.Left + 10, op.Top + 5);
                e.Graphics.FillPolygon(b, points1);
                Point[] points2 = new Point[3];
                points2[0] = new Point(op.Left + op.Width - 10, op.Top + 5);
                points2[1] = new Point(op.Left + op.Width, op.Top + op.Height);
                points2[2] = new Point(op.Left + op.Width - 10, op.Top + op.Height);
                e.Graphics.FillPolygon(b, points2);
                e.Graphics.FillRectangle(b, new Rectangle(op.Left + 10, op.Top + 5, op.Width - 20, op.Height - 5));
                e.Graphics.Clip = new Region(new Rectangle(op.Left + 10, op.Top + 5, op.Width - 20, op.Height - 5));
                SizeF stringSize = e.Graphics.MeasureString(displayName, Font);
                e.Graphics.DrawString(displayName, Font, Brushes.Black, op.Left + op.Width / 2 - stringSize.Width / 2, op.Top  + 5 + (op.Height - 5) / 2 - stringSize.Height / 2);
                e.Graphics.Clip = new Region(op.Dimension);
            }

            b.Dispose();
            lightPen.Dispose();
            darkPen.Dispose();

            if (!op.IsProcessable || op.IsWarningPresent)
                e.Graphics.DrawImage(VerkstanEditor.Properties.Resources.warning_icon, op.Location.X + 1, op.Location.Y + 1);
            if (op == ViewedOperator)
                e.Graphics.DrawImage(VerkstanEditor.Properties.Resources.eye_icon, op.Location.X + 1, op.Location.Y + 1);

            e.Graphics.Clip = clip;


            /*
            Rectangle rect = new Rectangle(op.Location, op.Size);
            SizeF stringSize = e.Graphics.MeasureString(op.Binding.DisplayName, Font);
            Point namePoint = new Point(rect.Width / 2 - (int)stringSize.Width / 2 + rect.X,
                                        rect.Height / 2 - (int)stringSize.Height / 2 + rect.Y);

            double brightness = 1.0;
            if (op.Selected)
                brightness = 1.3;
            double saturation = 0.0;
            if (op.Binding.IsProcessable())
                saturation = 1.0;

            Color color = RGBHSL.ModifyBrightness(op.Color, brightness);
            color = RGBHSL.ModifySaturation(color, saturation);
            Color lightColor = RGBHSL.ModifyBrightness(color, 1.3);
            Color darkColor = RGBHSL.ModifyBrightness(color, 0.7);
            Brush brush = new SolidBrush(color);
            Pen lightPen = new Pen(lightColor);
            Pen darkPen = new Pen(darkColor);

            Brush gradientBrush = new LinearGradientBrush(rect, lightColor, color, 0.0f);
            e.Graphics.FillRectangle(brush, rect);
            e.Graphics.DrawLine(lightPen,
                                op.Location.X,
                                op.Location.Y + op.Size.Height - 1,
                                op.Location.X,
                                op.Location.Y);
            e.Graphics.DrawLine(lightPen,
                                op.Location.X,
                                op.Location.Y,
                                op.Location.X + op.Size.Width - 1,
                                op.Location.Y);
            e.Graphics.DrawLine(darkPen,
                                op.Location.X + op.Size.Width - 1,
                                op.Location.Y,
                                op.Location.X + op.Size.Width - 1,
                                op.Location.Y + op.Size.Height - 1);
            e.Graphics.DrawLine(darkPen,
                                op.Location.X,
                                op.Location.Y + op.Size.Height - 1,
                                op.Location.X + op.Size.Width - 1,
                                op.Location.Y + op.Size.Height - 1);
            Brush textBrush = new SolidBrush(op.TextColor);
            e.Graphics.DrawString(op.Binding.DisplayName, Font, textBrush, namePoint);

            int x1 = op.GetAreaForResize().Left;
            int y1 = op.Location.Y + 3;
            int y2 = op.Location.Y + op.Size.Height - 4;

            for (int i = 0; i < 4; i++)
            {
                e.Graphics.DrawLine(lightPen,
                                    x1 + i * 3,
                                    y1,
                                    x1 + i * 3,
                                    y2);
                e.Graphics.DrawLine(darkPen,
                                    x1 + 1 + i * 3,
                                    y1,
                                    x1 + 1 + i * 3,
                                    y2);
            }

            if (!op.Binding.IsProcessable() || op.Binding.IsWarningPresent())
                e.Graphics.DrawImage(VerkstanEditor.Properties.Resources.warning_icon, op.Location.X + 1, op.Location.Y + 1);
            if (op == Operators.ViewedOperator)
                e.Graphics.DrawImage(VerkstanEditor.Properties.Resources.eye_icon, op.Location.X + 1, op.Location.Y + 1);
        */
        }
        private void AddOperator(String typeName)
        {
            Operator op = OperatorFactory.Create(typeName);
            page.Add(op, addLocation);
        }
        private Color GetOperatorColor(Operator op)
        {
            switch (op.Type)
            {
                case Verkstan.Constants.OperatorTypes.Texture:
                    return Color.FromArgb(250, 40, 50);
                case Verkstan.Constants.OperatorTypes.Mesh:
                    return Color.FromArgb(70, 245, 90);
                case Verkstan.Constants.OperatorTypes.Model:
                    return Color.FromArgb(70, 90, 255);
                case Verkstan.Constants.OperatorTypes.Renderer:
                    return Color.FromArgb(225, 71, 223);
                default:
                    return Color.FromArgb(190, 190, 100);
            }
        }
        private Point CalculateMovePoint()
        {
            Point p = Operator.QuantizeLocation(mouseLocation);
            Point moveMarkerLocation = Operator.QuantizeLocation(markLocation);
            return new Point(p.X - moveMarkerLocation.X,
                             p.Y - moveMarkerLocation.Y);
        }
        private int CalculateResizeWidth(int width)
        {
            return Operator.QuantizeSize(new Size(width + (mouseLocation.X - markLocation.X), 0)).Width;
        }
        private int CalculateRelativeResizeWidth()
        {
            return mouseLocation.X - markLocation.X;
        }
        private Rectangle CalculateSelectionRectangle()
        {
            int x1 = 0;
            int y1 = 0;
            int x2 = 0;
            int y2 = 0;

            if (mouseLocation.X < selectMarkLocation.X)
            {
                x1 = mouseLocation.X;
                x2 = selectMarkLocation.X;
            }
            else
            {
                x2 = mouseLocation.X;
                x1 = selectMarkLocation.X;
            }

            if (mouseLocation.Y < selectMarkLocation.Y)
            {
                y1 = mouseLocation.Y;
                y2 = selectMarkLocation.Y;
            }
            else
            {
                y2 = mouseLocation.Y;
                y1 = selectMarkLocation.Y;
            }

            return new Rectangle(x1, y1, x2 - x1, y2 - y1);
        }
        private Rectangle CalculateMoveRectangle()
        {
            ICollection<Operator> selected = page.GetSelected();
            Rectangle result = selected.First().Dimension;
           
            foreach (Operator op in selected)
                result = Rectangle.Union(result, op.Dimension);

            Point movePoint = CalculateMovePoint();
            result.X += movePoint.X;
            result.Y += movePoint.Y;

            return result;
        }
        private Rectangle CalculateResizeRectangle()
        {
            ICollection<Operator> selected = page.GetSelected();
            Rectangle result = selected.First().Dimension;
            result.Width = CalculateResizeWidth(result.Width);
            foreach (Operator op in selected)
            {
                Rectangle opDimension = op.Dimension;
                opDimension.Width = CalculateResizeWidth(opDimension.Width);
                result = Rectangle.Union(result, opDimension);
            }

            return result;
        }
        private void UpdateSize()
        {
            if (page == null)
                return;

            Rectangle dimension = page.CalculateDimension();

            // Check the size of the operators dimension.
            Point move = new Point();
            if (dimension.X < 0)
                move.X = -dimension.X - 1;
            if (dimension.Y < 0)
                move.Y = -dimension.Y - 1;

            // Move operators if necessary.
            if (move.X != 0 || move.Y != 0)
            {
                page.SelectAll();
                page.MoveSelected(move);
                page.DeselectAll();
                return; // We return as this method will be called again due to the move.
            }
           
            if (Size.Width < dimension.Width)
                Size = new Size(dimension.Width + 1, Size.Height);

            if (Size.Height < dimension.Height)
                Size = new Size(Size.Width, dimension.Height + 1);
        }
        #endregion
    }
}
