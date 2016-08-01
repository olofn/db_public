namespace VerkstanEditor.Gui
{
    partial class OperatorPageViewPanel
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
            this.menu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.SuspendLayout();
            // 
            // menu
            // 
            this.menu.Name = "menu";
            this.menu.RenderMode = System.Windows.Forms.ToolStripRenderMode.Professional;
            this.menu.Size = new System.Drawing.Size(61, 4);
            this.menu.Opened += new System.EventHandler(this.menu_Opened);
            // 
            // OperatorPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ContextMenuStrip = this.menu;
            this.Name = "OperatorPage";
            this.Load += new System.EventHandler(this.OperatorPage_Load);
            this.DoubleClick += new System.EventHandler(this.OperatorPage_DoubleClick);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.OperatorPage_Paint);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.OperatorPage_MouseMove);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.OperatorPage_MouseDown);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.OperatorPage_MouseUp);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.OperatorPage_KeyDown);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ContextMenuStrip menu;
    }
}
