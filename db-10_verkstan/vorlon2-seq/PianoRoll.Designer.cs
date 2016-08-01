namespace VorlonSeq
{
    partial class PianoRoll
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
            this.SuspendLayout();
            // 
            // PianoRoll
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.Name = "PianoRoll";
            this.Size = new System.Drawing.Size(911, 612);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.PianoRoll_Paint);
            this.Layout += new System.Windows.Forms.LayoutEventHandler(this.PianoRoll_Layout);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.PianoRoll_MouseMove);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.PianoRoll_KeyUp);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.PianoRoll_MouseDown);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.PianoRoll_MouseUp);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.PianoRoll_KeyDown);
            this.ResumeLayout(false);

        }

        #endregion
    }
}
