using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
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
        #region Fields
        private MethodInfo programEntry;
        private Thread programThread;
        private ResourceDictionary resources;
        #endregion

        #region Properties
        public static ConcurrentQueue<string> CommandQueue
        {
            get;
            private set;
        }
        #endregion

        #region Constructor
        public ConsoleWindow()
        {
            InitializeComponent();

            resources = new ResourceDictionary();
            resources.Source = new Uri("ConsoleResources.xaml", UriKind.Relative);

            ((Paragraph)consoleTextBox.Document.Blocks.FirstBlock).LineHeight = 1;
            Trace.Listeners.Add(new TraceListener(consoleTextBox));

            string classname = null;
            if (App.CommandLineArgs.TryGetValue("class", out classname))
            {
                foreach (Assembly assembly in AppDomain.CurrentDomain.GetAssemblies())
                {
                    foreach (Type item in assembly.GetTypes())
                    {
                        if (item.GetCustomAttribute<ConsoleEntryPointAttribute>() == null)
                            continue;

                        if (AliasAttribute.MatchName(item, classname))
                        {
                            programEntry = item.GetMethod("Run", BindingFlags.NonPublic | BindingFlags.Static);
                            if (programEntry != null)
                                break;
                        }
                    }
                }

                if (programEntry == null)
                {
                    App.Current.Shutdown();
                    return;
                }

                ParameterInfo[] parameters = programEntry.GetParameters();
                object[] arguments = new object[parameters.Length];
                for (int i = 0; i < parameters.Length; i++)
                {
                    Type parameterType = parameters[i].ParameterType;

                    foreach (KeyValuePair<string, string> item in App.CommandLineArgs)
                    {
                        if (AliasAttribute.MatchName(parameters[i], item.Key))
                        {
                            if (parameterType == typeof(bool))
                            {
                                arguments[i] = string.Compare(item.Value, "t") == 0 ||
                                               string.Compare(item.Value, "true") == 0 ||
                                               string.Compare(item.Value, "y") == 0 ||
                                               string.Compare(item.Value, "yes") == 0;
                            }
                            else
                            {
                                try
                                {
                                    arguments[i] = Convert.ChangeType(item.Value, parameterType);
                                }
                                catch (FormatException)
                                {
                                    arguments[i] = null;
                                }
                                catch (InvalidCastException)
                                {
                                    arguments[i] = null;
                                }
                            }

                            break;
                        }
                    }
                }

                programThread = new Thread(() =>
                {
                    try
                    {
                        programEntry.Invoke(null, arguments);
                        Dispatcher.Invoke(new Action(() => { OnProgramEnded(); }));
                    }
                    catch (Exception e)
                    {
                        Trace.WriteLine(e.ToString());
                    }
                });
                programThread.Start();
            }
        }

        static ConsoleWindow()
        {
            CommandQueue = new ConcurrentQueue<string>();
        }
        #endregion

        #region Methods
        private void OnProgramEnded()
        {
            if (checkBoxExit.IsChecked.HasValue && checkBoxExit.IsChecked.Value)
                App.Current.Shutdown();

            consoleTextBox.Background = (Brush)resources["ProgramCompletedBrush"];
        }

        protected override void OnClosing(System.ComponentModel.CancelEventArgs e)
        {
            if (programThread != null && programThread.IsAlive)
            {
                CommandQueue.Enqueue("close");
                CommandQueue.Enqueue("exit");
                CommandQueue.Enqueue("quit");
            }

            base.OnClosing(e);
        }

        protected override void OnClosed(EventArgs e)
        {
            if (programThread != null)
            {
                // Program Thread가 정상적으로 끝나는 것을 10초 정도 기다립니다.
                // 그래도 안 끝나면 ""경험상"" 비정상적인 상황이므로 Thread를 강제로 종료합니다.
                programThread.Join(10000);
                programThread.Abort();
            }

            base.OnClosed(e);
        }
        #endregion

        #region TraceListener (Nested Class)
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

                System.Threading.Thread.Sleep(1);
            }

            public override void WriteLine(string message)
            {
                message += "\n";

                richTextBox.Dispatcher.Invoke(new Action(() =>
                {
                    richTextBox.AppendText(message);
                    richTextBox.ScrollToEnd();
                }));

                System.Threading.Thread.Sleep(1);
            }
            #endregion
        }
        #endregion
    }
}
