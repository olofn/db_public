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
    public partial class OperatorPageView : UserControl
    {
        #region Properties
        private Page page;
        public Page Page
        {
            set
            {
                page = value;
                operatorPageViewPanel1.Page = value;
            }
            get
            {
                return page;
            }
        }
        private Operator viewedOperator;
        public Operator ViewedOperator
        {
            set
            {
                viewedOperator = value;
                OnViewedOperatorChanged();
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
        public OperatorPageView()
        {
            InitializeComponent();
            operatorPageViewPanel1.MouseWheel += new MouseEventHandler(operatorPagePanel1_MouseWheel);
        }
        #endregion

        #region Event Handlers
        private void operatorPagePanel1_Resize(object sender, EventArgs e)
        {
            UpdateScrollBars();
        }
        private void OperatorPage_Resize(object sender, EventArgs e)
        {
            if (operatorPageViewPanel1.Width < (Width - vScrollBar1.Width - 1))
                operatorPageViewPanel1.Width = (Width - vScrollBar1.Width - 1);
            if (operatorPageViewPanel1.Height < (Height - hScrollBar1.Height - 1))
                operatorPageViewPanel1.Height = (Height - hScrollBar1.Height - 1);

            UpdateScrollBars();
        }
        private void operatorPagePanel1_MouseWheel(object sender, MouseEventArgs e)
        {
            if (e.Delta > 0)
            {
                if (vScrollBar1.Value - vScrollBar1.SmallChange > vScrollBar1.Minimum)
                    vScrollBar1.Value -= vScrollBar1.SmallChange;
                else
                    vScrollBar1.Value = vScrollBar1.Minimum;
            }
            else
            {
                if (vScrollBar1.Value + vScrollBar1.SmallChange < (vScrollBar1.Maximum - vScrollBar1.LargeChange + 1))
                    vScrollBar1.Value += vScrollBar1.SmallChange;
                else
                    vScrollBar1.Value = vScrollBar1.Maximum - vScrollBar1.LargeChange + 1;
            }

            operatorPageViewPanel1.Top = -vScrollBar1.Value;
        }
        private void hScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            operatorPageViewPanel1.Left = -e.NewValue; 
        }
        private void vScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            operatorPageViewPanel1.Top = -e.NewValue;
        }
        private void hScrollBar1_Layout(object sender, LayoutEventArgs e)
        {
            hScrollBar1.Width = Width - vScrollBar1.Width - 1;
        }
        private void vScrollBar1_Layout(object sender, LayoutEventArgs e)
        {
            vScrollBar1.Height = Height - hScrollBar1.Height - 1;
        }
        private void operatorPageViewPanel1_ViewedOperatorChanged(object sender, EventArgs e)
        {
            ViewedOperator = operatorPageViewPanel1.ViewedOperator;
        }
        private void operatorPageViewPanel1_ViewedOperatorPropertiesChanged(object sender, EventArgs e)
        {
            ViewedOperatorProperties = operatorPageViewPanel1.ViewedOperatorProperties;
        }
        #endregion

        #region Private Methods
        private void UpdateScrollBars()
        {
            hScrollBar1.Enabled = operatorPageViewPanel1.Width > (Width - vScrollBar1.Width - 1);
            vScrollBar1.Enabled = operatorPageViewPanel1.Height > (Height - hScrollBar1.Height - 1);

            hScrollBar1.Minimum = 0;
            hScrollBar1.Maximum = operatorPageViewPanel1.Width;
            hScrollBar1.LargeChange = Width - vScrollBar1.Width;
            hScrollBar1.SmallChange = 10;  
            vScrollBar1.Minimum = 0;
            vScrollBar1.Maximum = operatorPageViewPanel1.Height;
            vScrollBar1.LargeChange = Height - hScrollBar1.Height;
            vScrollBar1.SmallChange = 10;

            if (!hScrollBar1.Enabled)
                operatorPageViewPanel1.Left = 0;

            if (!vScrollBar1.Enabled)
                operatorPageViewPanel1.Top = 0;
        }
        #endregion
    }
}
