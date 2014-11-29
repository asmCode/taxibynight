using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Drawing.Imaging;
using System.Drawing.Drawing2D;
using System.Drawing.Text;

namespace font2bmp
{
	class CharInfo
	{
		public char Character { get; set; }

		/// <summary>
		/// Image with rendered char
		/// </summary>
		public Image CharImage { get; set; }

		/// <summary>
		/// Bounding box of character on CharImage
		/// </summary>
		public Rectangle BoundingBox { get; set; }

		/// <summary>
		/// Location on output file
		/// </summary>
		public Point GlobalLocation { get; set; }

		private CharInfo()
		{
		}

		private void CalcBoundingBox()
		{
			Bitmap bmp = (Bitmap)CharImage;

			int left = bmp.Width - 1;
			int right = 0;
			int top = bmp.Height - 1;
			int bottom = 0;

			for (int y = 0; y < bmp.Height; y++)
			{
				int ry = bmp.Height - 1 - y; // reverted y

				for (int x = 0; x < bmp.Width; x++)
				{
					int rx = bmp.Width - 1 - x; // reverted x

					// check top-left corner
					if (bmp.GetPixel(x, y).A != 0)
					{
						if (x < left)
							left = x; // new min left border
						if (top == bmp.Height - 1) // first non-transparent pixel from top is top of a character
							top = y;
					}

					// check bottom-right corner
					if (bmp.GetPixel(rx, ry).A != 0)
					{
						if (rx > right)
							right = rx; // new max right border
						if (bottom == 0) // first non-transparent pixel from bottom is bottom of a character
							bottom = ry;
					}
				}
			}

			//Console.Out.WriteLine("(" + left.ToString() + ", " + top.ToString() + ", " + (right - left).ToString() + ", " + (bottom - top).ToString() + ")");

			BoundingBox = new Rectangle(left, top, right - left + 1, bottom - top + 1);

            /*
            if (Character == ',' || Character == '.' || Character == ':' || Character == ';')
                BoundingBox = new Rectangle(left - 2, top, 7, bottom - top + 1);
            else if (Character == '1')
                BoundingBox = new Rectangle(left - 15, top, 20, bottom - top + 1);
            else
                BoundingBox = new Rectangle(left - 2, top, 20, bottom - top + 1);
             */
		}

		public static CharInfo Create(char character, Font font)
		{
			CharInfo charInfo = new CharInfo();

			charInfo.Character = character;
			charInfo.CharImage = new Bitmap((int)font.Size * 5, (int)font.Size * 5, PixelFormat.Format32bppArgb);

			Graphics graphics = Graphics.FromImage(charInfo.CharImage);
			graphics.SmoothingMode = SmoothingMode.HighQuality;
			graphics.TextRenderingHint = TextRenderingHint.AntiAliasGridFit;
			graphics.DrawString(character.ToString(), font, Brushes.White, new PointF(font.Size, font.Size));
			//charInfo.CalcBoundingBox();
			//graphics.DrawRectangle(Pens.Red, charInfo.BoundingBox);
			graphics.Dispose();

			// calc bounding box for rendered character
			charInfo.CalcBoundingBox();

			//charInfo.CharImage.Save(character.ToString() + ".png", ImageFormat.Png);

			return charInfo;
		}
	}
}
