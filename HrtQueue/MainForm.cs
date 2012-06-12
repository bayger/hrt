using System;
using System.Linq;
using System.Windows.Forms;

namespace HrtQueue
{
  public partial class MainForm : Form
  {
    private bool _isRunning;
    private bool IsRunning
    {
      get { return _isRunning; }
      set
      {
        _isRunning = value;
        statusLabel.Text = _isRunning ? "Processing queue..." : "Idle.";
        startButton.Enabled = !_isRunning;
        stopButton.Enabled = _isRunning;
      }
    }

    private JobRunner _currentJob;

    public MainForm()
    {
      InitializeComponent();
      IsRunning = false;
      threadsNum.Value = Environment.ProcessorCount;
    }

    private void addJobButton_Click(object sender, EventArgs e)
    {
      var openFileDialog = new OpenFileDialog();
      openFileDialog.Filter = "Scene files (*.ysf)|*.ysf|All files|*.*";
      openFileDialog.Multiselect = true;
      if (openFileDialog.ShowDialog(this) == DialogResult.OK)
      {
        foreach (var file in openFileDialog.FileNames)
        {
          var job = new JobItem
                      {
                        Status = JobStatus.Queued,
                        MaxRayDepth = 12,
                        RaysPerPixel = 64,
                        SceneFilename = file,
                        SigmaFilter = 5.0f,
                        VarianceFilter = 3.0f,
                        MaxPasses = 16
                      };
          jobItems.Add(job);
        }
      }
    }

    private void removeJobsButton_Click(object sender, EventArgs e)
    {
      MultiChange(item => jobItems.Remove(item));
    }

    private void MultiChange(Action<JobItem> changer)
    {
      foreach (var job in jobsGrid.SelectedRows.Cast<DataGridViewRow>())
      {
        var item = job.DataBoundItem as JobItem;
        if (item != null && item.Status != JobStatus.InProgress)
        {
          changer(item);
        }
      }
    }

    private void startButton_Click(object sender, EventArgs e)
    {
      if (IsRunning)
        return;

      IsRunning = true;
      TriggerNextQueuedItem();
    }

    private void TriggerNextQueuedItem()
    {
      if (!IsRunning)
        return;

      var queuedItem = GetFirstQueuedItem();
      if (queuedItem != null)
      {
        _currentJob = new JobRunner(queuedItem, () => TriggerNextQueuedItem(), jobsGrid, (int)threadsNum.Value);
        _currentJob.Run();
      }
      else
        IsRunning = false;
    }

    private JobItem GetFirstQueuedItem()
    {
      for(int i=0; i<jobItems.Count; i++)
      {
        var item = jobItems[i] as JobItem;
        if (item != null && item.Status == JobStatus.Queued)
          return item;
      }

      return null;
    }

    private float GetCurrentJobProgress()
    {
      for (int i = 0; i < jobItems.Count; i++)
      {
        var item = jobItems[i] as JobItem;
        if (item != null && item.Status == JobStatus.InProgress)
          return item.PercentComplete;
      }

      return 0;
    }

    private int CountDoneJobs()
    {
      var count = 0;
      for (int i = 0; i < jobItems.Count; i++)
      {
        var item = jobItems[i] as JobItem;
        if (item != null && item.Status == JobStatus.Done)
          count++;
      }

      return count;
    }

    private bool AskForCancelation()
    {
      var answer = MessageBox.Show(this, "Are you sure to abort current rendering?", "Question",
                     MessageBoxButtons.YesNo, MessageBoxIcon.Question);
      return (answer == DialogResult.Yes);
    }

    private void stopButton_Click(object sender, EventArgs e)
    {
      if (!IsRunning)
        return;

      if (!AskForCancelation())
        return;

      if (_currentJob != null)
        _currentJob.Abort();

      IsRunning = false;
    }

    private void MainForm_Load(object sender, EventArgs e)
    {
      for (int i = 2; i <= 100; i++)
        rppCombo.Items.Add(i*i);
      rppCombo.Text = "16";

      for (int i = 1; i <= 20; i++)
        rayDepthCombo.Items.Add(i);
      rayDepthCombo.Text = "12";
    }

    private void selectAllButton_Click(object sender, EventArgs e)
    {
      jobsGrid.SelectAll();
    }

    private void setRppButton_Click(object sender, EventArgs e)
    {
      var rpp = int.Parse(rppCombo.Text);
      MultiChange(item => item.RaysPerPixel = rpp);
    }

    private void setRayDepthButton_Click(object sender, EventArgs e)
    {
      var depth = int.Parse(rayDepthCombo.Text);
      MultiChange(item => item.MaxRayDepth = depth);
    }

    private void resetButton_Click(object sender, EventArgs e)
    {
      MultiChange(item => item.Status = JobStatus.Queued);
    }

    private void jobItems_ListChanged(object sender, System.ComponentModel.ListChangedEventArgs e)
    {
      progressBar.Maximum = jobItems.Count*100;
      progressBar.Value = CountDoneJobs()*100 + (int)GetCurrentJobProgress();
    }

    private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
    {
      if (IsRunning && !AskForCancelation())
      {
        e.Cancel = true;
      }

      if (_currentJob != null)
        _currentJob.Abort();
    }
  }
}
