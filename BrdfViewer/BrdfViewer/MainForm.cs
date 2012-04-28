using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.Windows.Forms;
using System.IO;
using System.Text;

namespace BrdfViewer
{
  public partial class MainForm : Form
  {
    public MainForm()
    {
      InitializeComponent();
    }

    private void browseSceneFile_Click(object sender, EventArgs e)
    {
      var openFileDialog = new OpenFileDialog();
      openFileDialog.Filter = "Scene files (*.ysf)|*.ysf|All files|*.*";
      if (openFileDialog.ShowDialog(this) == DialogResult.OK)
      {
        sceneFileName.Text = openFileDialog.FileName;
      }
    }

    private Process generateBrdf(string args)
    {
      var psi = new ProcessStartInfo
                  {
                    FileName = "brdfgen.exe",
                    Arguments = args,
                    RedirectStandardOutput = true,
                    CreateNoWindow = true,
                    UseShellExecute = false
                  };
      return Process.Start(psi);
    }

    private void getMaterials_Click(object sender, EventArgs e)
    {
      materialsSource.Clear();
      var process = generateBrdf("--materials " + sceneFileName.Text);
      while (!process.StandardOutput.EndOfStream)
      {
        var line = process.StandardOutput.ReadLine();
        if (line.StartsWith("#"))
          continue;

        var split = line.Split('\t');
        if (split.Length == 2)
          materialsSource.Add(new MaterialItem() {Name = split[0], Signature = split[1]});
      }
    }

    private void generate_Click(object sender, EventArgs e)
    {
      generateData();
    }

    private void generateData()
    {
      var data = new Dictionary<double, List<double>>();
      var args = sceneFileName.Text + " \"" + materials.Text + "\" -i "+incidentAngle.Value.ToString(CultureInfo.InvariantCulture);
      var process = generateBrdf(args);
      var reader = process.StandardOutput;
      while (!reader.EndOfStream)
      {
        var line = process.StandardOutput.ReadLine();
        if (line.StartsWith("#") || line.StartsWith("Input:") || line.StartsWith("Loading"))
          continue;

        var split = line.Split('\t');
        double angle, f;
        var angleParsed = double.TryParse(split[0], NumberStyles.Number, CultureInfo.InvariantCulture, out angle);

        if (angleParsed)
        {
          var cells = new List<double>();
          for (int i = 1; i < split.Length; i++)
          {
            if (double.TryParse(split[i], NumberStyles.Number, CultureInfo.InvariantCulture, out f))
              cells.Add(f);
            else
              cells.Add(0);
          }
          data.Add(angle, cells);
        }
      }
      angularPlotControl1.Data = data;
      var item = materials.SelectedItem as MaterialItem;
      angularPlotControl1.ChartTitle = item != null ? item.Signature : string.Empty;
    }

    private void materials_SelectedIndexChanged(object sender, EventArgs e)
    {
      generateData();
    }

    private void savePlot_Click(object sender, EventArgs e)
    {
      angularPlotControl1.SaveToWmf("plot.wmf");
    }
  }
}
