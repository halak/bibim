using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace Halak.Bibim.Toolkit.Workbench
{
    /// <summary>
    /// Interaction logic for ConsoleWindow.xaml
    /// </summary>
    public partial class ConsoleWindow : Window
    {
        #region Constructor
        public ConsoleWindow()
        {
            InitializeComponent();
            ((Paragraph)consoleTextBox.Document.Blocks.FirstBlock).LineHeight = 1;
            Trace.Listeners.Add(new TraceListener(this));

            Thread thread = new Thread(() =>
            {
                Halak.Bibim.Toolkit.Consoles.CppHeaderGenerator.MainA(new string[]
                {
                    @"%BIBIM_DIR%Source\Runtime\CPlusplus",
                    @"%BIBIM_DIR%Source\Runtime\CPlusplus\Foundation\Bibim\All.h",
                    @"excluded:TestBed;Animation;Collision2D;Script;SFX",
                });
            });
            thread.Start();
        }
        #endregion

        #region Methods
        public void Write(string message)
        {
            Dispatcher.Invoke(new Action(() =>
            {
                consoleTextBox.AppendText(message);
            }),
            DispatcherPriority.Normal);
        }

        public void WriteLine(string message)
        {
            Dispatcher.Invoke(new Action(() =>
            {
                consoleTextBox.AppendText(message);
                consoleTextBox.AppendText("\n");
            }),
            DispatcherPriority.Normal);
        }
        #endregion

        private class TraceListener : System.Diagnostics.TraceListener
        {
            #region Fields
            private ConsoleWindow console;
            #endregion

            #region Constructor
            public TraceListener(ConsoleWindow console)
            {
                this.console = console;
            }
            #endregion

            #region Write Methods
            public override void Write(string message)
            {
                console.Write(message);
            }

            public override void WriteLine(string message)
            {
                console.WriteLine(message);
            }
            #endregion
        }
    }
}
