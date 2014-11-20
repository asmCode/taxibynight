using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace AtlasMaker
{
    class AtlasLayout
    {
        private List<Rect> m_regions = new List<Rect>();

        public AtlasLayout(Size size)
        {
            CreateRegion(new Rect(0, 0, size.Width, size.Height));
        }

        public Point AddSprite(Size spriteSize)
        {
            Rect region = FindSuitableRegion(spriteSize);
            if (region == Rect.Empty)
                return new Point(-1, -1); // TODO, HACK

            SplitRegion(region, (int)spriteSize.Width, (int)spriteSize.Height);

            return region.Location;
        }

        private void SplitRegion(Rect region, int x, int y)
        {
            m_regions.Remove(region);

            m_regions.Add(new Rect(region.Location.X + x, region.Location.Y, region.Width - x, region.Height));
            m_regions.Add(new Rect(region.Location.X, region.Location.Y + y, x, region.Height - y));
        }

        private void CreateRegion(Rect rect)
        {
            m_regions.Add(new Rect(rect.Location, rect.Size));
        }

        private Rect FindSuitableRegion(Size size)
        {
            foreach (Rect region in m_regions)
            {
                if (region.Width >= size.Width && region.Height >= size.Height)
                    return region;
            }

            return Rect.Empty;
        }
    }
}
