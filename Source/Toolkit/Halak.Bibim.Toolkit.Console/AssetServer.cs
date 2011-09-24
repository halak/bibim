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
using Halak.Bibim.Asset.Pipeline.Recipes;
using Halak.Bibim.IO;
using System.Xml;
using System.Xml.Serialization;

namespace Halak.Bibim.Toolkit.Console
{
    public sealed class AssetServer
    {
        static string pipeName;
        
        static void Main(string[] args)
        {
            C.Title = "Halak Bibim Console > AssetServer";
            C.WriteLine("================================");
            C.WriteLine("Halak Bibim Asset Server");
            C.WriteLine("================================");
            C.WriteLine("Ready");

            pipeName = GetArgument("Pipe Name", args, 0);

            System.Diagnostics.Trace.Listeners.Add(ConsoleTraceListener.Instance);

            GameModuleTree modules = new GameModuleTree();
            
            GameAssetKitchen assetKitchen = new GameAssetKitchen();
            PipedGameAssetServer assetServer = new PipedGameAssetServer(assetKitchen, pipeName);
            modules.Root.AttachChild(assetKitchen);
            modules.Root.AttachChild(assetServer);
            
            for (; ; )
            {
            }

            System.Diagnostics.Trace.Listeners.Remove(ConsoleTraceListener.Instance);

            //NamedPipeServerStream serverPipe = new NamedPipeServerStream(pipeName, PipeDirection.InOut);
            //BinaryReader serverPipeReader = new BinaryReader(serverPipe);

            //byte[] buffer = new byte[4096];
            //for (; ; )
            //{
            //    if (serverPipe.IsConnected == false)
            //        serverPipe.WaitForConnection();
                
            //    uint id = serverPipeReader.ReadUInt32();
            //    switch (id)
            //    {
            //        case 1000:
            //            LoadAsset(serverPipeReader.ReadBibimString());
            //            break;
            //        default:
            //            break;
            //    }
            //}
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
    }
}
