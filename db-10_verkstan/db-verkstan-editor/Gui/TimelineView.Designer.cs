namespace VerkstanEditor.Gui
{
    partial class TimelineView
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
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.splitContainer3 = new System.Windows.Forms.SplitContainer();
            this.splitContainer4 = new System.Windows.Forms.SplitContainer();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.addChannelToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.removeChannelToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.timelineChannelsPropertiesView1 = new VerkstanEditor.Gui.TimelineChannelsPropertiesView();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.splitContainer5 = new System.Windows.Forms.SplitContainer();
            this.splitPositionAndChannels = new System.Windows.Forms.SplitContainer();
            this.beatPositionLine1 = new VerkstanEditor.Gui.BeatPositionLine();
            this.timelineChannelsView1 = new VerkstanEditor.Gui.TimelineChannelsView();
            this.vScrollBar1 = new System.Windows.Forms.VScrollBar();
            this.splitContainer7 = new System.Windows.Forms.SplitContainer();
            this.splitContainer8 = new System.Windows.Forms.SplitContainer();
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.hScrollBar1 = new System.Windows.Forms.HScrollBar();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.splitContainer3.Panel1.SuspendLayout();
            this.splitContainer3.SuspendLayout();
            this.splitContainer4.Panel2.SuspendLayout();
            this.splitContainer4.SuspendLayout();
            this.contextMenuStrip1.SuspendLayout();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            this.splitContainer5.Panel1.SuspendLayout();
            this.splitContainer5.Panel2.SuspendLayout();
            this.splitContainer5.SuspendLayout();
            this.splitPositionAndChannels.Panel1.SuspendLayout();
            this.splitPositionAndChannels.Panel2.SuspendLayout();
            this.splitPositionAndChannels.SuspendLayout();
            this.splitContainer7.Panel1.SuspendLayout();
            this.splitContainer7.SuspendLayout();
            this.splitContainer8.Panel1.SuspendLayout();
            this.splitContainer8.Panel2.SuspendLayout();
            this.splitContainer8.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer1.IsSplitterFixed = true;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.splitContainer3);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.splitContainer2);
            this.splitContainer1.Size = new System.Drawing.Size(451, 259);
            this.splitContainer1.SplitterDistance = 135;
            this.splitContainer1.TabIndex = 0;
            // 
            // splitContainer3
            // 
            this.splitContainer3.BackColor = System.Drawing.SystemColors.Control;
            this.splitContainer3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer3.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.splitContainer3.IsSplitterFixed = true;
            this.splitContainer3.Location = new System.Drawing.Point(0, 0);
            this.splitContainer3.Margin = new System.Windows.Forms.Padding(0);
            this.splitContainer3.Name = "splitContainer3";
            this.splitContainer3.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer3.Panel1
            // 
            this.splitContainer3.Panel1.Controls.Add(this.splitContainer4);
            // 
            // splitContainer3.Panel2
            // 
            this.splitContainer3.Panel2.BackColor = System.Drawing.SystemColors.Control;
            this.splitContainer3.Panel2MinSize = 16;
            this.splitContainer3.Size = new System.Drawing.Size(133, 257);
            this.splitContainer3.SplitterDistance = 240;
            this.splitContainer3.SplitterWidth = 1;
            this.splitContainer3.TabIndex = 0;
            // 
            // splitContainer4
            // 
            this.splitContainer4.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.splitContainer4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer4.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer4.IsSplitterFixed = true;
            this.splitContainer4.Location = new System.Drawing.Point(0, 0);
            this.splitContainer4.Margin = new System.Windows.Forms.Padding(0);
            this.splitContainer4.Name = "splitContainer4";
            this.splitContainer4.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer4.Panel1
            // 
            this.splitContainer4.Panel1.BackColor = System.Drawing.SystemColors.Control;
            // 
            // splitContainer4.Panel2
            // 
            this.splitContainer4.Panel2.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.splitContainer4.Panel2.ContextMenuStrip = this.contextMenuStrip1;
            this.splitContainer4.Panel2.Controls.Add(this.timelineChannelsPropertiesView1);
            this.splitContainer4.Size = new System.Drawing.Size(133, 240);
            this.splitContainer4.SplitterDistance = 25;
            this.splitContainer4.SplitterWidth = 1;
            this.splitContainer4.TabIndex = 0;
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addChannelToolStripMenuItem,
            this.removeChannelToolStripMenuItem});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(200, 48);
            this.contextMenuStrip1.Opening += new System.ComponentModel.CancelEventHandler(this.contextMenuStrip1_Opening);
            // 
            // addChannelToolStripMenuItem
            // 
            this.addChannelToolStripMenuItem.Name = "addChannelToolStripMenuItem";
            this.addChannelToolStripMenuItem.Size = new System.Drawing.Size(199, 22);
            this.addChannelToolStripMenuItem.Text = "Add Channel";
            this.addChannelToolStripMenuItem.Click += new System.EventHandler(this.addChannelToolStripMenuItem_Click);
            // 
            // removeChannelToolStripMenuItem
            // 
            this.removeChannelToolStripMenuItem.Name = "removeChannelToolStripMenuItem";
            this.removeChannelToolStripMenuItem.Size = new System.Drawing.Size(199, 22);
            this.removeChannelToolStripMenuItem.Text = "Remove Selected Channel";
            this.removeChannelToolStripMenuItem.Click += new System.EventHandler(this.removeChannelToolStripMenuItem_Click);
            // 
            // timelineChannelsPropertiesView1
            // 
            this.timelineChannelsPropertiesView1.BackColor = System.Drawing.SystemColors.ControlText;
            this.timelineChannelsPropertiesView1.ChannelHeight = 31;
            this.timelineChannelsPropertiesView1.Location = new System.Drawing.Point(0, 0);
            this.timelineChannelsPropertiesView1.Margin = new System.Windows.Forms.Padding(0);
            this.timelineChannelsPropertiesView1.Name = "timelineChannelsPropertiesView1";
            this.timelineChannelsPropertiesView1.Size = new System.Drawing.Size(0, 0);
            this.timelineChannelsPropertiesView1.TabIndex = 0;
            this.timelineChannelsPropertiesView1.Timeline = null;
            // 
            // splitContainer2
            // 
            this.splitContainer2.BackColor = System.Drawing.SystemColors.Control;
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.splitContainer2.ForeColor = System.Drawing.SystemColors.Control;
            this.splitContainer2.IsSplitterFixed = true;
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Margin = new System.Windows.Forms.Padding(0);
            this.splitContainer2.Name = "splitContainer2";
            this.splitContainer2.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.Controls.Add(this.splitContainer5);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.splitContainer7);
            this.splitContainer2.Panel2MinSize = 16;
            this.splitContainer2.Size = new System.Drawing.Size(310, 257);
            this.splitContainer2.SplitterDistance = 240;
            this.splitContainer2.SplitterWidth = 1;
            this.splitContainer2.TabIndex = 0;
            // 
            // splitContainer5
            // 
            this.splitContainer5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer5.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.splitContainer5.IsSplitterFixed = true;
            this.splitContainer5.Location = new System.Drawing.Point(0, 0);
            this.splitContainer5.Margin = new System.Windows.Forms.Padding(0);
            this.splitContainer5.Name = "splitContainer5";
            // 
            // splitContainer5.Panel1
            // 
            this.splitContainer5.Panel1.Controls.Add(this.splitPositionAndChannels);
            // 
            // splitContainer5.Panel2
            // 
            this.splitContainer5.Panel2.Controls.Add(this.vScrollBar1);
            this.splitContainer5.Panel2MinSize = 16;
            this.splitContainer5.Size = new System.Drawing.Size(310, 240);
            this.splitContainer5.SplitterDistance = 293;
            this.splitContainer5.SplitterWidth = 1;
            this.splitContainer5.TabIndex = 0;
            // 
            // splitPositionAndChannels
            // 
            this.splitPositionAndChannels.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.splitPositionAndChannels.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitPositionAndChannels.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitPositionAndChannels.ForeColor = System.Drawing.SystemColors.ControlText;
            this.splitPositionAndChannels.IsSplitterFixed = true;
            this.splitPositionAndChannels.Location = new System.Drawing.Point(0, 0);
            this.splitPositionAndChannels.Margin = new System.Windows.Forms.Padding(0);
            this.splitPositionAndChannels.Name = "splitPositionAndChannels";
            this.splitPositionAndChannels.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitPositionAndChannels.Panel1
            // 
            this.splitPositionAndChannels.Panel1.BackColor = System.Drawing.SystemColors.Control;
            this.splitPositionAndChannels.Panel1.Controls.Add(this.beatPositionLine1);
            this.splitPositionAndChannels.Panel1.Font = new System.Drawing.Font("Microsoft Sans Serif", 6F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.splitPositionAndChannels.Panel1.ForeColor = System.Drawing.SystemColors.ControlDark;
            // 
            // splitPositionAndChannels.Panel2
            // 
            this.splitPositionAndChannels.Panel2.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.splitPositionAndChannels.Panel2.ContextMenuStrip = this.contextMenuStrip1;
            this.splitPositionAndChannels.Panel2.Controls.Add(this.timelineChannelsView1);
            this.splitPositionAndChannels.Panel2.Resize += new System.EventHandler(this.splitPositionAndChannels_Panel2_Resize);
            this.splitPositionAndChannels.Size = new System.Drawing.Size(293, 240);
            this.splitPositionAndChannels.SplitterDistance = 25;
            this.splitPositionAndChannels.SplitterWidth = 1;
            this.splitPositionAndChannels.TabIndex = 0;
            // 
            // beatPositionLine1
            // 
            this.beatPositionLine1.AutoScroll = true;
            this.beatPositionLine1.BeatWidth = 16;
            this.beatPositionLine1.ForeColor = System.Drawing.SystemColors.ControlDarkDark;
            this.beatPositionLine1.Location = new System.Drawing.Point(0, 0);
            this.beatPositionLine1.Margin = new System.Windows.Forms.Padding(2);
            this.beatPositionLine1.Name = "beatPositionLine1";
            this.beatPositionLine1.Size = new System.Drawing.Size(714, 25);
            this.beatPositionLine1.TabIndex = 0;
            // 
            // timelineChannelsView1
            // 
            this.timelineChannelsView1.BackColor = System.Drawing.SystemColors.ControlText;
            this.timelineChannelsView1.BeatWidth = 16;
            this.timelineChannelsView1.ChannelHeight = 31;
            this.timelineChannelsView1.Location = new System.Drawing.Point(0, 0);
            this.timelineChannelsView1.Mode = VerkstanEditor.Gui.TimelineChannelsView.Modes.Move;
            this.timelineChannelsView1.Name = "timelineChannelsView1";
            this.timelineChannelsView1.Size = new System.Drawing.Size(0, 0);
            this.timelineChannelsView1.TabIndex = 0;
            this.timelineChannelsView1.Timeline = null;
            this.timelineChannelsView1.ViewedClip = null;
            this.timelineChannelsView1.Resize += new System.EventHandler(this.timelineChannels1_Resize);
            this.timelineChannelsView1.ViewedClipChanged += new System.EventHandler(this.timelineChannelsView1_ViewedClipChanged);
            // 
            // vScrollBar1
            // 
            this.vScrollBar1.Dock = System.Windows.Forms.DockStyle.Right;
            this.vScrollBar1.Enabled = false;
            this.vScrollBar1.Location = new System.Drawing.Point(0, 0);
            this.vScrollBar1.Name = "vScrollBar1";
            this.vScrollBar1.Size = new System.Drawing.Size(16, 240);
            this.vScrollBar1.TabIndex = 0;
            this.vScrollBar1.Scroll += new System.Windows.Forms.ScrollEventHandler(this.vScrollBar1_Scroll);
            // 
            // splitContainer7
            // 
            this.splitContainer7.BackColor = System.Drawing.SystemColors.Control;
            this.splitContainer7.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer7.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.splitContainer7.IsSplitterFixed = true;
            this.splitContainer7.Location = new System.Drawing.Point(0, 0);
            this.splitContainer7.Margin = new System.Windows.Forms.Padding(0);
            this.splitContainer7.Name = "splitContainer7";
            // 
            // splitContainer7.Panel1
            // 
            this.splitContainer7.Panel1.Controls.Add(this.splitContainer8);
            this.splitContainer7.Panel1MinSize = 16;
            this.splitContainer7.Panel2MinSize = 16;
            this.splitContainer7.Size = new System.Drawing.Size(310, 16);
            this.splitContainer7.SplitterDistance = 293;
            this.splitContainer7.SplitterWidth = 1;
            this.splitContainer7.TabIndex = 0;
            // 
            // splitContainer8
            // 
            this.splitContainer8.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer8.Location = new System.Drawing.Point(0, 0);
            this.splitContainer8.Name = "splitContainer8";
            // 
            // splitContainer8.Panel1
            // 
            this.splitContainer8.Panel1.BackColor = System.Drawing.SystemColors.Control;
            this.splitContainer8.Panel1.Controls.Add(this.numericUpDown1);
            // 
            // splitContainer8.Panel2
            // 
            this.splitContainer8.Panel2.Controls.Add(this.hScrollBar1);
            this.splitContainer8.Size = new System.Drawing.Size(293, 16);
            this.splitContainer8.SplitterDistance = 45;
            this.splitContainer8.SplitterWidth = 1;
            this.splitContainer8.TabIndex = 0;
            // 
            // numericUpDown1
            // 
            this.numericUpDown1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.numericUpDown1.Location = new System.Drawing.Point(0, -4);
            this.numericUpDown1.Minimum = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.numericUpDown1.Name = "numericUpDown1";
            this.numericUpDown1.Size = new System.Drawing.Size(45, 20);
            this.numericUpDown1.TabIndex = 0;
            this.numericUpDown1.Value = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.numericUpDown1.ValueChanged += new System.EventHandler(this.numericUpDown1_ValueChanged);
            // 
            // hScrollBar1
            // 
            this.hScrollBar1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.hScrollBar1.Enabled = false;
            this.hScrollBar1.Location = new System.Drawing.Point(0, 0);
            this.hScrollBar1.Name = "hScrollBar1";
            this.hScrollBar1.Size = new System.Drawing.Size(247, 16);
            this.hScrollBar1.TabIndex = 0;
            this.hScrollBar1.Scroll += new System.Windows.Forms.ScrollEventHandler(this.hScrollBar1_Scroll);
            // 
            // TimelineView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.splitContainer1);
            this.Margin = new System.Windows.Forms.Padding(0);
            this.Name = "TimelineView";
            this.Size = new System.Drawing.Size(451, 259);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            this.splitContainer3.Panel1.ResumeLayout(false);
            this.splitContainer3.ResumeLayout(false);
            this.splitContainer4.Panel2.ResumeLayout(false);
            this.splitContainer4.ResumeLayout(false);
            this.contextMenuStrip1.ResumeLayout(false);
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel2.ResumeLayout(false);
            this.splitContainer2.ResumeLayout(false);
            this.splitContainer5.Panel1.ResumeLayout(false);
            this.splitContainer5.Panel2.ResumeLayout(false);
            this.splitContainer5.ResumeLayout(false);
            this.splitPositionAndChannels.Panel1.ResumeLayout(false);
            this.splitPositionAndChannels.Panel2.ResumeLayout(false);
            this.splitPositionAndChannels.ResumeLayout(false);
            this.splitContainer7.Panel1.ResumeLayout(false);
            this.splitContainer7.ResumeLayout(false);
            this.splitContainer8.Panel1.ResumeLayout(false);
            this.splitContainer8.Panel2.ResumeLayout(false);
            this.splitContainer8.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.SplitContainer splitContainer3;
        private System.Windows.Forms.SplitContainer splitContainer4;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.SplitContainer splitContainer5;
        private System.Windows.Forms.SplitContainer splitPositionAndChannels;
        private System.Windows.Forms.VScrollBar vScrollBar1;
        private System.Windows.Forms.SplitContainer splitContainer7;
        private System.Windows.Forms.SplitContainer splitContainer8;
        private System.Windows.Forms.HScrollBar hScrollBar1;
        private System.Windows.Forms.NumericUpDown numericUpDown1;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem addChannelToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem removeChannelToolStripMenuItem;
        private TimelineChannelsPropertiesView timelineChannelsPropertiesView1;
        private TimelineChannelsView timelineChannelsView1;
        private BeatPositionLine beatPositionLine1;
    }
}
