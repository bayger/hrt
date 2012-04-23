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
      this.numThetaI = new System.Windows.Forms.NumericUpDown();
      this.label9 = new System.Windows.Forms.Label();
      this.numThetaK = new System.Windows.Forms.NumericUpDown();
      this.label10 = new System.Windows.Forms.Label();
      this.pictureBox4 = new System.Windows.Forms.PictureBox();
      this.pictureBox3 = new System.Windows.Forms.PictureBox();
      this.pictureBox2 = new System.Windows.Forms.PictureBox();
      this.pictureBox1 = new System.Windows.Forms.PictureBox();
      this.label8 = new System.Windows.Forms.Label();
      this.numZ = new System.Windows.Forms.TextBox();
      this.textBoxK = new System.Windows.Forms.TextBox();
      this.labelK = new System.Windows.Forms.Label();
      this.textBoxSigma = new System.Windows.Forms.TextBox();
      this.label4 = new System.Windows.Forms.Label();
      ((System.ComponentModel.ISupportInitialize)(this.numY)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.numSigma0)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.numTau)).BeginInit();
      this.groupBox1.SuspendLayout();
      this.groupBox2.SuspendLayout();
      ((System.ComponentModel.ISupportInitialize)(this.numThetaI)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.numThetaK)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
      this.SuspendLayout();
      // 
      // label1
      // 
      this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
      this.label1.Location = new System.Drawing.Point(6, 16);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(203, 22);
      this.label1.TabIndex = 0;
      this.label1.Text = "y=x*exp(x)";
      this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
      // 
      // numY
      // 
      this.numY.DecimalPlaces = 8;
      this.numY.Location = new System.Drawing.Point(37, 68);
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
      this.numY.Size = new System.Drawing.Size(120, 20);
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
      this.label2.Location = new System.Drawing.Point(13, 70);
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size(18, 13);
      this.label2.TabIndex = 2;
      this.label2.Text = "y=";
      // 
      // label3
      // 
      this.label3.AutoSize = true;
      this.label3.Location = new System.Drawing.Point(13, 96);
      this.label3.Name = "label3";
      this.label3.Size = new System.Drawing.Size(18, 13);
      this.label3.TabIndex = 4;
      this.label3.Text = "x=";
      // 
      // verify
      // 
      this.verify.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.76923F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
      this.verify.Location = new System.Drawing.Point(12, 121);
      this.verify.Name = "verify";
      this.verify.Size = new System.Drawing.Size(162, 23);
      this.verify.TabIndex = 5;
      this.verify.Text = "0";
      this.verify.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
      // 
      // result
      // 
      this.result.Location = new System.Drawing.Point(37, 96);
      this.result.Name = "result";
      this.result.ReadOnly = true;
      this.result.Size = new System.Drawing.Size(120, 20);
      this.result.TabIndex = 6;
      // 
      // label5
      // 
      this.label5.AutoSize = true;
      this.label5.Location = new System.Drawing.Point(12, 422);
      this.label5.Name = "label5";
      this.label5.Size = new System.Drawing.Size(15, 13);
      this.label5.TabIndex = 8;
      this.label5.Text = "i=";
      // 
      // numericUpDown1
      // 
      this.numericUpDown1.Location = new System.Drawing.Point(36, 420);
      this.numericUpDown1.Minimum = new decimal(new int[] {
            4,
            0,
            0,
            0});
      this.numericUpDown1.Name = "numericUpDown1";
      this.numericUpDown1.ReadOnly = true;
      this.numericUpDown1.Size = new System.Drawing.Size(120, 20);
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
      this.label6.Location = new System.Drawing.Point(283, 25);
      this.label6.Name = "label6";
      this.label6.Size = new System.Drawing.Size(24, 13);
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
      this.numSigma0.Location = new System.Drawing.Point(307, 23);
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
      this.numSigma0.Size = new System.Drawing.Size(120, 20);
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
      this.label7.Location = new System.Drawing.Point(283, 54);
      this.label7.Name = "label7";
      this.label7.Size = new System.Drawing.Size(19, 13);
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
      this.numTau.Location = new System.Drawing.Point(307, 52);
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
      this.numTau.Size = new System.Drawing.Size(120, 20);
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
      this.verifyZ.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.692307F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
      this.verifyZ.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
      this.verifyZ.Location = new System.Drawing.Point(283, 182);
      this.verifyZ.Name = "verifyZ";
      this.verifyZ.Size = new System.Drawing.Size(182, 23);
      this.verifyZ.TabIndex = 16;
      this.verifyZ.Text = "0";
      this.verifyZ.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
      // 
      // groupBox1
      // 
      this.groupBox1.Controls.Add(this.label1);
      this.groupBox1.Controls.Add(this.numY);
      this.groupBox1.Controls.Add(this.label2);
      this.groupBox1.Controls.Add(this.label3);
      this.groupBox1.Controls.Add(this.verify);
      this.groupBox1.Controls.Add(this.result);
      this.groupBox1.Location = new System.Drawing.Point(12, 254);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new System.Drawing.Size(215, 156);
      this.groupBox1.TabIndex = 17;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Basic x*exp(x) solver";
      // 
      // groupBox2
      // 
      this.groupBox2.BackColor = System.Drawing.Color.White;
      this.groupBox2.Controls.Add(this.textBoxSigma);
      this.groupBox2.Controls.Add(this.label4);
      this.groupBox2.Controls.Add(this.textBoxK);
      this.groupBox2.Controls.Add(this.labelK);
      this.groupBox2.Controls.Add(this.pictureBox4);
      this.groupBox2.Controls.Add(this.pictureBox3);
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
      this.groupBox2.Location = new System.Drawing.Point(12, 12);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new System.Drawing.Size(701, 236);
      this.groupBox2.TabIndex = 18;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Effective surface roughness solver";
      // 
      // numThetaI
      // 
      this.numThetaI.DecimalPlaces = 1;
      this.numThetaI.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
      this.numThetaI.Location = new System.Drawing.Point(307, 78);
      this.numThetaI.Maximum = new decimal(new int[] {
            90,
            0,
            0,
            0});
      this.numThetaI.Name = "numThetaI";
      this.numThetaI.Size = new System.Drawing.Size(96, 20);
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
      this.label9.Location = new System.Drawing.Point(283, 80);
      this.label9.Name = "label9";
      this.label9.Size = new System.Drawing.Size(21, 13);
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
      this.numThetaK.Location = new System.Drawing.Point(307, 107);
      this.numThetaK.Maximum = new decimal(new int[] {
            90,
            0,
            0,
            0});
      this.numThetaK.Name = "numThetaK";
      this.numThetaK.Size = new System.Drawing.Size(96, 20);
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
      this.label10.Location = new System.Drawing.Point(283, 109);
      this.label10.Name = "label10";
      this.label10.Size = new System.Drawing.Size(22, 13);
      this.label10.TabIndex = 20;
      this.label10.Text = "θr=";
      // 
      // pictureBox4
      // 
      this.pictureBox4.Image = global::NumericalTests.Properties.Resources.Geometrics;
      this.pictureBox4.Location = new System.Drawing.Point(6, 16);
      this.pictureBox4.Name = "pictureBox4";
      this.pictureBox4.Size = new System.Drawing.Size(252, 214);
      this.pictureBox4.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
      this.pictureBox4.TabIndex = 19;
      this.pictureBox4.TabStop = false;
      // 
      // pictureBox3
      // 
      this.pictureBox3.Image = global::NumericalTests.Properties.Resources.SigmaCalc3;
      this.pictureBox3.Location = new System.Drawing.Point(471, 155);
      this.pictureBox3.Name = "pictureBox3";
      this.pictureBox3.Size = new System.Drawing.Size(84, 71);
      this.pictureBox3.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
      this.pictureBox3.TabIndex = 22;
      this.pictureBox3.TabStop = false;
      // 
      // pictureBox2
      // 
      this.pictureBox2.Image = global::NumericalTests.Properties.Resources.SigmaCalc2;
      this.pictureBox2.Location = new System.Drawing.Point(460, 60);
      this.pictureBox2.Name = "pictureBox2";
      this.pictureBox2.Size = new System.Drawing.Size(224, 96);
      this.pictureBox2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
      this.pictureBox2.TabIndex = 21;
      this.pictureBox2.TabStop = false;
      // 
      // pictureBox1
      // 
      this.pictureBox1.Image = global::NumericalTests.Properties.Resources.SigmaCalc1;
      this.pictureBox1.Location = new System.Drawing.Point(460, 16);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new System.Drawing.Size(168, 49);
      this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
      this.pictureBox1.TabIndex = 19;
      this.pictureBox1.TabStop = false;
      // 
      // label8
      // 
      this.label8.AutoSize = true;
      this.label8.Location = new System.Drawing.Point(284, 162);
      this.label8.Name = "label8";
      this.label8.Size = new System.Drawing.Size(18, 13);
      this.label8.TabIndex = 14;
      this.label8.Text = "z=";
      // 
      // numZ
      // 
      this.numZ.Location = new System.Drawing.Point(307, 159);
      this.numZ.Name = "numZ";
      this.numZ.ReadOnly = true;
      this.numZ.Size = new System.Drawing.Size(120, 20);
      this.numZ.TabIndex = 15;
      // 
      // textBoxK
      // 
      this.textBoxK.Location = new System.Drawing.Point(307, 133);
      this.textBoxK.Name = "textBoxK";
      this.textBoxK.ReadOnly = true;
      this.textBoxK.Size = new System.Drawing.Size(120, 20);
      this.textBoxK.TabIndex = 24;
      // 
      // labelK
      // 
      this.labelK.AutoSize = true;
      this.labelK.Location = new System.Drawing.Point(284, 136);
      this.labelK.Name = "labelK";
      this.labelK.Size = new System.Drawing.Size(20, 13);
      this.labelK.TabIndex = 23;
      this.labelK.Text = "K=";
      // 
      // textBoxSigma
      // 
      this.textBoxSigma.Location = new System.Drawing.Point(307, 206);
      this.textBoxSigma.Name = "textBoxSigma";
      this.textBoxSigma.ReadOnly = true;
      this.textBoxSigma.Size = new System.Drawing.Size(120, 20);
      this.textBoxSigma.TabIndex = 26;
      // 
      // label4
      // 
      this.label4.AutoSize = true;
      this.label4.Location = new System.Drawing.Point(284, 209);
      this.label4.Name = "label4";
      this.label4.Size = new System.Drawing.Size(20, 13);
      this.label4.TabIndex = 25;
      this.label4.Text = "σ=";
      // 
      // MainForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.BackColor = System.Drawing.Color.White;
      this.ClientSize = new System.Drawing.Size(725, 451);
      this.Controls.Add(this.groupBox2);
      this.Controls.Add(this.groupBox1);
      this.Controls.Add(this.numericUpDown1);
      this.Controls.Add(this.label5);
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
      ((System.ComponentModel.ISupportInitialize)(this.numThetaI)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.numThetaK)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.pictureBox4)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();

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
  }
}

