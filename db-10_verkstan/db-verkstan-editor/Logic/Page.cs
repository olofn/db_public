using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Xml;

namespace VerkstanEditor.Logic
{
    public class Page: IDisposable
    {
        #region Private Variables
        Operator.EventHandler stateChangedHandler;
        #endregion

        #region Properties
        private List<Operator> operators;
        public ICollection<Operator> Operators
        {
            get
            {
                return operators.AsReadOnly();
            }
        }
        #endregion

        #region Events
        public class EventArgs : System.EventArgs
        {
            public readonly ICollection<Operator> Operators;
            public EventArgs(ICollection<Operator> operators)
            {
                Operators = operators;
            }
        }
        public delegate void EventHandler(EventArgs e);
        public event EventHandler Added;
        protected void OnAdded(ICollection<Operator> operators)
        {
            if (Added != null)
                Added(new Page.EventArgs(operators));
        }
        public event EventHandler Removed;
        protected void OnRemoved(ICollection<Operator> operators)
        {
            if (Removed != null)
                Removed(new Page.EventArgs(operators));
        }
        public event EventHandler Moved;
        protected void OnMoved(ICollection<Operator> operators)
        {
            if (Moved != null)
                Moved(new Page.EventArgs(operators));
        }
        public event EventHandler StateChanged;
        protected void OnStateChanged(Operator op)
        {
            ICollection<Operator> operators = new List<Operator>();
            operators.Add(op);
            if (StateChanged != null)
                StateChanged(new Page.EventArgs(operators));
        }
        public event EventHandler Resized;
        protected void OnResized(Operator op)
        {
            ICollection<Operator> operators = new List<Operator>();
            operators.Add(op);
            if (Resized != null)
                Resized(new Page.EventArgs(operators));
        }
        #endregion

        #region Constructors
        public Page()
        {
            operators = new List<Operator>();
            stateChangedHandler = new Operator.EventHandler(this.operator_StateChanged);
        }
        #endregion

        #region Public Methods
        public void Dispose()
        {
            foreach (Operator op in operators)
                op.Dispose();
        }
        public bool Add(Operator op, Point point)
        {
            Point p = Operator.QuantizeLocation(point);
            op.Dimension = new Rectangle(p.X, p.Y, op.Width, op.Height);
            foreach (Operator presentOp in operators)
            {
                if (presentOp.Dimension.IntersectsWith(op.Dimension))
                    return false;
            }

            operators.Add(op);
            ICollection<Operator> added = new List<Operator>();
            added.Add(op);
            OnAdded(added);
            Connect(op);
            op.StateChanged += stateChangedHandler;

            // As present load operators might have this operator as target
            // we have to tell all load operators that an operator has been added.
            LoadOperator.PropagateOnOperatorAdded(op);

            return true;
        }
        public void Remove(Operator op)
        {
            operators.Remove(op);
            ICollection<Operator> removed = new List<Operator>();
            removed.Add(op);
            OnRemoved(removed);
            Disconnect(op);
            op.StateChanged -= stateChangedHandler;
            op.Dispose();
        }
        public void Clear()
        {
            ICollection<Operator> removed = new List<Operator>();

            foreach (Operator op in operators)
                removed.Add(op);

            operators.Clear();
            OnRemoved(removed);

            foreach (Operator op in operators)
            {
                Disconnect(op);
                op.StateChanged -= stateChangedHandler;
                op.Dispose();
            }
        }
        public void Select(Rectangle rectangle)
        {
            ICollection<Operator> oldSelection = GetSelected();
            ICollection<Operator> newSelection = GetIn(rectangle);

            foreach (Operator op in oldSelection)
                if (!newSelection.Contains(op))
                    op.IsSelected = false;

            foreach (Operator op in newSelection)
                if (!oldSelection.Contains(op))
                    op.IsSelected = true;
        }
        public ICollection<Operator> GetSelected()
        {
            ICollection<Operator> selected = new List<Operator>();

            foreach (Operator op in operators)
                if (op.IsSelected)
                    selected.Add(op);

            return selected;
        }
        public ICollection<Operator> GetNotSelected()
        {
            ICollection<Operator> notSelected = new List<Operator>();

            foreach (Operator op in operators)
                if (!op.IsSelected)
                    notSelected.Add(op);

            return notSelected;
        }
        public Operator GetAt(Point point)
        {
            foreach (Operator op in operators)
                if (op.Dimension.Contains(point))
                    return op;
            return null;
        }
        public ICollection<Operator> GetIn(Rectangle rectangle)
        {
            List<Operator> result = new List<Operator>();

            foreach (Operator op in operators)
                if (rectangle.IntersectsWith(op.Dimension))
                    result.Add(op);

            result.Sort(delegate(Operator op1, Operator op2)
            {
                return op1.Dimension.X.CompareTo(op2.Dimension.X);
            });

            return result;
        }
        public void DeselectAll()
        {
            foreach (Operator op in operators)
                if (op.IsSelected)
                    op.IsSelected = false;
        }
        public void SelectAll()
        {
            foreach (Operator op in operators)
                if (!op.IsSelected)
                    op.IsSelected = true;
        }
        public void RemoveSelected()
        {
            ICollection<Operator> selected = GetSelected();
            foreach (Operator op in selected)
                operators.Remove(op);

            OnRemoved(selected);

            foreach (Operator op in selected)
            {
                Disconnect(op);
                op.StateChanged -= stateChangedHandler;
                op.Dispose();
            }
        }
        public void MoveSelected(Point point)
        {
            ICollection<Operator> selected = GetSelected();
            ICollection<Operator> notSelected = GetNotSelected();

            bool moveNecessary = false;
            foreach (Operator selectedOp in selected)
            {
                Point p = Operator.QuantizeLocation(new Point(selectedOp.Left + point.X,
                                                              selectedOp.Top + point.Y));
                Rectangle selectedOpDim = new Rectangle(p.X,
                                                        p.Y,
                                                        selectedOp.Width,
                                                        selectedOp.Height);

                if (!selectedOpDim.Equals(selectedOp.Dimension))
                    moveNecessary = true;
                    
                foreach (Operator nonSelectedOp in notSelected)
                {
                    if (nonSelectedOp.Dimension.IntersectsWith(selectedOpDim))
                    {
                        // Cannot peform move due to a collision.
                        return;
                    }
                }
            }

            if (!moveNecessary)
                return;

            foreach (Operator op in selected)
            {
                operators.Remove(op);
                Disconnect(op);
            }

            foreach (Operator op in selected)
            {
                Move(op, point);
            }

            foreach (Operator op in selected)
            {
                operators.Add(op);
                Connect(op);
            }

            OnMoved(selected);
        }
        public void ResizeSelected(int width)
        {
            ICollection<Operator> selected = GetSelected();
            ICollection<Operator> notSelected = GetNotSelected();

            foreach (Operator selectedOp in selected)
            {
                Size s = Operator.QuantizeSize(new Size(selectedOp.Width + width, selectedOp.Height));
                Rectangle selectedOpDim = new Rectangle(selectedOp.Left,
                                                        selectedOp.Top,
                                                        s.Width,
                                                        s.Height);

                foreach (Operator nonSelectedOp in notSelected)
                {
                    if (nonSelectedOp.Dimension.IntersectsWith(selectedOpDim))
                    {
                        // Cannot peform resize due to a collision.
                        return;
                    }
                }
            }

            foreach (Operator op in selected)
                if (Resize(op, width))
                    OnResized(op);
        }
        public Rectangle CalculateDimension()
        {
            int x1 = 0;
            int y1 = 0;
            int x2 = 0;
            int y2 = 0;

            foreach (Operator op in operators)
            {
                if (op.Location.X < x1)
                    x1 = op.Location.X;
                if (op.Location.Y < y1)
                    y1 = op.Location.Y;
                if (op.Location.X + op.Size.Width > x2)
                    x2 = op.Location.X + op.Size.Width;
                if (op.Location.Y + op.Size.Height > y2)
                    y2 = op.Location.Y + op.Size.Height;
            }

            return new Rectangle(x1, y1, x2 - x1, y2 - y1);
        }
        public XmlElement ToXmlElement(XmlDocument doc)
        {
            XmlElement root = doc.CreateElement("page");
            foreach (Operator op in Operators)
                root.AppendChild(op.ToXmlElement(doc));

            return root;
        }
        public void FromXmlElement(XmlElement root)
        {
            foreach (XmlNode node in root.ChildNodes)
            {
                if (node.Name == "operator")
                {
                    XmlElement opElement = (XmlElement)node;
                    Operator op = OperatorFactory.Create(opElement.GetAttribute("type"));
                    op.FromXmlElement(opElement);
                    Add(op, op.Location);
                }
            }
        }
        #endregion

