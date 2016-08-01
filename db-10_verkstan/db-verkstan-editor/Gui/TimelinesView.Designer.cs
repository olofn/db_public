namespace VerkstanEditor.Gui
{
    partial class TimelinesView
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
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.timelinesComboBox1 = new System.Windows.Forms.ComboBox();
            this.selectedToolLabel = new System.Windows.Forms.Label();
            this.splineButton = new System.Windows.Forms.Button();
            this.generatorButton = new System.Windows.Forms.Button();
            this.moveButton = new System.Windows.Forms.Button();
            this.timelineView1 = new VerkstanEditor.Gui.TimelineView();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.timelinesComboBox1);
            this.splitContainer1.Panel1.Controls.Add(this.selectedToolLabel);
            this.splitContainer1.Panel1.Controls.Add(this.splineButton);
            this.splitContainer1.Panel1.Controls.Add(this.generatorButton);
            this.splitContainer1.Panel1.Controls.Add(this.moveButton);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.timelineView1);
            this.splitContainer1.Size = new System.Drawing.Size(621, 273);
            this.splitContainer1.SplitterDistance = 30;
            this.splitContainer1.SplitterWidth = 1;
            this.splitContainer1.TabIndex = 0;
            // 
            // timelinesComboBox1
            // 
            this.timelinesComboBox1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.timelinesComboBox1.FormattingEnabled = true;
            this.timelinesComboBox1.Location = new System.Drawing.Point(3, 5);
            this.timelinesComboBox1.Name = "timelinesComboBox1";
            this.timelinesComboBox1.Size = new System.Drawing.Size(121, 21);
            this.timelinesComboBox1.TabIndex = 4;
            this.timelinesComboBox1.SelectedIndexChanged += new System.EventHandler(this.timelinesComboBox1_SelectedIndexChanged);
            // 
            // selectedToolLabel
            // 
            this.selectedToolLabel.AutoSize = true;
            this.selectedToolLabel.Location = new System.Drawing.Point(300, 8);
            this.selectedToolLabel.Name = "selectedToolLabel";
            this.selectedToolLabel.Size = new System.Drawing.Size(97, 13);
            this.selectedToolLabel.TabIndex = 3;
            this.selectedToolLabel.Text = "Move tool selected";
            // 
            // splineButton
            // 
            this.splineButton.Location = new System.Drawing.Point(248, 3);
            this.splineButton.Name = "splineButton";
            this.splineButton.Size = new System.Drawing.Size(46, 23);
            this.splineButton.TabIndex = 2;
            this.splineButton.Text = "Spline";
            this.splineButton.UseVisualStyleBackColor = true;
            this.splineButton.Click += new System.EventHandler(this.splineButton_Click);
            // 
            // generatorButton
            // 
            this.generatorButton.Location = new System.Drawing.Point(179, 3);
            this.generatorButton.Name = "generatorButton";
            this.generatorButton.Size = new System.Drawing.Size(63, 23);
            this.generatorButton.TabIndex = 1;
            this.generatorButton.Text = "Generator";
            this.generatorButton.UseVisualStyleBackColor = true;
            this.generatorButton.Click += new System.EventHandler(this.generatorButton_Click);
            // 
            // moveButton
            // 
            this.moveButton.Location = new System.Drawing.Point(129, 3);
            this.moveButton.Name = "moveButton";
            this.moveButton.Size = new System.Drawing.Size(44, 23);
            this.moveButton.TabIndex = 0;
            this.moveButton.Text = "Move";
            this.moveButton.UseVisualStyleBackColor = true;
            this.moveButton.Click += new System.EventHandler(this.moveButton_Click);
            // 
            // timelineView1
            // 
            this.timelineView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.timelineView1.Location = new System.Drawing.Point(0, 0);
            this.timelineView1.Margin = new System.Windows.Forms.Padding(0);
            this.timelineView1.Mode = VerkstanEditor.Gui.TimelineChannelsView.Modes.Move;
            this.timelineView1.Name = "timelineView1";
            this.timelineView1.Size = new System.Drawing.Size(621, 242);
            this.timelineView1.TabIndex = 0;
            this.timelineView1.Timeline = null;
            this.timelineView1.ViewedClip = null;
            this.timelineView1.ViewedClipChanged += new System.EventHandler(this.timelineView1_ViewedClipChanged);
            // 
            // TimelinesView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.splitContainer1);
            this.Name = "TimelinesView";
            this.Size = new System.Drawing.Size(621, 273);
            this.VisibleChanged += new System.EventHandler(this.TimelinesView_VisibleChanged);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel1.PerformLayout();
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.Label selectedToolLabel;
        private System.Windows.Forms.Button splineButton;
        private System.Windows.Forms.Button generatorButton;
        private System.Windows.Forms.Button moveButton;
        private TimelineView timelineView1;
        private System.Windows.Forms.ComboBox timelinesComboBox1;
    }
}
