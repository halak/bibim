using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;

namespace Bibim.Asset.Pipeline.Recipes
{
    public static class Utility
    {
        public static void WriteToFile(string path, string data)
        {
            using (var fs = new FileStream(path, FileMode.Create, FileAccess.Write))
            using (var sw = new StreamWriter(fs))
            {
                sw.Write(data);
            }
        }

        public static byte[] ConvertUsingExternalTool(string path, string args, string output)
        {
            ProcessStartInfo start = new ProcessStartInfo(path, args)
            {
                CreateNoWindow = true,
                UseShellExecute = false,
                RedirectStandardOutput = true,
                RedirectStandardError = true,
            };
            Process process = Process.Start(start);
            process.WaitForExit();

            string compileMessage = process.StandardOutput.ReadToEnd();
            string compileErrorMessage = process.StandardError.ReadToEnd();

            if (string.IsNullOrEmpty(compileErrorMessage))
            {
                using (var fs = new FileStream(output, FileMode.Open, FileAccess.Read))
                {
                    BinaryReader reader = new BinaryReader(fs);
                    return reader.ReadBytes((int)fs.Length);
                }
            }
            else
            {
                throw new InvalidDataException(string.Format("Converting failure.\n{0}\n{1}\n{2}", compileMessage, compileErrorMessage, args));
            }
        }
    }
}
