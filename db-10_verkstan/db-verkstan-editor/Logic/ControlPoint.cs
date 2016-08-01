using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace VerkstanEditor.Logic
{
    public class ControlPoint
    {
        #region Properties
        private float y;
        public float Y
        {
            get
            {
                return y;
            }
            set
            {
                if (y != value)
                {
                    lastY = y;
                    y = value;
                }
            }
        }
        private float lastY;
        public float LastY
        {
            get
            {
                return lastY;
            }
        }
        private int x;
        public int X
        {
            get
            {
                return x;
            }
            set
            {
                if (x != value)
                {
                    lastX = x;
                    x = value;
                }
            }
        }
        private int lastX;
        public int LastX
        {
            get
            {
                return lastX;
            }
        }
        private bool isSelected = false;
        public bool IsSelected
        {
            get
            {
                return isSelected;
            }
            set
            {
                if (isSelected != value)
                {
                    isSelected = value;
                    OnStateChanged();
                }
            }
        }
        #endregion

        #region Events
        public class EventArgs : System.EventArgs
        {
            public readonly ControlPoint ControlPoint;
            public EventArgs(ControlPoint controlPoint)
            {
                ControlPoint = controlPoint;
            }
        }
        public delegate void EventHandler(ControlPoint.EventArgs e);
        public event EventHandler StateChanged;
        protected void OnStateChanged()
        {
            if (StateChanged != null)
                StateChanged(new ControlPoint.EventArgs(this));
        }
        #endregion

        #region Public Methods
        public XmlElement ToXmlElement(XmlDocument doc)
        {
            XmlElement root = doc.CreateElement("controlpoint");
            XmlElement dimension = doc.CreateElement("dimension");
            dimension.SetAttribute("x", x.ToString());
            dimension.SetAttribute("y", y.ToString());
            root.AppendChild(dimension);
            return root;
        }
        public void FromXmlElement(XmlElement root)
        {
            foreach (XmlNode node in root.ChildNodes)
            {
                if (node.Name == "dimension")
                {
                    XmlElement element = (XmlElement)node;
                    X = int.Parse(element.GetAttribute("x"));
                    Y = float.Parse(element.GetAttribute("y"));
                }
            }
        }
        #endregion
    }
}
