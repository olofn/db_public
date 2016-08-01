namespace VerkstanEditor.Gui
{
    partial class VectorProperty
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
            this.z = new System.Windows.Forms.NumericUpDown();
            this.y = new System.Windows.Forms.NumericUpDown();
            this.x = new System.Windows.Forms.NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)(this.z)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.y)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.x)).BeginInit();
            this.SuspendLayout();
            // 
            // z
            // 
            this.z.DecimalPlaces = 3;
            this.z.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.z.Location = new System.Drawing.Point(123, 3);
            this.z.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.z.Minimum = new decimal(new int[] {
            255,
            0,
            0,
            -2147483648});
            this.z.Name = "z";
            this.z.Size = new System.Drawing.Size(57, 20);
            this.z.TabIndex = 5;
            this.z.ValueChanged += new System.EventHandler(this.z_ValueChanged);
            // 
            // y
            // 
            this.y.DecimalPlaces = 3;
            this.y.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.y.Location = new System.Drawing.Point(61, 3);
            this.y.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.y.Minimum = new decimal(new int[] {
            255,
            0,
            0,
            -2147483648});
            this.y.Name = "y";
            this.y.Size = new System.Drawing.Size(56, 20);
            this.y.TabIndex = 4;
            this.y.ValueChanged += new System.EventHandler(this.y_ValueChanged);
            // 
            // x
            // 
            this.x.DecimalPlaces = 3;
            this.x.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.x.Location = new System.Drawing.Point(0, 3);
            this.x.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.x.Minimum = new decimal(new int[] {
            255,
            0,
            0,
            -2147483648});
            this.x.Name = "x";
            this.x.Size = new System.Drawing.Size(55, 20);
            this.x.TabIndex = 3;
            this.x.ValueChanged += new System.EventHandler(this.x_ValueChanged);
            // 
            // VectorProperty
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.z);
            this.Controls.Add(this.y);
            this.Controls.Add(this.x);
            this.Name = "VectorProperty";
            this.Size = new System.Drawing.Size(206, 26);
            ((System.ComponentModel.ISupportInitialize)(this.z)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.y)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.x)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.NumericUpDown z;
        private System.Windows.Forms.NumericUpDown y;
        private System.Windows.Forms.NumericUpDown x;
    }
}
