using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media.Imaging;

namespace AtlasMaker
{
    class Program
    {
        private static readonly string DefaultBitmapFilename = "atlas.png";
        private static readonly string DefaultLayoutFilename = "atlas.xml";

        static void Main(string[] args)
        {
            if (File.Exists(DefaultBitmapFilename))
                File.Delete(DefaultBitmapFilename);

            string[] fileNames = GetGraphicsFileNames();

            SpriteData[] spritesData = GetSpritesData(fileNames);

            SortSpritesBySize(spritesData);

            LayoutSprites(spritesData);

            WriteAtlasImage(DefaultBitmapFilename, spritesData);
            WriteAtlasLayout(DefaultLayoutFilename, spritesData);
        }

        private static void WriteAtlasLayout(string filename, SpriteData[] spritesData)
        {
            string xml = "";

            xml += "<Atlas>\n";

            foreach (var sprite in spritesData)
            {
                string name = System.IO.Path.GetFileNameWithoutExtension(sprite.FileName);
                xml += string.Format("\t<Sprite name=\"{4}\" bounds=\"{0},{1},{2},{3}\" />\n", sprite.Bounds.X, sprite.Bounds.Y, sprite.Bounds.Width, sprite.Bounds.Height, name);
            }

            xml += "</Atlas>\n";

            System.IO.File.WriteAllText(filename, xml);
        }

        private static void WriteAtlasImage(string atlasFileName, SpriteData[] spritesData)
        {
            Bitmap bitmap = new Bitmap(1024, 1024, System.Drawing.Imaging.PixelFormat.Format32bppArgb);
            Graphics graphics = Graphics.FromImage(bitmap);

            foreach (var sprite in spritesData)
            {
                Bitmap image = new Bitmap(Image.FromFile(sprite.FileName));
                image = image.Clone(new Rectangle((int)sprite.CropBounds.X, (int)sprite.CropBounds.Y, (int)sprite.CropBounds.Width, (int)sprite.CropBounds.Height), System.Drawing.Imaging.PixelFormat.Format32bppArgb);

                graphics.DrawImage(image, new System.Drawing.Point((int)sprite.Bounds.Location.X, (int)sprite.Bounds.Location.Y));

                image.Dispose();
            }

            bitmap.Save(atlasFileName, System.Drawing.Imaging.ImageFormat.Png);
            graphics.Dispose();
        }

        private static void SortSpritesBySize(SpriteData[] spritesData)
        {
            Array.Sort(
                spritesData,
                (s1, s2) => (s1.CropBounds.Width != s2.CropBounds.Width ?
                    s2.CropBounds.Width.CompareTo(s1.CropBounds.Width) :
                    s2.CropBounds.Height.CompareTo(s1.CropBounds.Height)));
        }

        static string[] GetGraphicsFileNames()
        {
            return Directory.GetFiles(".", "*.png");
        }

        static SpriteData[] GetSpritesData(string[] fileNames)
        {
            SpriteData[] spritesData = new SpriteData[fileNames.Length];

            for (int i = 0; i < fileNames.Length; i++)
            {
                spritesData[i] = new SpriteData();
                spritesData[i].FileName = fileNames[i];

                Rect bounds;
                Rect rectBounds;

                GetImageBounds(fileNames[i], out bounds, out rectBounds);
                spritesData[i].Bounds = bounds;
                spritesData[i].CropBounds = rectBounds;
            }

            return spritesData;
        }

        static void GetImageBounds(string fileName, out Rect bounds, out Rect cropBounds)
        {
            bounds = Rect.Empty;
            cropBounds = Rect.Empty;

            Image image = Image.FromFile(fileName);
            if (image == null)
                return;

            bounds = new Rect(0, 0, image.Width, image.Height);
            cropBounds = BitmapUtils.CalcBoundingBox(new Bitmap(image));
        }

        static void LayoutSprites(SpriteData[] sprites)
        {
            AtlasLayout atlas = new AtlasLayout(new System.Windows.Size(1024, 1024));

            foreach (var sprite in sprites)
            {
                System.Windows.Point location = atlas.AddSprite(sprite.CropBounds.Size);
                if (location.X == -1)
                {
                    Console.WriteLine("No space for sprite " + sprite.FileName);
                    continue;
                }

                sprite.Bounds = new Rect(location, sprite.Bounds.Size);
            }
        }
    }
}
