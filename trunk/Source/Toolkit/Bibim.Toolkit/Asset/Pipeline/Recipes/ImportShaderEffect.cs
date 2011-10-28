using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using Bibim.Graphics;

namespace Bibim.Asset.Pipeline.Recipes
{
    public sealed class ImportShaderEffect : CookingNode<ShaderEffect>
    {
        #region Properties
        [XmlElement]
        public CookingNode<Stream> Input
        {
            get;
            set;
        }
        #endregion

        #region Constructor
        public ImportShaderEffect()
        {
        }

        public ImportShaderEffect(CookingNode<Stream> input)
        {
            Input = input;
        }
        #endregion

        public override ShaderEffect Cook(CookingContext context)
        {
            Stream stream = Input.Cook(context);
            StreamReader reader = new StreamReader(stream);
            string text = reader.ReadToEnd();
            reader.Close();

            string inputFXFileName = Path.GetTempFileName();
            string outputFileName = Path.GetTempFileName();

            using (var fs = new FileStream(inputFXFileName,
                                           FileMode.Create,
                                           FileAccess.Write,
                                           FileShare.Read | FileShare.Delete))
            {
                StreamWriter writer = new StreamWriter(fs);
                writer.Write(text);
                writer.Close();
            }

            string args = string.Format("/T fx_2_0 /Fo \"{1}\" \"{0}\"", inputFXFileName, outputFileName);

            ProcessStartInfo start = new ProcessStartInfo(@"Plugin\fxc.exe", args)
            {
                UseShellExecute = false,
                RedirectStandardOutput = true,
                RedirectStandardError = true,
            };
            Process process = Process.Start(start);
            process.WaitForExit();
            string message1 = process.StandardOutput.ReadToEnd();
            string message2 = process.StandardError.ReadToEnd();

            byte[] buffer = null;
            using (var fs = new FileStream(outputFileName, FileMode.Open, FileAccess.Read))
            {
                BinaryReader fxoReader = new BinaryReader(fs);
                buffer = fxoReader.ReadBytes((int)fs.Length);
            }

            File.Delete(inputFXFileName);
            File.Delete(outputFileName);

            return new ShaderEffect(null)
                   {
                       Tag = new ShaderEffectCookingTag(buffer)
                   };
        }
    }
}
