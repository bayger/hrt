using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;
using System.IO;

namespace RefractConvert
{
	public partial class MainForm : Form
	{
		private Dictionary<string, List<double>> series;
		List<double> lambdas;

		public MainForm()
		{
			InitializeComponent();
			inputFilenameTextBox.Font = new Font(inputFilenameTextBox.Font, FontStyle.Italic);
		}

		private void reloadButton_Click(object sender, EventArgs e)
		{
			LoadData();
		}

		private void LoadData()
		{
			using (var parser = new CsvParser(openFileDialog.FileName))
			{
				if (parser.Header.Length < 2)
				{
					ShowError("Selected file is invalid");
					return;
				}

				series = new Dictionary<string, List<double>>();
				for (int i = 1; i < parser.Header.Length; i++)
					series.Add(parser.Header[i], new List<double>());
				lambdas = new List<double>();

				while (parser.Read())
				{
					lambdas.Add(parser.GetValue<double>(0));
					for (int i = 1; i < parser.Header.Length; i++)
						series[parser.Header[i]].Add(parser.GetValue<double>(i));
				}
			}

			inputFilenameTextBox.Font = new Font(inputFilenameTextBox.Font, FontStyle.Regular);
			inputFilenameTextBox.Enabled = true;
			reloadButton.Enabled = true;
			string names = string.Empty;
			seriesLabel.Text = series.Keys.Aggregate(names, (s, k) => s += s.Length == 0 ? k : ", "+k);
			saveButton.Enabled = true;

			chart1.Titles[0].Text = "Data visualization";
			chart1.Series.Clear();
			foreach (var s in series)
				ShowSeries(s.Key);
			chart1.ChartAreas[0].RecalculateAxesScale();
		}

		private void ShowError(string p)
		{
			MessageBox.Show(this, p, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
		}

		private void openBrowseButton_Click(object sender, EventArgs e)
		{
			if (openFileDialog.ShowDialog() == DialogResult.OK)
			{
				inputFilenameTextBox.Text = openFileDialog.FileName;
				outputFilenameTextBox.Text = Path.Combine(Path.GetDirectoryName(openFileDialog.FileName),
					Path.GetFileNameWithoutExtension(openFileDialog.FileName) + ".$series$.spc");
				LoadData();
			}
		}

		private void ShowSeries(string p)
		{
			var series = new Series(p);
			var data = this.series[p];

			series.ChartType = SeriesChartType.Line;
			for (int i = 0; i < data.Count; i++)
				series.Points.AddXY(lambdas[i], data[i]);

			chart1.Series.Add(series);
		}

		private IEnumerable<double> GetOutputPoints()
		{
			var x = startNumeric.Value;
			while (x <= endNumeric.Value)
			{
				yield return (double)x * 1e-3;
				x += stepNumeric.Value;
			}
		}

		private void saveButton_Click(object sender, EventArgs e)
		{
			double? min = null;
			double? max = null;

			foreach (var s in series)
			{
				var input = s.Value.Select((y, i) => new PairXY() { X = lambdas[i] , Y = y}).ToList();
				input.Sort((p1, p2) => p1.X.CompareTo(p2.X));
				var output = GetOutputPoints().ToList();

				IEnumerable<PairXY> data = Interpolator.Interpolate(input, output);
				var chartSeries = new Series(s.Key + " (out)");
				chartSeries.ChartType = SeriesChartType.Point;
				foreach (var point in data)
					chartSeries.Points.AddXY(point.X, point.Y);
				var dataMin = data.Min(p => p.Y);
				var dataMax = data.Max(p => p.Y);

				if (!min.HasValue || min > dataMin)
					min = dataMin;
				if (!max.HasValue || max < dataMax)
					max = dataMax;

				chart1.Series.Add(chartSeries);
			}

			chart1.ChartAreas[0].AxisX.Minimum = (double)startNumeric.Value * 1e-3;
			chart1.ChartAreas[0].AxisX.Maximum = (double)endNumeric.Value * 1e-3;
			chart1.ChartAreas[0].AxisY.Minimum = Math.Floor(min.Value);
			chart1.ChartAreas[0].AxisY.Maximum = Math.Ceiling(max.Value);
		}

	}
}
