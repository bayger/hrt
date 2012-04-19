namespace RefractConvert
{
	partial class MainForm
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
			System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
			System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
			System.Windows.Forms.DataVisualization.Charting.Title title1 = new System.Windows.Forms.DataVisualization.Charting.Title();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.reloadButton = new System.Windows.Forms.Button();
			this.label2 = new System.Windows.Forms.Label();
			this.openBrowseButton = new System.Windows.Forms.Button();
			this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
			this.label1 = new System.Windows.Forms.Label();
			this.inputFilenameTextBox = new System.Windows.Forms.TextBox();
			this.saveButton = new System.Windows.Forms.Button();
			this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.label8 = new System.Windows.Forms.Label();
			this.stepNumeric = new System.Windows.Forms.NumericUpDown();
			this.label7 = new System.Windows.Forms.Label();
			this.label6 = new System.Windows.Forms.Label();
			this.endNumeric = new System.Windows.Forms.NumericUpDown();
			this.label5 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.startNumeric = new System.Windows.Forms.NumericUpDown();
			this.label3 = new System.Windows.Forms.Label();
			this.outputFilenameTextBox = new System.Windows.Forms.TextBox();
			this.saveFileDialog = new System.Windows.Forms.SaveFileDialog();
			this.seriesLabel = new System.Windows.Forms.Label();
			this.groupBox1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
			this.groupBox2.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.stepNumeric)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.endNumeric)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.startNumeric)).BeginInit();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
									| System.Windows.Forms.AnchorStyles.Left)
									| System.Windows.Forms.AnchorStyles.Right)));
			this.groupBox1.Controls.Add(this.seriesLabel);
			this.groupBox1.Controls.Add(this.reloadButton);
			this.groupBox1.Controls.Add(this.label2);
			this.groupBox1.Controls.Add(this.openBrowseButton);
			this.groupBox1.Controls.Add(this.chart1);
			this.groupBox1.Controls.Add(this.label1);
			this.groupBox1.Controls.Add(this.inputFilenameTextBox);
			this.groupBox1.Location = new System.Drawing.Point(12, 12);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(509, 377);
			this.groupBox1.TabIndex = 0;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Input";
			// 
			// reloadButton
			// 
			this.reloadButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.reloadButton.Enabled = false;
			this.reloadButton.Location = new System.Drawing.Point(428, 44);
			this.reloadButton.Name = "reloadButton";
			this.reloadButton.Size = new System.Drawing.Size(75, 23);
			this.reloadButton.TabIndex = 4;
			this.reloadButton.Text = "Reload";
			this.reloadButton.UseVisualStyleBackColor = true;
			this.reloadButton.Click += new System.EventHandler(this.reloadButton_Click);
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(6, 48);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(39, 13);
			this.label2.TabIndex = 3;
			this.label2.Text = "Series:";
			// 
			// openBrowseButton
			// 
			this.openBrowseButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.openBrowseButton.Location = new System.Drawing.Point(428, 18);
			this.openBrowseButton.Name = "openBrowseButton";
			this.openBrowseButton.Size = new System.Drawing.Size(75, 23);
			this.openBrowseButton.TabIndex = 2;
			this.openBrowseButton.Text = "Browse...";
			this.openBrowseButton.UseVisualStyleBackColor = true;
			this.openBrowseButton.Click += new System.EventHandler(this.openBrowseButton_Click);
			// 
			// chart1
			// 
			this.chart1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
									| System.Windows.Forms.AnchorStyles.Left)
									| System.Windows.Forms.AnchorStyles.Right)));
			chartArea1.Name = "ChartArea1";
			this.chart1.ChartAreas.Add(chartArea1);
			legend1.Name = "Legend1";
			this.chart1.Legends.Add(legend1);
			this.chart1.Location = new System.Drawing.Point(9, 80);
			this.chart1.Name = "chart1";
			this.chart1.Size = new System.Drawing.Size(494, 291);
			this.chart1.TabIndex = 1;
			this.chart1.Text = "chart1";
			title1.Name = "Title1";
			title1.Text = "Select input file";
			this.chart1.Titles.Add(title1);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(6, 22);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(52, 13);
			this.label1.TabIndex = 1;
			this.label1.Text = "Filename:";
			// 
			// inputFilenameTextBox
			// 
			this.inputFilenameTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
									| System.Windows.Forms.AnchorStyles.Right)));
			this.inputFilenameTextBox.Enabled = false;
			this.inputFilenameTextBox.Location = new System.Drawing.Point(64, 19);
			this.inputFilenameTextBox.Name = "inputFilenameTextBox";
			this.inputFilenameTextBox.ReadOnly = true;
			this.inputFilenameTextBox.Size = new System.Drawing.Size(358, 20);
			this.inputFilenameTextBox.TabIndex = 0;
			this.inputFilenameTextBox.Text = "click Browse button to open file";
			// 
			// saveButton
			// 
			this.saveButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.saveButton.Enabled = false;
			this.saveButton.Location = new System.Drawing.Point(427, 18);
			this.saveButton.Name = "saveButton";
			this.saveButton.Size = new System.Drawing.Size(75, 23);
			this.saveButton.TabIndex = 2;
			this.saveButton.Text = "Save";
			this.saveButton.UseVisualStyleBackColor = true;
			this.saveButton.Click += new System.EventHandler(this.saveButton_Click);
			// 
			// openFileDialog
			// 
			this.openFileDialog.FileName = "openFileDialog";
			// 
			// groupBox2
			// 
			this.groupBox2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
									| System.Windows.Forms.AnchorStyles.Right)));
			this.groupBox2.Controls.Add(this.label8);
			this.groupBox2.Controls.Add(this.stepNumeric);
			this.groupBox2.Controls.Add(this.label7);
			this.groupBox2.Controls.Add(this.label6);
			this.groupBox2.Controls.Add(this.endNumeric);
			this.groupBox2.Controls.Add(this.label5);
			this.groupBox2.Controls.Add(this.label4);
			this.groupBox2.Controls.Add(this.startNumeric);
			this.groupBox2.Controls.Add(this.label3);
			this.groupBox2.Controls.Add(this.outputFilenameTextBox);
			this.groupBox2.Controls.Add(this.saveButton);
			this.groupBox2.Location = new System.Drawing.Point(12, 395);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(509, 109);
			this.groupBox2.TabIndex = 3;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "Output";
			// 
			// label8
			// 
			this.label8.AutoSize = true;
			this.label8.Location = new System.Drawing.Point(177, 78);
			this.label8.Name = "label8";
			this.label8.Size = new System.Drawing.Size(21, 13);
			this.label8.TabIndex = 12;
			this.label8.Text = "nm";
			// 
			// stepNumeric
			// 
			this.stepNumeric.Location = new System.Drawing.Point(102, 76);
			this.stepNumeric.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
			this.stepNumeric.Name = "stepNumeric";
			this.stepNumeric.Size = new System.Drawing.Size(69, 20);
			this.stepNumeric.TabIndex = 11;
			this.stepNumeric.Value = new decimal(new int[] {
            5,
            0,
            0,
            0});
			// 
			// label7
			// 
			this.label7.AutoSize = true;
			this.label7.Location = new System.Drawing.Point(6, 76);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(80, 13);
			this.label7.TabIndex = 10;
			this.label7.Text = "Spectrum Step:";
			// 
			// label6
			// 
			this.label6.AutoSize = true;
			this.label6.Location = new System.Drawing.Point(268, 52);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(21, 13);
			this.label6.TabIndex = 9;
			this.label6.Text = "nm";
			// 
			// endNumeric
			// 
			this.endNumeric.Location = new System.Drawing.Point(193, 50);
			this.endNumeric.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
			this.endNumeric.Name = "endNumeric";
			this.endNumeric.Size = new System.Drawing.Size(69, 20);
			this.endNumeric.TabIndex = 8;
			this.endNumeric.Value = new decimal(new int[] {
            700,
            0,
            0,
            0});
			// 
			// label5
			// 
			this.label5.AutoSize = true;
			this.label5.Location = new System.Drawing.Point(177, 52);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(10, 13);
			this.label5.TabIndex = 7;
			this.label5.Text = "-";
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point(6, 52);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(90, 13);
			this.label4.TabIndex = 6;
			this.label4.Text = "Spectrum Range:";
			// 
			// startNumeric
			// 
			this.startNumeric.Location = new System.Drawing.Point(102, 50);
			this.startNumeric.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
			this.startNumeric.Name = "startNumeric";
			this.startNumeric.Size = new System.Drawing.Size(69, 20);
			this.startNumeric.TabIndex = 5;
			this.startNumeric.Value = new decimal(new int[] {
            380,
            0,
            0,
            0});
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(6, 22);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(52, 13);
			this.label3.TabIndex = 4;
			this.label3.Text = "Filename:";
			// 
			// outputFilenameTextBox
			// 
			this.outputFilenameTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
									| System.Windows.Forms.AnchorStyles.Right)));
			this.outputFilenameTextBox.Location = new System.Drawing.Point(64, 19);
			this.outputFilenameTextBox.Name = "outputFilenameTextBox";
			this.outputFilenameTextBox.Size = new System.Drawing.Size(358, 20);
			this.outputFilenameTextBox.TabIndex = 3;
			// 
			// saveFileDialog
			// 
			this.saveFileDialog.DefaultExt = "spc";
			this.saveFileDialog.Filter = "Spectrum Files (*.spc)|*.spc";
			// 
			// seriesLabel
			// 
			this.seriesLabel.AutoSize = true;
			this.seriesLabel.Location = new System.Drawing.Point(61, 48);
			this.seriesLabel.Name = "seriesLabel";
			this.seriesLabel.Size = new System.Drawing.Size(0, 13);
			this.seriesLabel.TabIndex = 5;
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(533, 516);
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.groupBox1);
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Name = "MainForm";
			this.Text = "H-RT Spectrum and Refractive/Absorption Index Import Tool";
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
			this.groupBox2.ResumeLayout(false);
			this.groupBox2.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.stepNumeric)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.endNumeric)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.startNumeric)).EndInit();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.Button openBrowseButton;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox inputFilenameTextBox;
		private System.Windows.Forms.DataVisualization.Charting.Chart chart1;
		private System.Windows.Forms.Button saveButton;
		private System.Windows.Forms.OpenFileDialog openFileDialog;
		private System.Windows.Forms.Button reloadButton;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.TextBox outputFilenameTextBox;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.NumericUpDown startNumeric;
		private System.Windows.Forms.Label label8;
		private System.Windows.Forms.NumericUpDown stepNumeric;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.NumericUpDown endNumeric;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.SaveFileDialog saveFileDialog;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label seriesLabel;
	}
}

