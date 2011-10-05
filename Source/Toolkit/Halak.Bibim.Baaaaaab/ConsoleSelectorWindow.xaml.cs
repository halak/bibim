using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
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
using Halak.Bibim.Bab.Consoles;
using Halak.Bibim.Reflection;
using Halak.Bibim.Toolkit;

namespace Halak.Bibim.Bab
{
    /// <summary>
    /// Interaction logic for ConsoleSelectorWindow.xaml
    /// </summary>
    public partial class ConsoleSelectorWindow : Window
    {
        public ConsoleSelectorWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            foreach (Assembly assembly in AppDomain.CurrentDomain.GetAssemblies())
            {
                foreach (Type item in assembly.GetTypes())
                {
                    if (item.GetCustomAttribute<ConsoleEntryPointAttribute>() != null)
                    {
                        listViewConsoles.Items.Add(item);
                    }
                }
            }
        }

        private void listViewConsoles_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            Trace.Assert(e.AddedItems.Count <= 1);

            if (e.AddedItems.Count == 1)
            {
                Type item = (Type)e.AddedItems[0];
            }
        }
    }
}
