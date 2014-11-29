using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace font2bmp
{
	public class ProgramParams
	{
		protected IDictionary<string, string> namedParams;
		protected IList<string> freeParams;

		private enum State
		{
			Initial,
			InsideNamedParamName,
			InsideNamedParamValue,
			InsideFreeParamValue,
			WaitingForNamedParamValue
		}

		public ProgramParams(string paramsString)
		{
			namedParams = new Dictionary<string, string>();
			freeParams = new List<string>();

			State state = State.Initial;

			string namedParamName = "";
			string namedParamValue = "";
			string freeParamValue = "";

			foreach (char item in paramsString)
			{
				if (item == '-')
					state = State.InsideNamedParamName;
				else if (item == ' ')
				{
					switch (state)
					{
						case State.InsideNamedParamName:
							state = State.WaitingForNamedParamValue;
							break;

						case State.InsideNamedParamValue:
							namedParams.Add(namedParamName, namedParamValue);
							namedParamName = "";
							namedParamValue = "";
							state = State.Initial;
							break;

						case State.InsideFreeParamValue:
							freeParams.Add(freeParamValue);
							freeParamValue = "";
							break;
					}
				}
				else
				{
					switch (state)
					{
						case State.WaitingForNamedParamValue:
							state = State.InsideNamedParamValue;
							namedParamValue += item;
							break;

						case State.InsideNamedParamName:
							namedParamName += item;
							break;

						case State.InsideNamedParamValue:
							namedParamValue += item;
							break;

						case State.InsideFreeParamValue:
							freeParamValue += item;
							break;

						case State.Initial:
							state = State.InsideFreeParamValue;
							freeParamValue += item;
							break;
					}
				}
			}

			if (freeParamValue != "")
				freeParams.Add(freeParamValue);

			if (namedParamName != "" && namedParamValue != "")
				namedParams.Add(namedParamName, namedParamValue);
		}

		public ProgramParams(string[] args)
		{
			namedParams = new Dictionary<string, string>();
			freeParams = new List<string>();

			int index = 0;
			while (index != args.Length)
			{
				if (args[index][0] == '-')
				{
					namedParams.Add(args[index].Substring(1), args[index + 1]);
					index += 2;
				}
				else
				{
					freeParams.Add(args[index]);
					index++;
				}
			}
		}

		public string GetNamedParam(string name)
		{
			string val;
			if (!namedParams.TryGetValue(name, out val))
				return null;
			else
				return val;
		}
	}
}
