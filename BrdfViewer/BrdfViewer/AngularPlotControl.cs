using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;

namespace BrdfViewer
{
  public partial class AngularPlotControl : Control
  {
    private Dictionary<double, double> _data;
    private Color _chartBackColor;

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
      using (var drawPen = new Pen(ForeColor))
      {
        g.SmoothingMode = SmoothingMode.AntiAlias;

        g.FillRectangle(fillBrush, offsetX, offsetY, size * 2, size);
        g.DrawRectangle(drawPen, offsetX, offsetY, size * 2, size);
        g.DrawArc(drawPen, offsetX, offsetY, size * 2, size * 2, 0, -180);
        DrawAngleTicks(g, drawPen, offsetX, offsetY, size);
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
        var sx = angle == 90 ? offsetX + size : (float)(ex - Math.Cos(radians) * tickSize);
        var sy = angle == 90 ? offsetY + size : (float)(ey + Math.Sin(radians) * tickSize);

        g.DrawLine(drawPen, ex, ey, sx, sy);
      }
    }
  }
}
