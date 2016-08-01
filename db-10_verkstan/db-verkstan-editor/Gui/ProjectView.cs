using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using VerkstanEditor.Logic;

namespace VerkstanEditor.Gui
{
    public partial class ProjectView : Form
    {
        #region Private Variables
        private Verkstan.Window verkstanWindow;
        private Operator viewedOperator;
        private Project project;
        private MouseButtons previewPanelLastMouseButtonDown;
        #endregion

        #region Constructor
        public ProjectView()
        {
            InitializeComponent();
            verkstanWindow = new Verkstan.Window();
            verkstanWindow.ClearColor = Color.DarkCyan.ToArgb();
            unsafe
            {
                verkstanWindow.Boot(previewPanel.Handle.ToPointer());
            }

            fastRenderTimer.Enabled = true;
            slowRenderTimer.Enabled = true;

            project = new Project();
            Page page = new Page();
            project.OperatorPages.Add(page);
            operatorPageView1.Page = page;
        }
        #endregion

        #region Public Methods
        public String SaveBackup()
        {
            String filename;

            if (project.Filename == null)
                filename = Environment.GetFolderPath(Environment.SpecialFolder.Personal) + "\\demo-backup";
            else
                filename = project.Filename + "-backup";

            filename += "-"+DateTime.Now.ToShortTimeString().Replace(":", "_")+"_"+DateTime.Now.ToShortDateString().Replace(":", "_");
            XmlDocument doc = new XmlDocument();
            doc.AppendChild(project.ToXmlElement(doc));
            doc.Save(filename);

            return filename;
        }
        #endregion

        #region Event Handlers
        private void FastRenderTimer_Tick(object sender, EventArgs e)
        {
            Verkstan.CoreOperator coreOp = null;

            if (tabControl1.SelectedTab == stacksTab
                && viewedOperator != null
                && viewedOperator.IsProcessable)
                coreOp = viewedOperator.BindedCoreOperator;
            else if (tabControl1.SelectedTab == timelinesTab
                    && timelinesView1.ViewedTimelineOperator != null
                    && timelinesView1.ViewedTimelineOperator.IsProcessable)
                coreOp = timelinesView1.ViewedTimelineOperator.BindedCoreOperator;

            verkstanWindow.ViewedOperator = coreOp;
            verkstanWindow.Render(Metronome.Tick);
            Metronome.OnBeatChangedFastUpdate(Metronome.Tick);
        }
        private void previewPanel_SizeChanged(object sender, EventArgs e)
        {
            if (verkstanWindow != null)
                verkstanWindow.Resize();
        }
        private void previewPanel_DoubleClick(object sender, EventArgs e)
        {
            previewBoardSplitContainer.Panel2Collapsed = !previewBoardSplitContainer.Panel2Collapsed;

            if (previewPanelLastMouseButtonDown == MouseButtons.Right
                && !mainLeftAndRightSplitContainer.Panel2Collapsed)
                mainLeftAndRightSplitContainer.Panel2Collapsed = true;
            else
                mainLeftAndRightSplitContainer.Panel2Collapsed = false;
        }
        private void previewPanel_MouseDown(object sender, MouseEventArgs e)
        {
            previewPanelLastMouseButtonDown = e.Button;

            int button = 0;

            if (e.Button == MouseButtons.Left)
                button = 1;
            else if (e.Button == MouseButtons.Middle)
                button = 2;
            else if (e.Button == MouseButtons.Right)
                button = 3;

            verkstanWindow.MouseDown(button, e.X, e.Y);
        }
        private void previewPanel_MouseUp(object sender, MouseEventArgs e)
        {
            int button = 0;

            if (e.Button == MouseButtons.Left)
                button = 1;
            else if (e.Button == MouseButtons.Middle)
                button = 2;
            else if (e.Button == MouseButtons.Right)
                button = 3;

            verkstanWindow.MouseUp(button, e.X, e.Y);
        }
        private void previewPanel_MouseMove(object sender, MouseEventArgs e)
        {
            verkstanWindow.MouseMove(e.X, e.Y);
        }
        private void slowRenderTimer_Tick(object sender, EventArgs e)
        {
            Metronome.OnBeatChangedSlowUpdate(Metronome.Tick);
        }
        private void operatorPageView1_ViewedOperatorChanged(object sender, EventArgs e)
        {
            viewedOperator = operatorPageView1.ViewedOperator;
        }
        private void operatorPageView1_ViewedOperatorPropertiesChanged(object sender, EventArgs e)
        {
            operatorPropertyGrid.Operator = operatorPageView1.ViewedOperatorProperties;
        }
        private void timelinesView1_ViewedClipChanged(object sender, EventArgs e)
        {
            if (timelinesView1.ViewedClip != null)
            {
                clipView1.Clip = timelinesView1.ViewedClip;
                tabControl1.SelectedTab = clipTab;
            }
        }
        private void newMenuItem_Click(object sender, EventArgs e)
        {
            project = new Project();
            Page page = new Page();
            project.OperatorPages.Add(page);
            operatorPageView1.Page = page;
            transport1.Project = project;
            timelinesView1.Timeline = null;
            timelinesView1.Reset();
            Text = "db verkstan 1 - untitled.dbv"; 
        }
        private void openMenuItem_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
        }
        private void saveMenuItem_Click(object sender, EventArgs e)
        {
            if (project.Filename == null)
            {
                saveFileDialog1.FileName = "demo.dbv";
                saveFileDialog1.ShowDialog();
                return;
            }
                
            XmlDocument doc = new XmlDocument();
            doc.AppendChild(project.ToXmlElement(doc));
            doc.Save(project.Filename);
        }
        private void saveAsMenuItem_Click(object sender, EventArgs e)
        {
            if (project.Filename != null)
                saveFileDialog1.FileName = project.Filename;
            else
                saveFileDialog1.FileName = "demo.dbv";
            saveFileDialog1.ShowDialog();
        }
        private void saveFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            project.Filename = saveFileDialog1.FileName;
            XmlDocument doc = new XmlDocument();
            doc.AppendChild(project.ToXmlElement(doc));
            doc.Save(project.Filename);

