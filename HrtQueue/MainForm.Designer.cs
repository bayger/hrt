namespace HrtQueue
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
      this.components = new System.ComponentModel.Container();
      System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
      this.threadsNum = new System.Windows.Forms.NumericUpDown();
      this.label1 = new System.Windows.Forms.Label();
      this.stopButton = new System.Windows.Forms.Button();
      this.startButton = new System.Windows.Forms.Button();
      this.progressBar = new System.Windows.Forms.ProgressBar();
      this.pictureBox1 = new System.Windows.Forms.PictureBox();
      this.panel1 = new System.Windows.Forms.Panel();
      this.resetButton = new System.Windows.Forms.Button();
      this.selectAllButton = new System.Windows.Forms.Button();
      this.setRayDepthButton = new System.Windows.Forms.Button();
      this.rayDepthCombo = new System.Windows.Forms.ComboBox();
      this.setRppButton = new System.Windows.Forms.Button();
      this.rppCombo = new System.Windows.Forms.ComboBox();
      this.removeJobsButton = new System.Windows.Forms.Button();
      this.addJobButton = new System.Windows.Forms.Button();
      this.jobsGrid = new System.Windows.Forms.DataGridView();
      this.statusLabel = new System.Windows.Forms.Label();
      this.jobItems = new System.Windows.Forms.BindingSource(this.components);
      this.sceneFilenameDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
      this.raysPerPixelDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
      this.VarianceFilter = new System.Windows.Forms.DataGridViewTextBoxColumn();
      this.SigmaFilter = new System.Windows.Forms.DataGridViewTextBoxColumn();
      this.MaxPasses = new System.Windows.Forms.DataGridViewTextBoxColumn();
      this.maxRayDepthDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
      this.statusTextDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
      ((System.ComponentModel.ISupportInitialize)(this.threadsNum)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.jobsGrid)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.jobItems)).BeginInit();
      this.SuspendLayout();
      // 
      // threadsNum
      // 
      this.threadsNum.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
      this.threadsNum.Location = new System.Drawing.Point(529, 478);
      this.threadsNum.Maximum = new decimal(new int[] {
            64,
            0,
            0,
            0});
      this.threadsNum.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
      this.threadsNum.Name = "threadsNum";
      this.threadsNum.Size = new System.Drawing.Size(59, 20);
      this.threadsNum.TabIndex = 6;
      this.threadsNum.Value = new decimal(new int[] {
            4,
            0,
            0,
            0});
      // 
      // label1
      // 
      this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(456, 480);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(67, 13);
      this.label1.TabIndex = 5;
      this.label1.Text = "Use threads:";
      // 
      // stopButton
      // 
      this.stopButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
      this.stopButton.Location = new System.Drawing.Point(616, 475);
      this.stopButton.Name = "stopButton";
      this.stopButton.Size = new System.Drawing.Size(75, 23);
      this.stopButton.TabIndex = 4;
      this.stopButton.Text = "Stop";
      this.stopButton.UseVisualStyleBackColor = true;
      this.stopButton.Click += new System.EventHandler(this.stopButton_Click);
      // 
      // startButton
      // 
      this.startButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
      this.startButton.Location = new System.Drawing.Point(697, 475);
      this.startButton.Name = "startButton";
      this.startButton.Size = new System.Drawing.Size(75, 23);
      this.startButton.TabIndex = 2;
      this.startButton.Text = "Start";
      this.startButton.UseVisualStyleBackColor = true;
      this.startButton.Click += new System.EventHandler(this.startButton_Click);
      // 
      // progressBar
      // 
      this.progressBar.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
      this.progressBar.Location = new System.Drawing.Point(12, 475);
      this.progressBar.Name = "progressBar";
      this.progressBar.Size = new System.Drawing.Size(271, 23);
      this.progressBar.TabIndex = 7;
      // 
      // pictureBox1
      // 
      this.pictureBox1.Image = global::HrtQueue.Properties.Resources.H_RT_Queue_Banner;
      this.pictureBox1.Location = new System.Drawing.Point(0, 0);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new System.Drawing.Size(800, 73);
      this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
      this.pictureBox1.TabIndex = 8;
      this.pictureBox1.TabStop = false;
      // 
      // panel1
      // 
      this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
      this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(78)))), ((int)(((byte)(81)))), ((int)(((byte)(75)))));
      this.panel1.Location = new System.Drawing.Point(800, 0);
      this.panel1.Name = "panel1";
      this.panel1.Size = new System.Drawing.Size(0, 73);
      this.panel1.TabIndex = 9;
      // 
      // resetButton
      // 
      this.resetButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
      this.resetButton.Location = new System.Drawing.Point(697, 87);
      this.resetButton.Name = "resetButton";
      this.resetButton.Size = new System.Drawing.Size(75, 23);
      this.resetButton.TabIndex = 18;
      this.resetButton.Text = "Reset";
      this.resetButton.UseVisualStyleBackColor = true;
      this.resetButton.Click += new System.EventHandler(this.resetButton_Click);
      // 
      // selectAllButton
      // 
      this.selectAllButton.Location = new System.Drawing.Point(174, 87);
      this.selectAllButton.Name = "selectAllButton";
      this.selectAllButton.Size = new System.Drawing.Size(75, 23);
      this.selectAllButton.TabIndex = 17;
      this.selectAllButton.Text = "Select All";
      this.selectAllButton.UseVisualStyleBackColor = true;
      this.selectAllButton.Click += new System.EventHandler(this.selectAllButton_Click);
      // 
      // setRayDepthButton
      // 
      this.setRayDepthButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
      this.setRayDepthButton.Location = new System.Drawing.Point(585, 87);
      this.setRayDepthButton.Name = "setRayDepthButton";
      this.setRayDepthButton.Size = new System.Drawing.Size(92, 23);
      this.setRayDepthButton.TabIndex = 16;
      this.setRayDepthButton.Text = "Set Ray Depth";
      this.setRayDepthButton.UseVisualStyleBackColor = true;
      this.setRayDepthButton.Click += new System.EventHandler(this.setRayDepthButton_Click);
      // 
      // rayDepthCombo
      // 
      this.rayDepthCombo.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
      this.rayDepthCombo.FormatString = "N0";
      this.rayDepthCombo.FormattingEnabled = true;
      this.rayDepthCombo.Location = new System.Drawing.Point(519, 88);
      this.rayDepthCombo.Name = "rayDepthCombo";
      this.rayDepthCombo.Size = new System.Drawing.Size(60, 21);
      this.rayDepthCombo.TabIndex = 15;
      // 
      // setRppButton
      // 
      this.setRppButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
      this.setRppButton.Location = new System.Drawing.Point(407, 87);
      this.setRppButton.Name = "setRppButton";
      this.setRppButton.Size = new System.Drawing.Size(92, 23);
      this.setRppButton.TabIndex = 14;
      this.setRppButton.Text = "Set Rays/Pixel";
      this.setRppButton.UseVisualStyleBackColor = true;
      this.setRppButton.Click += new System.EventHandler(this.setRppButton_Click);
      // 
      // rppCombo
      // 
      this.rppCombo.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
      this.rppCombo.FormatString = "N0";
      this.rppCombo.FormattingEnabled = true;
      this.rppCombo.Location = new System.Drawing.Point(341, 88);
      this.rppCombo.Name = "rppCombo";
      this.rppCombo.Size = new System.Drawing.Size(60, 21);
      this.rppCombo.TabIndex = 13;
      // 
      // removeJobsButton
      // 
      this.removeJobsButton.Location = new System.Drawing.Point(93, 87);
      this.removeJobsButton.Name = "removeJobsButton";
      this.removeJobsButton.Size = new System.Drawing.Size(75, 23);
      this.removeJobsButton.TabIndex = 12;
      this.removeJobsButton.Text = "Remove";
      this.removeJobsButton.UseVisualStyleBackColor = true;
      this.removeJobsButton.Click += new System.EventHandler(this.removeJobsButton_Click);
      // 
      // addJobButton
      // 
      this.addJobButton.Location = new System.Drawing.Point(12, 87);
      this.addJobButton.Name = "addJobButton";
      this.addJobButton.Size = new System.Drawing.Size(75, 23);
      this.addJobButton.TabIndex = 11;
      this.addJobButton.Text = "Add...";
      this.addJobButton.UseVisualStyleBackColor = true;
      this.addJobButton.Click += new System.EventHandler(this.addJobButton_Click);
      // 
      // jobsGrid
      // 
      this.jobsGrid.AllowUserToAddRows = false;
      this.jobsGrid.AllowUserToDeleteRows = false;
      this.jobsGrid.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
      this.jobsGrid.AutoGenerateColumns = false;
      this.jobsGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.jobsGrid.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.sceneFilenameDataGridViewTextBoxColumn,
            this.raysPerPixelDataGridViewTextBoxColumn,
            this.VarianceFilter,
            this.SigmaFilter,
            this.MaxPasses,
            this.maxRayDepthDataGridViewTextBoxColumn,
            this.statusTextDataGridViewTextBoxColumn});
      this.jobsGrid.DataSource = this.jobItems;
      this.jobsGrid.Location = new System.Drawing.Point(12, 120);
      this.jobsGrid.Name = "jobsGrid";
      this.jobsGrid.RowHeadersWidth = 24;
      this.jobsGrid.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
      this.jobsGrid.Size = new System.Drawing.Size(760, 340);
      this.jobsGrid.TabIndex = 10;
      // 
      // statusLabel
      // 
      this.statusLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
      this.statusLabel.Location = new System.Drawing.Point(289, 475);
      this.statusLabel.Name = "statusLabel";
      this.statusLabel.Size = new System.Drawing.Size(161, 23);
      this.statusLabel.TabIndex = 19;
      this.statusLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
      // 
      // jobItems
      // 
      this.jobItems.DataSource = typeof(HrtQueue.JobItem);
      this.jobItems.ListChanged += new System.ComponentModel.ListChangedEventHandler(this.jobItems_ListChanged);
      // 
      // sceneFilenameDataGridViewTextBoxColumn
      // 
      this.sceneFilenameDataGridViewTextBoxColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
      this.sceneFilenameDataGridViewTextBoxColumn.DataPropertyName = "SceneFilename";
      this.sceneFilenameDataGridViewTextBoxColumn.HeaderText = "Scene Filename";
      this.sceneFilenameDataGridViewTextBoxColumn.Name = "sceneFilenameDataGridViewTextBoxColumn";
      this.sceneFilenameDataGridViewTextBoxColumn.ReadOnly = true;
      // 
      // raysPerPixelDataGridViewTextBoxColumn
      // 
      this.raysPerPixelDataGridViewTextBoxColumn.DataPropertyName = "RaysPerPixel";
      this.raysPerPixelDataGridViewTextBoxColumn.HeaderText = "Rays per Pixel";
      this.raysPerPixelDataGridViewTextBoxColumn.Name = "raysPerPixelDataGridViewTextBoxColumn";
      this.raysPerPixelDataGridViewTextBoxColumn.Width = 70;
      // 
      // VarianceFilter
      // 
      this.VarianceFilter.DataPropertyName = "VarianceFilter";
      this.VarianceFilter.HeaderText = "Variance Filter";
      this.VarianceFilter.Name = "VarianceFilter";
      // 
      // SigmaFilter
      // 
      this.SigmaFilter.DataPropertyName = "SigmaFilter";
      this.SigmaFilter.HeaderText = "Sigma Filter";
      this.SigmaFilter.Name = "SigmaFilter";
      this.SigmaFilter.Width = 70;
      // 
      // MaxPasses
      // 
      this.MaxPasses.DataPropertyName = "MaxPasses";
      this.MaxPasses.HeaderText = "Max Passes";
      this.MaxPasses.Name = "MaxPasses";
      // 
      // maxRayDepthDataGridViewTextBoxColumn
      // 
      this.maxRayDepthDataGridViewTextBoxColumn.DataPropertyName = "MaxRayDepth";
      this.maxRayDepthDataGridViewTextBoxColumn.HeaderText = "Ray Depth";
      this.maxRayDepthDataGridViewTextBoxColumn.Name = "maxRayDepthDataGridViewTextBoxColumn";
      this.maxRayDepthDataGridViewTextBoxColumn.Width = 70;
      // 
      // statusTextDataGridViewTextBoxColumn
      // 
      this.statusTextDataGridViewTextBoxColumn.DataPropertyName = "StatusText";
      this.statusTextDataGridViewTextBoxColumn.HeaderText = "Status";
      this.statusTextDataGridViewTextBoxColumn.Name = "statusTextDataGridViewTextBoxColumn";
      this.statusTextDataGridViewTextBoxColumn.ReadOnly = true;
      // 
      // MainForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(784, 510);
      this.Controls.Add(this.statusLabel);
      this.Controls.Add(this.resetButton);
      this.Controls.Add(this.selectAllButton);
      this.Controls.Add(this.setRayDepthButton);
      this.Controls.Add(this.rayDepthCombo);
      this.Controls.Add(this.setRppButton);
      this.Controls.Add(this.rppCombo);
      this.Controls.Add(this.removeJobsButton);
      this.Controls.Add(this.addJobButton);
      this.Controls.Add(this.jobsGrid);
      this.Controls.Add(this.panel1);
      this.Controls.Add(this.pictureBox1);
      this.Controls.Add(this.progressBar);
      this.Controls.Add(this.stopButton);
      this.Controls.Add(this.threadsNum);
      this.Controls.Add(this.startButton);
      this.Controls.Add(this.label1);
      this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
      this.MinimumSize = new System.Drawing.Size(800, 550);
      this.Name = "MainForm";
      this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
      this.Text = "H-RT Queue";
      this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
      this.Load += new System.EventHandler(this.MainForm_Load);
      ((System.ComponentModel.ISupportInitialize)(this.threadsNum)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.jobsGrid)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.jobItems)).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.BindingSource jobItems;
    private System.Windows.Forms.Button stopButton;
    private System.Windows.Forms.Button startButton;
    private System.Windows.Forms.NumericUpDown threadsNum;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.ProgressBar progressBar;
    private System.Windows.Forms.PictureBox pictureBox1;
    private System.Windows.Forms.Panel panel1;
    private System.Windows.Forms.Button resetButton;
    private System.Windows.Forms.Button selectAllButton;
    private System.Windows.Forms.Button setRayDepthButton;
    private System.Windows.Forms.ComboBox rayDepthCombo;
    private System.Windows.Forms.Button setRppButton;
    private System.Windows.Forms.ComboBox rppCombo;
    private System.Windows.Forms.Button removeJobsButton;
    private System.Windows.Forms.Button addJobButton;
    private System.Windows.Forms.DataGridView jobsGrid;
    private System.Windows.Forms.Label statusLabel;
    private System.Windows.Forms.DataGridViewTextBoxColumn sceneFilenameDataGridViewTextBoxColumn;
    private System.Windows.Forms.DataGridViewTextBoxColumn raysPerPixelDataGridViewTextBoxColumn;
    private System.Windows.Forms.DataGridViewTextBoxColumn VarianceFilter;
    private System.Windows.Forms.DataGridViewTextBoxColumn SigmaFilter;
    private System.Windows.Forms.DataGridViewTextBoxColumn MaxPasses;
    private System.Windows.Forms.DataGridViewTextBoxColumn maxRayDepthDataGridViewTextBoxColumn;
    private System.Windows.Forms.DataGridViewTextBoxColumn statusTextDataGridViewTextBoxColumn;
  }
}

