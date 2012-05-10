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
      this.groupBox1 = new System.Windows.Forms.GroupBox();
      this.jobsGrid = new System.Windows.Forms.DataGridView();
      this.addJobButton = new System.Windows.Forms.Button();
      this.startButton = new System.Windows.Forms.Button();
      this.removeJobsButton = new System.Windows.Forms.Button();
      this.stopButton = new System.Windows.Forms.Button();
      this.queueStatusLabel = new System.Windows.Forms.Label();
      this.sceneFilenameDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
      this.outputFilenameDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
      this.raysPerPixelDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
      this.maxRayDepthDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
      this.statusTextDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
      this.jobItems = new System.Windows.Forms.BindingSource(this.components);
      this.groupBox1.SuspendLayout();
      ((System.ComponentModel.ISupportInitialize)(this.jobsGrid)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.jobItems)).BeginInit();
      this.SuspendLayout();
      // 
      // groupBox1
      // 
      this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
      this.groupBox1.Controls.Add(this.queueStatusLabel);
      this.groupBox1.Controls.Add(this.stopButton);
      this.groupBox1.Controls.Add(this.removeJobsButton);
      this.groupBox1.Controls.Add(this.startButton);
      this.groupBox1.Controls.Add(this.addJobButton);
      this.groupBox1.Controls.Add(this.jobsGrid);
      this.groupBox1.Location = new System.Drawing.Point(12, 12);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new System.Drawing.Size(765, 493);
      this.groupBox1.TabIndex = 0;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Jobs";
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
            this.outputFilenameDataGridViewTextBoxColumn,
            this.raysPerPixelDataGridViewTextBoxColumn,
            this.maxRayDepthDataGridViewTextBoxColumn,
            this.statusTextDataGridViewTextBoxColumn});
      this.jobsGrid.DataSource = this.jobItems;
      this.jobsGrid.Location = new System.Drawing.Point(6, 19);
      this.jobsGrid.Name = "jobsGrid";
      this.jobsGrid.ReadOnly = true;
      this.jobsGrid.RowHeadersWidth = 24;
      this.jobsGrid.Size = new System.Drawing.Size(753, 439);
      this.jobsGrid.TabIndex = 0;
      // 
      // addJobButton
      // 
      this.addJobButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
      this.addJobButton.Location = new System.Drawing.Point(6, 464);
      this.addJobButton.Name = "addJobButton";
      this.addJobButton.Size = new System.Drawing.Size(75, 23);
      this.addJobButton.TabIndex = 1;
      this.addJobButton.Text = "Add...";
      this.addJobButton.UseVisualStyleBackColor = true;
      // 
      // startButton
      // 
      this.startButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
      this.startButton.Location = new System.Drawing.Point(684, 464);
      this.startButton.Name = "startButton";
      this.startButton.Size = new System.Drawing.Size(75, 23);
      this.startButton.TabIndex = 2;
      this.startButton.Text = "Start";
      this.startButton.UseVisualStyleBackColor = true;
      // 
      // removeJobsButton
      // 
      this.removeJobsButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
      this.removeJobsButton.Location = new System.Drawing.Point(87, 464);
      this.removeJobsButton.Name = "removeJobsButton";
      this.removeJobsButton.Size = new System.Drawing.Size(75, 23);
      this.removeJobsButton.TabIndex = 3;
      this.removeJobsButton.Text = "Remove";
      this.removeJobsButton.UseVisualStyleBackColor = true;
      // 
      // stopButton
      // 
      this.stopButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
      this.stopButton.Location = new System.Drawing.Point(603, 464);
      this.stopButton.Name = "stopButton";
      this.stopButton.Size = new System.Drawing.Size(75, 23);
      this.stopButton.TabIndex = 4;
      this.stopButton.Text = "Stop";
      this.stopButton.UseVisualStyleBackColor = true;
      // 
      // queueStatusLabel
      // 
      this.queueStatusLabel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
      this.queueStatusLabel.Location = new System.Drawing.Point(168, 464);
      this.queueStatusLabel.Name = "queueStatusLabel";
      this.queueStatusLabel.Size = new System.Drawing.Size(429, 23);
      this.queueStatusLabel.TabIndex = 2;
      this.queueStatusLabel.Text = "Idle";
      this.queueStatusLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
      // 
      // sceneFilenameDataGridViewTextBoxColumn
      // 
      this.sceneFilenameDataGridViewTextBoxColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
      this.sceneFilenameDataGridViewTextBoxColumn.DataPropertyName = "SceneFilename";
      this.sceneFilenameDataGridViewTextBoxColumn.HeaderText = "Scene Filename";
      this.sceneFilenameDataGridViewTextBoxColumn.Name = "sceneFilenameDataGridViewTextBoxColumn";
      this.sceneFilenameDataGridViewTextBoxColumn.ReadOnly = true;
      // 
      // outputFilenameDataGridViewTextBoxColumn
      // 
      this.outputFilenameDataGridViewTextBoxColumn.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
      this.outputFilenameDataGridViewTextBoxColumn.DataPropertyName = "OutputFilename";
      this.outputFilenameDataGridViewTextBoxColumn.HeaderText = "Render Filename";
      this.outputFilenameDataGridViewTextBoxColumn.Name = "outputFilenameDataGridViewTextBoxColumn";
      this.outputFilenameDataGridViewTextBoxColumn.ReadOnly = true;
      // 
      // raysPerPixelDataGridViewTextBoxColumn
      // 
      this.raysPerPixelDataGridViewTextBoxColumn.DataPropertyName = "RaysPerPixel";
      this.raysPerPixelDataGridViewTextBoxColumn.HeaderText = "Rays/Pixel";
      this.raysPerPixelDataGridViewTextBoxColumn.Name = "raysPerPixelDataGridViewTextBoxColumn";
      this.raysPerPixelDataGridViewTextBoxColumn.ReadOnly = true;
      // 
      // maxRayDepthDataGridViewTextBoxColumn
      // 
      this.maxRayDepthDataGridViewTextBoxColumn.DataPropertyName = "MaxRayDepth";
      this.maxRayDepthDataGridViewTextBoxColumn.HeaderText = "Ray Depth";
      this.maxRayDepthDataGridViewTextBoxColumn.Name = "maxRayDepthDataGridViewTextBoxColumn";
      this.maxRayDepthDataGridViewTextBoxColumn.ReadOnly = true;
      // 
      // statusTextDataGridViewTextBoxColumn
      // 
      this.statusTextDataGridViewTextBoxColumn.DataPropertyName = "StatusText";
      this.statusTextDataGridViewTextBoxColumn.HeaderText = "Status";
      this.statusTextDataGridViewTextBoxColumn.Name = "statusTextDataGridViewTextBoxColumn";
      this.statusTextDataGridViewTextBoxColumn.ReadOnly = true;
      // 
      // jobItems
      // 
      this.jobItems.DataSource = typeof(HrtQueue.JobItem);
      // 
      // MainForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(789, 517);
      this.Controls.Add(this.groupBox1);
      this.Name = "MainForm";
      this.Text = "H-RT Queue";
      this.groupBox1.ResumeLayout(false);
      ((System.ComponentModel.ISupportInitialize)(this.jobsGrid)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.jobItems)).EndInit();
      this.ResumeLayout(false);

    }

    #endregion

    private System.Windows.Forms.GroupBox groupBox1;
    private System.Windows.Forms.DataGridView jobsGrid;
    private System.Windows.Forms.Button addJobButton;
    private System.Windows.Forms.BindingSource jobItems;
    private System.Windows.Forms.Button stopButton;
    private System.Windows.Forms.Button removeJobsButton;
    private System.Windows.Forms.Button startButton;
    private System.Windows.Forms.DataGridViewTextBoxColumn sceneFilenameDataGridViewTextBoxColumn;
    private System.Windows.Forms.DataGridViewTextBoxColumn outputFilenameDataGridViewTextBoxColumn;
    private System.Windows.Forms.DataGridViewTextBoxColumn raysPerPixelDataGridViewTextBoxColumn;
    private System.Windows.Forms.DataGridViewTextBoxColumn maxRayDepthDataGridViewTextBoxColumn;
    private System.Windows.Forms.DataGridViewTextBoxColumn statusTextDataGridViewTextBoxColumn;
    private System.Windows.Forms.Label queueStatusLabel;
  }
}

