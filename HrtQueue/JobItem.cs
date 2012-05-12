using System;
using System.ComponentModel;

namespace HrtQueue
{
  public class JobItem : INotifyPropertyChanged
  {
    public string SceneFilename { get; set; }
    public string OutputFilename { get; set; }
    private float _percentComplete;
    public float PercentComplete
    {
      get { return _percentComplete; }
      set
      {
        _percentComplete = value;
        OnPropertyChanged(new PropertyChangedEventArgs("PerecentComplete"));
        OnPropertyChanged(new PropertyChangedEventArgs("StatusText"));
      }
    }

    private JobStatus _status;
    public JobStatus Status
    {
      get { return _status; }
      set
      {
        _status = value;
        OnPropertyChanged(new PropertyChangedEventArgs("Status"));
        OnPropertyChanged(new PropertyChangedEventArgs("StatusText"));
      }
    }

    private int _raysPerPixel;
    public int RaysPerPixel
    {
      get { return _raysPerPixel; }
      set
      {
        _raysPerPixel = value;
        OnPropertyChanged(new PropertyChangedEventArgs("RaysPerPixel"));
      }
    }

    private int _maxRayDepth;

    public int MaxRayDepth
    {
      get { return _maxRayDepth; }
      set
      {
        _maxRayDepth = value;
        OnPropertyChanged(new PropertyChangedEventArgs("MaxRayDepth"));
      }
    }

    private float _sigmaFilter;

    public float SigmaFilter
    {
      get { return _sigmaFilter; }
      set
      {
        _sigmaFilter = value;
        OnPropertyChanged(new PropertyChangedEventArgs("SigmaFilter"));
      }
    }

    public string StatusText
    {
      get
      {
        switch (Status)
        {
          case JobStatus.Queued:
            return "Queued";
          case JobStatus.InProgress:
            return string.Format("{0:0.00}% complete", PercentComplete);
          case JobStatus.Done:
            return "Done";
          case JobStatus.Failed:
            return "Failed";
          case JobStatus.Preprocessing:
            return "Preparing";
          default:
            throw new ArgumentOutOfRangeException();
        }
      }
    }

    public event PropertyChangedEventHandler PropertyChanged;

    public void OnPropertyChanged(PropertyChangedEventArgs e)
    {
      PropertyChangedEventHandler handler = PropertyChanged;
      if (handler != null) handler(this, e);
    }
  }

  public enum JobStatus
  {
    Queued,
    InProgress,
    Preprocessing,
    Done,
    Failed
  }
}