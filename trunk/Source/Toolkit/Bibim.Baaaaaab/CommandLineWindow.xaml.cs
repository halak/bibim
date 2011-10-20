using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using dragonz.actb.core;
using dragonz.actb.provider;
using Bibim.Bab.Properties;
using Bibim.Reflection;
using IWshRuntimeLibrary;
using Path = System.IO.Path;

namespace Bibim.Bab
{
    /// <summary>
    /// Interaction logic for CommandLineWindow.xaml
    /// </summary>
    public partial class CommandLineWindow : Window
    {
        private AutoCompleteManager commandLineACM;

        public string[] commandLineArgs
        {
            get;
            private set;
        }

        public CommandLineWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            string[] commandLineSuggestions = new string[Settings.Default.CommandLines.Count];
            Settings.Default.CommandLines.CopyTo(commandLineSuggestions, 0);

            commandLineACM = new AutoCompleteManager(textBoxCommandLine);
            commandLineACM.DataProvider = new SimpleStaticDataProvider(commandLineSuggestions);
            commandLineACM.AutoAppend = true;

            textBoxCommandLine.Text = Settings.Default.RecentCommandLine ?? string.Empty;
            textBoxCommandLine.Focus();
            textBoxCommandLine.SelectAll();
        }

        private void buttonExecute_Click(object sender, RoutedEventArgs e)
        {
            string input = textBoxCommandLine.Text;

            #region 입력한 CommandLine을 따로 목록에 넣어놓고 저장합니다. 재실행 때 사용됩니다.
            if (string.IsNullOrEmpty(input) == false)
            {
                if (Settings.Default.CommandLines.Contains(input) == false)
                    Settings.Default.CommandLines.Add(input);

                Settings.Default.RecentCommandLine = textBoxCommandLine.Text;
                Settings.Default.Save();
            }
            #endregion

            commandLineArgs = input.Split(' ');
            DialogResult = true;
        }

        private void buttonCreateShortcut_Click(object sender, RoutedEventArgs e)
        {
            #region Verify
            if (string.IsNullOrEmpty(textBoxShortcutName.Text))
            {
                textBoxShortcutName.Focus();
                // TODO: [NOTIFICATION] 파일 이름을 입력하세요.
                // 텍스트 박스 붉은 빛으로 깜빡이기
                return;
            }

            char[] invalidFileNameChars = Path.GetInvalidFileNameChars();
            int invalidCharIndex = textBoxShortcutName.Text.IndexOfAny(invalidFileNameChars);
            if (invalidCharIndex != -1)
            {
                int lastInvalidCharIndex = textBoxShortcutName.Text.LastIndexOfAny(invalidFileNameChars);
                textBoxShortcutName.Focus();
                textBoxShortcutName.Select(invalidCharIndex, Math.Max(lastInvalidCharIndex - invalidCharIndex, 1));
                // TODO: [NOTIFICATION] 파일 이름에 이상한 문자가 있습니다. 파일 이름에 다음의 문자들은 사용할 수 없습니다. invalidFileNameChars
                // 텍스트 박스 붉은 빛으로 깜빡이기
                return;
            }
            #endregion

            try
            {
                string directory = Environment.GetFolderPath(Environment.SpecialFolder.DesktopDirectory);
                string filename = textBoxShortcutName.Text;
                string description = "Execute Bibimbaaaaaab with custom arguments.";
                string arguments = textBoxCommandLine.Text;

                #region Create Shortcut
                if (directory.IndexOfAny(Path.GetInvalidPathChars()) != -1)
                    throw new ArgumentException("directory");
                if (filename.IndexOfAny(Path.GetInvalidFileNameChars()) != -1)
                    throw new ArgumentException("filename");

                WshShell shell = new WshShell();
                string shortcutPath = Path.ChangeExtension(Path.Combine(directory, filename), "lnk");
                IWshShortcut shortcut = (IWshShortcut)shell.CreateShortcut(shortcutPath);
                shortcut.TargetPath = System.Reflection.Assembly.GetEntryAssembly().CodeBase;
                shortcut.WorkingDirectory = Path.GetDirectoryName(shortcut.TargetPath);
                shortcut.Arguments = arguments;
                shortcut.Description = description;
                shortcut.Save();
                #endregion
            }
            catch (Exception ex)
            {
                // TODO: [NOTIFICATION] 바로가기를 만드는 중 문제가 발생하였습니다.
                throw ex;
            }

            // TODO: [NOTIFICATION] 성공하였습니다.
            // 버튼 주위에 툴팁 보여주기
            textBoxShortcutName.Text = string.Empty;
        }
    }
}
