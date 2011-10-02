using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Toolkit.Workbench.Consoles
{
    [ConsoleEntryPoint]
    [Alias("cppfull.h")]
    public static class CppFullHeaderGenerator
    {
        static void Run([Alias("proj", "project")] string projectName,
                        [Alias("src", "source")] string sourceDirectoryPath,
                        [Alias("dest", "destination")] string destinationFilePath,
                        [Alias("excluded")] string excludedCategories,
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

            excludedCategories = excludedCategories ?? string.Empty;

            string[] excludedCategoryArray = excludedCategories.Split(',', '|', ';');

            List<string> headerFiles = FindAllHeaderFiles(projectName, sourceDirectoryPath);

            using (FileStream fs = new FileStream(destinationFilePath, FileMode.Create, FileAccess.Write))
            using (StreamWriter w = new StreamWriter(fs))
            {
                string guid = Guid.NewGuid().ToString();
                string definition = string.Format("__{0}_{1}_ALL_H__", projectName.ToUpper(), guid.Replace('-', '_').ToUpper());
                w.WriteLine("#pragma once");
                w.Write("#ifndef ");
                w.WriteLine(definition);
                w.Write("#define ");
                w.WriteLine(definition);
                w.WriteLine();
                w.WriteLine("   // This file was \"AUTOMATICALLY GENERATED\" by Bibim Console ({0})", DateTime.Now.ToString(new CultureInfo("en-us")));
                w.WriteLine(@"   // > Halak.Bibim.Toolkit.Console.exe \class:cppfull.h \proj:[Project-Name] \src:[Source-Directory] \dest:[Header-File]");
                w.WriteLine();

                string lastCategory = string.Empty;
                foreach (string item in headerFiles)
                {
                    if (string.Compare(item, sourceDirectoryPath, true) == 0)
                        continue;

                    string category = Path.GetFileName(Path.GetDirectoryName(Path.GetDirectoryName(item)));
                    if (excludedCategoryArray.Contains(category))
                        continue;

                    if (category != lastCategory)
                    {
                        w.WriteLine();
                        w.WriteLine("   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
                        w.Write("   // ");
                        w.WriteLine(category);
                        lastCategory = category;
                    }

                    string filename = Path.GetFileName(item);
                    w.Write("#  include <");
                    w.Write(projectName);
                    w.Write("/");
                    w.Write(filename);
                    w.WriteLine(">");

                    if (silence == false)
                        Trace.WriteLine(filename);
                }

                w.WriteLine();
                w.Write("#endif");
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
