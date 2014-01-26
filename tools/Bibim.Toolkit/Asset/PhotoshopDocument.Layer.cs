using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Drawing;
using System.Text;
using Bibim.Graphics;
using GDIGraphics = System.Drawing.Graphics;

namespace Bibim.Asset
{
    public sealed partial class PhotoshopDocument
    {
        #region ChannelID
        public enum ChannelID : short
        {
            Red = 0,
            Green = 1,
            Blue = 2,
            TransparencyMask = -1,
            UserSppliedLayerMask = -2,
            UserSppliedVectorMask = -3,
        }
        #endregion

        #region Channel
        public sealed class Channel
        {
            #region Properties
            public ChannelID ID
            {
                get;
                private set;
            }

            public uint Size
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

            public byte[] Bitmap
            {
                get;
                private set;
            }
            #endregion

            #region Constructor
            public Channel(ChannelID id, uint size)
            {
                ID = id;
                Size = size;
            }
            #endregion

            #region PixelData
            public void ReadPixelData(int width, int height, int bitsPerPixel, Reader reader)
            {
                Width = width;
                Height = height;
                BitsPerPixel = bitsPerPixel;

                // 크기 (0, 0)인 Channel도 압축여부는 기록되어 있습니다.
                Compression compression = (Compression)reader.ReadInt16();

                if (Width == 0 || Height == 0)
                    return;

                switch (compression)
                {
                    case Compression.RawData:
                        Bitmap = reader.ReadRawPixelData(Width, Height, BitsPerPixel);
                        break;
                    case Compression.RLECompression:
                        // 행별로 열의 길이가 기록되어 있습니다만 무시합니다.
                        reader.BaseStream.Position += (long)height * 2;
                        Bitmap = reader.ReadRLECompressedPixelData(Width, Height, BitsPerPixel);
                        break;
                    default:
                        throw new Exception(string.Format("{0} 로 저장된 PSD는 읽어올 수 없습니다. (프로그래머에게 연락하세요)", compression));
                }
            }

            public void SkipPixelData(int width, int height, int bitsPerPixel, Reader reader)
            {
                Width = width;
                Height = height;
                BitsPerPixel = bitsPerPixel;

                Compression compression = (Compression)reader.ReadInt16();

                if (Width == 0 || Height == 0)
                    return;

                switch (compression)
                {
                    case Compression.RawData:
                        reader.SkipRawPixelData(Width, Height, BitsPerPixel);
                        break;
                    case Compression.RLECompression:
                        // 행별로 열의 길이가 기록되어 있습니다만 무시합니다.
                        reader.BaseStream.Position += (long)height * 2;
                        reader.SkipRLECompressedPixelData(Width, Height, BitsPerPixel);
                        break;
                    default:
                        throw new Exception(string.Format("{0} 로 저장된 PSD는 읽어올 수 없습니다. (프로그래머에게 연락하세요)", compression));
                }
            }

            public byte GetPixel(int x, int y)
            {
                return Bitmap[x + (y * Width)];
            }
            #endregion
        }
        #endregion

        #region Mask
        public sealed class Mask
        {
            #region Properties
            public Rectangle Rectangle
            {
                get;
                private set;
            }

            public byte DefaultColor
            {
                get;
                private set;
            }

            public bool PositionRelativeToLayer
            {
                get;
                private set;
            }

            public bool Disabled
            {
                get;
                private set;
            }

            public bool InvertWhenBlending
            {
                get;
                private set;
            }

            public Channel Channel
            {
                get;
                private set;
            }
            #endregion

            #region Constructor
            public Mask(Rectangle rectangle, byte defaultColor, bool positionRelativeToLayer, bool disabled, bool invertWhenBlending)
            {
                Rectangle = rectangle;
                DefaultColor = defaultColor;
                PositionRelativeToLayer = positionRelativeToLayer;
                Disabled = disabled;
                InvertWhenBlending = invertWhenBlending;
            }
            #endregion

            #region PixelData
            public void ReadPixelData(Channel channel, int bitsPerPixel, Reader reader)
            {
                Channel = channel;
                Channel.ReadPixelData(Rectangle.Width, Rectangle.Height, bitsPerPixel, reader);
            }

            public void SkipPixelData(Channel channel, int bitsPerPixel, Reader reader)
            {
                Channel = channel;
                Channel.SkipPixelData(Rectangle.Width, Rectangle.Height, bitsPerPixel, reader);
            }
            #endregion
        }
        #endregion

