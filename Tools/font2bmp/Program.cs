using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Drawing.Text;

namespace font2bmp
{
	class Program
	{
		private static readonly int OutputBitmapWidth = 512;

		private static readonly string Alphabet =
			"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789,./<>?;':\"[]{}|\\!@#$%^&*()_+-=";

		private static string GenerateXml(IList<CharInfo> charsInfo, string bmpFilename)
		{
			string code = "<alphabet bitmap=\"" + bmpFilename + "\">\n";

			foreach (var item in charsInfo)
			{
				code += "\t";
				code +=
					"<char letter=\"" +
					System.Security.SecurityElement.Escape(item.Character.ToString()) +
					"\" bounds=\"";
				code += item.GlobalLocation.X + ";";
				code += item.GlobalLocation.Y + ";";
				code += item.BoundingBox.Width + ";";
				code += item.BoundingBox.Height + "\"";
				code += "/>\n";
			}

			code += "</alphabet>\n";

			return code;
		}

		private static void SaveXml(string path, string code)
		{
			StreamWriter writer = new StreamWriter(path, false);
			writer.Write(code);
			writer.Close();
		}

		private static int RoundToPowOf2(double val)
		{
			return (int)Math.Pow(2, Math.Ceiling(Math.Log(val, 2)));
		}

		static IList<CharInfo> CreateCharInfos(Font font)
		{
			IList<CharInfo> charInfos = new List<CharInfo>();

			foreach (var letter in Alphabet)
				charInfos.Add(CharInfo.Create(letter, font));

			// add space with BoundingBox from "_" character
			CharInfo spaceChar = CharInfo.Create(' ', font);
			spaceChar.BoundingBox = charInfos.Single(s => s.Character == '_').BoundingBox;
			charInfos.Add(spaceChar);

			return charInfos;
		}

		static void FindCommonHeight(IList<CharInfo> charInfos, out int top, out int bottom)
		{
			top = int.MaxValue;
			bottom = 0;

			foreach (var charInfo in charInfos)
			{
				if (charInfo.BoundingBox.Top < top)
					top = charInfo.BoundingBox.Top;

				if (charInfo.BoundingBox.Bottom > bottom)
					bottom = charInfo.BoundingBox.Bottom;
			}
		}

        static void FindCommonWidth(IList<CharInfo> charInfos, out int left, out int right)
        {
            right = 0;
            left = int.MaxValue;

            foreach (var charInfo in charInfos)
            {
                if (charInfo.BoundingBox.Right > right)
                    right = charInfo.BoundingBox.Right;

                if (charInfo.BoundingBox.Left < left)
                    left = charInfo.BoundingBox.Left;
            }
        }

		static void SetCommonHeight(IList<CharInfo> charInfos, int top, int bottom)
		{
			foreach (var charInfo in charInfos)
				charInfo.BoundingBox = new Rectangle(charInfo.BoundingBox.X, top, charInfo.BoundingBox.Width, bottom - top + 1);
		}

        static void SetCommonWidth(IList<CharInfo> charInfos, int left, int right)
        {
            foreach (var charInfo in charInfos)
                charInfo.BoundingBox = new Rectangle(left, charInfo.BoundingBox.Top, right - left + 1, charInfo.BoundingBox.Height);
        }

