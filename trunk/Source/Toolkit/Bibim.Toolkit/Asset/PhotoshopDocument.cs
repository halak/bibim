using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Drawing;
using System.IO;
using System.Reflection;
using System.Text;
using Bibim.Reflection;

namespace Bibim.Asset
{   
    /// <summary>
    /// Adobe Photoshop Document (*.psd)를 나타내는 class 
    /// </summary>
    /// <seealso cref="http://www.endogine.com/CS/"/>
    public sealed partial class PhotoshopDocument
    {
        #region Static Fields
        private static Dictionary<ImageResourceID, Type> imageResourceDictionary;
        #endregion

        #region Fields
        List<ImageResource> imageResources;
        List<Layer> layers;
        ReadOnlyCollection<ImageResource> readOnlyImageResources;
        ReadOnlyCollection<Layer> readOnlyLayers;
        #endregion

        #region Properties
        public int Channels
        {
            get;
            private set;
        }

        public int Width
        {
            get;
            private set;
        }

        public int Height
        {
            get;
            private set;
        }

        public int BitsPerPixel
        {
            get;
            private set;
        }

        public ColorModes ColorMode
        {
            get;
            private set;
        }

        public IList<ImageResource> ImageResources
        {
            get { return readOnlyImageResources; }
        }
        
        public IList<Layer> Layers
        {
            get { return readOnlyLayers; }
        }

        public Bitmap MergedBitmap
        {
            get;
            private set;
        }
        #endregion

        #region Constructors
        public PhotoshopDocument(string path)
        {
            using (var fs = new FileStream(path, FileMode.Open, FileAccess.Read))
                Load(fs);
        }

        public PhotoshopDocument(Stream stream)
        {
            Load(stream);
        }
        #endregion

