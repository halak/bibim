using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.IO;
using System.Text.RegularExpressions;
using System.Reflection;
using System.Windows;

namespace Bibim.Bab
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

            string[] args = null;
            #region 실행할 때 명령행 인자를 넣지 않았다면 따로 인자를 넣을 수 있는 CommandLineWindow를 보여줍니다.
            if (e.Args.Length == 0)
            {
                var commandLineWindow = new CommandLineWindow();
                bool? result = commandLineWindow.ShowDialog();
                if (result.HasValue && result.Value)
                    args = commandLineWindow.commandLineArgs;
            }
            else
                args = e.Args;
            #endregion

            if (args == null)
            {
                Shutdown();
                return;
            }

            #region "/Key:Value" 혹은 "/Flag" 형태로 되어 있는 명령행 인자들을 분석하여 따로 보관합니다.
            CommandLineArgs = new SortedList<string, string>(args.Length, StringComparer.CurrentCultureIgnoreCase);
            if (args.Length > 0)
            {
                string keyValuePattern = @"(?<name>/\w+):(?<value>.+)";
                string flagPattern = @"(?<name>/\w+)";
                Match match = null;
                foreach (string item in args)
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
            #endregion

            #region 명령행 인자를 확인하고 적절한 Window로 표시해줍니다.
            if (args.Length > 0)
            {
                if (string.Compare(args[0], "con", true) == 0 ||
                    string.Compare(args[0], "console", true) == 0)
                {
                    if (CommandLineArgs.ContainsKey("class"))
                        StartupUri = new Uri("ConsoleWindow.xaml", UriKind.Relative);
                }
            }
            #endregion

            base.OnStartup(e);
        }
    }
}
