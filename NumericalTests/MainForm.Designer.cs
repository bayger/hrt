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
      this.label4 = new System.Windows.Forms.Label();
      this.label6 = new System.Windows.Forms.Label();
      this.numSigma0 = new System.Windows.Forms.NumericUpDown();
      this.label7 = new System.Windows.Forms.Label();
      this.numK = new System.Windows.Forms.NumericUpDown();
      this.numZ = new System.Windows.Forms.TextBox();
      this.label8 = new System.Windows.Forms.Label();
      this.verifyZ = new System.Windows.Forms.Label();
      ((System.ComponentModel.ISupportInitialize)(this.numY)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.numSigma0)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.numK)).BeginInit();
      this.SuspendLayout();
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
      this.label1.Location = new System.Drawing.Point(39, 9);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(96, 22);
      this.label1.TabIndex = 0;
      this.label1.Text = "y=x*exp(x)";
      // 
      // numY
      // 
      this.numY.DecimalPlaces = 8;
      this.numY.Location = new System.Drawing.Point(43, 51);
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
      this.label2.Location = new System.Drawing.Point(19, 53);
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size(18, 13);
      this.label2.TabIndex = 2;
      this.label2.Text = "y=";
      // 
      // label3
      // 
      this.label3.AutoSize = true;
      this.label3.Location = new System.Drawing.Point(19, 79);
      this.label3.Name = "label3";
      this.label3.Size = new System.Drawing.Size(18, 13);
      this.label3.TabIndex = 4;
      this.label3.Text = "x=";
      // 
      // verify
      // 
      this.verify.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.76923F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
      this.verify.Location = new System.Drawing.Point(12, 145);
      this.verify.Name = "verify";
      this.verify.Size = new System.Drawing.Size(162, 23);
      this.verify.TabIndex = 5;
      this.verify.Text = "0";
      this.verify.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
      // 
      // result
      // 
      this.result.Location = new System.Drawing.Point(43, 79);
      this.result.Name = "result";
      this.result.ReadOnly = true;
      this.result.Size = new System.Drawing.Size(120, 20);
      this.result.TabIndex = 6;
      // 
      // label5
      // 
      this.label5.AutoSize = true;
      this.label5.Location = new System.Drawing.Point(19, 107);
      this.label5.Name = "label5";
      this.label5.Size = new System.Drawing.Size(15, 13);
      this.label5.TabIndex = 8;
      this.label5.Text = "i=";
      // 
      // numericUpDown1
      // 
      this.numericUpDown1.Location = new System.Drawing.Point(43, 105);
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
      this.numericUpDown1.ValueChanged += new System.EventHandler(this.numericUpDown1_ValueChanged);
      // 
      // label4
      // 
      this.label4.AutoSize = true;
      this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
      this.label4.Location = new System.Drawing.Point(206, 9);
      this.label4.Name = "label4";
      this.label4.Size = new System.Drawing.Size(278, 22);
      this.label4.TabIndex = 9;
      this.label4.Text = "sqrt(PI/2)z = σₒ*K*exp(-z^2/2σₒ^2)";
      // 
      // label6
      // 
      this.label6.AutoSize = true;
      this.label6.Location = new System.Drawing.Point(209, 53);
      this.label6.Name = "label6";
      this.label6.Size = new System.Drawing.Size(24, 13);
      this.label6.TabIndex = 11;
      this.label6.Text = "σₒ=";
      this.label6.Click += new System.EventHandler(this.label6_Click);
      // 
      // numSigma0
      // 
      this.numSigma0.DecimalPlaces = 12;
      this.numSigma0.Increment = new decimal(new int[] {
            1,
            0,
            0,
            589824});
      this.numSigma0.Location = new System.Drawing.Point(233, 51);
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
      this.label7.Location = new System.Drawing.Point(209, 82);
      this.label7.Name = "label7";
      this.label7.Size = new System.Drawing.Size(20, 13);
      this.label7.TabIndex = 13;
      this.label7.Text = "K=";
      // 
      // numK
      // 
      this.numK.DecimalPlaces = 12;
      this.numK.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
      this.numK.Location = new System.Drawing.Point(233, 80);
      this.numK.Maximum = new decimal(new int[] {
            1410065408,
            2,
            0,
            0});
      this.numK.Minimum = new decimal(new int[] {
            1410065408,
            2,
            0,
            -2147483648});
      this.numK.Name = "numK";
      this.numK.Size = new System.Drawing.Size(120, 20);
      this.numK.TabIndex = 12;
      this.numK.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
      this.numK.ValueChanged += new System.EventHandler(this.numK_ValueChanged);
      // 
      // numZ
      // 
      this.numZ.Location = new System.Drawing.Point(233, 104);
      this.numZ.Name = "numZ";
      this.numZ.ReadOnly = true;
      this.numZ.Size = new System.Drawing.Size(120, 20);
      this.numZ.TabIndex = 15;
      // 
      // label8
      // 
      this.label8.AutoSize = true;
      this.label8.Location = new System.Drawing.Point(209, 104);
      this.label8.Name = "label8";
      this.label8.Size = new System.Drawing.Size(18, 13);
      this.label8.TabIndex = 14;
      this.label8.Text = "z=";
      // 
      // verifyZ
      // 
      this.verifyZ.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.76923F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
      this.verifyZ.Location = new System.Drawing.Point(208, 145);
      this.verifyZ.Name = "verifyZ";
      this.verifyZ.Size = new System.Drawing.Size(276, 23);
      this.verifyZ.TabIndex = 16;
      this.verifyZ.Text = "0";
      this.verifyZ.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
      // 
      // MainForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(600, 190);
      this.Controls.Add(this.verifyZ);
      this.Controls.Add(this.numZ);
      this.Controls.Add(this.label8);
      this.Controls.Add(this.label7);
      this.Controls.Add(this.numK);
      this.Controls.Add(this.label6);
      this.Controls.Add(this.numSigma0);
      this.Controls.Add(this.label4);
      this.Controls.Add(this.label5);
      this.Controls.Add(this.numericUpDown1);
      this.Controls.Add(this.result);
      this.Controls.Add(this.verify);
      this.Controls.Add(this.label3);
      this.Controls.Add(this.label2);
      this.Controls.Add(this.numY);
      this.Controls.Add(this.label1);
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
      this.Name = "MainForm";
      this.Text = "EqSolv";
      this.Load += new System.EventHandler(this.Form1_Load);
      ((System.ComponentModel.ISupportInitialize)(this.numY)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.numSigma0)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.numK)).EndInit();
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
    private System.Windows.Forms.Label label4;
    private System.Windows.Forms.Label label6;
    private System.Windows.Forms.NumericUpDown numSigma0;
    private System.Windows.Forms.Label label7;
    private System.Windows.Forms.NumericUpDown numK;
    private System.Windows.Forms.TextBox numZ;
    private System.Windows.Forms.Label label8;
    private System.Windows.Forms.Label verifyZ;
  }
}

