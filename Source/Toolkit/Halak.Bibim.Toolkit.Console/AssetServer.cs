using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.IO.Compression;
using System.IO.Pipes;
using System.Linq;
using System.Text;
using System.Threading;
using C = System.Console;
using Halak.Bibim.Asset;
using Halak.Bibim.Asset.Pipeline;
using Halak.Bibim.Asset.Pipeline.Cook;
using Halak.Bibim.IO;
using System.Xml;
using System.Xml.Serialization;

namespace Halak.Bibim.Toolkit.Console
{
    public sealed class AssetServer
    {
        static string pipeName;
        static string assetDirectory;
        
        static void Main(string[] args)
        {
            AssetRecipe recipe = new AssetRecipe();
            recipe.Result = "Main";
            recipe.Directions.Add(new ImportBitmap("$(self.filename).psd", "Main"));
            recipe.Directions.Add(new BitmapToTexture2D("Main", "Main"));

            XmlSerializer xml = new XmlSerializer(recipe.GetType(), new Type[]{typeof(ImportBitmap),typeof(BitmapToTexture2D)})
            {
              
            };
            FileStream fs = new FileStream("AAA.txt", FileMode.Create, FileAccess.Write);
            XmlTextWriter w = new XmlTextWriter(fs, Encoding.UTF8)
            {
                Formatting = Formatting.Indented,
                Indentation = 1,
                IndentChar = '\t',
            };
            xml.Serialize(w, recipe);
            w.Close();


            C.Title = "Halak Bibim Console > AssetServer";
            C.WriteLine("================================");
            C.WriteLine("Halak Bibim Asset Server");
            C.WriteLine("================================");
            C.WriteLine("Ready");

            pipeName = GetArgument("Pipe Name", args, 0);
            assetDirectory = GetArgument("Asset Directory", args, 1);

            NamedPipeServerStream serverPipe = new NamedPipeServerStream(pipeName, PipeDirection.InOut);
            BinaryReader serverPipeReader = new BinaryReader(serverPipe);

            byte[] buffer = new byte[4096];
            for (; ; )
            {
                if (serverPipe.IsConnected == false)
                    serverPipe.WaitForConnection();
                
                uint id = serverPipeReader.ReadUInt32();
                switch (id)
                {
                    case 1000:
                        LoadAsset(serverPipeReader.ReadBibimString());
                        break;
                    default:
                        break;
                }
            }
        }

        static string GetArgument(string argumentName, string[] args, int index)
        {
            if (args.Length >= index+1 && string.IsNullOrEmpty(args[index]) == false)
            {
                C.WriteLine("{0} : {1}", argumentName, args[index]);
                return args[index];
            }
            else
            {
                string result = string.Empty;
                C.Write("{0} : ", argumentName);
                result = C.ReadLine().Trim();

                if (string.IsNullOrEmpty(result))
                {
                    C.WriteLine("{0} is empty. byebye", argumentName);
                    throw new ArgumentException(string.Empty, argumentName);
                }

                return result;
            }
        }

        static void LoadAsset(string assetName)
        {
            using (Bitmap asset = (Bitmap)Bitmap.FromFile(Path.Combine(assetDirectory, assetName)))
            {
                MemoryStream assetStream = new MemoryStream();
                BinaryWriter assetStreamWriter = new BinaryWriter(assetStream);
                Rectangle wholeBitmapRect = new Rectangle(0, 0, asset.Width, asset.Height);
                BitmapData bitmapData = asset.LockBits(wholeBitmapRect, ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb, new BitmapData());

                assetStreamWriter.Write(FOURCC.Make('S', 'T', 'X', '2'));
                assetStreamWriter.Write((uint)0);
                assetStreamWriter.Write((short)bitmapData.Width);
                assetStreamWriter.Write((short)bitmapData.Height);
                assetStreamWriter.Write(bitmapData.Stride);

                byte[] destination = new byte[bitmapData.Stride * bitmapData.Height];
                unsafe
                {
                    byte* source = (byte*)bitmapData.Scan0.ToPointer();
                    for (int i = 0; i < destination.Length; i++)
                        destination[i] = source[i];
                }
                assetStreamWriter.Write(destination);

                asset.UnlockBits(bitmapData);
                
                byte[] buffer = assetStream.GetBuffer();

                NamedPipeServerStream serverStream = new NamedPipeServerStream(pipeName + "_" + assetName,
                                                                               PipeDirection.Out,
                                                                               NamedPipeServerStream.MaxAllowedServerInstances,
                                                                               PipeTransmissionMode.Byte,
                                                                               PipeOptions.Asynchronous);
                serverStream.WaitForConnection();
                serverStream.BeginWrite(buffer, 0, buffer.Length, new AsyncCallback(AssetWriteCompleted), serverStream);

                FileStream stream = new FileStream(Path.ChangeExtension(Path.Combine(assetDirectory, assetName), "cas"), FileMode.Create, FileAccess.Write);
                stream.Write(buffer, 0, buffer.Length);
                stream.Close();
                
                assetStream.Close();

            }
        }

            static void AssetWriteCompleted(IAsyncResult ar)
            {
                NamedPipeServerStream stream = (NamedPipeServerStream)ar.AsyncState;
                stream.Disconnect();
                stream.Close();
            }

            //Thread th = new Thread(delegate(object assetNameObject)
            //{
            //    string assetName = assetName_;// (string)assetNameObject;
            //    using (Bitmap image = (Bitmap)Bitmap.FromFile(Path.Combine(assetDirectory, assetName)))
            //    {
            //        NamedPipeServerStream assetStream = new NamedPipeServerStream(pipeName + "_" + assetName, PipeDirection.Out);
            //        BinaryWriter assetStreamWriter = new BinaryWriter(assetStream);
            //        assetStream.WaitForConnection();

            //        BitmapData bitmapData = image.LockBits(new Rectangle(0, 0, image.Width, image.Height), ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb, new BitmapData());

            //        assetStreamWriter.Write(FOURCC.Make('S', 'T', 'X', '2'));
            //        assetStreamWriter.Write((uint)0);
            //        assetStreamWriter.Write((short)bitmapData.Width);
            //        assetStreamWriter.Write((short)bitmapData.Height);
            //        assetStreamWriter.Write(bitmapData.Stride);

            //        byte[] destination = new byte[bitmapData.Stride * bitmapData.Height];
            //        unsafe
            //        {
            //            byte* source = (byte*)bitmapData.Scan0.ToPointer();
            //            for (int i = 0; i < destination.Length; i++)
            //                destination[i] = source[i];
            //        }
            //        assetStreamWriter.Write(destination);

            //        image.UnlockBits(bitmapData);
            //        assetStream.Dispose();
            //    }
            //}
            //    });
            //th.Start(assetName_);
       // }
    }
}
