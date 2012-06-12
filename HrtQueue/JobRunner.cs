using System;
using System.Diagnostics;
using System.Globalization;
using System.Threading;
using System.Windows.Forms;

namespace HrtQueue
{
  public class JobRunner
  {
    private readonly JobItem _job;
    private readonly Action _completeHandler;
    private readonly Control _hostControl;
    private readonly int _threads;
    private Thread _thread;
    private Process _process;

    public JobRunner(JobItem job, Action completeHandler, Control hostControl, int threads)
    {
      if (job == null) throw new ArgumentNullException("job");
      if (completeHandler == null) throw new ArgumentNullException("completeHandler");
      if (hostControl == null) throw new ArgumentNullException("hostControl");

      _job = job;
      _completeHandler = completeHandler;
      _hostControl = hostControl;
      _threads = threads;
    }

    private string CreateArgs()
    {
      return " -r " + _job.RaysPerPixel.ToString(CultureInfo.InvariantCulture)
             + " -d " + _job.MaxRayDepth.ToString(CultureInfo.InvariantCulture)
             + " -t " + _threads.ToString(CultureInfo.InvariantCulture)
             + (_job.SigmaFilter > 0 ? " --sigma-filter " + _job.SigmaFilter.ToString(CultureInfo.InvariantCulture) : "")
             + (_job.VarianceFilter > 0 ? " --variance-filter " + _job.VarianceFilter.ToString(CultureInfo.InvariantCulture) + " --variance-max-passes " + _job.MaxPasses.ToString(CultureInfo.InvariantCulture) : "")
             + " \"" + _job.SceneFilename + "\""
             + (!string.IsNullOrEmpty(_job.OutputFilename) ? " \"" + _job.OutputFilename + "\"" : "")
             + " --percentage";
    }

    public void Run()
    {
      _thread = new Thread(ThreadProc);
      _thread.Start();
    }

    public void Abort()
    {
      if (_process != null)
      {
        _process.Kill();
        _process = null;
      }
    }

    public void ThreadProc()
    {
      var args = CreateArgs();
      var psi = new ProcessStartInfo
                  {
                    Arguments = args,
                    CreateNoWindow = true,
                    RedirectStandardOutput = true,
                    FileName = "HrtRender.exe",
                    UseShellExecute = false
                  };

      _process = Process.Start(psi);
      UpdateStatus(JobStatus.Preprocessing);

      var completed = false;
      while(!_process.StandardOutput.EndOfStream)
      {
        var line = _process.StandardOutput.ReadLine();
        if (line.StartsWith("Completed: "))
        {
          float perc;
          if (float.TryParse(line.Substring(11), NumberStyles.Float, CultureInfo.InvariantCulture, out perc))
          {
            if (_job.Status == JobStatus.Preprocessing)
              UpdateStatus(JobStatus.InProgress);
            UpdatePercentage(perc);
          }
        }
        else if (line.Contains("Rendering complete"))
          completed = true;
      }

      _process = null;
      UpdateStatus(completed ? JobStatus.Done : JobStatus.Failed);
      _hostControl.Invoke((Action)(() => _completeHandler()));
    }

    private void UpdatePercentage(float perc)
    {
      _hostControl.Invoke((Action)(() => _job.PercentComplete = perc));
    }

    private void UpdateStatus(JobStatus status)
    {
      _hostControl.Invoke((Action)(() => _job.Status = status));
    }
  }
}