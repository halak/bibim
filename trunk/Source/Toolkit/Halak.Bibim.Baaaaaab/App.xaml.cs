using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.IO;
using System.Text.RegularExpressions;
using System.Reflection;
using System.Windows;

namespace Halak.Bibim.Bab
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        public static SortedList<string, string> CommandLineArgs
        {
            get;
            private set;
        }

        protected override void OnStartup(StartupEventArgs e)
        {
            string[] dllFiles = Directory.GetFiles("Plugin", "*.dll", SearchOption.TopDirectoryOnly);
            foreach (string item in dllFiles)
            {
                try
                {
                    AssemblyName name = AssemblyName.GetAssemblyName(item);
                    AppDomain.CurrentDomain.Load(name);
                }
                catch (Exception)
                {
                }
            }

            CommandLineArgs = new SortedList<string, string>(StringComparer.CurrentCultureIgnoreCase);
            if (e.Args.Length > 0)
            {
                string keyValuePattern = @"(?<name>/\w+):(?<value>.+)";
                string flagPattern = @"(?<name>/\w+)";
                Match match = null;
                foreach (string item in e.Args)
                {
                    match = Regex.Match(item, keyValuePattern);
                    if (match.Success)
                    {
                        CommandLineArgs.Add(match.Groups["name"].Value.Substring(1), match.Groups["value"].Value);
                        continue;
                    }

                    match = Regex.Match(item, flagPattern);
                    if (match.Success)
                    {
                        CommandLineArgs.Add(match.Groups["name"].Value.Substring(1), "yes");
                        continue;
                    }
                }
            }

            if (e.Args.Length > 0)
            {
                if (string.Compare(e.Args[0], "con", true) == 0 ||
                    string.Compare(e.Args[0], "console", true) == 0)
                {
                    if (CommandLineArgs.ContainsKey("class"))
                        StartupUri = new Uri("ConsoleWindow.xaml", UriKind.Relative);
                    else
                        StartupUri = new Uri("ConsoleSelectorWindow.xaml", UriKind.Relative);
                }
            }

            base.OnStartup(e);
        }
    }
}