		static void Main(string[] args)
		{
			//string paramsString = "";
			//for (int i = 0; i < args.Length; i++)
			//{
			//    paramsString += args[i];
			//    if (i != args.Length - 1)
			//        paramsString += " ";
			//}

			ProgramParams programParams = new ProgramParams(args);

			//string paramBmpFile = programParams.GetNamedParam("bmp");
			//string paramXmlFile = programParams.GetNamedParam("xml");
			string paramOutputFiles = programParams.GetNamedParam("o");
			string paramFontName = programParams.GetNamedParam("n");
			string paramFontFile = programParams.GetNamedParam("f");
			string paramFontSize = programParams.GetNamedParam("s");
			string paramFontStyle = programParams.GetNamedParam("d");
            string paramConstWidth = programParams.GetNamedParam("w");

			//if (paramBmpFile == null)
			//    paramBmpFile = "font.png";
			//if (paramXmlFile == null)
			//    paramXmlFile = "font.xml";
			if (paramOutputFiles == null)
			    paramOutputFiles = "font";
			if (paramFontName == null)
			{
				Console.Out.Write("no -n parameter!\n\n");
				return;
			}
			if (paramFontSize == null)
				paramFontSize = "32";
			float paramFontSizeVal;
			if (!float.TryParse(paramFontSize, out paramFontSizeVal))
			{
				Console.Out.Write("wrong -s parameter!\n\n");
				return;
			}
			if (paramFontStyle == null)
				paramFontStyle = "r";
			FontStyle fontStyle = FontStyle.Regular;
			switch (paramFontStyle)
			{
				case "r": fontStyle = FontStyle.Regular; break;
				case "b": fontStyle = FontStyle.Bold; break;
				case "i": fontStyle = FontStyle.Italic; break;
				default:
					Console.Out.Write("unknown font style parameter\n\n");
					return;
			}

            int userDefinedWidth = 0;
            if (paramConstWidth != null)
                int.TryParse(paramConstWidth, out userDefinedWidth);

			Font font;
			try
			{
				font = new Font(new FontFamily(paramFontName), paramFontSizeVal, fontStyle, GraphicsUnit.Point);
			}
			catch (ArgumentException e)
			{
				Console.Out.Write("exception: " + e.Message + " \n\n");
				return;
			}

			IList<CharInfo> charInfos = CreateCharInfos(font);

			int commonTop;
			int commonBottom;

			// get common, maximal height of all characters
			FindCommonHeight(charInfos, out commonTop, out commonBottom);

			int commonHeight = commonBottom - commonTop + 1;

			// apply common height to all characters
			SetCommonHeight(charInfos, commonTop, commonBottom);

            if (userDefinedWidth != 0)
            {
                SetCommonWidth(charInfos, 0, userDefinedWidth);
            }

			//int index = 0;
			//foreach (var item in charInfos)
			//{
			//    Graphics g = Graphics.FromImage(item.CharImage);
			//    g.DrawRectangle(Pens.Blue, item.BoundingBox);
			//    g.Dispose();
			//    item.CharImage.Save("dupa\\" + index.ToString() + ".png", ImageFormat.Png);
			//    index++;
			//}

			// calc size of output image
			Size outputImageDim = LayoutCharacters(charInfos, commonHeight);

			// copy all characters to one bitmap
			Bitmap alphabetBitmap = CreateAlphabetBitmap(charInfos, outputImageDim);
			alphabetBitmap.Save(paramOutputFiles + ".png", ImageFormat.Png);

			string xmlCode = GenerateXml(charInfos, paramOutputFiles + ".png");
			SaveXml(paramOutputFiles + ".xml", xmlCode);

			Console.Out.Write("You are lucky - no crash, finished with success!\n\n");
		}

		private static Bitmap CreateAlphabetBitmap(IList<CharInfo> charInfos, Size outputImageDim)
		{
			Bitmap bmp = new Bitmap(outputImageDim.Width, outputImageDim.Height, PixelFormat.Format32bppArgb);

			Graphics graphics = Graphics.FromImage(bmp);

			foreach (var charInfo in charInfos)
				graphics.DrawImage(
					charInfo.CharImage,
					charInfo.GlobalLocation.X,
					charInfo.GlobalLocation.Y,
					charInfo.BoundingBox,
					GraphicsUnit.Pixel);

			graphics.Dispose();

			return bmp;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="charInfos"></param>
		/// <param name="charHeight"></param>
		/// <returns>Size of output image</returns>
		private static Size LayoutCharacters(IList<CharInfo> charInfos, int charHeight)
		{
			int xOffset = 0;
			int yOffset = 0;

			foreach (var charInfo in charInfos)
			{
				if (xOffset + charInfo.BoundingBox.Width >= OutputBitmapWidth)
				{
					xOffset = 0;
					yOffset += charHeight;
				}

				charInfo.GlobalLocation = new Point(xOffset, yOffset);

				xOffset += charInfo.BoundingBox.Width;
			}

			//return new Size(OutputBitmapWidth, yOffset + charHeight);
			return new Size(OutputBitmapWidth, OutputBitmapWidth);
		}
	}
}
