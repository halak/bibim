using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.IO.Compression;
using System.IO.Pipes;
using System.Text;
using System.Threading;
using System.Xml;
using System.Xml.Serialization;
using Halak.Bibim;
using Halak.Bibim.Asset;
using Halak.Bibim.Asset.Pipeline;
using Halak.Bibim.Asset.Pipeline.Recipes;
using Halak.Bibim.IO;
using Halak.Bibim.Toolkit;

namespace Halak.Bibim.Bab.Consoles
{
    [ConsoleEntryPoint]
    [Alias("assetsvr")]
    public static class AssetServer
    {
        static void Run([Alias("pipe")] string pipeName)
        {
            if (string.IsNullOrEmpty(pipeName))
                throw new ArgumentException("pipeName");

            Trace.WriteLine("================================");
            Trace.WriteLine("Halak Bibim Asset Server");
            Trace.WriteLine("================================");
            Trace.WriteLine("Ready");

            GameModuleTree modules = new GameModuleTree();
            
            GameAssetKitchen assetKitchen = new GameAssetKitchen();
            PipedGameAssetServer assetServer = new PipedGameAssetServer(assetKitchen, pipeName);
            modules.Root.AttachChild(assetKitchen);
            modules.Root.AttachChild(assetServer);

            bool closed = false;
            while (closed == false)
            {
                string command;
                if (ConsoleWindow.CommandQueue.TryDequeue(out command))
                {
                    switch (command.ToLower())
                    {
                        case "clear":
                        case "cls":
                            break;
                        case "exit":
                            closed = true;
                            break;
                    }
                }
                else
                    System.Threading.Thread.Sleep(10);
            }

            assetServer.Alive = false;
        }
    }
}
