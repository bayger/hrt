using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Windows.Forms;

namespace HrtQueue
{
  public partial class MainForm : Form
  {
    private ObservableCollection<JobItem> _jobs = new ObservableCollection<JobItem>();

    public MainForm()
    {
      InitializeComponent();
    }

    private void addJobButton_Click(object sender, EventArgs e)
    {
      var openFileDialog = new OpenFileDialog();
      openFileDialog.Filter = "Scene files (*.ysf)|*.ysf|All files|*.*";
      if (openFileDialog.ShowDialog(this) == DialogResult.OK)
      {
        var job = new JobItem
                    {
                      Status = JobStatus.Queued,
                      MaxRayDepth = 12,
                      RaysPerPixel = 16,
                      SceneFilename = openFileDialog.FileName
                    };
        jobItems.Add(job);
      }
    }
  }
}
