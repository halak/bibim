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
using Bibim.Bab.Consoles;
using Bibim.Reflection;
using Bibim.Toolkit;

namespace Bibim.Bab
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

            Trace.Listeners.Add(new TraceListener(listBoxLogs));
            Trace.TraceError("AAAAA");
            Trace.TraceError("BBBB");

            string classname = null;
            if (App.CommandLineArgs.TryGetValue("class", out classname))
            {
                //foreach (Assembly assembly in AppDomain.CurrentDomain.GetAssemblies())
                {
                    Assembly assembly = Assembly.GetEntryAssembly();
                    foreach (Type item in assembly.GetTypes())
                    {
                        if (item.GetCustomAttribute<ConsoleEntryPointAttribute>() == null)
                            continue;

                        if (AliasAttribute.MatchName(item, classname))
                        {
                            programEntry = item.GetMethod("Run", BindingFlags.NonPublic | BindingFlags.Public | BindingFlags.Static);
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
        private class TraceListener : System.Diagnostics.TraceListener, Bibim.Diagnostics.IExtendedTraceListenable
        {
            #region Fields
            private ListBox listBox;
            #endregion

            #region Constructor
            public TraceListener(ListBox listBox)
            {
                this.listBox = listBox;
            }
            #endregion

            #region Write Methods
            public void TraceObject(object key, string message, object obj)
            {
            }

            public override void Write(string message)
            {
                listBox.Dispatcher.Invoke(new Action(() =>
                {
                    int index = listBox.Items.Count - 1;
                    if (index >= 0)
                    {
                        object value = ((ListBoxItem)listBox.Items[index]).Content;
                        if (value is string)
                            ((ListBoxItem)listBox.Items[index]).Content = (string)value + message;
                        else if (value is TextBlock)
                            ((TextBlock)value).Text += value;
                        else if (value is Label)
                            ((Label)value).Content += (string)((Label)value).Content + message;
                        else if (value is StackPanel)
                            ((StackPanel)value).Children.Add(new TextBlock() { Text = message });
                        else
                            throw new InvalidOperationException();
                    }
                    else
                    {
                        listBox.Items.Add(new ListBoxItem() { Content = message });
                    }
                }));

                System.Threading.Thread.Sleep(1);
            }

            public override void WriteLine(string message)
            {
                listBox.Dispatcher.Invoke(new Action(() =>
                {
                    listBox.Items.Add(new ListBoxItem() { Content = message });
                    listBox.ScrollIntoView(listBox.Items[listBox.Items.Count - 1]);
                }));

                System.Threading.Thread.Sleep(1);
            }
            #endregion
        }
        #endregion
    }
}