        #region BlendMode
        public enum BlendMode
        {
            Normal,
            Dissolve,
            Darken,
            Multiply,
            ColorBurn,
            LinearBurn,
            Lighten,
            Screen,
            ColorDodge,
            LinearDodge,
            Overlay,
            SoftLight,
            HardLight,
            VividLight,
            LinearLight,
            PinLight,
            HardMix,
            Difference,
            Exclusion,
            Hue,
            Saturation,
            Color,
            Luminosity,
            Unknown,
        }
        #endregion

        #region Layer
        public sealed class Layer
        {
            #region Fields
            private List<Layer> subLayers;
            private ReadOnlyCollection<Layer> readonlySubLayers;
            private List<Channel> channels;
            private ReadOnlyCollection<Channel> readonlyChannels;
            private SortedList<ChannelID, Channel> sortedChannels;
            #endregion

            #region Properties
            public string Name
            {
                get;
                private set;
            }

            public string FullName
            {
                get
                {
                    if (Group != null)
                        return Group.FullName + "/" + Name;
                    else
                        return Name;
                }
            }

            public Layer Group
            {
                get;
                private set;
            }

            public Rectangle Rectangle
            {
                get;
                private set;
            }

            public BlendMode BlendMode
            {
                get;
                private set;
            }

            public byte Opacity
            {
                get;
                private set;
            }

            public bool Clipping
            {
                get;
                private set;
            }

            public bool TransparencyProtected
            {
                get;
                private set;
            }

            public bool Visible
            {
                get;
                private set;
            }

            public bool IsGroup
            {
                get;
                private set;
            }

            private IList<Channel> Channels
            {
                get { return readonlyChannels; }
            }

            public IList<Layer> SubLayers
            {
                get { return readonlySubLayers; }
            }

            private Mask Mask
            {
                get;
                set;
            }

            public Bitmap Bitmap
            {
                get;
                private set;
            }

            private Channel this[ChannelID id]
            {
                get { return sortedChannels[id]; }
            }
            #endregion

            #region Constructor
            public Layer(Reader reader)
            {
                subLayers = new List<Layer>();
                readonlySubLayers = new ReadOnlyCollection<Layer>(subLayers);

                #region Layer 사각영역 정보를 읽어옵니다.
                Rectangle = reader.ReadRectangle();
                #endregion

                #region Channel 정보를 읽어옵니다.
                ushort numberOfChannels = reader.ReadUInt16();
                if (numberOfChannels > 0)
                {
                    channels = new List<Channel>(numberOfChannels);
                    readonlyChannels = new ReadOnlyCollection<Channel>(channels);
                    sortedChannels = new SortedList<ChannelID, Channel>(numberOfChannels);

                    for (ushort i = 0; i < numberOfChannels; i++)
                    {
                        ChannelID channelID = (ChannelID)reader.ReadInt16();
                        uint channelSize = reader.ReadUInt32();

                        Channel newChannel = new Channel(channelID, channelSize);

                        channels.Add(newChannel);
                        sortedChannels.Add(newChannel.ID, newChannel);
                    }
                }
                #endregion

                #region Layer 기본 정보를 읽어옵니다.
                string signature = new string(reader.ReadChars(4));
                if (signature != "8BIM")
                    throw new Exception("Channel 정보가 올바르지 않습니다.");

                BlendMode = ParseBlendMode(new string(reader.ReadChars(4)));
                Opacity = reader.ReadByte();
                Clipping = reader.ReadByte() != 0;

                byte flags = reader.ReadByte();
                TransparencyProtected = (flags & (0x01 << 0)) != 0x00;
                Visible = (flags & (0x01 << 1)) == 0x00;
                IsGroup = (flags & (0x01 << 4)) != 0x00;

                reader.BaseStream.Position += 1; // 한 Byte 건너뛰기
                #endregion

                #region Layer 추가 정보를 읽어옵니다.
                uint extraDataSize = reader.ReadUInt32();
                if (extraDataSize > 0)
                {
                    long extraDataEndPosition = reader.BaseStream.Position + (long)extraDataSize;

                    #region Mask 정보를 읽어옵니다.
                    {
                        uint maskSize = reader.ReadUInt32();
                        if (maskSize > 0)
                        {
                            long maskEndPosition = reader.BaseStream.Position + (long)maskSize;

                            Rectangle maskRectangle = reader.ReadRectangle();
                            byte maskDefaultColor = reader.ReadByte();
                            byte maskFlags = reader.ReadByte();

                            bool positionRelativeToLayer = (maskFlags & (0x01 << 0)) != 0x00;
                            bool maskDisabled = (maskFlags & (0x01 << 1)) != 0x00;
                            bool maskInvertWhenBlending = (maskFlags & (0x01 << 2)) != 0x00;

                            Mask = new Mask(maskRectangle, maskDefaultColor, positionRelativeToLayer, maskDisabled, maskInvertWhenBlending);

                            reader.BaseStream.Position = maskEndPosition;
                        }
                    }
                    #endregion

                    #region Blend Ranges 정보를 읽어옵니다.
                    {
                        int blendRangesSize = reader.ReadInt32();
                        if (blendRangesSize > 0)
                        {
                            // 필요한 정보가 없으므로 건너뜁니다.
                            reader.BaseStream.Position += (long)blendRangesSize;
                        }
                    }
                    #endregion

                    #region Layer 이름을 읽어옵니다.
                    {
                        long namePosition = reader.BaseStream.Position;

                        Name = reader.ReadPSDString();

                        // 4-byte Padding 시킵니다.
                        long paddingSize = (4 - ((reader.BaseStream.Position - namePosition) % 4)) % 4;
                        reader.BaseStream.Position += paddingSize;
                    }
                    #endregion

                    #region Additional Layer 정보를 읽어옵니다.
                    ReadAdditionalInfo(reader, extraDataEndPosition);
                    #endregion

                    reader.BaseStream.Position = extraDataEndPosition;
                }
                #endregion
            }
            #endregion
            
