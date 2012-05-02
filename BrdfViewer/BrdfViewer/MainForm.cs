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
      var args = sceneFileName.Text + " \"" + materials.Text 
        + "\" -i "+incidentAngle.Value.ToString(CultureInfo.InvariantCulture) 
        + " -s "+angleStep.Value.ToString(CultureInfo.InvariantCulture);
      var selectedMaterial = materials.SelectedItem as MaterialItem;
      materialSignature.Text = selectedMaterial != null ? selectedMaterial.Signature : string.Empty;
      var process = generateBrdf(args);
      var reader = process.StandardOutput;
      var readHeader = false;
      while (!reader.EndOfStream)
      {
        var line = process.StandardOutput.ReadLine();
        if (line.StartsWith("#") || line.StartsWith("Input:") || line.StartsWith("Loading"))
          continue;

        if (!readHeader)
        {
          readHeader = true;
          continue;
        }

        var split = line.Split('\t');
        double thetaR, thetaI, f;
        var parsedR = double.TryParse(split[1], NumberStyles.Number, CultureInfo.InvariantCulture, out thetaR);
        var parsedI = double.TryParse(split[0], NumberStyles.Number, CultureInfo.InvariantCulture, out thetaI);

        if (parsedR && parsedI)
        {
          var cells = new List<double>();
          for (int i = 2; i < split.Length; i++)
          {
            if (double.TryParse(split[i], NumberStyles.Number, CultureInfo.InvariantCulture, out f))
              cells.Add(f);
            else
              cells.Add(0);
          }
          data.Add(thetaR, cells);
        }
      }
      angularPlotControl1.Data = data;
      angularPlotControl1.IncidentAngle = (double) incidentAngle.Value;
      var item = materials.SelectedItem as MaterialItem;
      angularPlotControl1.ChartTitle = item != null ? item.Signature : string.Empty;
    }

    private void materials_SelectedIndexChanged(object sender, EventArgs e)
    {
      generateData();
    }

    private void savePlot_Click(object sender, EventArgs e)
    {
      var item = materials.SelectedItem as MaterialItem;
      if (item != null)
      {
        angularPlotControl1.SaveToWmf(item.Name + ",angle=" + incidentAngle.Value.ToString(CultureInfo.InvariantCulture) +
                                      ".wmf");
      }
    }

    private void timer_Tick(object sender, EventArgs e)
    {
      timer.Stop();
      generateData();
    }

    private void incidentAngle_ValueChanged(object sender, EventArgs e)
    {
      timer.Stop();
      timer.Start();
    }

    private void angleStep_ValueChanged(object sender, EventArgs e)
    {
      timer.Stop();
      timer.Start();
    }
  }
}
