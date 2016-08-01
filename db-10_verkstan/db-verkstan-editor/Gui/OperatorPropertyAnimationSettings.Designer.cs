namespace VerkstanEditor.Gui
{
    partial class OperatorPropertyAnimationSettings
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
            this.label1 = new System.Windows.Forms.Label();
            this.channelNumericUpDown = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.amplifyNumericUpDown = new System.Windows.Forms.NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)(this.channelNumericUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.amplifyNumericUpDown)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(2, 3);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(46, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Channel";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // channelNumericUpDown
            // 
            this.channelNumericUpDown.Location = new System.Drawing.Point(49, 1);
            this.channelNumericUpDown.Maximum = new decimal(new int[] {
            1024,
            0,
            0,
            0});
            this.channelNumericUpDown.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.channelNumericUpDown.Name = "channelNumericUpDown";
            this.channelNumericUpDown.Size = new System.Drawing.Size(52, 20);
            this.channelNumericUpDown.TabIndex = 1;
            this.channelNumericUpDown.ValueChanged += new System.EventHandler(this.channelNumericUpDown_ValueChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(8, 25);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(40, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Amplify";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // amplifyNumericUpDown
            // 
            this.amplifyNumericUpDown.DecimalPlaces = 3;
            this.amplifyNumericUpDown.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.amplifyNumericUpDown.Location = new System.Drawing.Point(49, 23);
            this.amplifyNumericUpDown.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.amplifyNumericUpDown.Minimum = new decimal(new int[] {
            1000,
            0,
            0,
            -2147483648});
            this.amplifyNumericUpDown.Name = "amplifyNumericUpDown";
            this.amplifyNumericUpDown.Size = new System.Drawing.Size(93, 20);
            this.amplifyNumericUpDown.TabIndex = 4;
            this.amplifyNumericUpDown.ValueChanged += new System.EventHandler(this.amplifyNumericUpDown_ValueChanged);
            // 
            // OperatorPropertyAnimationSettings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.label1);
            this.Controls.Add(this.amplifyNumericUpDown);
            this.Controls.Add(this.channelNumericUpDown);
            this.Controls.Add(this.label2);
            this.Name = "OperatorPropertyAnimationSettings";
            this.Size = new System.Drawing.Size(146, 45);
            ((System.ComponentModel.ISupportInitialize)(this.channelNumericUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.amplifyNumericUpDown)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown channelNumericUpDown;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown amplifyNumericUpDown;
    }
}