            #region Methods
            public Layer FindSubLayer(string name, bool allSubLayers)
            {
                foreach (Layer item in SubLayers)
                {
                    if (string.Compare(item.Name, name, true) == 0)
                        return item;

                    if (allSubLayers)
                    {
                        Layer found = item.FindSubLayer(name, true);
                        if (found != null)
                            return found;
                    }
                }

                return null;
            }

            public Rectangle ComputeUnionRectangle()
            {
                Rectangle result = Rectangle;
                foreach (Layer item in subLayers)
                {
                    if (result.IsEmpty)
                        result = item.ComputeUnionRectangle();
                    else
                        result = System.Drawing.Rectangle.Union(result, item.ComputeUnionRectangle());
                }

                return result;
            }

            public void Scale(double scaleX, double scaleY)
            {
                int x = (int)((double)Rectangle.X * scaleX);
                int y = (int)((double)Rectangle.Y * scaleY);
                int w = (int)((double)Rectangle.Width * scaleY);
                int h = (int)((double)Rectangle.Height * scaleY);
                Rectangle = new Rectangle(x, y, w, h);

                if (Bitmap != null)
                {
                    var resizedBitmap = new Bitmap(Bitmap, w, h);
                    Bitmap.Dispose();
                    Bitmap = resizedBitmap;
                }

                // Mask와 Channels도 Resize해야합니다.

                foreach (var item in SubLayers)
                    item.Scale(scaleX, scaleY);
            }

            public void ClipByCanvas(int width, int height, bool clipSubLayers)
            {
                var canvasRectangle = new Rectangle(0, 0, width, height);
                var clippedRectangle = Rectangle.Intersect(canvasRectangle, Rectangle);

                if (Rectangle != clippedRectangle)
                {
                    if (clippedRectangle.Width > 0 && clippedRectangle.Height > 0)
                    {
                        if (Bitmap != null)
                        {
                            var sourceRectangle = new Rectangle(clippedRectangle.X - Rectangle.X,
                                                                clippedRectangle.Y - Rectangle.Y,
                                                                clippedRectangle.Width,
                                                                clippedRectangle.Height);

                            var trimmedRectangle = this.Bitmap.GetTrimmedRect(sourceRectangle);

                            clippedRectangle.X += trimmedRectangle.X - sourceRectangle.X;
                            clippedRectangle.Y += trimmedRectangle.Y - sourceRectangle.Y;
                            clippedRectangle.Width = trimmedRectangle.Width;
                            clippedRectangle.Height = trimmedRectangle.Height;

                            var newBitmap = new Bitmap(clippedRectangle.Width, clippedRectangle.Height);
                            using (var g = GDIGraphics.FromImage(newBitmap))
                            {
                                g.DrawImage(Bitmap,
                                            new Rectangle(0, 0, newBitmap.Width, newBitmap.Height),
                                            trimmedRectangle,
                                            GraphicsUnit.Pixel);
                            }

                            this.Bitmap.Dispose();
                            this.Bitmap = newBitmap;
                        }
                    }
                    else
                        Bitmap = null;

                    Rectangle = clippedRectangle;
                }
                
                if (clipSubLayers)
                {
                    foreach (var item in SubLayers)
                        item.ClipByCanvas(width, height, true);
                }
            }

