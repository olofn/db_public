namespace VerkstanEditor.Gui
{
    partial class OperatorPageView
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.hScrollBar1 = new System.Windows.Forms.HScrollBar();
            this.vScrollBar1 = new System.Windows.Forms.VScrollBar();
            this.operatorPageViewPanel1 = new VerkstanEditor.Gui.OperatorPageViewPanel();
            this.SuspendLayout();
            // 
            // hScrollBar1
            // 
            this.hScrollBar1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.hScrollBar1.Enabled = false;
            this.hScrollBar1.Location = new System.Drawing.Point(0, 259);
            this.hScrollBar1.Name = "hScrollBar1";
            this.hScrollBar1.Size = new System.Drawing.Size(246, 16);
            this.hScrollBar1.TabIndex = 0;
            this.hScrollBar1.Layout += new System.Windows.Forms.LayoutEventHandler(this.hScrollBar1_Layout);
            this.hScrollBar1.Scroll += new System.Windows.Forms.ScrollEventHandler(this.hScrollBar1_Scroll);
            // 
            // vScrollBar1
            // 
            this.vScrollBar1.Dock = System.Windows.Forms.DockStyle.Right;
            this.vScrollBar1.Enabled = false;
            this.vScrollBar1.Location = new System.Drawing.Point(230, 0);
            this.vScrollBar1.Name = "vScrollBar1";
            this.vScrollBar1.Size = new System.Drawing.Size(16, 259);
            this.vScrollBar1.TabIndex = 1;
            this.vScrollBar1.Layout += new System.Windows.Forms.LayoutEventHandler(this.vScrollBar1_Layout);
            this.vScrollBar1.Scroll += new System.Windows.Forms.ScrollEventHandler(this.vScrollBar1_Scroll);
            // 
            // operatorPageViewPanel1
            // 
            this.operatorPageViewPanel1.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.operatorPageViewPanel1.Location = new System.Drawing.Point(0, 0);
            this.operatorPageViewPanel1.Name = "operatorPageViewPanel1";
            this.operatorPageViewPanel1.Page = null;
            this.operatorPageViewPanel1.Size = new System.Drawing.Size(150, 150);
            this.operatorPageViewPanel1.TabIndex = 2;
            this.operatorPageViewPanel1.ViewedOperator = null;
            this.operatorPageViewPanel1.ViewedOperatorProperties = null;
            this.operatorPageViewPanel1.ViewedOperatorPropertiesChanged += new System.EventHandler(this.operatorPageViewPanel1_ViewedOperatorPropertiesChanged);
            this.operatorPageViewPanel1.Resize += new System.EventHandler(this.operatorPagePanel1_Resize);
            this.operatorPageViewPanel1.ViewedOperatorChanged += new System.EventHandler(this.operatorPageViewPanel1_ViewedOperatorChanged);
            // 
            // OperatorPageView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.Controls.Add(this.vScrollBar1);
            this.Controls.Add(this.hScrollBar1);
            this.Controls.Add(this.operatorPageViewPanel1);
            this.Name = "OperatorPageView";
            this.Size = new System.Drawing.Size(246, 275);
            this.Resize += new System.EventHandler(this.OperatorPage_Resize);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.HScrollBar hScrollBar1;
        private System.Windows.Forms.VScrollBar vScrollBar1;
        private OperatorPageViewPanel operatorPageViewPanel1;
    }
}
