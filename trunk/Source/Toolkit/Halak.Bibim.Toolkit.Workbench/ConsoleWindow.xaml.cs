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
using Halak.Bibim.Reflection;
using Halak.Bibim.Toolkit.Workbench.Consoles;

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
            Trace.Listeners.Add(new TraceListener(consoleTextBox));

            //foreach (Type item in AssemblyUtility.FindClasses(typeof(ConsoleProgram), true, true))
            //{
            //    item.Name == "hra"
            //}

            Thread thread = new Thread(() =>
            {
                AssetServer assetServer = new AssetServer()
                {
                    PipeName = "TestAssets",
                };
                assetServer.Run();

                //Halak.Bibim.Toolkit.Consoles.CppHeaderGenerator.MainA(new string[]

                //{
                //    @"%BIBIM_DIR%Source\Runtime\CPlusplus",
                //    @"%BIBIM_DIR%Source\Runtime\CPlusplus\Foundation\Bibim\All.h",
                //    @"excluded:TestBed;Animation;Collision2D;Script;SFX",
                //});
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
            private RichTextBox richTextBox;
            #endregion

            #region Constructor
            public TraceListener(RichTextBox richTextBox)
            {
                this.richTextBox = richTextBox;
            }
            #endregion

            #region Write Methods
            public override void Write(string message)
            {
                richTextBox.Dispatcher.Invoke(new Action(()=>
                {
                    richTextBox.AppendText(message);
                }));
            }

            public override void WriteLine(string message)
            {
                message += "\n";

                richTextBox.Dispatcher.Invoke(new Action(() =>
                {
                    richTextBox.AppendText(message);
                }));
            }
            #endregion
        }
    }
}