            internal void AddSubLayer(Layer item)
            {
                if (item.Group == this)
                    return;

                if (item.Group != null)
                    item.Group.subLayers.Remove(item);

                item.Group = this;
                subLayers.Add(item);
            }

            internal void ReadPixelData(int bitsPerPixel, Reader reader)
            {
                foreach (Channel channel in Channels)
                {
                    if (channel.ID == ChannelID.UserSppliedLayerMask || channel.ID == ChannelID.UserSppliedVectorMask)
                        continue;

                    channel.ReadPixelData(Rectangle.Width, Rectangle.Height, bitsPerPixel, reader);
                }

                if (Rectangle.IsEmpty == false)
                {
                    if (sortedChannels.ContainsKey(ChannelID.TransparencyMask))
                    {
                        Bitmap = MergeChannels(Rectangle.Width, Rectangle.Height,
                                               this[ChannelID.Red].Bitmap,
                                               this[ChannelID.Green].Bitmap,
                                               this[ChannelID.Blue].Bitmap,
                                               this[ChannelID.TransparencyMask].Bitmap);
                    }
                    else
                    {
                        Bitmap = MergeChannels(Rectangle.Width, Rectangle.Height,
                                               this[ChannelID.Red].Bitmap,
                                               this[ChannelID.Green].Bitmap,
                                               this[ChannelID.Blue].Bitmap,
                                               null);
                    }
                }

                if (Mask != null)
                {
                    Mask.ReadPixelData(sortedChannels[ChannelID.UserSppliedLayerMask], bitsPerPixel, reader);
                }
            }

            internal void SkipPixelData(int bitsPerPixel, Reader reader)
            {
                foreach (Channel channel in Channels)
                {
                    if (channel.ID == ChannelID.UserSppliedLayerMask || channel.ID == ChannelID.UserSppliedVectorMask)
                        continue;

                    channel.SkipPixelData(Rectangle.Width, Rectangle.Height, bitsPerPixel, reader);
                }

                if (Mask != null)
                    Mask.SkipPixelData(sortedChannels[ChannelID.UserSppliedLayerMask], bitsPerPixel, reader);
            }

            private void ReadAdditionalInfo(Reader reader, long extraDataEndPosition)
            {
                while (reader.BaseStream.Position < extraDataEndPosition)
                {
                    string signature = new string(reader.ReadChars(4));
                    if (signature != "8BIM")
                        return;

                    string fourcc = new string(reader.ReadChars(4));
                    uint size = reader.ReadUInt32();
                    long endPosition = reader.BaseStream.Position + (long)size;
                    switch (fourcc)
                    {
                        case "luni": Read_luni(reader, size); break;
                        // case "TySh": Read_TySh(reader, size); break;
                    }

                    reader.BaseStream.Position = endPosition;
                }
            }

            private void Read_luni(Reader reader, uint size)
            {
                // 기본 정보에서 레이어 이름은 31자까지 저장되고,
                // 추가 정보에서 레이어의 풀네임이 기록됩니다.
                // 그렇기 때문에 luni 추가 정보가 있으면 이름을 대체합니다.

                uint stringLength = reader.ReadUInt32();
                byte[] buffer = reader.ReadBytes((int)stringLength * 2);

                Name = Encoding.BigEndianUnicode.GetString(buffer);
            }

