using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;

namespace dragonz.actb.provider
{
    public class FileSysDataProvider : IAutoCompleteDataProvider, IAutoAppendDataProvider
    {
        [StructLayout(LayoutKind.Sequential, CharSet=CharSet.Auto)]
        struct WIN32_FIND_DATA
        {
            public FileAttributes dwFileAttributes;
            public FILETIME ftCreationTime;
            public FILETIME ftLastAccessTime;
            public FILETIME ftLastWriteTime;
            public uint nFileSizeHigh;
            public uint nFileSizeLow;
            public uint dwReserved0;
            public uint dwReserved1;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst=260)]
            public string cFileName;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst=14)]
            public string cAlternateFileName;
        }
        [DllImport("kernel32.dll", CharSet = CharSet.Auto)]
        static extern IntPtr FindFirstFile(string lpFileName, out WIN32_FIND_DATA lpFindFileData);
        [DllImport("kernel32.dll", CharSet = CharSet.Auto)]
        static extern bool FindNextFile(IntPtr hFindFile, out WIN32_FIND_DATA lpFindFileData);
        [DllImport("kernel32.dll")]
        public static extern bool FindClose(IntPtr hFindFile);
        const short INVALID_HANDLE_VALUE = -1;

        //
        public bool IncludeFiles{ get; set;}

        public IEnumerable<string> GetItems(string textPattern)
        {
            if (textPattern.Length < 2 || textPattern[1] != ':')
            {
                yield break;
            }
            int lastSlashPos = textPattern.LastIndexOf('\\');
            if (lastSlashPos == -1)
            {
                yield break;
            }
            int fileNamePatternLength = textPattern.Length - lastSlashPos - 1;
            string baseFolder = textPattern.Substring(0, lastSlashPos + 1);
            WIN32_FIND_DATA fd;
            var hFind = FindFirstFile(textPattern + "*", out fd);
            if(hFind.ToInt32() == INVALID_HANDLE_VALUE)
            {
                yield break;
            }
            do
            {
                if(fd.cFileName[0] == '.')
                {
                    continue;
                }
                if((fd.dwFileAttributes & FileAttributes.Hidden) != 0)
                {
                    continue;
                }
                if((fd.dwFileAttributes & FileAttributes.Directory) == 0 && !IncludeFiles)
                {
                    continue;
                }
                if (fileNamePatternLength > fd.cFileName.Length)
                {
                    continue;
                }
                yield return baseFolder + fd.cFileName;
            } while (FindNextFile(hFind, out fd));
            FindClose(hFind);
        }

        public string GetAppendText(string textPattern, string firstMatch)
        {
            if(textPattern.EndsWith("\\"))
            {
                return null;
            }
            return firstMatch.Substring(textPattern.Length);
        }
    }
}
