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
      var materials = new List<string>();
      var process = generateBrdf("--materials " + sceneFileName.Text);
      while (!process.StandardOutput.EndOfStream)
      {
        var line = process.StandardOutput.ReadLine();
        if (line.StartsWith("#"))
          continue;
        materials.Add(line);
      }

      this.materials.Items.Clear();
      this.materials.Items.AddRange(materials.ToArray());
    }

    private void generate_Click(object sender, EventArgs e)
    {
      generateData();
    }

    private void generateData()
    {
      var data = new Dictionary<double, double>();
      var args = sceneFileName.Text + " \"" + materials.Text + "\"";
      var process = generateBrdf(args);
      var reader = process.StandardOutput;
      while (!reader.EndOfStream)
      {
        var line = process.StandardOutput.ReadLine();
        if (line.StartsWith("#") || line.StartsWith("Input:") || line.StartsWith("Loading"))
          continue;

        var split = line.Split('\t');
        double angle, f;
        if (double.TryParse(split[0], NumberStyles.Number, CultureInfo.InvariantCulture, out angle)
            && double.TryParse(split[1], NumberStyles.Number, CultureInfo.InvariantCulture, out f))
          data.Add(angle, f);
      }
      angularPlotControl1.Data = data;
    }

    private void materials_SelectedIndexChanged(object sender, EventArgs e)
    {
      generateData();
    }
  }
}