            /*
            private void Read_TySh(Reader reader, uint size)
            {
                ushort version = reader.ReadUInt16();
                double xx = reader.ReadDouble();
                double xy = reader.ReadDouble();
                double yz = reader.ReadDouble();
                double yy = reader.ReadDouble();
                double tx = reader.ReadDouble();
                double ty = reader.ReadDouble();
                ushort textVersion = reader.ReadUInt16();
                uint descriptorVersion = reader.ReadUInt32();
                ReadDescriptor(reader);
                version = version;
                xx = xx;
                xy = xy;
                yz = yz;
                yy = yy;
                tx = tx;
                ty = ty;
                textVersion = textVersion;
                descriptorVersion = descriptorVersion;
            }

            private void ReadDescriptor(Reader reader)
            {
                uint nameLength = reader.ReadUInt32();
                byte[] nameBuffer = reader.ReadBytes((int)nameLength * 2);
                string name = Encoding.Default.GetString(nameBuffer);
                nameLength = nameLength;
                nameBuffer = nameBuffer;
                name = name;

                uint classIDLength = reader.ReadUInt32();
                uint classID = 0;
                string classIDName = string.Empty;
                if (classIDLength == 0)
                    classID = reader.ReadUInt32();
                else
                {
                    byte[] classIDBuffer = reader.ReadBytes((int)classIDLength);
                    classIDName = Encoding.Default.GetString(classIDBuffer);
                }
                classID = classID;
                uint numberOfItems = reader.ReadUInt32();
                for (uint i = 0; i < numberOfItems; i++)
                {
                    uint keyLength = reader.ReadUInt32();
                    uint key = 0;
                    string keyName = string.Empty;
                    if (keyLength == 0)
                        key = reader.ReadUInt32();
                    else
                    {
                        byte[] keyBuffer = reader.ReadBytes((int)keyLength);
                        keyName = Encoding.Default.GetString(keyBuffer);
                    }

                    string osType = new string(reader.ReadChars(4));
                    switch (osType)
                    {
                        case "TEXT":
                            uint valueLength = reader.ReadUInt32();
                            byte[] valueBuffer = reader.ReadBytes((int)valueLength * 2);
                            string s = Encoding.BigEndianUnicode.GetString(valueBuffer);
                            s = s;
                            break;
                        case "enum":
                            uint typeLength = reader.ReadUInt32();
                            uint type = 0;
                            string typeName = "";
                            if (typeLength == 0)
                                type = reader.ReadUInt32();
                            else
                            {
                                typeName = new string(reader.ReadChars((int)typeLength));
                            }
                            type = type;
                            typeName = typeName;

                            uint enumLength = reader.ReadUInt32();
                            uint enum_ = 0;
                            string enumName = "";
                            if (enumLength == 0)
                                enum_ = reader.ReadUInt32();
                            else
                            {
                                enumName = new string(reader.ReadChars((int)enumLength));
                            }
                            enum_ = enum_;
                            enumName = enumName;
                            break;
                    }

                    key = key;
                    keyName = keyName;
                    osType = osType;

                }
            }
             * */

            public override string ToString()
            {
                return FullName;
            }
            #endregion
        }
        #endregion

        #region ParseBlendMode
        private static BlendMode ParseBlendMode(string mode)
        {
            switch (mode)
            {
                case "norm":
                    return BlendMode.Normal;
                case "diss":
                    return BlendMode.Dissolve;
                case "dark":
                    return BlendMode.Darken;
                case "mul ":
                    return BlendMode.Multiply;
                case "idiv":
                    return BlendMode.ColorBurn;
                case "lbrn":
                    return BlendMode.LinearBurn;
                case "lite":
                    return BlendMode.Lighten;
                case "scrn":
                    return BlendMode.Screen;
                case "div ":
                    return BlendMode.ColorDodge;
                case "lddg":
                    return BlendMode.LinearDodge;
                case "over":
                    return BlendMode.Overlay;
                case "sLit":
                    return BlendMode.SoftLight;
                case "hLit":
                    return BlendMode.HardLight;
                case "vLit":
                    return BlendMode.VividLight;
                case "lLit":
                    return BlendMode.LinearLight;
                case "pLit":
                    return BlendMode.PinLight;
                case "hMix":
                    return BlendMode.HardMix;
                case "diff":
                    return BlendMode.Difference;
                case "smud":
                    return BlendMode.Exclusion;
                case "hue ":
                    return BlendMode.Hue;
                case "sat ":
                    return BlendMode.Saturation;
                case "colr":
                    return BlendMode.Color;
                case "lum ":
                    return BlendMode.Luminosity;
                default:
                    return BlendMode.Unknown;
            }
        }
        #endregion
    }
}
