namespace VorlonSeq
{
    partial class ChannelTimeline
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
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.loadPatchToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.savePatchToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.contextMenuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.Filter = "Vorlon 2 patch files (*.vpa)|*.vpa|All files (*.*)|*.*";
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.loadPatchToolStripMenuItem,
            this.toolStripMenuItem1,
            this.savePatchToolStripMenuItem});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(141, 54);
            // 
            // loadPatchToolStripMenuItem
            // 
            this.loadPatchToolStripMenuItem.Name = "loadPatchToolStripMenuItem";
            this.loadPatchToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.loadPatchToolStripMenuItem.Text = "Patch";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(137, 6);
            // 
            // savePatchToolStripMenuItem
            // 
            this.savePatchToolStripMenuItem.Name = "savePatchToolStripMenuItem";
            this.savePatchToolStripMenuItem.Size = new System.Drawing.Size(140, 22);
            this.savePatchToolStripMenuItem.Text = "Save Patch...";
            this.savePatchToolStripMenuItem.Click += new System.EventHandler(this.savePatchToolStripMenuItem_Click);
            // 
            // ChannelTimeline
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ContextMenuStrip = this.contextMenuStrip1;
            this.Name = "ChannelTimeline";
            this.Size = new System.Drawing.Size(680, 460);
            this.Load += new System.EventHandler(this.ChannelTimeline_Load);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.ChannelTimeline_Paint);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.ChannelTimeline_MouseMove);
            this.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.ChannelTimeline_MouseDoubleClick);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.ChannelTimeline_KeyUp);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.ChannelTimeline_MouseDown);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.ChannelTimeline_MouseUp);
            this.SizeChanged += new System.EventHandler(this.ChannelTimeline_SizeChanged);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.ChannelTimeline_KeyDown);
            this.contextMenuStrip1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem loadPatchToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem savePatchToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
    }
}
