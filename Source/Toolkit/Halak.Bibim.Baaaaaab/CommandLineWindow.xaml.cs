using System;
using System.Collections.Generic;
using System.Linq;
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
using Halak.Bibim.Bab.Properties;

namespace Halak.Bibim.Bab
{
    /// <summary>
    /// Interaction logic for CommandLineWindow.xaml
    /// </summary>
    public partial class CommandLineWindow : Window
    {
        private AutoCompleteManager commandLineACM;

        public CommandLineWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            string[] commandLines = new string[Settings.Default.CommandLines.Count];
            Settings.Default.CommandLines.CopyTo(commandLines, 0);

            commandLineACM = new AutoCompleteManager(textBoxCommandLine);
            commandLineACM.DataProvider = new SimpleStaticDataProvider(commandLines);
            commandLineACM.AutoAppend = true;

            textBoxCommandLine.Focus();
        }

        private void buttonExecute_Click(object sender, RoutedEventArgs e)
        {
            if (Settings.Default.CommandLines.Contains(textBoxCommandLine.Text) == false)
                Settings.Default.CommandLines.Add(textBoxCommandLine.Text);

            Settings.Default["RecentCommandLine"] = textBoxCommandLine.Text;

            Settings.Default.Save();
        }

        private void buttonCreateShortcut_Click(object sender, RoutedEventArgs e)
        {
            ToolTip tooltip = new ToolTip();
            tooltip.Content = "AAAA";

            textBoxShortcutName.ToolTip = tooltip;
            tooltip.IsOpen = true;
            ToolTipService.SetShowDuration(textBoxShortcutName, 1);
        }
    }
}
