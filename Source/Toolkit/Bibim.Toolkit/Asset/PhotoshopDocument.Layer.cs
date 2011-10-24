using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Drawing;
using System.Text;

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
            #endregion
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

            public string BlendMode
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

            public IList<Channel> Channels
            {
                get { return readonlyChannels; }
            }

            public IList<Layer> SubLayers
            {
                get { return readonlySubLayers; }
            }

            public Mask Mask
            {
                get;
                private set;
            }

            public Bitmap Bitmap
            {
                get;
                private set;
            }

            public Channel this[ChannelID id]
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

                BlendMode = new string(reader.ReadChars(4));
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
                        long paddingSize = (reader.BaseStream.Position - namePosition) % 4;
                        reader.BaseStream.Position += paddingSize;
                    }
                    #endregion

                    #region Adjustment 정보를 읽어옵니다.
                    {
                    }
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
            #endregion
        }
        #endregion
    }
}
