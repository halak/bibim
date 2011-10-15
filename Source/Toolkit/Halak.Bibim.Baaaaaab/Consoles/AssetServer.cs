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
            Trace.WriteLine(string.Format("Ready : {0}", pipeName));

            GameModuleTree modules = new GameModuleTree();
            GameAssetStorage assetStorage = new GameAssetStorage();
            GameAssetKitchen assetKitchen = new GameAssetKitchen(assetStorage);
            PipedGameAssetServer assetServer = new PipedGameAssetServer(assetKitchen, pipeName);
            modules.Root.AttachChild(assetStorage);
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
