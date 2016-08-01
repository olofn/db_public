using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace VorlonSeq
{
    public partial class ProperScrollPanel : Panel
    {
        public ProperScrollPanel()
        {
            InitializeComponent();
        }

        protected override Point ScrollToControl(Control activeControl)
        {
            return AutoScrollPosition;
        }
    }
}
