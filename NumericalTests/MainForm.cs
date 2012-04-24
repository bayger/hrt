using System;
using System.Windows.Forms;
using MicrosoftResearch.Infer.Maths;

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
      const int iterations = 50000;
      var x = y < 500 ? 1.0 : 100.0;
      int i = 0;
      var err = 0.0;
      do
      {
        var new_x = x - (x * Math.Exp(x) - y) / ((x + 1) * Math.Exp(x));
        if (double.IsNaN(new_x))
          x = 0;
        x = new_x;
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

    private void Form1_Load(object sender, EventArgs e)
    {
      updateX();
      updateZ();
    }

    private void numSigma0_ValueChanged(object sender, EventArgs e)
    {
      updateZ();
    }

    private void updateZ()
    {
      var sigma0 = (double)numSigma0.Value;
      var thetaI = (double) numThetaI.Value / 180 * Math.PI;
      var thetaK = (double)numThetaK.Value / 180 * Math.PI;
      var tau = (double) numTau.Value;

      var Ki = Math.Tan(thetaI)*MMath.Erfc(tau/(2*sigma0)/Math.Tan(thetaI));
      var Kr = Math.Tan(thetaK)*MMath.Erfc(tau/(2*sigma0)/Math.Tan(thetaK));
      var K = (Ki + Kr)/4;
      
      var y = 2*K*K/Math.PI;
      var x = solve_xexpx(y);
      var zz = x*sigma0*sigma0;
      var z1 = -Math.Sqrt(zz);
      var z2 = Math.Sqrt(zz);

      numZ.Text = Math.Abs(z1).ToString();

      var left1 = Math.Sqrt(Math.PI/2)*z1;
      var left2 = Math.Sqrt(Math.PI/2)*z2;
      var right = sigma0*K/Math.Sqrt(Math.Exp(zz/(sigma0*sigma0)));

      var d1 = Math.Abs(left1 - right);
      var d2 = Math.Abs(left2 - right);
      var d = d1 < d2 ? d1 : d2;

      verifyZ.Text = string.Format("±{0:p8}", Math.Abs(d / right));
      textBoxK.Text = K.ToString();

      var sigma = sigma0/Math.Sqrt(1 + x);
      textBoxSigma.Text = sigma.ToString("0.000000000000");
    }

    private void numK_ValueChanged(object sender, EventArgs e)
    {
      updateZ();
    }

    private void numThetaI_ValueChanged(object sender, EventArgs e)
    {
      updateZ();
    }

    private void numThetaK_ValueChanged(object sender, EventArgs e)
    {
      updateZ();
    }

    private void button1_Click(object sender, EventArgs e)
    {

    }
  }
}
