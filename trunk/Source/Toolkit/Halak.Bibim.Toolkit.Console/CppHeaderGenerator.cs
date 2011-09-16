using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using C = System.Console;

namespace Halak.Bibim.Toolkit.Console
{
    /// <summary>
    /// C++ Header File들을 자동으로 생성하는 Program.
    /// </summary>
    /// <example>
    /// CppHeaderGenerator all Bibim %BIBIM_DIR%Source\Runtime\CPlusplus %BIBIM_DIR%Source\Runtime\CPlusplus\Foundation\Bibim\All.h
    /// </example>
    public sealed class CppHeaderGenerator
    {
        static void Main(string[] args)
        {
            if (args.Length == 0)
            {
                C.WriteLine("");
                return;
            }

            switch (args[0].ToLower())
            {
                case "all":
                case "full":
                    {
                        if (args.Length < 3)
                        {
                            C.WriteLine("");
                            break;
                        }

                        string libraryName = args[1];
                        string sourceDirectoryPath = Environment.ExpandEnvironmentVariables(args[2]);
                        string destinationFilePath = Environment.ExpandEnvironmentVariables(args[3]);
                        GenerateFullHeader(libraryName, sourceDirectoryPath, destinationFilePath);
                    }
                    break;
                case "fwd":
                    {
                        if (args.Length < 3)
                        {
                            C.WriteLine("");
                            break;
                        }

                        string sourceDirectoryPath = Environment.ExpandEnvironmentVariables(args[1]);
                        string destinationFilePath = Environment.ExpandEnvironmentVariables(args[2]);
                        GenerateForwardDeclarationHeader(sourceDirectoryPath, destinationFilePath);
                    }
                    break;
            }
        }

        /// <summary>
        /// 지정한 Directory의 모든 Header-file들을 include하는 Header-file을 생성합니다.
        /// </summary>
        /// <param name="name">Library의 이름</param>
        /// <param name="sourceDirectoryPath">Header-file들이 들어있는 Directory 경로</param>
        /// <param name="destinationFilePath">모든 Header-file들을 include하는 Header-file 경로</param>
        static void GenerateFullHeader(string libraryName, string sourceDirectoryPath, string destinationFilePath)
        {
            List<string> headerFiles = FindAllHeaderFiles(libraryName, sourceDirectoryPath);

            FileStream fileStream = new FileStream(destinationFilePath, FileMode.Create, FileAccess.Write);
            StreamWriter w = new StreamWriter(fileStream);

            string definition = string.Format("__{0}_ALL_H__", libraryName.ToUpper());
            w.WriteLine("#pragma once");
            w.Write("#ifndef ");
            w.WriteLine(definition);
            w.Write("#define ");
            w.WriteLine(definition);
            w.WriteLine();
            w.WriteLine("   // This file was \"AUTOMATICALLY GENERATED\" by Bibim Console ({0})", DateTime.Now);
            w.WriteLine("   // > Halak.Bibim.Toolkit.Console.exe CppHeaderGenerator full [Library-Name] [Source-Directory] [Header-File]");
            w.WriteLine();

            string lastCategory = string.Empty;
            foreach (string item in headerFiles)
            {
                if (string.Compare(item, sourceDirectoryPath) == 0)
                    continue;

                string category = Path.GetFileName(Path.GetDirectoryName(Path.GetDirectoryName(item)));
                if (category != lastCategory)
                {
                    w.WriteLine();
                    w.WriteLine("   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
                    w.Write("   // ");
                    w.WriteLine(category);
                    lastCategory = category;
                }

                w.Write("#  include <");
                w.Write(libraryName);
                w.Write("/");
                w.Write(Path.GetFileName(item));
                w.WriteLine(">");
            }

            w.WriteLine();
            w.Write("#endif");

            w.Close();
        }

        /// <summary>
        /// 지정한 Directory에 있는 Header-file들을 모두 가져옵니다.
        /// </summary>
        /// <param name="libraryName">Library의 이름</param>
        /// <param name="sourceDirectoryPath">Header-file들이 있는 Directory 경로</param>
        /// <returns>Header-file 목록</returns>
        static List<string> FindAllHeaderFiles(string libraryName, string sourceDirectoryPath)
        {
            string[] files = Directory.GetFiles(sourceDirectoryPath, "*.h", SearchOption.AllDirectories);
            List<string> result = new List<string>(files.Length);

            foreach (string item in files)
            {
                // File의 상위 Directory가 "Bibim"인 것만 찾습니다.
                if (string.Compare(Path.GetFileName(Path.GetDirectoryName(item)), libraryName, true) != 0)
                    continue;

                result.Add(item);
            }

            result.Sort();

            return result;
        }

        static void GenerateForwardDeclarationHeader(string sourceDirectoryPath, string destinationFilePath)
        {
            throw new NotImplementedException();
        }
    }
}
