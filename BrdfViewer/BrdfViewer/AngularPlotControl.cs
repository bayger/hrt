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
    private Dictionary<double, double> _data;
    private Color _chartBackColor = Color.White;
    private Color _chartPlotColor = Color.Blue;
    private Color _chartAxisColor = Color.SlateGray;

    public Dictionary<double, double> Data
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
        g.DrawRectangle(axisPen, offsetX, offsetY, size * 2, size);
        g.DrawArc(axisPen, offsetX, offsetY, size * 2, size * 2, 0, -180);
        DrawAngleTicks(g, axisPen, offsetX, offsetY, size);

        PlotData(g, offsetX, offsetY, size);
      }
    }

    private void PlotData(Graphics g, int offsetX, int offsetY, int size)
    {
      if (Data == null || !Data.Any())
      {
        using(var axisBrush = new SolidBrush(ChartAxisColor))
        {
          g.DrawString("No BRDF data loaded", Font, axisBrush, 10, 10);
        }
        return;
      }

      var angles = Data.Keys.ToList();
      angles.Sort();

      using (var plotPen = new Pen(ChartPlotColor))
      {
        var maxF = Data.Max(x => x.Value);
        var px = (float) (offsetX + size);
        var py = (float) (offsetY + size);
        foreach (var item in angles)
        {
          var angle = 180.0f - (item + 90.0f); // -90..90 --> 180..0
          var radians = angle / 180 * Math.PI;
          var normalizedF = Data[item]/maxF;
          var ex = (float) (offsetX + size + Math.Cos(radians)*size*normalizedF);
          var ey = (float) (offsetY + size - Math.Sin(radians)*size*normalizedF);
          g.DrawLine(plotPen, px, py, ex, ey);

          px = ex;
          py = ey;
        }
      }
    }

    private void DrawAngleTicks(Graphics g, Pen drawPen, int offsetX, int offsetY, int size)
    {
      const float tickSize = 10.0f;
      for (float angle = 0; angle <= 180; angle += 5)
      {
        var radians = angle / 180 * Math.PI;
        var ex = (float)(offsetX + size + Math.Cos(radians) * size);
        var ey = (float)(offsetY + size - Math.Sin(radians) * size);
        var sx = angle == 90.0f ? offsetX + size : (float)(ex - Math.Cos(radians) * tickSize);
        var sy = angle == 90.0f ? offsetY + size : (float)(ey + Math.Sin(radians) * tickSize);

        g.DrawLine(drawPen, ex, ey, sx, sy);
      }
    }
  }
}
