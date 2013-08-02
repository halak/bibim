using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Net;
using System.Runtime.InteropServices;
using System.Text;
using System.Web;
using System.Windows;
using System.Windows.Input;
using dragonz.actb.core;
using dragonz.actb.provider;

namespace WpfApplication1
{
    /// <summary>
    ///   Interaction logic for Window1.xaml
    /// </summary>
    public partial class Window1 : Window
    {
        private AutoCompleteManager _acmBingSuggestion;
        private AutoCompleteManager _acmRegistryPath;
        private AutoCompleteManager _acmUrlHistory;

        public Window1()
        {
            test();

            InitializeComponent();

            _acmBingSuggestion = new AutoCompleteManager(txtBingSearch);
            _acmBingSuggestion.DataProvider = new BingSuggestionProvider();
            _acmBingSuggestion.Asynchronous = true;
            txtBingSearch.KeyDown += txtBingSearch_KeyDown;

            btnBingSearch.Click += btnBingSearch_Click;

            _acmRegistryPath = new AutoCompleteManager(txtRegistryPath);
            _acmRegistryPath.DataProvider = new RegistryDataProvider();

            accbStates.ItemsSource = StateData.States;
            accbStates.AutoCompleteManager.DataProvider = new SimpleStaticDataProvider(StateData.States);
            accbStates.AutoCompleteManager.AutoAppend = true;

            _acmUrlHistory = new AutoCompleteManager(txtUrlHistory);
            _acmUrlHistory.DataProvider = new UrlHistoryDataProvider();
            //_acmUrlHistory.Asynchronous = true;
            _acmUrlHistory.AutoAppend = true;
        }


        [DllImport(@"wininet", SetLastError = true, CharSet = CharSet.Auto, EntryPoint = "FindFirstUrlCacheEntryA", CallingConvention = CallingConvention.StdCall)]
        public static extern IntPtr FindFirstUrlCacheEntry([MarshalAs(UnmanagedType.LPTStr)] string lpszUrlSearchPattern, IntPtr lpFirstCacheEntryInfo, ref int lpdwFirstCacheEntryInfoBufferSize);

        private void test()
        {
            //FindFirstUrlCacheEntry("http://")
        }

        void txtBingSearch_KeyDown(object sender, KeyEventArgs e)
        {
            if(e.Key == Key.Enter)
            {
                bing(txtBingSearch.Text);
            }
        }

        private void btnBingSearch_Click(object sender, RoutedEventArgs e)
        {
            bing(txtBingSearch.Text);
        }

        private void bing(string text)
        {
            Process.Start("http://www.bing.com/search?q=" + HttpUtility.UrlEncode(text));
        }

        private void ChkIncludeFiles_Click(object sender, RoutedEventArgs e)
        {
            var fileSysDataProvider = actbFileSysPath.AutoCompleteManager.DataProvider as FileSysDataProvider;
            fileSysDataProvider.IncludeFiles = chkIncludeFiles.IsChecked.Value;
        }

        private void ChkAutoAppend_Click(object sender, RoutedEventArgs e)
        {
            actbFileSysPath.AutoCompleteManager.AutoAppend = chkAutoAppend.IsChecked.Value;
        }
    }
}