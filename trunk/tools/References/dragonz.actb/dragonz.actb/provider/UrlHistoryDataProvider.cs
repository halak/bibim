using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace dragonz.actb.provider
{
    public class UrlHistoryDataProvider : IAutoCompleteDataProvider, IAutoAppendDataProvider
    {
        private List<string> _historyUrls;

        public IEnumerable<string> GetItems(string textPattern)
        {
            if(_historyUrls == null)
            {
                lock(this)
                {
                    _historyUrls = LoadHistoryUrls();
                }
            }

            if("http://".IndexOf(textPattern) == 0)
            {
                return _historyUrls;
            }
            var pattern = textPattern;
            if(!pattern.StartsWith("http://"))
            {
                pattern = "http://" + textPattern;
            }
            var result = new List<string>();
            foreach (var url in _historyUrls)
            {
                if(url.StartsWith(pattern, StringComparison.OrdinalIgnoreCase))
                {
                    result.Add(url);
                }
            }
            if (!textPattern.StartsWith("http://") && !textPattern.StartsWith("www."))
            {
                pattern = "http://www." + textPattern;
                result.AddRange(GetItems(pattern));
            }
            return result;
        }

        public string GetAppendText(string textPattern, string firstMatch)
        {
            if(!textPattern.StartsWith("http://"))
            {
                textPattern = "http://" + textPattern;
            }
            if(firstMatch.IndexOf(textPattern, StringComparison.OrdinalIgnoreCase) != 0)
            {
                return null;
            }
            var result = firstMatch.Substring(textPattern.Length);
            int slashPos = result.IndexOf('/');
            if(slashPos != -1)
            {
                result = result.Substring(0, slashPos + 1);
            }
            return result;
        }

        //
        [DllImport("wininet.dll", SetLastError = true, CharSet = CharSet.Ansi)]
        private static extern IntPtr FindFirstUrlCacheEntry(string lpszUrlSearchPattern,
                                                           IntPtr lpFirstCacheEntryInfo,
                                                           ref int lpdwFirstCacheEntryInfoBufferSize);
        [DllImport("wininet.dll", SetLastError = true, CharSet = CharSet.Ansi)]
        private static extern bool FindNextUrlCacheEntry(IntPtr hEnumHandle,
                                                        IntPtr lpNextCacheEntryInfo,
                                                        ref int lpdwNextCacheEntryInfoBufferSize);

        [DllImport("wininet.dll", SetLastError = true, CharSet = CharSet.Ansi)]
        private static extern long FindCloseUrlCache(IntPtr hEnumHandle);

        private const int ERROR_NO_MORE_ITEMS = 0x103;
        private const int ERROR_INSUFFICIENT_BUFFER = 122;

        public List<string> LoadHistoryUrls()
        {
            var result = new List<string>();
            int cb = 0;
            const string pattern = "visited:";
            FindFirstUrlCacheEntry(pattern, IntPtr.Zero, ref cb);

            IntPtr buf = Marshal.AllocHGlobal(cb);
            try
            {
                IntPtr hFind = FindFirstUrlCacheEntry(pattern, buf, ref cb);

                while (true)
                {
                    var pSourceUrl = Marshal.ReadIntPtr(buf, 4);
                    string url = Marshal.PtrToStringAnsi(pSourceUrl);
                    int atPos = url.IndexOf("@");
                    if (atPos != -1)
                    {
                        url = url.Substring(atPos + 1);
                    }
                    if (url.StartsWith("http://"))
                    {
                        result.Add(url);
                    }

                    bool retval = FindNextUrlCacheEntry(hFind, buf, ref cb);
                    if (!retval)
                    {
                        var win32Err = Marshal.GetLastWin32Error();
                        if (win32Err == ERROR_NO_MORE_ITEMS)
                        {
                            break;
                        }
                        if (win32Err == ERROR_INSUFFICIENT_BUFFER)
                        {
                            buf = Marshal.ReAllocHGlobal(buf, new IntPtr(cb));
                            FindNextUrlCacheEntry(hFind, buf, ref cb);
                        }
                    }
                }
                FindCloseUrlCache(hFind);
            }
            finally
            {
                Marshal.FreeHGlobal(buf);
            }
            return result;
        }
    }
}
