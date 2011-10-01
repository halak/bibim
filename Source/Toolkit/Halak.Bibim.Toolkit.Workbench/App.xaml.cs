using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Windows;

namespace Halak.Bibim.Toolkit.Workbench
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            if (e.Args.Length > 0)
            {
                if (string.Compare(e.Args[0], "con", true) == 0 ||
                    string.Compare(e.Args[0], "console", true) == 0)
                {
                    StartupUri = new Uri("ConsoleWindow.xaml", UriKind.Relative);
                }
            }

            base.OnStartup(e);
        }
    }
}
