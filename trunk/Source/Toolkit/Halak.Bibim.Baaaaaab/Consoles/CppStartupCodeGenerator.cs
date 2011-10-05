using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.IO;
using System.Text;
using Halak.Bibim.Toolkit;

namespace Halak.Bibim.Bab.Consoles
{
    [ConsoleEntryPoint]
    [Alias("CppStartup.cpp")]
    public static class CppStartupCodeGenerator
    {
        static void Run([Alias("proj", "project")] string projectName,
                        [Alias("src", "source")] string sourceDirectoryPath,
                        [Alias("dest", "destination")] string destinationFilePath,
                        bool silence)
        {
            if (string.IsNullOrEmpty(projectName))
                throw new ArgumentException("projectName");
            if (string.IsNullOrEmpty(sourceDirectoryPath))
                throw new ArgumentException("sourceDirectoryPath");
            if (string.IsNullOrEmpty(destinationFilePath))
                throw new ArgumentException("destinationFilePath");

            sourceDirectoryPath = Environment.ExpandEnvironmentVariables(sourceDirectoryPath);
            destinationFilePath = Environment.ExpandEnvironmentVariables(destinationFilePath);

            List<string> headerFiles = FindAllHeaderFiles(projectName, sourceDirectoryPath);
            
            foreach (string item in headerFiles)
            {
                //using (FileStream fs = new FileStream(item, FileMode.Open, FileAccess.Read))
                //using (StreamReader r = new StreamReader(fs))
                //{
                //    string s = r.ReadToEnd();
                //    int index = 0;

                //    // index = s.IndexOf("BBReadableObjectClass(", index);
                //}
            }

            using (FileStream fs = new FileStream(destinationFilePath, FileMode.Create, FileAccess.Write))
            using (StreamWriter w = new StreamWriter(fs))
            {
                w.WriteLine("#include <{0}/Startup.h>", projectName);
                w.WriteLine("#include <{0}/All.h>", projectName);
                w.WriteLine();
                w.WriteLine("namespace {0}", projectName);
                w.WriteLine("{");
                w.WriteLine("    void Startup::All()");
                w.WriteLine("    {");
                foreach (int i in new int[] { 10, 20, 30 })
                {
                    w.WriteLine("        {0}Factory::AddEntry<{1}>();", "", "");
                }
                foreach (int i in new int[] { 10, 20, 30 })
                {
                    w.WriteLine("        {0}Factory::SortEntries();", "");
                }
                w.WriteLine("    }");
                w.WriteLine("}");
            }
        }

        static List<string> FindAllHeaderFiles(string projectName, string sourceDirectoryPath)
        {
            string[] files = Directory.GetFiles(sourceDirectoryPath, "*.h", SearchOption.AllDirectories);
            List<string> result = new List<string>(files.Length);

            foreach (string item in files)
            {
                // File의 상위 Directory가 "Bibim"인 것만 찾습니다.
                if (string.Compare(Path.GetFileName(Path.GetDirectoryName(item)), projectName, true) != 0)
                    continue;

                result.Add(item);
            }

            result.Sort();

            return result;
        }

    }
}
