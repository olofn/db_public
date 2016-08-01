namespace VerkstanEditor.Gui
{
    partial class ColorProperty
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
            this.ColorPropertyR = new System.Windows.Forms.NumericUpDown();
            this.ColorPropertyG = new System.Windows.Forms.NumericUpDown();
            this.ColorPropertyB = new System.Windows.Forms.NumericUpDown();
            this.ColorPropertyColor = new System.Windows.Forms.Panel();
            ((System.ComponentModel.ISupportInitialize)(this.ColorPropertyR)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ColorPropertyG)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ColorPropertyB)).BeginInit();
            this.SuspendLayout();
            // 
            // ColorPropertyR
            // 
            this.ColorPropertyR.Location = new System.Drawing.Point(0, 0);
            this.ColorPropertyR.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.ColorPropertyR.Name = "ColorPropertyR";
            this.ColorPropertyR.Size = new System.Drawing.Size(50, 20);
            this.ColorPropertyR.TabIndex = 0;
            this.ColorPropertyR.ValueChanged += new System.EventHandler(this.ColorPropertyR_ValueChanged);
            // 
            // ColorPropertyG
            // 
            this.ColorPropertyG.Location = new System.Drawing.Point(56, 0);
            this.ColorPropertyG.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.ColorPropertyG.Name = "ColorPropertyG";
            this.ColorPropertyG.Size = new System.Drawing.Size(50, 20);
            this.ColorPropertyG.TabIndex = 1;
            this.ColorPropertyG.ValueChanged += new System.EventHandler(this.ColorPropertyG_ValueChanged);
            // 
            // ColorPropertyB
            // 
            this.ColorPropertyB.Location = new System.Drawing.Point(112, 0);
            this.ColorPropertyB.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.ColorPropertyB.Name = "ColorPropertyB";
            this.ColorPropertyB.Size = new System.Drawing.Size(50, 20);
            this.ColorPropertyB.TabIndex = 2;
            this.ColorPropertyB.ValueChanged += new System.EventHandler(this.ColorPropertyB_ValueChanged);
            // 
            // ColorPropertyColor
            // 
            this.ColorPropertyColor.Location = new System.Drawing.Point(168, 0);
            this.ColorPropertyColor.MinimumSize = new System.Drawing.Size(65, 20);
            this.ColorPropertyColor.Name = "ColorPropertyColor";
            this.ColorPropertyColor.Size = new System.Drawing.Size(65, 20);
            this.ColorPropertyColor.TabIndex = 3;
            // 
            // ColorProperty
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.ColorPropertyColor);
            this.Controls.Add(this.ColorPropertyB);
            this.Controls.Add(this.ColorPropertyG);
            this.Controls.Add(this.ColorPropertyR);
            this.Name = "ColorProperty";
            this.Size = new System.Drawing.Size(236, 20);
            ((System.ComponentModel.ISupportInitialize)(this.ColorPropertyR)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ColorPropertyG)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ColorPropertyB)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.NumericUpDown ColorPropertyR;
        private System.Windows.Forms.NumericUpDown ColorPropertyG;
        private System.Windows.Forms.NumericUpDown ColorPropertyB;
        private System.Windows.Forms.Panel ColorPropertyColor;
    }
}
