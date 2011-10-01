using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Diagnostics;
using System.IO;
using System.IO.Compression;
using System.IO.Pipes;
using System.Linq;
using System.Text;
using System.Threading;
using Halak.Bibim.Asset;
using Halak.Bibim.Asset.Pipeline;
using Halak.Bibim.Asset.Pipeline.Recipes;
using Halak.Bibim.IO;
using System.Xml;
using System.Xml.Serialization;

namespace Halak.Bibim.Toolkit.Workbench.Consoles
{
    public sealed class AssetServer : ConsoleProgram
    {
        #region Fields
        private string pipeName;
        #endregion

        #region Properties
        public string PipeName
        {
            get { return pipeName; }
            set
            {
                pipeName = value ?? string.Empty;
            }
        }
        #endregion

        #region Constructors
        public AssetServer()
        {
            PipeName = string.Empty;
        }
        #endregion

        public override void Run()
        {
            Trace.WriteLine("================================");
            Trace.WriteLine("Halak Bibim Asset Server");
            Trace.WriteLine("================================");
            Trace.WriteLine("Ready");

            GameModuleTree modules = new GameModuleTree();
            
            GameAssetKitchen assetKitchen = new GameAssetKitchen();
            PipedGameAssetServer assetServer = new PipedGameAssetServer(assetKitchen, PipeName);
            modules.Root.AttachChild(assetKitchen);
            modules.Root.AttachChild(assetServer);
            
            for (; ; )
            {
                System.Threading.Thread.Sleep(100);
            }
        }
    }
}
