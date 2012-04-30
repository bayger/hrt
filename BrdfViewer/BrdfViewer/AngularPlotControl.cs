using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Windows.Forms;

namespace BrdfViewer
{
  public partial class AngularPlotControl : Control
  {
    private Dictionary<double, List<double>> _data;
    private Color _chartBackColor = Color.White;
    private Color _chartPlotColor = Color.Blue;
    private Color _chartAxisColor = Color.Gray;
    private string _chartTitle;

    public Dictionary<double, List<double>> Data
    {
      get { return _data; }
      set
      {
        _data = value;
        Invalidate();
      }
    }

    public Color ChartBackColor
    {
      get { return _chartBackColor; }
      set
      {
        _chartBackColor = value;
        Invalidate();
      }
    }

    public Color ChartPlotColor
    {
      get { return _chartPlotColor; }
      set
      {
        _chartPlotColor = value;
        Invalidate();
      }
    }

    public Color ChartAxisColor
    {
      get { return _chartAxisColor; }
      set
      {
        _chartAxisColor = value;
        Invalidate();
      }
    }

    public string ChartTitle
    {
      get { return _chartTitle; }
      set
      {
        _chartTitle = value;
        Invalidate();
      }
    }

    public AngularPlotControl()
    {
      InitializeComponent();
      this.SetDoubleBuffered();
    }

    protected override void OnSizeChanged(EventArgs e)
    {
      base.OnSizeChanged(e);
      Invalidate();
    }

    public void SaveToWmf(string fileName)
    {
      
    }

    protected override void OnPaint(PaintEventArgs pe)
    {
      var g = pe.Graphics;
      var r = ClientRectangle;
      var w = r.Width - 2;
      var h = r.Height - 2;
      var size = w > h * 2 ? h : w / 2;
      var offsetX = (r.Width - size * 2) / 2;
      var offsetY = (r.Height - size) / 2;

      using (var fillBrush = new SolidBrush(_chartBackColor))
      using (var axisPen = new Pen(ChartAxisColor))
      {
        g.SmoothingMode = SmoothingMode.AntiAlias;

        g.FillRectangle(fillBrush, offsetX, offsetY, size * 2, size);
        //g.DrawRectangle(axisPen, offsetX, offsetY, size * 2, size);

        size -= 32;
        offsetX = (r.Width - size * 2) / 2;
        offsetY = (r.Height - size) / 2;

        g.DrawArc(axisPen, offsetX, offsetY, size * 2, size * 2, 0, -180);
        DrawAngleTicks(g, axisPen, offsetX, offsetY, size);

        PlotData(g, offsetX, offsetY, size);
      }
    }

    private void PlotData(Graphics g, int offsetX, int offsetY, int size)
    {
      using (var axisBrush = new SolidBrush(ChartAxisColor))
      {
        if (Data == null || !Data.Any())
        {
          g.DrawString("No data loaded", Font, axisBrush, offsetX + 10, offsetY + 10);

          return;
        }

        int valCount = Data.First().Value.Count;
        if (Data.Any(x => x.Value.Count != valCount))
          throw new InvalidOperationException("Incorrect data for plot");

        var angles = Data.Keys.ToList();
        angles.Sort();

        var pens = new List<Pen>();
        pens.Add(new Pen(Color.Blue));
        pens.Add(new Pen(Color.Green));
        pens.Add(new Pen(Color.Red));

        using (var plotPen = new Pen(ChartPlotColor))
        {
          var maxF = new List<double>();
          for (int i = 0; i < valCount; i++)
            maxF.Add(Data.Select(x => x.Value[i]).Max());
          var normalizationFactor = maxF.Max();
          g.DrawString(normalizationFactor.ToString(), Font, axisBrush, offsetX, offsetY + size + 2);

          for (int i = 0; i < valCount; i++)
          {
            var px = (float) (offsetX + size);
            var py = (float) (offsetY + size);
            foreach (var item in angles)
            {
              var angle = item + 90.0f; // -90..90 --> 0..180
              var radians = angle/180*Math.PI;
              var normalizedF = (Data[item])[i]/normalizationFactor;
              var ex = (float) (offsetX + size + Math.Cos(radians)*size*normalizedF);
              var ey = (float) (offsetY + size - Math.Sin(radians)*size*normalizedF);
              g.DrawLine(pens[i%pens.Count], px, py, ex, ey);

              px = ex;
              py = ey;
            }
          }
        }

        foreach (var pen in pens)
          pen.Dispose();
      }
    }

    private void DrawAngleTicks(Graphics g, Pen drawPen, int offsetX, int offsetY, int size)
    {
      using (var brush = new SolidBrush(ChartAxisColor))
      using (var dottedPen = new Pen(ChartAxisColor))
      {
        dottedPen.DashStyle = DashStyle.Dash;
        dottedPen.DashPattern = new float[] {3.0f, 3.0f};
        const float tickSize = 10.0f;
        for (float angle = 0; angle <= 180; angle += 10)
        {
          var radians = angle/180*Math.PI;
          var ex = (float) (offsetX + size + Math.Cos(radians)*size);
          var ey = (float) (offsetY + size - Math.Sin(radians)*size);
          var sx = angle == 90.0f ? offsetX + size : (float) (ex - Math.Cos(radians)*tickSize);
          var sy = angle == 90.0f ? offsetY + size : (float) (ey + Math.Sin(radians)*tickSize);

          g.DrawLine(dottedPen, sx, sy, offsetX + size, offsetY + size);
          g.DrawLine(drawPen, ex, ey, sx, sy);

          var label = (angle - 90).ToString("0°");
          var labelSize = g.MeasureString(label, Font);
          g.DrawString(label, Font, brush, angle <= 90 ? ex : ex - labelSize.Width, ey - labelSize.Height);
        }
      }
    }
  }
}
