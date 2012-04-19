using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RefractConvert
{
	public class Interpolator
	{
		public static IEnumerable<PairXY> Interpolate(IList<PairXY> inputXY, IList<double> outputX)
		{
			if (inputXY.Count < 2)
				throw new ArgumentOutOfRangeException("inputXY");
			if (outputX.Count < 1)
				throw new ArgumentOutOfRangeException("outputX");

			var rangeEnd = FindRangeEnd(outputX[0], inputXY);
			for (int i = 0; i < outputX.Count; i++)
			{
				while (rangeEnd < inputXY.Count)
				{
					if (inputXY[rangeEnd].X >= outputX[i])
						break;
					rangeEnd++;
				}

				if (rangeEnd == 0)
				{
					yield return new PairXY()
					{
						X = outputX[i],
						Y = inputXY[0].Y
					};
					continue;
				}
				else if (rangeEnd == inputXY.Count)
				{
					yield return new PairXY()
					{
						X = outputX[i],
						Y = inputXY[inputXY.Count-1].Y
					};
					continue;
				}					

				var xa = inputXY[rangeEnd - 1].X;
				var xb = inputXY[rangeEnd].X;

				var t = (outputX[i] - xa) / (xb - xa);
				yield return new PairXY() 
				{ 
					X = outputX[i], 
					Y = inputXY[rangeEnd - 1].Y + t * (inputXY[rangeEnd].Y - inputXY[rangeEnd - 1].Y) 
				};
			}
		}

		private static int FindRangeEnd(double x, IList<PairXY> inputXY)
		{
			int i = 0;
			while (i < inputXY.Count)
			{
				if (inputXY[i].X >= x)
					break;
				i++;
			}

			return i;
		}
	}
}