        #region Methods
        private void Load(Stream stream)
        {
            Reader reader = new Reader(stream);

            #region PSD인지 검사합니다.
            {
                string signature = new string(reader.ReadChars(4));
                if (signature != "8BPS")
                    throw new Exception("올바른 PSD File이 아닙니다.");

                short version = reader.ReadInt16();
                if (version != 1)
                    throw new Exception("PSD File의 Version이 맞지 않습니다.");
            }
            #endregion

            int channels = 0;
            int width = 0;
            int height = 0;
            int bitsPerPixel = 0;
            ColorModes colorMode = ColorModes.RGB;
            #region Header를 읽어옵니다.
            {
                reader.BaseStream.Position += 6; // 예약분

                channels = reader.ReadInt16();
                height = reader.ReadInt32();
                width = reader.ReadInt32();
                bitsPerPixel = reader.ReadInt16();
                colorMode = (ColorModes)reader.ReadInt16();

                if (colorMode != ColorModes.RGB)
                    throw new Exception(string.Format("{0} Color Format인 PSD는 읽어올 수 없습니다. (가능한 Color Format : RGB)", colorMode));
                if (bitsPerPixel != 8)
                    throw new Exception(string.Format("한 Pixel이 Channel당 {0} byte인 PSD는 읽어올 수 없습니다. (가능한 Bytes : 1 Byte", bitsPerPixel));
            }
            #endregion

            byte[] colorModeData = null;
            #region ColorModeData를 가져옵니다.
            {
                uint sectionSize = reader.ReadUInt32();
                if (sectionSize > 0)
                    colorModeData = reader.ReadBytes((int)sectionSize);
            }
            #endregion

            List<ImageResource> imageResources = null;
            #region ImageResource들을 읽어옵니다.
            {
                uint sectionSize = reader.ReadUInt32();
                if (sectionSize > 0)
                {
                    long sectionEndPosition = reader.BaseStream.Position + (long)sectionSize;

                    imageResources = new List<ImageResource>();
                    while (reader.BaseStream.Position < sectionEndPosition)
                    {
                        string signature = new string(reader.ReadChars(4));
                        if (signature != "8BIM" && signature != "MeSa")
                            throw new Exception("올바르지 않은 ImageResource가 존재합니다.");

                        ImageResourceID id = (ImageResourceID)reader.ReadInt16();
                        string name = reader.ReadPascalString();
                        uint size = reader.ReadUInt32();
                        long endPosition = reader.BaseStream.Position + (long)size;
                        if (size > 0)
                        {
                            ImageResource resource = CreateImageResource(id, name, size, reader);
                            if (resource != null)
                                imageResources.Add(resource);
                        }

                        // 위치는 짝수로 맞춥니다.
                        reader.BaseStream.Position = (endPosition % 2 == 0) ? endPosition : endPosition + 1;
                    }

                    reader.BaseStream.Position = sectionEndPosition;
                }
            }
            #endregion

            List<Layer> layers = null;
            #region Layer와 Mask 정보를 읽어옵니다.
            {
                uint sectionSize = reader.ReadUInt32();
                if (sectionSize > 0)
                {
                    long sectionEndPosition = reader.BaseStream.Position + (long)sectionSize;

                    #region Layer를 읽어옵니다.
                    layers = new List<Layer>();

                    uint layersSize = reader.ReadUInt32();
                    if (layersSize > 0)
                    {
                        long layersEndPosition = reader.BaseStream.Position + (long)layersSize;

                        //bool absoluteAlpha = false;
                        short numberOfLayers = reader.ReadInt16();
                        if (numberOfLayers < 0)
                        {
                            //absoluteAlpha = true;
                            numberOfLayers = Math.Abs(numberOfLayers);
                        }

                        #region Layer들의 기본 정보를 읽어서 보관합니다.
                        for (short i = 0; i < numberOfLayers; i++)
                        {
                            layers.Add(new Layer(reader));
                        }
                        #endregion

                        #region Layer들의 Pixel 정보를 읽어옵니다.
                        foreach (Layer layer in layers)
                        {
                            layer.ReadPixelData(bitsPerPixel, reader);
                        }
                        #endregion

                        #region Group을 정리합니다.
                        {
                            Stack<Layer> layerStack = new Stack<Layer>(layers.Count / 2);
                            for (int i = layers.Count - 1; i >= 0; i--)
                            {
                                Layer item = layers[i];
                                bool isEndLayerSetTag = (item.Name == "</Layer set>") ||
                                                        (item.Name == "</Layer group>");

                                if (layerStack.Count > 0 && isEndLayerSetTag == false)
                                    layerStack.Peek().AddSubLayer(item);

                                if (item.IsGroup)
                                {
                                    if (isEndLayerSetTag == false)
                                        layerStack.Push(item);
                                    else
                                    {
                                        layerStack.Pop();
                                        layers.RemoveAt(i);
                                    }
                                }
                            }

                            for (int i = 0; i < layers.Count;)
                            {
                                if (layers[i].Group != null)
                                    layers.RemoveAt(i);
                                else
                                    i++;
                            }
                        }
                        #endregion

                        reader.BaseStream.Position = layersEndPosition;
                    }
                    #endregion

                    #region Layer Global Mask정보를 읽어옵니다.
                    {
                        // 쓰지 않으므로 무시합니다.
                    }
                    #endregion

                    reader.BaseStream.Position = sectionEndPosition;
                }
            }
            #endregion

            Bitmap mergedImageData = null;
            byte[][] mergedImageChannelData = null;
            #region PSD 마지막 부분에 있는 합쳐진 Image를 읽어옵니다.
            int numberOfPixels = width * height;
            Compression compressionMode = (Compression)reader.ReadInt16();
            mergedImageChannelData = new byte[channels][];
            
            #region Channel 별로 기록된 Pixel Data를 읽어옵니다.
            switch (compressionMode)
            {
                case Compression.RawData:
                    for (int i = 0; i < mergedImageChannelData.Length; i++)
                        mergedImageChannelData[i] = reader.ReadRawPixelData(width, height, bitsPerPixel);
                    break;
                case Compression.RLECompression:
                    // 행별로 열의 길이가 기록되어 있습니다만 무시합니다.
                    reader.BaseStream.Position += height * channels * 2;
                    for (int i = 0; i < mergedImageChannelData.Length; i++)
                        mergedImageChannelData[i] = reader.ReadRLECompressedPixelData(width, height, bitsPerPixel);
                    break;
                default:
                    throw new Exception(string.Format("{0} 로 저장된 PSD는 읽어올 수 없습니다. (프로그래머에게 연락하세요)", compressionMode));
            }
            #endregion
            
            #region BitmapContent에 Pixel들을 채워 넣습니다.
            switch (colorMode)
            {
                case ColorModes.RGB:
                    if (channels == 3)
                        mergedImageData = MergeChannels(width, height, mergedImageChannelData[0], mergedImageChannelData[1], mergedImageChannelData[2], null);
                    else if (channels >= 4)
                        mergedImageData = MergeChannels(width, height, mergedImageChannelData[0], mergedImageChannelData[1], mergedImageChannelData[2], mergedImageChannelData[3]);
                    break;
            }
            #endregion
            #endregion

            #region 읽어온 정보들을 Field에 설정합니다.
            this.Channels = channels;
            this.Width = width;
            this.Height = height;
            this.BitsPerPixel = bitsPerPixel;
            this.ColorMode = colorMode;
            this.imageResources = imageResources;
            this.layers = layers;
            this.readOnlyImageResources = new ReadOnlyCollection<ImageResource>(this.imageResources);
            this.readOnlyLayers = new ReadOnlyCollection<Layer>(this.layers);
            this.MergedBitmap = mergedImageData;
            #endregion
        }

