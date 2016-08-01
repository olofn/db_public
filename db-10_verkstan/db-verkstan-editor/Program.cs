using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace VerkstanEditor
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Gui.ExceptionForm exceptionForm = new Gui.ExceptionForm(); 
            Gui.ProjectView projectView = new Gui.ProjectView();

            Application.Run(projectView);
            /*
            try
            {
                Application.Run(projectView);
            }
            catch (Exception e)
            {
                exceptionForm.BackupFilename = projectView.SaveBackup();
                exceptionForm.Stacktrace = e.StackTrace;
                Application.Run(exceptionForm);
            }
             */ 
        }
    }
}
