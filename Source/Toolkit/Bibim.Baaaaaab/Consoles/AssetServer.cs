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
using Bibim;
using Bibim.Asset;
using Bibim.Asset.Pipeline;
using Bibim.Asset.Pipeline.Recipes;
using Bibim.IO;
using Bibim.Toolkit;

namespace Bibim.Bab.Consoles
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

                    if (command.StartsWith("deletecache "))
                    {
                        int numberOfDeletedFiles = 0;
                        string path = command.Substring("deletecache ".Length).Trim();
                        try
                        {
                            string[] files = Directory.GetFiles(path, "*." + GameAsset.BinaryFileExtension, SearchOption.AllDirectories);
                            foreach (string item in files)
                            {
                                try
                                {
                                    File.Delete(item);
                                    numberOfDeletedFiles++;
                                }
                                catch (Exception ex)
                                {
                                    Trace.WriteLine(ex);
                                }
                            }
                        }
                        catch (Exception ex)
                        {
                            Trace.WriteLine(ex);
                        }

                        Trace.TraceInformation("Asset cache deleted ({0}).", numberOfDeletedFiles);
                    }

                    if (command.StartsWith("precook "))
                    {
                        Precook(assetServer, command.Substring("precook ".Length).Trim());
                    }

                    if (command.StartsWith("precook_and_compress "))
                    {
                        int index1 = "precook_and_compress ".Length;
                        int index2 = command.IndexOf(">>", index1);

                        string directory = command.Substring(index1, index2 - index1);
                        string zipFilePath = Path.ChangeExtension(command.Substring(index2 + ">>".Length), "zip");
                        Precook(assetServer, directory);

                        Trace.WriteLine("Begin Create ZIP");
                        using (var zipFile = new Ionic.Zip.ZipFile())
                        {
                            string[] files = Directory.GetFiles(directory, "*." + GameAsset.BinaryFileExtension, SearchOption.AllDirectories);
                        }
                    }
                }
                else
                    System.Threading.Thread.Sleep(10);
            }

            assetServer.Alive = false;
            Trace.TraceInformation("AssetServer closed.");
        }

        private static void Precook(GameAssetServer assetServer, string directory)
        {
            try
            {
                string[] files = Directory.GetFiles(directory, "*." + GameAsset.TextFileExtension, SearchOption.AllDirectories);
                int countingIndex = files.Length / 10;
                for (int i = 0, k = 0; i < files.Length; i++, k++)
                {
                    try
                    {
                        string assetPath = files[i].Substring(directory.Length + 1);

                        if (i == files.Length - 1)
                        {
                            assetServer.Precook(directory, assetPath, (_, __, ___) => { Trace.TraceInformation("LAST COOKING!"); }, () => { Trace.TraceInformation("LAST COOKING!"); });
                        }
                        else if (k == countingIndex)
                        {
                            k = 0;
                            int count = i;
                            assetServer.Precook(directory, assetPath, (_, __, ___) => { Trace.TraceInformation("({0}/{1})", count, files.Length); }, () => { Trace.TraceInformation("({0}/{1})", count, files.Length); });
                        }
                        else
                        {
                            assetServer.Precook(directory, assetPath);
                        }
                    }
                    catch (Exception ex)
                    {
                        Trace.WriteLine(ex);
                    }
                }
            }
            catch (Exception ex)
            {
                Trace.WriteLine(ex);
            }
        }
    }
}
