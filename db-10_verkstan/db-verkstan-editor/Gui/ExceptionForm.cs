using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace VerkstanEditor.Gui
{
    public partial class ExceptionForm : Form
    {
        #region Properties
        public String BackupFilename
        {
            set
            {
                label3.Text = value;
            }
        }
        public String Stacktrace
        {
            set
            {
                textBox1.Text = value;
            }
        }

        #endregion

        #region Constructors
        public ExceptionForm()
        {
            InitializeComponent();
        }
        #endregion
    }
}
