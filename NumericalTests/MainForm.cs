using System;
using System.Windows.Forms;

namespace NumericalTests
{
  public partial class MainForm : Form
  {
    public MainForm()
    {
      InitializeComponent();
    }

    static double solve_xexpx2(double y, int iterations)
		{
			var x=(y>1)?Math.Sqrt(Math.Log(y)):y;
			int i;
			if (y > 3.0)
				for (i=0;i<iterations;i++)
					x=Math.Sqrt(Math.Log(y/x));
			else
				for (i=0;i<iterations;i++)
					x=0.5*(x+y*Math.Exp(-(x*x)));
			return x;
		}

    double solve_xexpx(double y)
    {
      const int iterations = 10000;
      var x = 1.0;
      int i = 0;
      var err = 0.0;
      do
      {
        x = x - (x * Math.Exp(x) - y) / ((x + 1) * Math.Exp(x));
        err = (x*Math.Exp(x) - y)/y;
        i++;
      } while (err > 0.001 && i < iterations);

      numericUpDown1.Maximum = i;
      numericUpDown1.Value = i;

      return x;
    }

    private void updateX()
    {
      var y = (double) numY.Value;
      var result = solve_xexpx(y);
      this.result.Text = result.ToString("0.00000000");

      var verification = Math.Abs(y - result * Math.Exp(result)) / y;
      verify.Text = verification.ToString("p8");      
    }

    private void numY_ValueChanged(object sender, EventArgs e)
    {
      updateX();
    }

    private void numericUpDown1_ValueChanged(object sender, EventArgs e)
    {
      updateX();
    }

    private void Form1_Load(object sender, EventArgs e)
    {
      updateX();
      updateZ();
    }

    private void label6_Click(object sender, EventArgs e)
    {

    }

    private void numSigma0_ValueChanged(object sender, EventArgs e)
    {
      updateZ();
    }

    private void updateZ()
    {
      var sigma0 = (double)numSigma0.Value;
      var K = (double) numK.Value;
      
      var y = 2*K*K/Math.PI;
      var x = solve_xexpx(y);
      var zz = x*sigma0*sigma0;
      var z = Math.Sqrt(zz);

      numZ.Text = z.ToString();

      var left = Math.Sqrt(Math.PI/2)*z;
      var right = sigma0*K/Math.Sqrt(Math.Exp(zz/(sigma0*sigma0)));
      verifyZ.Text = string.Format("err = {0:p8}", Math.Abs((left - right)/left));
    }

    private void numK_ValueChanged(object sender, EventArgs e)
    {
      updateZ();
    }
  }
}
