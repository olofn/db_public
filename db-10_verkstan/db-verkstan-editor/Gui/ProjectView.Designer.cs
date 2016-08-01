namespace VerkstanEditor.Gui
{
    partial class ProjectView
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ProjectView));
            this.fastRenderTimer = new System.Windows.Forms.Timer(this.components);
            this.mainMenu = new System.Windows.Forms.MenuStrip();
            this.mainMenuFile = new System.Windows.Forms.ToolStripMenuItem();
            this.newMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exportAsHeaderMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.viewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.resetCameraMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tileTextureMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.filterTextureMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.solidMeshMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.lightModelMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mainMenuHelp = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripContainer1 = new System.Windows.Forms.ToolStripContainer();
            this.mainTransportSplitContainer = new System.Windows.Forms.SplitContainer();
            this.mainLeftAndRightSplitContainer = new System.Windows.Forms.SplitContainer();
            this.previewBoardSplitContainer = new System.Windows.Forms.SplitContainer();
            this.previewPanel = new System.Windows.Forms.Panel();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.stacksTab = new System.Windows.Forms.TabPage();
            this.operatorPageView1 = new VerkstanEditor.Gui.OperatorPageView();
            this.timelinesTab = new System.Windows.Forms.TabPage();
            this.timelinesView1 = new VerkstanEditor.Gui.TimelinesView();
            this.clipTab = new System.Windows.Forms.TabPage();
            this.clipView1 = new VerkstanEditor.Gui.ClipView();
            this.operatorPropertyGrid = new VerkstanEditor.Gui.OperatorPropertyGrid();
            this.transport1 = new VerkstanEditor.Gui.Transport();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.slowRenderTimer = new System.Windows.Forms.Timer(this.components);
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.exportAsHeaderSaveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.mainMenu.SuspendLayout();
            this.toolStripContainer1.ContentPanel.SuspendLayout();
            this.toolStripContainer1.SuspendLayout();
            this.mainTransportSplitContainer.Panel1.SuspendLayout();
            this.mainTransportSplitContainer.Panel2.SuspendLayout();
            this.mainTransportSplitContainer.SuspendLayout();
            this.mainLeftAndRightSplitContainer.Panel1.SuspendLayout();
            this.mainLeftAndRightSplitContainer.Panel2.SuspendLayout();
            this.mainLeftAndRightSplitContainer.SuspendLayout();
            this.previewBoardSplitContainer.Panel1.SuspendLayout();
            this.previewBoardSplitContainer.Panel2.SuspendLayout();
            this.previewBoardSplitContainer.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.stacksTab.SuspendLayout();
            this.timelinesTab.SuspendLayout();
            this.clipTab.SuspendLayout();
            this.SuspendLayout();
            // 
            // fastRenderTimer
            // 
            this.fastRenderTimer.Interval = 10;
            this.fastRenderTimer.Tick += new System.EventHandler(this.FastRenderTimer_Tick);
            // 
            // mainMenu
            // 
            this.mainMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mainMenuFile,
            this.viewToolStripMenuItem,
            this.mainMenuHelp});
            this.mainMenu.Location = new System.Drawing.Point(0, 0);
            this.mainMenu.Name = "mainMenu";
            this.mainMenu.Size = new System.Drawing.Size(766, 24);
            this.mainMenu.TabIndex = 0;
            this.mainMenu.Text = "menuStrip1";
            // 
            // mainMenuFile
            // 
            this.mainMenuFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newMenuItem,
            this.openMenuItem,
            this.saveMenuItem,
            this.saveAsMenuItem,
            this.exportAsHeaderMenuItem,
            this.exitMenuItem});
            this.mainMenuFile.Name = "mainMenuFile";
            this.mainMenuFile.Size = new System.Drawing.Size(35, 20);
            this.mainMenuFile.Text = "File";
            // 
            // newMenuItem
            // 
            this.newMenuItem.Name = "newMenuItem";
            this.newMenuItem.Size = new System.Drawing.Size(169, 22);
            this.newMenuItem.Text = "New";
            this.newMenuItem.Click += new System.EventHandler(this.newMenuItem_Click);
            // 
            // openMenuItem
            // 
            this.openMenuItem.Name = "openMenuItem";
            this.openMenuItem.Size = new System.Drawing.Size(169, 22);
            this.openMenuItem.Text = "Open";
            this.openMenuItem.Click += new System.EventHandler(this.openMenuItem_Click);
            // 
            // saveMenuItem
            // 
            this.saveMenuItem.Name = "saveMenuItem";
            this.saveMenuItem.Size = new System.Drawing.Size(169, 22);
            this.saveMenuItem.Text = "Save";
            this.saveMenuItem.Click += new System.EventHandler(this.saveMenuItem_Click);
            // 
            // saveAsMenuItem
            // 
            this.saveAsMenuItem.Name = "saveAsMenuItem";
            this.saveAsMenuItem.Size = new System.Drawing.Size(169, 22);
            this.saveAsMenuItem.Text = "Save As...";
            this.saveAsMenuItem.Click += new System.EventHandler(this.saveAsMenuItem_Click);
            // 
            // exportAsHeaderMenuItem
            // 
            this.exportAsHeaderMenuItem.Name = "exportAsHeaderMenuItem";
            this.exportAsHeaderMenuItem.Size = new System.Drawing.Size(169, 22);
            this.exportAsHeaderMenuItem.Text = "Export as header...";
            this.exportAsHeaderMenuItem.Click += new System.EventHandler(this.exportAsHeaderMenuItem_Click);
            // 
            // exitMenuItem
            // 
            this.exitMenuItem.Name = "exitMenuItem";
            this.exitMenuItem.Size = new System.Drawing.Size(169, 22);
            this.exitMenuItem.Text = "Exit";
            // 
            // viewToolStripMenuItem
            // 
            this.viewToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.resetCameraMenuItem,
            this.tileTextureMenuItem,
            this.filterTextureMenuItem,
            this.solidMeshMenuItem,
            this.lightModelMenuItem});
            this.viewToolStripMenuItem.Name = "viewToolStripMenuItem";
            this.viewToolStripMenuItem.Size = new System.Drawing.Size(41, 20);
            this.viewToolStripMenuItem.Text = "View";
            // 
            // resetCameraMenuItem
            // 
            this.resetCameraMenuItem.Name = "resetCameraMenuItem";
            this.resetCameraMenuItem.Size = new System.Drawing.Size(152, 22);
            this.resetCameraMenuItem.Text = "Reset Camera";
            this.resetCameraMenuItem.Click += new System.EventHandler(this.resetCameraMenuItem_Click);
            // 
            // tileTextureMenuItem
            // 
            this.tileTextureMenuItem.CheckOnClick = true;
            this.tileTextureMenuItem.Name = "tileTextureMenuItem";
            this.tileTextureMenuItem.Size = new System.Drawing.Size(152, 22);
            this.tileTextureMenuItem.Text = "Tile Texture";
            this.tileTextureMenuItem.CheckedChanged += new System.EventHandler(this.tileTextureMenuItem_CheckedChanged);
            // 
            // filterTextureMenuItem
            // 
            this.filterTextureMenuItem.CheckOnClick = true;
            this.filterTextureMenuItem.Name = "filterTextureMenuItem";
            this.filterTextureMenuItem.Size = new System.Drawing.Size(152, 22);
            this.filterTextureMenuItem.Text = "Filter Texture";
            this.filterTextureMenuItem.CheckedChanged += new System.EventHandler(this.filterTextureMenuItem_CheckedChanged);
            // 
            // solidMeshMenuItem
            // 
            this.solidMeshMenuItem.CheckOnClick = true;
            this.solidMeshMenuItem.Name = "solidMeshMenuItem";
            this.solidMeshMenuItem.Size = new System.Drawing.Size(152, 22);
            this.solidMeshMenuItem.Text = "Solid Mesh";
            this.solidMeshMenuItem.CheckedChanged += new System.EventHandler(this.solidMeshMenuItem_CheckedChanged);
            // 
            // lightModelMenuItem
            // 
            this.lightModelMenuItem.Checked = true;
            this.lightModelMenuItem.CheckOnClick = true;
            this.lightModelMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.lightModelMenuItem.Name = "lightModelMenuItem";
            this.lightModelMenuItem.Size = new System.Drawing.Size(152, 22);
            this.lightModelMenuItem.Text = "Light Model";
            this.lightModelMenuItem.CheckedChanged += new System.EventHandler(this.lightModelMenuItem_CheckedChanged);
            // 
            // mainMenuHelp
            // 
            this.mainMenuHelp.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutMenuItem});
            this.mainMenuHelp.Name = "mainMenuHelp";
            this.mainMenuHelp.Size = new System.Drawing.Size(40, 20);
            this.mainMenuHelp.Text = "Help";
            // 
            // aboutMenuItem
            // 
            this.aboutMenuItem.Name = "aboutMenuItem";
            this.aboutMenuItem.Size = new System.Drawing.Size(103, 22);
            this.aboutMenuItem.Text = "About";
            this.aboutMenuItem.Click += new System.EventHandler(this.aboutMenuItem_Click);
            // 
            // toolStripContainer1
            // 
            // 
            // toolStripContainer1.ContentPanel
            // 
            this.toolStripContainer1.ContentPanel.Controls.Add(this.mainTransportSplitContainer);
            this.toolStripContainer1.ContentPanel.Size = new System.Drawing.Size(766, 306);
            this.toolStripContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.toolStripContainer1.Location = new System.Drawing.Point(0, 24);
            this.toolStripContainer1.Name = "toolStripContainer1";
            this.toolStripContainer1.Size = new System.Drawing.Size(766, 331);
            this.toolStripContainer1.TabIndex = 0;
            this.toolStripContainer1.Text = "toolStripContainer1";
            // 
            // mainTransportSplitContainer
            // 
            this.mainTransportSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainTransportSplitContainer.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.mainTransportSplitContainer.IsSplitterFixed = true;
            this.mainTransportSplitContainer.Location = new System.Drawing.Point(0, 0);
            this.mainTransportSplitContainer.Name = "mainTransportSplitContainer";
            this.mainTransportSplitContainer.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // mainTransportSplitContainer.Panel1
            // 
            this.mainTransportSplitContainer.Panel1.Controls.Add(this.mainLeftAndRightSplitContainer);
            // 
            // mainTransportSplitContainer.Panel2
            // 
            this.mainTransportSplitContainer.Panel2.Controls.Add(this.transport1);
            this.mainTransportSplitContainer.Size = new System.Drawing.Size(766, 306);
            this.mainTransportSplitContainer.SplitterDistance = 238;
            this.mainTransportSplitContainer.TabIndex = 0;
            // 
            // mainLeftAndRightSplitContainer
            // 
            this.mainLeftAndRightSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainLeftAndRightSplitContainer.Location = new System.Drawing.Point(0, 0);
            this.mainLeftAndRightSplitContainer.Name = "mainLeftAndRightSplitContainer";
            // 
            // mainLeftAndRightSplitContainer.Panel1
            // 
            this.mainLeftAndRightSplitContainer.Panel1.Controls.Add(this.previewBoardSplitContainer);
            // 
            // mainLeftAndRightSplitContainer.Panel2
            // 
            this.mainLeftAndRightSplitContainer.Panel2.Controls.Add(this.operatorPropertyGrid);
            this.mainLeftAndRightSplitContainer.Size = new System.Drawing.Size(766, 238);
            this.mainLeftAndRightSplitContainer.SplitterDistance = 556;
            this.mainLeftAndRightSplitContainer.TabIndex = 0;
            // 
            // previewBoardSplitContainer
            // 
            this.previewBoardSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.previewBoardSplitContainer.Location = new System.Drawing.Point(0, 0);
            this.previewBoardSplitContainer.Margin = new System.Windows.Forms.Padding(0);
            this.previewBoardSplitContainer.Name = "previewBoardSplitContainer";
            this.previewBoardSplitContainer.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // previewBoardSplitContainer.Panel1
            // 
            this.previewBoardSplitContainer.Panel1.Controls.Add(this.previewPanel);
            // 
            // previewBoardSplitContainer.Panel2
            // 
            this.previewBoardSplitContainer.Panel2.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.previewBoardSplitContainer.Panel2.Controls.Add(this.tabControl1);
            this.previewBoardSplitContainer.Panel2MinSize = 0;
            this.previewBoardSplitContainer.Size = new System.Drawing.Size(556, 238);
            this.previewBoardSplitContainer.SplitterDistance = 82;
            this.previewBoardSplitContainer.TabIndex = 0;
            // 
            // previewPanel
            // 
            this.previewPanel.BackColor = System.Drawing.SystemColors.ControlText;
            this.previewPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.previewPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.previewPanel.Location = new System.Drawing.Point(0, 0);
            this.previewPanel.Name = "previewPanel";
            this.previewPanel.Size = new System.Drawing.Size(556, 82);
            this.previewPanel.TabIndex = 0;
            this.previewPanel.DoubleClick += new System.EventHandler(this.previewPanel_DoubleClick);
            this.previewPanel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.previewPanel_MouseMove);
            this.previewPanel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.previewPanel_MouseDown);
            this.previewPanel.MouseUp += new System.Windows.Forms.MouseEventHandler(this.previewPanel_MouseUp);
            this.previewPanel.SizeChanged += new System.EventHandler(this.previewPanel_SizeChanged);
            // 
            // tabControl1
            // 
            this.tabControl1.Appearance = System.Windows.Forms.TabAppearance.Buttons;
            this.tabControl1.Controls.Add(this.stacksTab);
            this.tabControl1.Controls.Add(this.timelinesTab);
            this.tabControl1.Controls.Add(this.clipTab);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Margin = new System.Windows.Forms.Padding(0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(556, 152);
            this.tabControl1.TabIndex = 0;
            // 
            // stacksTab
            // 
            this.stacksTab.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.stacksTab.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.stacksTab.Controls.Add(this.operatorPageView1);
            this.stacksTab.Location = new System.Drawing.Point(4, 25);
            this.stacksTab.Margin = new System.Windows.Forms.Padding(0);
            this.stacksTab.Name = "stacksTab";
            this.stacksTab.Size = new System.Drawing.Size(548, 123);
            this.stacksTab.TabIndex = 2;
            this.stacksTab.Text = "Stacks";
            this.stacksTab.UseVisualStyleBackColor = true;
            // 
            // operatorPageView1
            // 
            this.operatorPageView1.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.operatorPageView1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.operatorPageView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.operatorPageView1.Location = new System.Drawing.Point(0, 0);
            this.operatorPageView1.Name = "operatorPageView1";
            this.operatorPageView1.Page = null;
            this.operatorPageView1.Size = new System.Drawing.Size(548, 123);
            this.operatorPageView1.TabIndex = 0;
            this.operatorPageView1.ViewedOperator = null;
            this.operatorPageView1.ViewedOperatorProperties = null;
            this.operatorPageView1.ViewedOperatorPropertiesChanged += new System.EventHandler(this.operatorPageView1_ViewedOperatorPropertiesChanged);
            this.operatorPageView1.ViewedOperatorChanged += new System.EventHandler(this.operatorPageView1_ViewedOperatorChanged);
            // 
            // timelinesTab
            // 
            this.timelinesTab.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.timelinesTab.Controls.Add(this.timelinesView1);
            this.timelinesTab.Location = new System.Drawing.Point(4, 25);
            this.timelinesTab.Name = "timelinesTab";
            this.timelinesTab.Size = new System.Drawing.Size(548, 123);
            this.timelinesTab.TabIndex = 1;
            this.timelinesTab.Text = "Timelines";
            this.timelinesTab.UseVisualStyleBackColor = true;
            // 
            // timelinesView1
            // 
            this.timelinesView1.BackColor = System.Drawing.SystemColors.Control;
            this.timelinesView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.timelinesView1.Location = new System.Drawing.Point(0, 0);
            this.timelinesView1.Name = "timelinesView1";
            this.timelinesView1.Size = new System.Drawing.Size(548, 123);
            this.timelinesView1.TabIndex = 0;
            this.timelinesView1.Timeline = null;
            this.timelinesView1.ViewedClip = null;
            this.timelinesView1.ViewedClipChanged += new System.EventHandler(this.timelinesView1_ViewedClipChanged);
            // 
            // clipTab
            // 
            this.clipTab.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.clipTab.Controls.Add(this.clipView1);
            this.clipTab.Location = new System.Drawing.Point(4, 25);
            this.clipTab.Name = "clipTab";
            this.clipTab.Size = new System.Drawing.Size(548, 123);
            this.clipTab.TabIndex = 3;
            this.clipTab.Text = "Clip";
            this.clipTab.UseVisualStyleBackColor = true;
            // 
            // clipView1
            // 
            this.clipView1.BackColor = System.Drawing.SystemColors.Control;
            this.clipView1.Clip = null;
            this.clipView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.clipView1.Location = new System.Drawing.Point(0, 0);
            this.clipView1.Name = "clipView1";
            this.clipView1.Size = new System.Drawing.Size(548, 123);
            this.clipView1.TabIndex = 0;
            // 
            // operatorPropertyGrid
            // 
            this.operatorPropertyGrid.AutoScroll = true;
            this.operatorPropertyGrid.AutoSize = true;
            this.operatorPropertyGrid.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.operatorPropertyGrid.BackColor = System.Drawing.SystemColors.ControlDark;
            this.operatorPropertyGrid.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.operatorPropertyGrid.Dock = System.Windows.Forms.DockStyle.Fill;
            this.operatorPropertyGrid.Location = new System.Drawing.Point(0, 0);
            this.operatorPropertyGrid.Name = "operatorPropertyGrid";
            this.operatorPropertyGrid.Operator = null;
            this.operatorPropertyGrid.Size = new System.Drawing.Size(206, 238);
            this.operatorPropertyGrid.TabIndex = 0;
            // 
            // transport1
            // 
            this.transport1.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.transport1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.transport1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.transport1.Location = new System.Drawing.Point(0, 0);
            this.transport1.Name = "transport1";
            this.transport1.Project = null;
            this.transport1.Size = new System.Drawing.Size(766, 64);
            this.transport1.TabIndex = 0;
            // 
            // statusStrip1
            // 
            this.statusStrip1.Location = new System.Drawing.Point(0, 355);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(766, 22);
            this.statusStrip1.TabIndex = 2;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // slowRenderTimer
            // 
            this.slowRenderTimer.Tick += new System.EventHandler(this.slowRenderTimer_Tick);
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.Filter = "db verkstan files|*.dbv|All files|*.*";
            this.saveFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.saveFileDialog1_FileOk);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "demo.dbv";
            this.openFileDialog1.Filter = "db verkstan files|*.dbv|All files|*.*";
            this.openFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialog1_FileOk);
            // 
            // exportAsHeaderSaveFileDialog
            // 
            this.exportAsHeaderSaveFileDialog.FileName = "graphicsdata.hpp";
            this.exportAsHeaderSaveFileDialog.Filter = "C++ header files|*.hpp";
            this.exportAsHeaderSaveFileDialog.FileOk += new System.ComponentModel.CancelEventHandler(this.exportAsHeaderSaveFileDialog_FileOk);
            // 
            // ProjectView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(766, 377);
            this.Controls.Add(this.toolStripContainer1);
            this.Controls.Add(this.mainMenu);
            this.Controls.Add(this.statusStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.mainMenu;
            this.Name = "ProjectView";
            this.Text = "db verkstan 1";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.mainMenu.ResumeLayout(false);
            this.mainMenu.PerformLayout();
            this.toolStripContainer1.ContentPanel.ResumeLayout(false);
            this.toolStripContainer1.ResumeLayout(false);
            this.toolStripContainer1.PerformLayout();
            this.mainTransportSplitContainer.Panel1.ResumeLayout(false);
            this.mainTransportSplitContainer.Panel2.ResumeLayout(false);
            this.mainTransportSplitContainer.ResumeLayout(false);
            this.mainLeftAndRightSplitContainer.Panel1.ResumeLayout(false);
            this.mainLeftAndRightSplitContainer.Panel2.ResumeLayout(false);
            this.mainLeftAndRightSplitContainer.Panel2.PerformLayout();
            this.mainLeftAndRightSplitContainer.ResumeLayout(false);
            this.previewBoardSplitContainer.Panel1.ResumeLayout(false);
            this.previewBoardSplitContainer.Panel2.ResumeLayout(false);
            this.previewBoardSplitContainer.ResumeLayout(false);
            this.tabControl1.ResumeLayout(false);
            this.stacksTab.ResumeLayout(false);
            this.timelinesTab.ResumeLayout(false);
            this.clipTab.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer fastRenderTimer;
        private System.Windows.Forms.Panel previewPanel;
        private System.Windows.Forms.MenuStrip mainMenu;
        private System.Windows.Forms.ToolStripMenuItem mainMenuFile;
        private System.Windows.Forms.ToolStripMenuItem newMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitMenuItem;
        private System.Windows.Forms.ToolStripMenuItem mainMenuHelp;
        private System.Windows.Forms.ToolStripMenuItem aboutMenuItem;
        private System.Windows.Forms.ToolStripContainer toolStripContainer1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.SplitContainer mainLeftAndRightSplitContainer;
        private System.Windows.Forms.SplitContainer previewBoardSplitContainer;
        private VerkstanEditor.Gui.OperatorPropertyGrid operatorPropertyGrid;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage timelinesTab;
        private System.Windows.Forms.TabPage stacksTab;
        private System.Windows.Forms.TabPage clipTab;
        private Transport transport1;
        private System.Windows.Forms.SplitContainer mainTransportSplitContainer;
        private System.Windows.Forms.Timer slowRenderTimer;
        private OperatorPageView operatorPageView1;
        private TimelinesView timelinesView1;
        private ClipView clipView1;
        private System.Windows.Forms.ToolStripMenuItem saveMenuItem;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.ToolStripMenuItem saveAsMenuItem;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.ToolStripMenuItem exportAsHeaderMenuItem;
        private System.Windows.Forms.SaveFileDialog exportAsHeaderSaveFileDialog;
        private System.Windows.Forms.ToolStripMenuItem viewToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem resetCameraMenuItem;
        private System.Windows.Forms.ToolStripMenuItem tileTextureMenuItem;
        private System.Windows.Forms.ToolStripMenuItem filterTextureMenuItem;
        private System.Windows.Forms.ToolStripMenuItem solidMeshMenuItem;
        private System.Windows.Forms.ToolStripMenuItem lightModelMenuItem;
    }
}