        #region Event Handlers
        public void operator_StateChanged(Operator.EventArgs e)
        {
            OnStateChanged(e.Operator);
        }
        #endregion

        #region Private Methods
        private bool Move(Operator op, Point point)
        {
            Point newLocation = Operator.QuantizeLocation(new Point(op.Left + point.X,
                                                                    op.Top + point.Y));

            // Don't move the operator if it hasn't been moved.
            if (newLocation == op.Location)
                return false;

            op.Dimension = new Rectangle(newLocation.X, newLocation.Y, op.Width, op.Height);
            return true;
        }
        private bool Resize(Operator op, int width)
        {
            Size newSize = Operator.QuantizeSize(new Size(op.Width + width, op.Height));

            // Don't resize the operator if it hasn't been resized.
            if (newSize == op.Size)
                return false;

            op.Dimension = new Rectangle(op.Left, op.Top, newSize.Width, newSize.Height);
            Disconnect(op);
            Connect(op);
            return true;
        }
        private void Disconnect(Operator op)
        {
            Operator.Disconnect(op);
        }
        private void Connect(Operator op)
        {
            ICollection<Operator> inConnections = GetIn(op.GetAreaForInConnections());
            foreach (Operator inOperator in inConnections)
                Operator.Connect(inOperator, op);

            ICollection<Operator> outConnections = GetIn(op.GetAreaForOutConnections());
            foreach (Operator outOperator in outConnections)
            {
                // Here we do a special trick with the outOperator.
                // Instead of simply connection the op operator we
                // disconnect the outOperator and reconnect it so it will
                // refresh it's input connection. By doing this we know
                // the order of inputs for the outOperator will stay fixed,
                // i.e. the left most input operator will be the first input
                // and the right most input operator will be the last input.
                // This is very important for operators that rely on a certain
                // order of inputs (like the distortion operator that takes
                // a texture to distort as the first input and a texture telling
                // the distortion operator how to the distort the first input as
                // second input).
                Disconnect(outOperator);
                Connect(outOperator);
            }
        }
        #endregion
    }
}
