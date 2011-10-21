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

namespace Bibim.Bab
{
    /// <summary>
    /// Interaction logic for ConsoleHtmlBox.xaml
    /// </summary>
    public partial class ConsoleHtmlBox : Window
    {
        public ConsoleHtmlBox()
        {
            InitializeComponent();
        }

        public ConsoleHtmlBox(string text)
            : this()
        {            
            this.webBrowser.NavigateToString(string.Format("<html><head><META http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head><body><pre>{0}</pre></body></html>", text));
        }
    }
}
