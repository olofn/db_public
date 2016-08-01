using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Xml;

namespace VerkstanEditor.Logic
{
    public class SplineClip: Clip
    {
        #region Properties
        public Verkstan.CoreSplineClip BindedSplineCoreClip
        {
            get
            {
                return bindedSplineCoreClip;
            }
        }
        public override ushort Id
        {
            get { return bindedSplineCoreClip.Id; }
        }
        public ICollection<ControlPoint> ControlPoints
        {
            get
            {
                return controlPoints;
            }
        }
        public ControlPoint Selected
        {
            get
            {
                foreach (ControlPoint controlPoint in controlPoints)
                    if (controlPoint.IsSelected)
                        return controlPoint;
                return null;
            }
        }
        #endregion

        #region Private Variables
        private Verkstan.CoreSplineClip bindedSplineCoreClip;
        private List<ControlPoint> controlPoints;
        private ControlPoint.EventHandler controlPointStateChangedHandler;
        #endregion

        #region Constructors
        public SplineClip()
        {
            bindedSplineCoreClip = new Verkstan.CoreSplineClip();
            SetBindedCoreClip(bindedSplineCoreClip);
            controlPoints = new List<ControlPoint>();
            controlPointStateChangedHandler = new ControlPoint.EventHandler(this.controlPoint_StateChanged);
        }
        #endregion

        #region Public Methods
        public int GetSplineType()
        {
            return bindedSplineCoreClip.GetSplineType();
        }
        public void SetSplineType(int type)
        {
            bindedSplineCoreClip.SetSplineType(type);
            DestroyPreview();
            OnStateChanged();
        }
        public override void Dispose()
        {
            bindedSplineCoreClip.Dispose();
        }
        public void Add(ControlPoint controlPoint, int x, float y)
        {
            Deselect();
            controlPoint.X = x;
            controlPoint.Y = y;
            controlPoint.IsSelected = true;
            controlPoints.Add(controlPoint);
            controlPoint.StateChanged += controlPointStateChangedHandler;
            DestroyPreview();
            UpdateCoreClip();
            OnAdded(controlPoint);
        }
        public void RemoveSelected()
        {
            ControlPoint selected = Selected;

            if (selected == null)
                return;

            controlPoints.Remove(selected);
            DestroyPreview();
            UpdateCoreClip();
            OnRemoved(selected);
        }
        public void MoveSelected(int x, float y)
        {
            ControlPoint selected = Selected;

            if (selected == null)
                return;

            selected.X = x;
            selected.Y = y;
            DestroyPreview();
            UpdateCoreClip();
            OnMoved(selected);
        }
        public void Select(int x, float y, int xRelax, float yRelax)
        {
            Deselect();
            foreach (ControlPoint controlPoint in controlPoints)
            {
                if (controlPoint.X > x - xRelax
                    && controlPoint.X < x + xRelax
                    && controlPoint.Y > y - yRelax
                    && controlPoint.Y < y + yRelax)
                {
                    controlPoint.IsSelected = true;
                    return;
                }
            }
        }
        public void Deselect()
        {
            foreach (ControlPoint controlPoint in controlPoints)
                if (controlPoint.IsSelected)
                    controlPoint.IsSelected = false;
        }
        public override XmlElement ToXmlElement(XmlDocument doc)
        {
            XmlElement root = doc.CreateElement("clip");
            root.SetAttribute("type", "spline");

            PopulateXmlElementWithBasicClipInformation(root, doc);
        
            XmlElement splineTypeElement = doc.CreateElement("splinetype");
            splineTypeElement.InnerText = GetSplineType().ToString();
            root.AppendChild(splineTypeElement);

            XmlElement controlPointsElement = doc.CreateElement("controlpoints");
            root.AppendChild(controlPointsElement);

            foreach (ControlPoint controlPoint in controlPoints)
                controlPointsElement.AppendChild(controlPoint.ToXmlElement(doc));

            return root;
        }
        public override void FromXmlElement(XmlElement root)
        {
            PopulateClipWithBasicInformationFromXmlElement(root);

            foreach (XmlNode node in root.ChildNodes)
            {
                if (node.Name == "splinetype")
                {
                    int type = int.Parse(node.InnerText);
                    SetSplineType(type);
                }
                else if (node.Name == "controlpoints")
                {
                    foreach (XmlNode subnode in node.ChildNodes)
                    {
                        ControlPoint controlPoint = new ControlPoint();
                        controlPoint.FromXmlElement((XmlElement)subnode);
                        Add(controlPoint, controlPoint.X, controlPoint.Y);
                    }
                }
            }
        }
        #endregion

        #region Private Methods
        private void UpdateCoreClip()
        {
            controlPoints.Sort(delegate(ControlPoint p1, ControlPoint p2)
            {
                return p1.X.CompareTo(p2.X);
            });

            for(int i = 0; i < controlPoints.Count; i++)
                bindedSplineCoreClip.SetControlPoint(i, controlPoints[i].X, (sbyte)(128 * controlPoints[i].Y));

            bindedSplineCoreClip.SetNumberOfControlPoints(controlPoints.Count);
        }
        #endregion

        #region Events
        public class EventArgs : System.EventArgs
        {
            public readonly ICollection<ControlPoint> ControlPoints;
            public EventArgs(ICollection<ControlPoint> controlPoints)
            {
                ControlPoints = controlPoints;
            }
        }
        public delegate void EventHandler(SplineClip.EventArgs e);
        public event EventHandler ControlPointStateChanged;
        protected void OnControlPointStateChanged(ControlPoint controlPoint)
        {
            List<ControlPoint> controlPoints = new List<ControlPoint>();
            controlPoints.Add(controlPoint);
            if (ControlPointStateChanged != null)
                ControlPointStateChanged(new SplineClip.EventArgs(controlPoints));
        }
        public event EventHandler Added;
        protected void OnAdded(ControlPoint controlPoint)
        {
            List<ControlPoint> controlPoints = new List<ControlPoint>();
            controlPoints.Add(controlPoint);
            if (Added != null)
                Added(new SplineClip.EventArgs(controlPoints));
        }
        public event EventHandler Removed;
        protected void OnRemoved(ControlPoint controlPoint)
        {
            List<ControlPoint> controlPoints = new List<ControlPoint>();
            controlPoints.Add(controlPoint);
            if (Removed != null)
                Removed(new SplineClip.EventArgs(controlPoints));
        }
        public event EventHandler Moved;
        protected void OnMoved(ControlPoint controlPoint)
        {
            List<ControlPoint> controlPoints = new List<ControlPoint>();
            controlPoints.Add(controlPoint);
            if (Moved != null)
                Moved(new SplineClip.EventArgs(controlPoints));
        }
        #endregion

        #region Event Handlers
        private void controlPoint_StateChanged(ControlPoint.EventArgs e)
        {
            OnControlPointStateChanged(e.ControlPoint);
        }
        #endregion
    }
}
