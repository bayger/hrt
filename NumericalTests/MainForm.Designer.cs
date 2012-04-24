namespace NumericalTests
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
      this.label1 = new System.Windows.Forms.Label();
      this.numY = new System.Windows.Forms.NumericUpDown();
      this.label2 = new System.Windows.Forms.Label();
      this.label3 = new System.Windows.Forms.Label();
      this.verify = new System.Windows.Forms.Label();
      this.result = new System.Windows.Forms.TextBox();
      this.label5 = new System.Windows.Forms.Label();
      this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
      this.label6 = new System.Windows.Forms.Label();
      this.numSigma0 = new System.Windows.Forms.NumericUpDown();
      this.label7 = new System.Windows.Forms.Label();
      this.numTau = new System.Windows.Forms.NumericUpDown();
      this.verifyZ = new System.Windows.Forms.Label();
      this.groupBox1 = new System.Windows.Forms.GroupBox();
      this.groupBox2 = new System.Windows.Forms.GroupBox();
      this.pictureBox3 = new System.Windows.Forms.PictureBox();
      this.button2 = new System.Windows.Forms.Button();
      this.button1 = new System.Windows.Forms.Button();
      this.textBoxSigma = new System.Windows.Forms.TextBox();
      this.label4 = new System.Windows.Forms.Label();
      this.textBoxK = new System.Windows.Forms.TextBox();
      this.labelK = new System.Windows.Forms.Label();
      this.pictureBox4 = new System.Windows.Forms.PictureBox();
      this.pictureBox2 = new System.Windows.Forms.PictureBox();
      this.pictureBox1 = new System.Windows.Forms.PictureBox();
      this.numThetaI = new System.Windows.Forms.NumericUpDown();
      this.label9 = new System.Windows.Forms.Label();
      this.numThetaK = new System.Windows.Forms.NumericUpDown();
      this.label10 = new System.Windows.Forms.Label();
      this.numZ = new System.Windows.Forms.TextBox();
      this.label8 = new System.Windows.Forms.Label();
      ((System.ComponentModel.ISupportInitialize)(this.numY)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.numSigma0)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.numTau)).BeginInit();
      this.groupBox1.SuspendLayout();
      this.groupBox2.SuspendLayout();
      ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.numThetaI)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.numThetaK)).BeginInit();
      this.SuspendLayout();
      // 
      // label1
      // 
      this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
      this.label1.Location = new System.Drawing.Point(7, 15);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(237, 20);
      this.label1.TabIndex = 0;
      this.label1.Text = "y=x*exp(x)";
      this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
      // 
      // numY
      // 
      this.numY.DecimalPlaces = 8;
      this.numY.Location = new System.Drawing.Point(43, 38);
      this.numY.Maximum = new decimal(new int[] {
            1410065408,
            2,
            0,
            0});
      this.numY.Minimum = new decimal(new int[] {
            1410065408,
            2,
            0,
            -2147483648});
      this.numY.Name = "numY";
      this.numY.Size = new System.Drawing.Size(140, 19);
      this.numY.TabIndex = 1;
      this.numY.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
      this.numY.ValueChanged += new System.EventHandler(this.numY_ValueChanged);
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point(15, 40);
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size(23, 13);
      this.label2.TabIndex = 2;
      this.label2.Text = "y=";
      // 
      // label3
      // 
      this.label3.AutoSize = true;
      this.label3.Location = new System.Drawing.Point(15, 64);
      this.label3.Name = "label3";
      this.label3.Size = new System.Drawing.Size(23, 13);
      this.label3.TabIndex = 4;
      this.label3.Text = "x=";
      // 
      // verify
      // 
      this.verify.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.76923F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
      this.verify.Location = new System.Drawing.Point(14, 87);
      this.verify.Name = "verify";
      this.verify.Size = new System.Drawing.Size(189, 21);
      this.verify.TabIndex = 5;
      this.verify.Text = "0";
      this.verify.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
      // 
      // result
      // 
      this.result.Location = new System.Drawing.Point(43, 64);
      this.result.Name = "result";
      this.result.ReadOnly = true;
      this.result.Size = new System.Drawing.Size(139, 19);
      this.result.TabIndex = 6;
      // 
      // label5
      // 
      this.label5.AutoSize = true;
      this.label5.Location = new System.Drawing.Point(14, 113);
      this.label5.Name = "label5";
      this.label5.Size = new System.Drawing.Size(23, 13);
      this.label5.TabIndex = 8;
      this.label5.Text = "i=";
      // 
      // numericUpDown1
      // 
      this.numericUpDown1.Location = new System.Drawing.Point(42, 111);
      this.numericUpDown1.Minimum = new decimal(new int[] {
            4,
            0,
            0,
            0});
      this.numericUpDown1.Name = "numericUpDown1";
      this.numericUpDown1.ReadOnly = true;
      this.numericUpDown1.Size = new System.Drawing.Size(140, 19);
      this.numericUpDown1.TabIndex = 7;
      this.numericUpDown1.Value = new decimal(new int[] {
            4,
            0,
            0,
            0});
      // 
      // label6
      // 
      this.label6.AutoSize = true;
      this.label6.Location = new System.Drawing.Point(330, 23);
      this.label6.Name = "label6";
      this.label6.Size = new System.Drawing.Size(26, 13);
      this.label6.TabIndex = 11;
      this.label6.Text = "σₒ=";
      // 
      // numSigma0
      // 
      this.numSigma0.DecimalPlaces = 12;
      this.numSigma0.Increment = new decimal(new int[] {
            1,
            0,
            0,
            589824});
      this.numSigma0.Location = new System.Drawing.Point(358, 21);
      this.numSigma0.Maximum = new decimal(new int[] {
            1410065408,
            2,
            0,
            0});
      this.numSigma0.Minimum = new decimal(new int[] {
            1410065408,
            2,
            0,
            -2147483648});
      this.numSigma0.Name = "numSigma0";
      this.numSigma0.Size = new System.Drawing.Size(160, 19);
      this.numSigma0.TabIndex = 10;
      this.numSigma0.Value = new decimal(new int[] {
            18,
            0,
            0,
            589824});
      this.numSigma0.ValueChanged += new System.EventHandler(this.numSigma0_ValueChanged);
      // 
      // label7
      // 
      this.label7.AutoSize = true;
      this.label7.Location = new System.Drawing.Point(330, 50);
      this.label7.Name = "label7";
      this.label7.Size = new System.Drawing.Size(23, 13);
      this.label7.TabIndex = 13;
      this.label7.Text = "τ=";
      // 
      // numTau
      // 
      this.numTau.DecimalPlaces = 12;
      this.numTau.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
      this.numTau.Location = new System.Drawing.Point(358, 48);
      this.numTau.Maximum = new decimal(new int[] {
            1410065408,
            2,
            0,
            0});
      this.numTau.Minimum = new decimal(new int[] {
            1410065408,
            2,
            0,
            -2147483648});
      this.numTau.Name = "numTau";
      this.numTau.Size = new System.Drawing.Size(160, 19);
      this.numTau.TabIndex = 12;
      this.numTau.Value = new decimal(new int[] {
            3,
            0,
            0,
            458752});
      this.numTau.ValueChanged += new System.EventHandler(this.numK_ValueChanged);
      // 
      // verifyZ
      // 
      this.verifyZ.AutoSize = true;
      this.verifyZ.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
      this.verifyZ.Location = new System.Drawing.Point(358, 169);
      this.verifyZ.Name = "verifyZ";
      this.verifyZ.Size = new System.Drawing.Size(15, 13);
      this.verifyZ.TabIndex = 16;
      this.verifyZ.Text = "0";
      // 
      // groupBox1
      // 
      this.groupBox1.Controls.Add(this.label1);
      this.groupBox1.Controls.Add(this.numY);
      this.groupBox1.Controls.Add(this.numericUpDown1);
      this.groupBox1.Controls.Add(this.label5);
      this.groupBox1.Controls.Add(this.label2);
      this.groupBox1.Controls.Add(this.label3);
      this.groupBox1.Controls.Add(this.verify);
      this.groupBox1.Controls.Add(this.result);
      this.groupBox1.Location = new System.Drawing.Point(583, 297);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new System.Drawing.Size(251, 144);
      this.groupBox1.TabIndex = 17;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Basic x*exp(x) solver";
      // 
      // groupBox2
      // 
      this.groupBox2.BackColor = System.Drawing.Color.White;
      this.groupBox2.Controls.Add(this.pictureBox3);
      this.groupBox2.Controls.Add(this.button2);
      this.groupBox2.Controls.Add(this.button1);
      this.groupBox2.Controls.Add(this.textBoxSigma);
      this.groupBox2.Controls.Add(this.label4);
      this.groupBox2.Controls.Add(this.textBoxK);
      this.groupBox2.Controls.Add(this.labelK);
      this.groupBox2.Controls.Add(this.pictureBox4);
      this.groupBox2.Controls.Add(this.pictureBox2);
      this.groupBox2.Controls.Add(this.pictureBox1);
      this.groupBox2.Controls.Add(this.numThetaI);
      this.groupBox2.Controls.Add(this.label9);
      this.groupBox2.Controls.Add(this.numThetaK);
      this.groupBox2.Controls.Add(this.label10);
      this.groupBox2.Controls.Add(this.numSigma0);
      this.groupBox2.Controls.Add(this.verifyZ);
      this.groupBox2.Controls.Add(this.label6);
      this.groupBox2.Controls.Add(this.numZ);
      this.groupBox2.Controls.Add(this.numTau);
      this.groupBox2.Controls.Add(this.label8);
      this.groupBox2.Controls.Add(this.label7);
      this.groupBox2.Location = new System.Drawing.Point(14, 11);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new System.Drawing.Size(818, 270);
      this.groupBox2.TabIndex = 18;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "σ solver";
      // 
      // pictureBox3
      // 
      this.pictureBox3.Image = global::NumericalTests.Properties.Resources.SigmaCalc3;
      this.pictureBox3.Location = new System.Drawing.Point(618, 15);
      this.pictureBox3.Name = "pictureBox3";
      this.pictureBox3.Size = new System.Drawing.Size(84, 71);
      this.pictureBox3.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
      this.pictureBox3.TabIndex = 22;
      this.pictureBox3.TabStop = false;
      // 
      // button2
      // 
      this.button2.Location = new System.Drawing.Point(404, 225);
      this.button2.Name = "button2";
      this.button2.Size = new System.Drawing.Size(159, 29);
      this.button2.TabIndex = 28;
      this.button2.Text = "Generate σ(θr)...";
      this.button2.UseVisualStyleBackColor = true;
      // 
      // button1
      // 
      this.button1.Location = new System.Drawing.Point(569, 225);
      this.button1.Name = "button1";
      this.button1.Size = new System.Drawing.Size(159, 29);
      this.button1.TabIndex = 27;
      this.button1.Text = "Generate σ(θi)...";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new System.EventHandler(this.button1_Click);
      // 
      // textBoxSigma
      // 
      this.textBoxSigma.Font = new System.Drawing.Font("Lucida Console", 8.307693F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
      this.textBoxSigma.Location = new System.Drawing.Point(358, 192);
      this.textBoxSigma.Name = "textBoxSigma";
      this.textBoxSigma.ReadOnly = true;
      this.textBoxSigma.Size = new System.Drawing.Size(160, 19);
      this.textBoxSigma.TabIndex = 26;
      // 
      // label4
      // 
      this.label4.AutoSize = true;
      this.label4.Font = new System.Drawing.Font("Lucida Console", 8.307693F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
      this.label4.Location = new System.Drawing.Point(329, 195);
      this.label4.Name = "label4";
      this.label4.Size = new System.Drawing.Size(25, 13);
      this.label4.TabIndex = 25;
      this.label4.Text = "σ=";
      // 
      // textBoxK
      // 
      this.textBoxK.Location = new System.Drawing.Point(358, 123);
      this.textBoxK.Name = "textBoxK";
      this.textBoxK.ReadOnly = true;
      this.textBoxK.Size = new System.Drawing.Size(160, 19);
      this.textBoxK.TabIndex = 24;
      // 
      // labelK
      // 
      this.labelK.AutoSize = true;
      this.labelK.Location = new System.Drawing.Point(331, 126);
      this.labelK.Name = "labelK";
      this.labelK.Size = new System.Drawing.Size(23, 13);
      this.labelK.TabIndex = 23;
      this.labelK.Text = "K=";
      // 
      // pictureBox4
      // 
      this.pictureBox4.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
      this.pictureBox4.Image = global::NumericalTests.Properties.Resources.Geometrics;
      this.pictureBox4.Location = new System.Drawing.Point(7, 15);
      this.pictureBox4.Name = "pictureBox4";
      this.pictureBox4.Size = new System.Drawing.Size(280, 249);
      this.pictureBox4.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
      this.pictureBox4.TabIndex = 19;
      this.pictureBox4.TabStop = false;
      // 
      // pictureBox2
      // 
      this.pictureBox2.Image = global::NumericalTests.Properties.Resources.SigmaCalc2;
      this.pictureBox2.Location = new System.Drawing.Point(548, 123);
      this.pictureBox2.Name = "pictureBox2";
      this.pictureBox2.Size = new System.Drawing.Size(224, 96);
      this.pictureBox2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
      this.pictureBox2.TabIndex = 21;
      this.pictureBox2.TabStop = false;
      // 
      // pictureBox1
      // 
      this.pictureBox1.Image = global::NumericalTests.Properties.Resources.SigmaCalc1;
      this.pictureBox1.Location = new System.Drawing.Point(576, 74);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new System.Drawing.Size(168, 49);
      this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
      this.pictureBox1.TabIndex = 19;
      this.pictureBox1.TabStop = false;
      // 
      // numThetaI
      // 
      this.numThetaI.DecimalPlaces = 1;
      this.numThetaI.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
      this.numThetaI.Location = new System.Drawing.Point(358, 72);
      this.numThetaI.Maximum = new decimal(new int[] {
            90,
            0,
            0,
            0});
      this.numThetaI.Name = "numThetaI";
      this.numThetaI.Size = new System.Drawing.Size(112, 19);
      this.numThetaI.TabIndex = 17;
      this.numThetaI.Value = new decimal(new int[] {
            30,
            0,
            0,
            0});
      this.numThetaI.ValueChanged += new System.EventHandler(this.numThetaI_ValueChanged);
      // 
      // label9
      // 
      this.label9.AutoSize = true;
      this.label9.Location = new System.Drawing.Point(330, 74);
      this.label9.Name = "label9";
      this.label9.Size = new System.Drawing.Size(31, 13);
      this.label9.TabIndex = 18;
      this.label9.Text = "θi=";
      // 
      // numThetaK
      // 
      this.numThetaK.DecimalPlaces = 1;
      this.numThetaK.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
      this.numThetaK.Location = new System.Drawing.Point(358, 99);
      this.numThetaK.Maximum = new decimal(new int[] {
            90,
            0,
            0,
            0});
      this.numThetaK.Name = "numThetaK";
      this.numThetaK.Size = new System.Drawing.Size(112, 19);
      this.numThetaK.TabIndex = 19;
      this.numThetaK.Value = new decimal(new int[] {
            89,
            0,
            0,
            0});
      this.numThetaK.ValueChanged += new System.EventHandler(this.numThetaK_ValueChanged);
      // 
      // label10
      // 
      this.label10.AutoSize = true;
      this.label10.Location = new System.Drawing.Point(330, 101);
      this.label10.Name = "label10";
      this.label10.Size = new System.Drawing.Size(31, 13);
      this.label10.TabIndex = 20;
      this.label10.Text = "θr=";
      // 
      // numZ
      // 
      this.numZ.Location = new System.Drawing.Point(358, 147);
      this.numZ.Name = "numZ";
      this.numZ.ReadOnly = true;
      this.numZ.Size = new System.Drawing.Size(160, 19);
      this.numZ.TabIndex = 15;
      // 
      // label8
      // 
      this.label8.AutoSize = true;
      this.label8.Location = new System.Drawing.Point(331, 150);
      this.label8.Name = "label8";
      this.label8.Size = new System.Drawing.Size(23, 13);
      this.label8.TabIndex = 14;
      this.label8.Text = "z=";
      // 
      // MainForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.BackColor = System.Drawing.Color.White;
      this.ClientSize = new System.Drawing.Size(846, 453);
      this.Controls.Add(this.groupBox2);
      this.Controls.Add(this.groupBox1);
      this.Font = new System.Drawing.Font("Lucida Console", 8.307693F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
      this.Name = "MainForm";
      this.Text = "HTSG Numerical Tests";
      this.Load += new System.EventHandler(this.Form1_Load);
      ((System.ComponentModel.ISupportInitialize)(this.numY)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.numSigma0)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.numTau)).EndInit();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.numThetaI)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.numThetaK)).EndInit();
      this.ResumeLayout(false);

    }

    #endregion

    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.NumericUpDown numY;
    private System.Windows.Forms.Label label2;
    private System.Windows.Forms.Label label3;
    private System.Windows.Forms.Label verify;
    private System.Windows.Forms.TextBox result;
    private System.Windows.Forms.Label label5;
    private System.Windows.Forms.NumericUpDown numericUpDown1;
    private System.Windows.Forms.Label label6;
    private System.Windows.Forms.NumericUpDown numSigma0;
    private System.Windows.Forms.Label label7;
    private System.Windows.Forms.NumericUpDown numTau;
    private System.Windows.Forms.Label verifyZ;
    private System.Windows.Forms.GroupBox groupBox1;
    private System.Windows.Forms.GroupBox groupBox2;
    private System.Windows.Forms.NumericUpDown numThetaI;
    private System.Windows.Forms.Label label9;
    private System.Windows.Forms.NumericUpDown numThetaK;
    private System.Windows.Forms.Label label10;
    private System.Windows.Forms.PictureBox pictureBox1;
    private System.Windows.Forms.PictureBox pictureBox2;
    private System.Windows.Forms.PictureBox pictureBox3;
    private System.Windows.Forms.PictureBox pictureBox4;
    private System.Windows.Forms.TextBox textBoxK;
    private System.Windows.Forms.Label labelK;
    private System.Windows.Forms.TextBox numZ;
    private System.Windows.Forms.Label label8;
    private System.Windows.Forms.TextBox textBoxSigma;
    private System.Windows.Forms.Label label4;
    private System.Windows.Forms.Button button2;
    private System.Windows.Forms.Button button1;
  }
}

