using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Globalization;

namespace RefractConvert
{
	public class CsvParser : IDisposable
	{
		TextReader input;
		string[] header;
		string[] current;

		public string[] Header
		{
			get
			{
				return header;
			}
		}

		public CsvParser(string fileName)
		{
			input = new StreamReader(fileName);
			ReadHeader();
		}

		public bool Read()
		{
			var line = input.ReadLine();
			if (line == null)
				return false;

			current = line.Split(',');

			return true;
		}

		private void ReadHeader()
		{
			header = input.ReadLine().Split(',');
		}

		public T GetValue<T>(int index)
			where T : IConvertible
		{
			return (T)Convert.ChangeType(current[index], typeof(T), CultureInfo.InvariantCulture);
		}

		#region IDisposable Members

		public void Dispose()
		{
			if (input != null)
			{
				input.Dispose();
				input = null;
			}
		}

		#endregion
	}
}