            string[] splitted = project.Filename.Split(new Char[] { '\\', '/', });
            Text = "db verkstan 1 - " + splitted[splitted.Count() - 1]; 
        }
        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            String filename = openFileDialog1.FileName;
            XmlDocument doc = new XmlDocument();
            doc.Load(filename);
            XmlElement rootElement = doc.DocumentElement;

            if (project != null)
            {
                verkstanWindow.ViewedOperator = null;
                project.Dispose();
            }

            project = new Project();
            project.Filename = filename;
            project.FromXmlElement(rootElement);
            operatorPageView1.Page = project.OperatorPages.First();
            transport1.Project = project;
            timelinesView1.Timeline = null;
            timelinesView1.Reset();
            string[] splitted = project.Filename.Split(new Char [] {'\\', '/',});
            Text = "db verkstan 1 - " + splitted[splitted.Count() - 1]; 
        }
        private void aboutMenuItem_Click(object sender, EventArgs e)
        {
            throw new Exception("balbal");
        }
        private void exportAsHeaderMenuItem_Click(object sender, EventArgs e)
        {
            Operator root = operatorPropertyGrid.Operator;

            if (root == null)
            {
                MessageBox.Show("A root operator must be selected!",
                                "Unable to export project!",
                                MessageBoxButtons.OK);
                return;
            }

            if (!root.IsProcessable)
            {
                MessageBox.Show("The root operator must be processable!",
                                "Unable to export project!",
                                MessageBoxButtons.OK);
                return;
            }

            DialogResult result = MessageBox.Show("The project will be exported with operator '" + root.UniqueName + "' as the root operator.",
                                                  "Export as header",
                                                  MessageBoxButtons.OKCancel);
            if (result == DialogResult.Cancel)
                return;

            exportAsHeaderSaveFileDialog.ShowDialog();                     
        }
        private void exportAsHeaderSaveFileDialog_FileOk(object sender, CancelEventArgs e)
        {
            Exporter.Export(operatorPropertyGrid.Operator, exportAsHeaderSaveFileDialog.FileName);
        }
        private void tileTextureMenuItem_CheckedChanged(object sender, EventArgs e)
        {
            verkstanWindow.TextureTiling = tileTextureMenuItem.Checked;
        }
        private void filterTextureMenuItem_CheckedChanged(object sender, EventArgs e)
        {
            verkstanWindow.TextureFiltering = filterTextureMenuItem.Checked;
        }
        private void solidMeshMenuItem_CheckedChanged(object sender, EventArgs e)
        {
            verkstanWindow.MeshSolid = solidMeshMenuItem.Checked;
        }
        private void resetCameraMenuItem_Click(object sender, EventArgs e)
        {
            verkstanWindow.ResetCamera();
        }
        private void lightModelMenuItem_CheckedChanged(object sender, EventArgs e)
        {
            verkstanWindow.ModelLightning = lightModelMenuItem.Checked;
        }
        #endregion
    }
}
