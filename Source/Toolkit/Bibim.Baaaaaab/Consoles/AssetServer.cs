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

using Bibim.Animation;

namespace Bibim.Bab.Consoles
{
    [ConsoleEntryPoint]
    [Alias("assetsvr")]
    public static class AssetServer
    {
        static void Run([Alias("pipe")] string pipeName)
        {
            var shakeAmount1 = new EvalFloatInterpolator()
            {
                Value1 = new EvalFloatConstant(50.0f),
                Value2 = new EvalFloatConstant(100.0f),
                Weight = new EvalUnitRandom(EvalUnitRandom.GenerationCycle.ResetOrManual),
            };
            var shakeAmount2 = new EvalFloatNegation()
            {
                Operand = shakeAmount1,
            };
            var shakeAnimation1 = new EvalFloatInterpolator()
            {
                Value1 = new EvalFloatConstant(0.0f),
                Value2 = shakeAmount1,
                Weight = new EvalTimeflow(1.0f),
            };
            var shakeAnimation2 = new EvalFloatInterpolator()
            {
                Value1 = shakeAmount1,
                Value2 = shakeAmount2,
                Weight = new EvalTimeflow(1.0f),
            };

            //seq.AddKeyframe(new Keyframe<bool>(true, 1.0f));
            //seq.AddKeyframe(new Keyframe<bool>(false, 0.7f));
            //seq.AddKeyframe(new Keyframe<bool>(true, 0.3f));
            
            //XmlSerializer serz = new XmlSerializer(typeof(object));//typeof(BoolSequence), new Type[]{typeof(Keyframe<bool>)});
            ////using (var fs = new FileStream("Hello.xml", FileMode.Create, FileAccess.Write))
            ////    serz.Serialize(fs, seq);
            //using (var fs = new FileStream("Hello.xml", FileMode.Open, FileAccess.Read))
            //{
            //    object o = serz.Deserialize(fs);
            //}


            ////GameAssetRecipe recipe = new GameAssetRecipe();
            ////recipe.Cook = new ReadGameAsset(seq);
            ////GameAssetRecipe.Serialize("Hello.asset", recipe);

            if (string.IsNullOrEmpty(pipeName))
                pipeName = PipedAssetProvider.DefaultPipeName;

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
                        int index1 = "precook ".Length;
                        int index2 = command.IndexOf(">>", index1);
                        if (index2 == -1)
                            Precook(assetServer, command.Substring(index1).Trim());
                        else
                        {
                            Precook(assetServer,
                                    command.Substring(index1, index2 - index1).Trim(),
                                    command.Substring(index2 + ">>".Length).Trim());
                        }
                    }

                    if (command.StartsWith("compress "))
                    {
                        int index1 = "compress ".Length;
                        int index2 = command.IndexOf(">>", index1);

                        string directory = command.Substring(index1, index2 - index1).Trim();
                        string zipFilePath = Path.ChangeExtension(command.Substring(index2 + ">>".Length), "zip").Trim();
                        Compress(directory, zipFilePath);
                    }


                    if (command.StartsWith("precook_and_compress "))
                    {
                        int index1 = "precook_and_compress ".Length;
                        int index2 = command.IndexOf(">>", index1);

                        string directory = command.Substring(index1, index2 - index1).Trim();
                        string zipFilePath = Path.ChangeExtension(command.Substring(index2 + ">>".Length), "zip").Trim();
                        Precook(assetServer, directory);
                        Compress(directory, zipFilePath);
                    }
                }
                else
                    System.Threading.Thread.Sleep(10);
            }

            assetServer.Alive = false;
            Trace.TraceInformation("AssetServer closed.");
        }

        private static void Precook(GameAssetServer assetServer, string path)
        {
            try
            {
                string[] files = Directory.GetFiles(path, "*." + GameAsset.TextFileExtension, SearchOption.AllDirectories);
                int countingIndex = files.Length / 10;
                for (int i = 0, k = 0; i < files.Length; i++, k++)
                {
                    try
                    {
                        string assetPath = files[i].Substring(path.Length + 1);

                        if (i == files.Length - 1)
                        {
                            assetServer.Precook(path, assetPath, (_, __, ___) => { Trace.TraceInformation("LAST COOKING!"); }, () => { Trace.TraceInformation("LAST COOKING!"); });
                        }
                        else if (k == countingIndex)
                        {
                            k = 0;
                            int count = i;
                            assetServer.Precook(path, assetPath, (_, __, ___) => { Trace.TraceInformation("({0}/{1})", count, files.Length); }, () => { Trace.TraceInformation("({0}/{1})", count, files.Length); });
                        }
                        else
                        {
                            assetServer.Precook(path, assetPath);
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

            while (assetServer.IsBusy)
                Thread.Sleep(100);
        }

        private static void Precook(GameAssetServer assetServer, string directory, string assetPath)
        {
            try
            {
                assetServer.Precook(directory, assetPath);
            }
            catch (Exception ex)
            {
                Trace.WriteLine(ex);
            }

            while (assetServer.IsBusy)
                Thread.Sleep(100);
        }

        private static void Compress(string directory, string zipFilePath)
        {
            using (var zipFile = new Ionic.Zip.ZipFile())
            {
                string[] files = Directory.GetFiles(directory, "*." + GameAsset.BinaryFileExtension, SearchOption.AllDirectories);
                foreach (string item in files)
                    zipFile.AddFile(item, Path.GetDirectoryName(item.Substring(directory.Length + 1)));

                Trace.WriteLine("Begin ZIP Creation");
                zipFile.Save(Path.Combine(directory, zipFilePath));
            }

            Trace.TraceInformation("ZIP FILE Created! {0}", zipFilePath);
        }
    }
}
