using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace AtlasMaker
{
    class BitmapUtils
    {
        public static Rect CalcBoundingBox(Bitmap bmp)
        {
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

            return new Rect(left, top, right - left + 1, bottom - top + 1);
        }
    }
}
