using System;

namespace HrtQueue
{
  public class JobItem
  {
    public string SceneFilename { get; set; }
    public string OutputFilename { get; set; }
    public float PercentComplete { get; set; }
    public JobStatus Status { get; set; }
    public int RaysPerPixel { get; set; }
    public int MaxRayDepth { get; set; }

    public string StatusText
    {
      get
      {
        switch (Status)
        {
          case JobStatus.Queued:
            return "Queued";
          case JobStatus.InProgress:
            return string.Format("{0:p}% complete", PercentComplete);
          case JobStatus.Done:
            return "Done";
          case JobStatus.Failed:
            return "Failed";
          default:
            throw new ArgumentOutOfRangeException();
        }
      }
    }
  }

  public enum JobStatus
  {
    Queued,
    InProgress,
    Done,
    Failed
  }
}