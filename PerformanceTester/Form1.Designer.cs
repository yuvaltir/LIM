using System.Windows.Forms;
namespace PerformanceTester
{
    partial class Form1
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
            this.button1 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.nudDays = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.nudHours = new System.Windows.Forms.NumericUpDown();
            this.nudMins = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.lStart = new System.Windows.Forms.Label();
            this.lEnd = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.nudDays)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudHours)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudMins)).BeginInit();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(456, 176);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(107, 32);
            this.button1.TabIndex = 0;
            this.button1.Text = "Start Logging";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(28, 41);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(30, 17);
            this.label1.TabIndex = 1;
            this.label1.Text = "File";
            this.toolTip1.SetToolTip(this.label1, "Choose existing log file to mimic");
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(64, 41);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(499, 22);
            this.textBox1.TabIndex = 2;
            this.textBox1.Text = "C:\\Users\\yt250091\\Downloads\\R10\\Server\\GPOSWebService_NCDWR10ASA0012.log";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(31, 83);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(40, 17);
            this.label2.TabIndex = 3;
            this.label2.Text = "Days";
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(64, 132);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(499, 23);
            this.progressBar1.TabIndex = 4;
            // 
            // nudDays
            // 
            this.nudDays.Location = new System.Drawing.Point(77, 83);
            this.nudDays.Name = "nudDays";
            this.nudDays.Size = new System.Drawing.Size(120, 22);
            this.nudDays.TabIndex = 5;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(214, 83);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(44, 17);
            this.label3.TabIndex = 6;
            this.label3.Text = "hours";
            // 
            // nudHours
            // 
            this.nudHours.Location = new System.Drawing.Point(264, 81);
            this.nudHours.Maximum = new decimal(new int[] {
            23,
            0,
            0,
            0});
            this.nudHours.Name = "nudHours";
            this.nudHours.Size = new System.Drawing.Size(120, 22);
            this.nudHours.TabIndex = 8;
            this.nudHours.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // nudMins
            // 
            this.nudMins.Location = new System.Drawing.Point(443, 80);
            this.nudMins.Maximum = new decimal(new int[] {
            59,
            0,
            0,
            0});
            this.nudMins.Name = "nudMins";
            this.nudMins.Size = new System.Drawing.Size(120, 22);
            this.nudMins.TabIndex = 10;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(399, 83);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(37, 17);
            this.label4.TabIndex = 9;
            this.label4.Text = "mins";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(31, 184);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(38, 17);
            this.label5.TabIndex = 11;
            this.label5.Text = "Start";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(261, 184);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(33, 17);
            this.label6.TabIndex = 12;
            this.label6.Text = "End";
            // 
            // lStart
            // 
            this.lStart.AutoSize = true;
            this.lStart.Location = new System.Drawing.Point(74, 184);
            this.lStart.Name = "lStart";
            this.lStart.Size = new System.Drawing.Size(150, 17);
            this.lStart.TabIndex = 13;
            this.lStart.Text = "dd/MM/yyyy HH:mm:ss";
            // 
            // lEnd
            // 
            this.lEnd.AutoSize = true;
            this.lEnd.Location = new System.Drawing.Point(300, 184);
            this.lEnd.Name = "lEnd";
            this.lEnd.Size = new System.Drawing.Size(150, 17);
            this.lEnd.TabIndex = 14;
            this.lEnd.Text = "dd/MM/yyyy HH:mm:ss";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(627, 241);
            this.Controls.Add(this.lEnd);
            this.Controls.Add(this.lStart);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.nudMins);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.nudHours);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.nudDays);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button1);
            this.Name = "Form1";
            this.Text = "PerfTester";
            ((System.ComponentModel.ISupportInitialize)(this.nudDays)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudHours)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudMins)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.NumericUpDown nudDays;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown nudHours;
        private System.Windows.Forms.NumericUpDown nudMins;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private Label lStart;
        private Label lEnd;
    }
}

