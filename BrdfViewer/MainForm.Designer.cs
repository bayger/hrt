namespace BrdfViewer
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
      this.label1 = new System.Windows.Forms.Label();
      this.sceneFileName = new System.Windows.Forms.TextBox();
      this.browseSceneFile = new System.Windows.Forms.Button();
      this.label2 = new System.Windows.Forms.Label();
      this.groupBox1 = new System.Windows.Forms.GroupBox();
      this.precalcAll = new System.Windows.Forms.Button();
      this.getMaterials = new System.Windows.Forms.Button();
      this.materials = new System.Windows.Forms.ComboBox();
      this.materialsSource = new System.Windows.Forms.BindingSource(this.components);
      this.groupBox2 = new System.Windows.Forms.GroupBox();
      this.generate = new System.Windows.Forms.Button();
      this.label5 = new System.Windows.Forms.Label();
      this.outgoingAngle = new System.Windows.Forms.NumericUpDown();
      this.angleStep = new System.Windows.Forms.NumericUpDown();
      this.label4 = new System.Windows.Forms.Label();
      this.pdfGen = new System.Windows.Forms.RadioButton();
      this.brdfGen = new System.Windows.Forms.RadioButton();
      this.label3 = new System.Windows.Forms.Label();
      this.timer = new System.Windows.Forms.Timer(this.components);
      this.pictureBox1 = new System.Windows.Forms.PictureBox();
      this.panel1 = new System.Windows.Forms.Panel();
      this.materialSignature = new System.Windows.Forms.Label();
      this.angularPlotControl1 = new BrdfViewer.AngularPlotControl();
      this.groupBox3 = new System.Windows.Forms.GroupBox();
      this.label6 = new System.Windows.Forms.Label();
      this.outAngleStep = new System.Windows.Forms.NumericUpDown();
      this.batch = new System.Windows.Forms.Button();
      this.savePlot = new System.Windows.Forms.Button();
      this.groupBox1.SuspendLayout();
      ((System.ComponentModel.ISupportInitialize)(this.materialsSource)).BeginInit();
      this.groupBox2.SuspendLayout();
      ((System.ComponentModel.ISupportInitialize)(this.outgoingAngle)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.angleStep)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
      this.groupBox3.SuspendLayout();
      ((System.ComponentModel.ISupportInitialize)(this.outAngleStep)).BeginInit();
      this.SuspendLayout();
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(16, 25);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(57, 13);
      this.label1.TabIndex = 0;
      this.label1.Text = "Scene file:";
      // 
      // sceneFileName
      // 
      this.sceneFileName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
      this.sceneFileName.Location = new System.Drawing.Point(107, 22);
      this.sceneFileName.Name = "sceneFileName";
      this.sceneFileName.Size = new System.Drawing.Size(548, 20);
      this.sceneFileName.TabIndex = 1;
      this.sceneFileName.Text = "experimental.ysf";
      // 
      // browseSceneFile
      // 
      this.browseSceneFile.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
      this.browseSceneFile.Location = new System.Drawing.Point(661, 20);
      this.browseSceneFile.Name = "browseSceneFile";
      this.browseSceneFile.Size = new System.Drawing.Size(75, 23);
      this.browseSceneFile.TabIndex = 2;
      this.browseSceneFile.Text = "Browse...";
      this.browseSceneFile.UseVisualStyleBackColor = true;
      this.browseSceneFile.Click += new System.EventHandler(this.browseSceneFile_Click);
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point(16, 56);
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size(76, 13);
      this.label2.TabIndex = 3;
      this.label2.Text = "Material name:";
      // 
      // groupBox1
      // 
      this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
      this.groupBox1.Controls.Add(this.precalcAll);
      this.groupBox1.Controls.Add(this.getMaterials);
      this.groupBox1.Controls.Add(this.materials);
      this.groupBox1.Controls.Add(this.label1);
      this.groupBox1.Controls.Add(this.browseSceneFile);
      this.groupBox1.Controls.Add(this.sceneFileName);
      this.groupBox1.Controls.Add(this.label2);
      this.groupBox1.Location = new System.Drawing.Point(12, 86);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new System.Drawing.Size(774, 92);
      this.groupBox1.TabIndex = 5;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Input";
      // 
      // precalcAll
      // 
      this.precalcAll.Location = new System.Drawing.Point(371, 51);
      this.precalcAll.Name = "precalcAll";
      this.precalcAll.Size = new System.Drawing.Size(140, 23);
      this.precalcAll.TabIndex = 8;
      this.precalcAll.Text = "Precalculate Materials";
      this.precalcAll.UseVisualStyleBackColor = true;
      this.precalcAll.Click += new System.EventHandler(this.precalcAll_Click);
      // 
      // getMaterials
      // 
      this.getMaterials.Location = new System.Drawing.Point(262, 51);
      this.getMaterials.Name = "getMaterials";
      this.getMaterials.Size = new System.Drawing.Size(100, 23);
      this.getMaterials.TabIndex = 6;
      this.getMaterials.Text = "Get Materials";
      this.getMaterials.UseVisualStyleBackColor = true;
      this.getMaterials.Click += new System.EventHandler(this.getMaterials_Click);
      // 
      // materials
      // 
      this.materials.DataSource = this.materialsSource;
      this.materials.DisplayMember = "Name";
      this.materials.FormattingEnabled = true;
      this.materials.Location = new System.Drawing.Point(107, 53);
      this.materials.Name = "materials";
      this.materials.Size = new System.Drawing.Size(149, 21);
      this.materials.TabIndex = 5;
      this.materials.SelectedIndexChanged += new System.EventHandler(this.materials_SelectedIndexChanged);
      // 
      // materialsSource
      // 
      this.materialsSource.DataSource = typeof(BrdfViewer.MaterialItem);
      // 
      // groupBox2
      // 
      this.groupBox2.Controls.Add(this.generate);
      this.groupBox2.Controls.Add(this.label5);
      this.groupBox2.Controls.Add(this.outgoingAngle);
      this.groupBox2.Controls.Add(this.angleStep);
      this.groupBox2.Controls.Add(this.label4);
      this.groupBox2.Controls.Add(this.pdfGen);
      this.groupBox2.Controls.Add(this.brdfGen);
      this.groupBox2.Controls.Add(this.label3);
      this.groupBox2.Location = new System.Drawing.Point(12, 184);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new System.Drawing.Size(392, 107);
      this.groupBox2.TabIndex = 6;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "BRDF Data Generation";
      // 
      // generate
      // 
      this.generate.Location = new System.Drawing.Point(262, 20);
      this.generate.Name = "generate";
      this.generate.Size = new System.Drawing.Size(103, 23);
      this.generate.TabIndex = 10;
      this.generate.Text = "Generate";
      this.generate.UseVisualStyleBackColor = true;
      this.generate.Click += new System.EventHandler(this.generate_Click);
      // 
      // label5
      // 
      this.label5.AutoSize = true;
      this.label5.Location = new System.Drawing.Point(16, 74);
      this.label5.Name = "label5";
      this.label5.Size = new System.Drawing.Size(82, 13);
      this.label5.TabIndex = 6;
      this.label5.Text = "Outgoing angle:";
      // 
      // outgoingAngle
      // 
      this.outgoingAngle.DecimalPlaces = 2;
      this.outgoingAngle.Increment = new decimal(new int[] {
            5,
            0,
            0,
            0});
      this.outgoingAngle.Location = new System.Drawing.Point(107, 72);
      this.outgoingAngle.Maximum = new decimal(new int[] {
            90,
            0,
            0,
            0});
      this.outgoingAngle.Minimum = new decimal(new int[] {
            90,
            0,
            0,
            -2147483648});
      this.outgoingAngle.Name = "outgoingAngle";
      this.outgoingAngle.Size = new System.Drawing.Size(120, 20);
      this.outgoingAngle.TabIndex = 5;
      this.outgoingAngle.Value = new decimal(new int[] {
            30,
            0,
            0,
            0});
      this.outgoingAngle.ValueChanged += new System.EventHandler(this.incidentAngle_ValueChanged);
      // 
      // angleStep
      // 
      this.angleStep.DecimalPlaces = 2;
      this.angleStep.Increment = new decimal(new int[] {
            5,
            0,
            0,
            131072});
      this.angleStep.Location = new System.Drawing.Point(107, 46);
      this.angleStep.Name = "angleStep";
      this.angleStep.Size = new System.Drawing.Size(120, 20);
      this.angleStep.TabIndex = 4;
      this.angleStep.Value = new decimal(new int[] {
            1,
            0,
            0,
            65536});
      this.angleStep.ValueChanged += new System.EventHandler(this.angleStep_ValueChanged);
      // 
      // label4
      // 
      this.label4.AutoSize = true;
      this.label4.Location = new System.Drawing.Point(16, 51);
      this.label4.Name = "label4";
      this.label4.Size = new System.Drawing.Size(60, 13);
      this.label4.TabIndex = 3;
      this.label4.Text = "Angle step:";
      // 
      // pdfGen
      // 
      this.pdfGen.AutoSize = true;
      this.pdfGen.Location = new System.Drawing.Point(181, 22);
      this.pdfGen.Name = "pdfGen";
      this.pdfGen.Size = new System.Drawing.Size(46, 17);
      this.pdfGen.TabIndex = 2;
      this.pdfGen.Text = "PDF";
      this.pdfGen.UseVisualStyleBackColor = true;
      this.pdfGen.CheckedChanged += new System.EventHandler(this.pdfGen_CheckedChanged);
      // 
      // brdfGen
      // 
      this.brdfGen.AutoSize = true;
      this.brdfGen.Checked = true;
      this.brdfGen.Location = new System.Drawing.Point(107, 23);
      this.brdfGen.Name = "brdfGen";
      this.brdfGen.Size = new System.Drawing.Size(54, 17);
      this.brdfGen.TabIndex = 1;
      this.brdfGen.TabStop = true;
      this.brdfGen.Text = "BRDF";
      this.brdfGen.UseVisualStyleBackColor = true;
      this.brdfGen.CheckedChanged += new System.EventHandler(this.brdfGen_CheckedChanged);
      // 
      // label3
      // 
      this.label3.AutoSize = true;
      this.label3.Location = new System.Drawing.Point(16, 25);
      this.label3.Name = "label3";
      this.label3.Size = new System.Drawing.Size(85, 13);
      this.label3.TabIndex = 0;
      this.label3.Text = "Generation type:";
      // 
      // timer
      // 
      this.timer.Interval = 250;
      this.timer.Tick += new System.EventHandler(this.timer_Tick);
      // 
      // pictureBox1
      // 
      this.pictureBox1.Image = global::BrdfViewer.Properties.Resources.Banner;
      this.pictureBox1.Location = new System.Drawing.Point(0, 0);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new System.Drawing.Size(800, 73);
      this.pictureBox1.TabIndex = 7;
      this.pictureBox1.TabStop = false;
      // 
      // panel1
      // 
      this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
      this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(78)))), ((int)(((byte)(81)))), ((int)(((byte)(75)))));
      this.panel1.Location = new System.Drawing.Point(800, 0);
      this.panel1.Name = "panel1";
      this.panel1.Size = new System.Drawing.Size(2, 73);
      this.panel1.TabIndex = 8;
      // 
      // materialSignature
      // 
      this.materialSignature.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
      this.materialSignature.Location = new System.Drawing.Point(12, 294);
      this.materialSignature.Name = "materialSignature";
      this.materialSignature.Size = new System.Drawing.Size(774, 13);
      this.materialSignature.TabIndex = 12;
      this.materialSignature.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
      // 
      // angularPlotControl1
      // 
      this.angularPlotControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
      this.angularPlotControl1.ChartAxisColor = System.Drawing.Color.DimGray;
      this.angularPlotControl1.ChartBackColor = System.Drawing.Color.White;
      this.angularPlotControl1.ChartPlotColor = System.Drawing.Color.Blue;
      this.angularPlotControl1.ChartSecondaryAxisColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
      this.angularPlotControl1.ChartTitle = null;
      this.angularPlotControl1.Data = null;
      this.angularPlotControl1.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.76923F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
      this.angularPlotControl1.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
      this.angularPlotControl1.IncidentAngle = 0D;
      this.angularPlotControl1.Location = new System.Drawing.Point(12, 310);
      this.angularPlotControl1.Name = "angularPlotControl1";
      this.angularPlotControl1.Size = new System.Drawing.Size(774, 364);
      this.angularPlotControl1.TabIndex = 13;
      this.angularPlotControl1.Text = "angularPlotControl1";
      // 
      // groupBox3
      // 
      this.groupBox3.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
      this.groupBox3.Controls.Add(this.label6);
      this.groupBox3.Controls.Add(this.outAngleStep);
      this.groupBox3.Controls.Add(this.batch);
      this.groupBox3.Controls.Add(this.savePlot);
      this.groupBox3.Location = new System.Drawing.Point(411, 185);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new System.Drawing.Size(375, 106);
      this.groupBox3.TabIndex = 14;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Plot Saving";
      // 
      // label6
      // 
      this.label6.AutoSize = true;
      this.label6.Location = new System.Drawing.Point(7, 50);
      this.label6.Name = "label6";
      this.label6.Size = new System.Drawing.Size(105, 13);
      this.label6.TabIndex = 19;
      this.label6.Text = "Outgoing angle step:";
      // 
      // outAngleStep
      // 
      this.outAngleStep.DecimalPlaces = 2;
      this.outAngleStep.Increment = new decimal(new int[] {
            5,
            0,
            0,
            0});
      this.outAngleStep.Location = new System.Drawing.Point(118, 48);
      this.outAngleStep.Maximum = new decimal(new int[] {
            90,
            0,
            0,
            0});
      this.outAngleStep.Minimum = new decimal(new int[] {
            90,
            0,
            0,
            -2147483648});
      this.outAngleStep.Name = "outAngleStep";
      this.outAngleStep.Size = new System.Drawing.Size(103, 20);
      this.outAngleStep.TabIndex = 18;
      this.outAngleStep.Value = new decimal(new int[] {
            5,
            0,
            0,
            0});
      // 
      // batch
      // 
      this.batch.Location = new System.Drawing.Point(118, 19);
      this.batch.Name = "batch";
      this.batch.Size = new System.Drawing.Size(103, 23);
      this.batch.TabIndex = 17;
      this.batch.Text = "Save batch";
      this.batch.UseVisualStyleBackColor = true;
      this.batch.Click += new System.EventHandler(this.batch_Click);
      // 
      // savePlot
      // 
      this.savePlot.Location = new System.Drawing.Point(9, 19);
      this.savePlot.Name = "savePlot";
      this.savePlot.Size = new System.Drawing.Size(103, 23);
      this.savePlot.TabIndex = 16;
      this.savePlot.Text = "Save current";
      this.savePlot.UseVisualStyleBackColor = true;
      this.savePlot.Click += new System.EventHandler(this.savePlot_Click);
      // 
      // MainForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(798, 686);
      this.Controls.Add(this.groupBox3);
      this.Controls.Add(this.materialSignature);
      this.Controls.Add(this.angularPlotControl1);
      this.Controls.Add(this.panel1);
      this.Controls.Add(this.pictureBox1);
      this.Controls.Add(this.groupBox2);
      this.Controls.Add(this.groupBox1);
      this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
      this.MinimumSize = new System.Drawing.Size(692, 600);
      this.Name = "MainForm";
      this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
      this.Text = "BRDF Viewer for H-RT";
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      ((System.ComponentModel.ISupportInitialize)(this.materialsSource)).EndInit();
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      ((System.ComponentModel.ISupportInitialize)(this.outgoingAngle)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.angleStep)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
      this.groupBox3.ResumeLayout(false);
      this.groupBox3.PerformLayout();
      ((System.ComponentModel.ISupportInitialize)(this.outAngleStep)).EndInit();
      this.ResumeLayout(false);

    }

    #endregion

    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.TextBox sceneFileName;
    private System.Windows.Forms.Button browseSceneFile;
    private System.Windows.Forms.Label label2;
    private System.Windows.Forms.GroupBox groupBox1;
    private System.Windows.Forms.GroupBox groupBox2;
    private System.Windows.Forms.Label label5;
    private System.Windows.Forms.NumericUpDown outgoingAngle;
    private System.Windows.Forms.NumericUpDown angleStep;
    private System.Windows.Forms.Label label4;
    private System.Windows.Forms.RadioButton pdfGen;
    private System.Windows.Forms.RadioButton brdfGen;
    private System.Windows.Forms.Label label3;
    private System.Windows.Forms.Button generate;
    private System.Windows.Forms.Button getMaterials;
    private System.Windows.Forms.ComboBox materials;
    private System.Windows.Forms.BindingSource materialsSource;
    private System.Windows.Forms.Timer timer;
    private System.Windows.Forms.Button precalcAll;
    private System.Windows.Forms.PictureBox pictureBox1;
    private System.Windows.Forms.Panel panel1;
    private System.Windows.Forms.Label materialSignature;
    private AngularPlotControl angularPlotControl1;
    private System.Windows.Forms.GroupBox groupBox3;
    private System.Windows.Forms.Label label6;
    private System.Windows.Forms.NumericUpDown outAngleStep;
    private System.Windows.Forms.Button batch;
    private System.Windows.Forms.Button savePlot;
  }
}