        #region CreateImageResource
        private static ImageResource CreateImageResource(ImageResourceID id, string name, uint size, Reader reader)
        {
            #region 만약 ImageResourceDictionary가 구축되어있지 않다면 구축합니다.
            if (imageResourceDictionary == null)
            {
                // ImageResource를 상속 받고,
                // ImageResourceAttribute를 정의하고, 
                // (ImageResourceID, string, BinaryReader)를 입력받는 생성자를 정의한 class를 모읍니다.

                imageResourceDictionary = new Dictionary<ImageResourceID, Type>();
                Assembly assembly = Assembly.GetCallingAssembly();
                Type[] constructorParameterTypes = new Type[] { typeof(ImageResourceID), typeof(string), typeof(uint), typeof(Reader) };
                foreach (Type item in assembly.GetTypes())
                {
                    if (item.IsVisible &&
                        item.IsClass &&
                        item.IsAbstract == false &&
                        item.IsSubclassOf(typeof(ImageResource)) &&
                        item.GetConstructor(constructorParameterTypes) != null)
                    {
                        ImageResourceAttribute attribute = item.GetCustomAttribute<ImageResourceAttribute>();
                        if (attribute != null)
                            imageResourceDictionary.Add(attribute.ID, item);
                    }
                }
            }
            #endregion

            Type imageResourceType = null;
            if (imageResourceDictionary.TryGetValue(id, out imageResourceType))
                return (ImageResource)Activator.CreateInstance(imageResourceType, new object[] { id, name, size, reader });
            else
                return null;
        }
        #endregion

        #region MergeChannels
        private static Bitmap MergeChannels(int width, int height, byte[] redChannel, byte[] greenChannel, byte[] blueChannel, byte[] alphaChannel)
        {
            Bitmap result = new Bitmap(width, height);

            if (alphaChannel != null)
            {
                Color color = Color.Black;
                int i = 0;
                for (int y = 0; y < height; y++)
                {
                    for (int x = 0; x < width; x++, i++)
                    {
                        color = Color.FromArgb(alphaChannel[i], redChannel[i], greenChannel[i], blueChannel[i]);
                        result.SetPixel(x, y, color);
                    }
                }
            }
            else
            {
                Color color = Color.Black;
                int i = 0;
                for (int y = 0; y < height; y++)
                {
                    for (int x = 0; x < width; x++, i++)
                    {
                        color = Color.FromArgb(255, redChannel[i], greenChannel[i], blueChannel[i]);
                        result.SetPixel(x, y, color);
                    }
                }
            }

            return result;
        }
        #endregion

        #region ParseBlendMode
        private static string ParseBlendMode(string mode)
        {
            switch (mode)
            {
                case "norm":
                    return "Normal";
                case "dark":
                    return "Darken";
                case "lite":
                    return "Lighten";
                case "mul ":
                    return "Multiply";
                case "scrn":
                    return "Screen";
                case "diff":
                    return "Difference";
                case "smud":
                    return "Exclusion";
                case "div ":
                    return "ColorDodge";
                case "idiv":
                    return "ColorBurn";
                case "lbrn":
                    return "LinearBurn";
                case "lddg":
                    return "LinearDodge";
                case "vLit":
                case "lLit":
                case "pLit":
                case "hMix":
                case "hue ":
                case "sat ":
                case "colr":
                case "lum ":
                case "diss":
                case "over":
                case "hLit":
                case "sLit":
                default:
                    return string.Empty;
            }
        }
        #endregion
        #endregion

        #region Enums
        public enum Compression
        {
            RawData = 0,
            RLECompression = 1,
            ZIPWithoutPrediction = 2,
            ZIPWithPrediction = 3,
        }

        public enum ColorModes : short
        {
            Grayscale = 1,
            Indexed = 2,
            RGB = 3,
            CMYK = 4,
            Duotone = 8,
            Lab = 9,
        }
        #endregion
    }
}
