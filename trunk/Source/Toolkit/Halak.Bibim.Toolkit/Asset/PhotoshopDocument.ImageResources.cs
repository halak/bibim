using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;

namespace Halak.Bibim.Asset
{
    public sealed partial class PhotoshopDocument
    {
        #region ImageResourceID
        public enum ImageResourceID : short
        {
            Undefined = 0,
            MacPrintInfo = 1001,
            ResolutionInfo = 1005,
            AlphaChannelNames = 1006,
            DisplayInfo = 1007,
            Caption = 1008,
            BorderInfo = 1009,
            BgColor = 1010,
            PrintFlags = 1011,
            MultiChannelHalftoneInfo = 1012,
            ColorHalftoneInfo = 1013,
            DuotoneHalftoneInfo = 1014,
            MultiChannelTransferFunctions = 1015,
            ColorTransferFunctions = 1016,
            DuotoneTransferFunctions = 1017,
            DuotoneImageInfo = 1018,
            BlackWhiteRange = 1019,
            EPSOptions = 1021,
            QuickMaskInfo = 1022, //2 bytes containing Quick Mask channel ID, 1 byte boolean indicating whether the mask was initially empty.
            LayerStateInfo = 1024, //2 bytes containing the index of target layer. 0=bottom layer.
            WorkingPathUnsaved = 1025,
            LayersGroupInfo = 1026, //2 bytes per layer containing a group ID for the dragging groups. Layers in a group have the same group ID.
            IPTC_NAA = 1028,
            RawFormatImageMode = 1029,
            JPEGQuality = 1030,
            GridGuidesInfo = 1032,
            Thumbnail1 = 1033,
            CopyrightInfo = 1034,
            URL = 1035,
            Thumbnail2 = 1036,
            GlobalAngle = 1037,
            ColorSamplers = 1038,
            ICCProfile = 1039, //The raw bytes of an ICC format profile, see the ICC34.pdf and ICC34.h files from the Internation Color Consortium located in the documentation section
            Watermark = 1040,
            ICCUntagged = 1041, //1 byte that disables any assumed profile handling when opening the file. 1 = intentionally untagged.
            EffectsVisible = 1042, //1 byte global flag to show/hide all the effects layer. Only present when they are hidden.
            SpotHalftone = 1043, // 4 bytes for version, 4 bytes for length, and the variable length data.
            DocumentSpecific = 1044,
            UnicodeAlphaNames = 1045, // 4 bytes for length and the string as a unicode string
            IndexedColorTableCount = 1046, // 2 bytes for the number of colors in table that are actually defined
            TransparentIndex = 1047,
            GlobalAltitude = 1049,  // 4 byte entry for altitude
            Slices = 1050,
            WorkflowURL = 1051, //Unicode string, 4 bytes of length followed by unicode string
            JumpToXPEP = 1052, //2 bytes major version, 2 bytes minor version,
            //4 bytes count. Following is repeated for count: 4 bytes block size,
            //4 bytes key, if key = 'jtDd' then next is a Boolean for the dirty flag
            //otherwise it뭩 a 4 byte entry for the mod date
            AlphaIdentifiers = 1053, //4 bytes of length, followed by 4 bytes each for every alpha identifier.
            URLList = 1054, //4 byte count of URLs, followed by 4 byte long, 4 byte ID, and unicode string for each count.
            VersionInfo = 1057, //4 byte version, 1 byte HasRealMergedData, unicode string of writer name, unicode string of reader name, 4 bytes of file version.
            Unknown4 = 1058, //pretty long, 302 bytes in one file. Holds creation date, maybe Photoshop license number
            XMLInfo = 1060, //some kind of XML definition of file. The xpacket tag seems to hold binary data
            Unknown = 1061, //seems to be common!
            Unknown2 = 1062, //seems to be common!
            Unknown3 = 1064, //seems to be common!
            PathInfo = 2000, //2000-2999 actually I think?
            ClippingPathName = 2999,
            PrintFlagsInfo = 10000
        }
        #endregion

        #region ImageResource
        public abstract class ImageResource
        {
            #region Properties
            public ImageResourceID ID
            {
                get;
                private set;
            }

            public string Name
            {
                get;
                private set;
            }
            #endregion

            #region Constructor
            public ImageResource(ImageResourceID id, string name)
            {
                ID = id;
                Name = name;
            }
            #endregion
        }

        [AttributeUsage(AttributeTargets.Class, AllowMultiple = false, Inherited = false)]
        public sealed class ImageResourceAttribute : Attribute
        {
            #region Properties
            public ImageResourceID ID
            {
                get;
                private set;
            }
            #endregion

            #region Constructor
            public ImageResourceAttribute(ImageResourceID id)
            {
                ID = id;
            }
            #endregion
        }
        #endregion

        #region ResolutionInfo
        [ImageResource(ImageResourceID.ResolutionInfo)]
        public sealed class ResolutionInfo : ImageResource
        {
            #region Properties
            public short HorizontalResolution
            {
                get;
                private set;
            }

            public short VerticalResolution
            {
                get;
                private set;
            }

            public ResolutionUnit HorizontalResolutionUnit
            {
                get;
                private set;
            }

            public ResolutionUnit VerticalResolutionUnit
            {
                get;
                private set;
            }

            public Unit WidthUnit
            {
                get;
                private set;
            }

            public Unit HeightUnit
            {
                get;
                private set;
            }
            #endregion

            #region Constructor
            public ResolutionInfo(ImageResourceID id, string name, uint size, Reader reader)
                : base(id, name)
            {
                HorizontalResolution = reader.ReadInt16();
                HorizontalResolutionUnit = (ResolutionUnit)reader.ReadInt32();
                WidthUnit = (Unit)reader.ReadInt16();

                VerticalResolution = reader.ReadInt16();
                VerticalResolutionUnit = (ResolutionUnit)reader.ReadInt32();
                HeightUnit = (Unit)reader.ReadInt16();
            }
            #endregion

            #region Enumeration
            public enum ResolutionUnit
            {
                PixelPerInch = 1,
                PixelPerCent = 2,
            }

            public enum Unit : short
            {
                Inch = 1,
                CentiMeter = 2,
                Point = 3,
                Picas = 4,
                Columns = 5
            }
            #endregion
        }
        #endregion

        #region AlphaChannelNames
        [ImageResource(ImageResourceID.AlphaChannelNames)]
        public sealed class AlphaChannelNames : ImageResource
        {
            #region Fields
            private List<string> names;
            private ReadOnlyCollection<string> readonlyNames;
            #endregion

            #region Properties
            public IList<string> Names
            {
                get { return readonlyNames; }
            }
            #endregion

            #region Constructor
            public AlphaChannelNames(ImageResourceID id, string name, uint size, Reader reader)
                : base(id, name)
            {
                names = new List<string>();
                readonlyNames = new ReadOnlyCollection<string>(names);

                long endPosition = reader.BaseStream.Position + (long)size;
                while (reader.BaseStream.Position < endPosition)
                {
                    string channelName = reader.ReadPSDString();
                    if (channelName.Length > 0)
                        names.Add(channelName);
                }
            }
            #endregion
        }
        #endregion
    }
}
