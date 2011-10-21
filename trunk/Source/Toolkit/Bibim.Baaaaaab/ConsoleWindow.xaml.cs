﻿using System;
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
        private int isProgramEnded;
        private int isWindowClosing;
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
            isProgramEnded = 0;
            isWindowClosing = 0;

            resources = new ResourceDictionary();
            resources.Source = new Uri("ConsoleResources.xaml", UriKind.Relative);

            Trace.Listeners.Add(new TraceListener(listBoxLogs));

            string classname = App.CommandLineArgs["class"];
            programEntry = ConsoleEntryPointAttribute.Find(classname);
            if (programEntry == null)
            {
                Close();
                return;
            }

            #region Command-Line에 입력한 인자들을 Console Program Parameter들에 맞게 변환합니다.
            ParameterInfo[] parameters = programEntry.GetParameters();
            object[] args = new object[parameters.Length];
            for (int i = 0; i < parameters.Length; i++)
            {
                foreach (KeyValuePair<string, string> item in App.CommandLineArgs)
                {
                    if (AliasAttribute.MatchName(parameters[i], item.Key))
                    {
                        try
                        {
                            args[i] = Convert.ChangeType(item.Value, parameters[i].ParameterType);
                        }
                        catch (FormatException) { args[i] = null; }
                        catch (InvalidCastException) { args[i] = null; }

                        break;
                    }
                }
            }
            #endregion

            programThread = new Thread(() =>
            {
                try
                {
                    programEntry.Invoke(null, args);
                    Interlocked.Exchange(ref isProgramEnded, 1);
                    if (isWindowClosing == 0)
                        this.Dispatcher.Invoke(new Action(() => { OnProgramEnded(); }));
                }
                catch (Exception ex)
                {
                    Trace.WriteLine(ex);
                }
            });
            programThread.Start();
        }

        static ConsoleWindow()
        {
            CommandQueue = new ConcurrentQueue<string>();
        }
        #endregion

        #region Methods
        private void OnProgramEnded()
        {
            textBoxCommand.IsEnabled = false;
            buttonCommand.IsEnabled = false;

            if (checkBoxCloseOnProgramEnded.IsChecked.Value && isWindowClosing == 0)
                Close();
        }

        protected override void OnClosing(System.ComponentModel.CancelEventArgs e)
        {
            Interlocked.Exchange(ref isWindowClosing, 1);

            if (isProgramEnded == 0)
            {
                CommandQueue.Enqueue("close");
                CommandQueue.Enqueue("exit");
                CommandQueue.Enqueue("quit");

                // Program Thread가 정상적으로 끝나는 것을 10초 정도 기다립니다.
                // 그래도 안 끝나면 ""경험상"" 비정상적인 상황이므로 Thread를 강제로 종료합니다.
                programThread.Join(10000);
                if (programThread.IsAlive)
                    programThread.Abort();
            }

            base.OnClosing(e);
        }

        protected override void OnClosed(EventArgs e)
        {
            App.Current.Shutdown();
            base.OnClosed(e);
        }

        private void buttonCommand_Click(object sender, RoutedEventArgs e)
        {
            CommandQueue.Enqueue(textBoxCommand.Text);
            textBoxCommand.Focus();
            textBoxCommand.Text = string.Empty;
        }

        private void buttonClear_Click(object sender, RoutedEventArgs e)
        {
            listBoxLogs.Items.Clear();
        }
        #endregion

        #region TraceListener (Nested Class)
        private class TraceListener : System.Diagnostics.TraceListener
        {
            #region Font (Nested Struct)
            public struct Font
            {
                public readonly Brush Foreground;
                public readonly Brush Background;
                public readonly FontStyle Style;
                public readonly FontWeight Weight;

                public Font(Brush foreground, Brush background, FontStyle style, FontWeight weight)
                {
                    Foreground = foreground;
                    Background = background;
                    Style = style;
                    Weight = weight;
                }
            }
            #endregion

            #region Fields
            private ListBox listBox;
            private bool newLine;
            private Dictionary<string, Font> categoryFonts;
            #endregion

            #region Constructor
            public TraceListener(ListBox listBox)
            {
                this.listBox = listBox;
                this.newLine = true;
                this.categoryFonts = new Dictionary<string, Font>(8, StringComparer.CurrentCultureIgnoreCase);
                this.categoryFonts.Add("ERROR", new Font(Brushes.Red, null, FontStyles.Normal, FontWeights.Bold));
                this.categoryFonts.Add("EXCEPTION", new Font(Brushes.Red, null, FontStyles.Normal, FontWeights.Bold));
                this.categoryFonts.Add("WARNING", new Font(Brushes.Yellow, null, FontStyles.Italic, FontWeights.Normal));
                this.categoryFonts.Add("INFORMATION", new Font(Brushes.Lime, null, FontStyles.Normal, FontWeights.Normal));
            }
            #endregion

            #region Methods
            public override void TraceEvent(TraceEventCache eventCache, string source, TraceEventType eventType, int id, string message)
            {
                string category = ConvertTraceEventTypeToCategory(eventType);
                if (category != null)
                    WriteLine(message, category);
                else
                    base.TraceEvent(eventCache, source, eventType, id, message);
            }

            public override void TraceEvent(TraceEventCache eventCache, string source, TraceEventType eventType, int id, string format, params object[] args)
            {
                string category = ConvertTraceEventTypeToCategory(eventType);
                if (category != null)
                    WriteLine(string.Format(format, args), category);
                else
                    base.TraceEvent(eventCache, source, eventType, id, format, args);
            }

            public override void Write(object o)
            {
                Write(o, null);
            }

            public override void Write(object o, string category)
            {
                WriteActually(() => CreateElement(o, category), false);
            }

            public override void WriteLine(object o)
            {
                WriteLine(o, null);
            }

            public override void WriteLine(object o, string category)
            {
                WriteActually(() => CreateElement(o, category), true);
            }

            public override void Write(string message)
            {
                Write(message, null);
            }

            public override void Write(string message, string category)
            {
                WriteActually(() => CreateTextBlock(message, category), false);
            }

            public override void WriteLine(string message)
            {
                WriteLine(message, null);
            }

            public override void WriteLine(string message, string category)
            {
                WriteActually(() => CreateTextBlock(message, category), true);
            }

            private void WriteActually(Func<IEnumerable<UIElement>> createElement, bool newLine)
            {
                this.listBox.Dispatcher.Invoke(new Action(() =>
                {
                    ListBoxItem item = null;
                    if (this.newLine)
                    {
                        item = new ListBoxItem()
                        {
                            Content = new StackPanel()
                            {
                                Orientation = Orientation.Horizontal
                            }
                        };
                        this.listBox.Items.Add(item);
                        this.listBox.ScrollIntoView(item);
                    }
                    else
                        item = (ListBoxItem)this.listBox.Items[this.listBox.Items.Count - 1];

                    var line = (StackPanel)item.Content;
                    foreach (UIElement element in createElement())
                        line.Children.Add(element);

                    this.newLine = newLine;
                }));
            }

            private IEnumerable<UIElement> CreateElement(object o, string category)
            {
                if (o is Exception)
                {
                    Exception ex = (Exception)o;

                    string message = string.Format("{0} Thrown ({1}).", ex.GetType().Name, ex.Message);
                    foreach (UIElement item in CreateTextBlock(message, "EXCEPTION"))
                        yield return item;

                    Button button = new Button()
                    {
                        Content = "자세히",
                    };

                    button.Click += new RoutedEventHandler((sender, e) =>
                    {
                        ConsoleHtmlBox htmlBox = new ConsoleHtmlBox(ex.ToString());
                        htmlBox.Show();
                    });

                    yield return button;
                }
                else
                {
                    foreach (UIElement item in CreateTextBlock((string)o.ToString(), category))
                        yield return item;
                }
            }

            private IEnumerable<UIElement> CreateTextBlock(string message, string category)
            {
                int singleLineIndex = Math.Min(message.IndexOf('\r'), message.IndexOf('\n'));
                string fullMessage = message;
                if (singleLineIndex != -1)
                    message = message.Substring(0, singleLineIndex);

                Font font;
                if (string.IsNullOrEmpty(category) == false && categoryFonts.TryGetValue(category, out font))
                {
                    TextBlock result = new TextBlock()
                    {
                        Text = message,
                        FontStyle = font.Style,
                        FontWeight = font.Weight,
                    };

                    if (font.Foreground != null)
                        result.Foreground = font.Foreground;
                    if (font.Background != null)
                        result.Background = font.Background;

                    yield return result;
                }
                else
                    yield return new TextBlock() { Text = message };

                if (singleLineIndex != -1)
                {
                    Button button = new Button()
                    {
                        Content = "자세히",
                    };
                    button.Click += new RoutedEventHandler((sender, e) =>
                    {
                        ConsoleHtmlBox htmlBox = new ConsoleHtmlBox(fullMessage);
                        htmlBox.Show();
                    });
                    yield return button;
                }
            }

            private static string ConvertTraceEventTypeToCategory(TraceEventType eventType)
            {
                switch (eventType)
                {
                    case TraceEventType.Error:
                        return "ERROR";
                    case TraceEventType.Warning:
                        return "WARNING";
                    case TraceEventType.Information:
                        return "INFORMATION";
                    default:
                        return null;
                }
            }
            #endregion
        }
        #endregion
    }
}
