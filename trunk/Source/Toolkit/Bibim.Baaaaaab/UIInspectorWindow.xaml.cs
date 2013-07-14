using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.IO.Pipes;
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
using System.Windows.Threading;
using Bibim.Bab.Properties;
using Bibim.IO;
using Bibim.Json.Serialization;
using Bibim.UI.Visuals;
using GlobalResources = Bibim.Bab.Properties.Resources;

namespace Bibim.Bab
{
    /// <summary>
    /// Interaction logic for UIInspectorWindow.xaml
    /// </summary>
    public partial class UIInspectorWindow : Window
    {
        private const uint UIDataPacketID = 44523;
        private const uint UIVisualSelectedPacketID = 44524;

        private static Uri GetEmbeddedResourceUri(string path)
        {
            return new Uri("pack://application:,,,/Bibim.Baaaaaab;component/Resources/" + path, UriKind.RelativeOrAbsolute);
        }

        private readonly BitmapFrame VISIBLE = BitmapFrame.Create(GetEmbeddedResourceUri("VISIBLE.png"));
        private readonly BitmapFrame INVISIBLE = BitmapFrame.Create(GetEmbeddedResourceUri("INVISIBLE.png"));
        private readonly BitmapFrame COLLAPSED = BitmapFrame.Create(GetEmbeddedResourceUri("COLLAPSED.png"));
        private readonly BitmapFrame PICKABLE = BitmapFrame.Create(GetEmbeddedResourceUri("Pickable.png"));
        private readonly BitmapFrame UNPICKABLE = BitmapFrame.Create(GetEmbeddedResourceUri("Unpickable.png"));

        private NamedPipeServerStream serverStream;
        private BinaryReader serverStreamReader;
        private BinaryWriter serverStreamWriter;
        private byte[] serverBuffer;
        private DataTemplate treeViewHeaderTemplate;

        private long selectedVisualID;

        private DispatcherTimer findingDispatcher;

        public UIInspectorWindow()
        {
            InitializeComponent();

            PreloadClassIcon();
            Ready();
            serverBuffer = new byte[16];
        }

        private void Synchronize(Dictionary<string, object> o)
        {
            if (treeViewHeaderTemplate == null)
            {
                treeViewHeaderTemplate = new DataTemplate();

                FrameworkElementFactory stackPanel = new FrameworkElementFactory(typeof(StackPanel));
                stackPanel.SetValue(StackPanel.OrientationProperty, Orientation.Horizontal);
                stackPanel.SetValue(StackPanel.HorizontalAlignmentProperty, System.Windows.HorizontalAlignment.Center);
                stackPanel.SetValue(StackPanel.VerticalAlignmentProperty, System.Windows.VerticalAlignment.Center);

                FrameworkElementFactory classIcon = new FrameworkElementFactory(typeof(Image));
                classIcon.SetValue(Image.SourceProperty, new Binding() { Converter = new AtValueConverter(0) });
                stackPanel.AppendChild(classIcon);

                FrameworkElementFactory nameLabel = new FrameworkElementFactory(typeof(TextBlock));
                nameLabel.SetValue(TextBlock.MarginProperty, new Thickness(8, 0, 8, 0));
                nameLabel.SetValue(TextBlock.TextProperty, new Binding() { Converter = new AtValueConverter(1) });
                nameLabel.SetValue(TextBlock.ForegroundProperty, new Binding() { Converter = new AtValueConverter(2) });
                stackPanel.AppendChild(nameLabel);

                FrameworkElementFactory visibilityIcon = new FrameworkElementFactory(typeof(Image));
                visibilityIcon.SetValue(Image.SourceProperty, new Binding() { Converter = new AtValueConverter(3) });
                stackPanel.AppendChild(visibilityIcon);

                FrameworkElementFactory pickableIcon = new FrameworkElementFactory(typeof(Image));
                pickableIcon.SetValue(Image.SourceProperty, new Binding() { Converter = new AtValueConverter(4) });
                stackPanel.AppendChild(pickableIcon);

                treeViewHeaderTemplate.VisualTree = stackPanel;
            }

            //Stopwatch s = new Stopwatch();
            //s.Start();
            Synchronize(treeView.Items, GetChildren(o));
            //s.Stop();
            //Trace.TraceInformation("Synchronize time: {0}", s.ElapsedMilliseconds);

            HighlightTreeViewItemsByText(textBoxFind.Text);
        }

        private void Synchronize(ItemCollection subItems, List<object> children)
        {
            if (children == null || children.Count == 0)
                return;

            var changedItems = new List<object>(subItems.Count);
            for (int i = 0; i < children.Count; i++)
            {
                var child = (Dictionary<string, object>)children[i];
                var subItem = FindTreeViewItem(subItems, GetID(child), findAllItems: false);
                if (subItem == null)
                {
                    subItem = new TreeViewItem()
                    {
                        HeaderTemplate = treeViewHeaderTemplate,
                    };
                    ToolTipService.SetInitialShowDelay(subItem, 0);
                }

                if (subItems.IndexOf(subItem) != i)
                {
                    if (subItem.Parent != null)
                    {
                        if (subItem.Parent is TreeViewItem)
                            ((TreeViewItem)subItem.Parent).Items.Remove(subItem);
                        else if (subItem.Parent is TreeView)
                            ((TreeView)subItem.Parent).Items.Remove(subItem);
                        else
                            throw new NotImplementedException();
                    }

                    subItems.Insert(i, subItem);
                }

                subItem.Tag = GetID(child);
                subItem.ToolTip = GenerateTooltip(child);

                object nameForeground = null;
                object visibilityIcon = null;
                switch (GetVisibility(child))
                {
                    case UIVisibility.Visible:
                        nameForeground = Brushes.Black;
                        visibilityIcon = VISIBLE;
                        break;
                    case UIVisibility.Invisible:
                        nameForeground = Brushes.Gray;
                        visibilityIcon = INVISIBLE;
                        break;
                    case UIVisibility.Collapsed:
                        nameForeground = Brushes.Gray;
                        visibilityIcon = COLLAPSED;
                        break;
                }

                object[] data = (object[])subItem.Header;
                if (data == null)
                {
                    data = new object[5];
                    subItem.Header = data;
                }
                data[0] = GetClassIcon(child);
                data[1] = GetName(child);
                data[2] = nameForeground;
                data[3] = visibilityIcon;
                data[4] = GetPickable(child) ? PICKABLE : UNPICKABLE;

                changedItems.Add(subItem);

                Synchronize(subItem.Items, GetChildren(child));
            }

            for (int i = 0; i < subItems.Count; i++)
            {
                if (changedItems.Contains(subItems[i]) == false)
                    subItems.RemoveAt(i--);
            }
        }

        private void HighlightTreeViewItemsByText(string text)
        {
            if (string.IsNullOrWhiteSpace(text))
                text = null;

            //Stopwatch s = new Stopwatch();
            //s.Start();
            HighlightTreeViewItemsByText(treeView.Items, text);
            //s.Stop();

            //Trace.TraceInformation("Highlight time: {0}", s.ElapsedMilliseconds);
        }

        private static void HighlightTreeViewItemsByText(ItemCollection items, string text)
        {
            if (text != null)
            {
                foreach (TreeViewItem item in items)
                {
                    var name = GetName(item);
                    if (text != null && name.Contains(text))
                        item.FontWeight = FontWeights.Heavy;
                    else
                    {
                        item.FontWeight = FontWeights.Normal;
                        item.FontStyle = FontStyles.Normal;
                    }

                    HighlightTreeViewItemsByText(item.Items, text);
                }
            }
            else
            {
                foreach (TreeViewItem item in items)
                {
                    item.FontWeight = FontWeights.Normal;
                    item.FontStyle = FontStyles.Normal;
                    HighlightTreeViewItemsByText(item.Items, text);
                }
            }
        }

        private void SelectNextTreeViewItemByText(string text)
        {
            var selectedItem = (TreeViewItem)treeView.SelectedItem;
            TreeViewItem nextItem = null;
            if (selectedItem != null)
                nextItem = FindNextTreeViewItemBySubstring(GetContainer(selectedItem), selectedItem, text);

            if (nextItem == null)
                nextItem = FindNextTreeViewItemBySubstring(treeView.Items, null, text);

            if (nextItem != null)
            {
                if (selectedItem != null && object.ReferenceEquals(selectedItem, nextItem) == false)
                {
                    selectedItem.IsSelected = false;
                    selectedItem.FontStyle = FontStyles.Normal;
                }

                nextItem.IsSelected = true;
                nextItem.FontStyle = FontStyles.Italic;
                nextItem.BringIntoView();
            }
        }

        private static TreeViewItem FindNextTreeViewItemBySubstring(ItemCollection items, TreeViewItem selectedItem, string text)
        {
            int firstIndex = 0;
            if (selectedItem != null)
                firstIndex = items.IndexOf(selectedItem) + 1;
            for (int i = firstIndex; i < items.Count; i++)
            {
                var item = (TreeViewItem)items[i];
                var name = GetName(item);
                if (name.Contains(text))
                    return item;

                if (item.Items.Count > 0)
                {
                    var found = FindNextTreeViewItemBySubstring(item.Items, null, text);
                    if (found != null)
                        return found;
                }
            }

            if (selectedItem != null)
            {
                var parent = selectedItem.Parent as TreeViewItem;
                if (parent != null)
                    return FindNextTreeViewItemBySubstring(GetContainer(parent), parent, text);
            }

            return null;
        }

        private static TreeViewItem FindTreeViewItem(ItemCollection items, long id, bool findAllItems = true)
        {
            if (findAllItems)
            {
                foreach (TreeViewItem item in items)
                {
                    if ((long)item.Tag == id)
                        return item;

                    var found = FindTreeViewItem(item.Items, id, true);
                    if (found != null)
                        return found;
                }
            }
            else
            {
                foreach (TreeViewItem item in items)
                {
                    if ((long)item.Tag == id)
                        return item;
                }
            }

            return null;
        }

        private static ItemCollection GetContainer(TreeViewItem item)
        {
            if (item.Parent is TreeViewItem)
                return ((TreeViewItem)item.Parent).Items;
            else
                return ((TreeView)item.Parent).Items;
        }

        static object GenerateTooltip(Dictionary<string, object> o)
        {
            return string.Format(
                "{0}: {1}\n{2}: {3}\n{4}: {5}\n{6}: {7}\n{8}: {9}",
                "위치", o["xy"],
                "크기", o["size"],
                "앵커", o["anchor"],
                "원점", o["origin"],
                "불투명도", o["opacity"]
            );
        }

        static long GetID(Dictionary<string, object> o)
        {
            return Convert.ToInt64(o["id"]);
        }

        static string GetName(TreeViewItem item)
        {
            return (string)((object[])item.Header)[1];
        }

        static string GetName(Dictionary<string, object> o)
        {
            object nameObject = null;
            if (o.TryGetValue("name", out nameObject))
            {
                string name = nameObject.ToString();
                if (string.IsNullOrEmpty(name) == false)
                    return name;
            }

            long id = GetID(o);
            if (id >= (long)int.MaxValue)
                return string.Format("<0x{0}>", id.ToString("X"));
            else
                return string.Format("<0x{0}>", id.ToString("X"));
        }

        static SortedList<int, ImageSource> ClassIconDictionary;
        static void PreloadClassIcon()
        {
            if (ClassIconDictionary == null)
            {
                Type[] iconEmbeddedClasses = 
                {
                    typeof(UIButton),
                    typeof(UICheckBox),
                    typeof(UIDocument),
                    typeof(UIEditText),
                    typeof(UIEllipse),
                    typeof(UIImage),
                    typeof(UILabel),
                    typeof(UIPanel),
                    typeof(UIRadioButton),
                    typeof(UIRect),
                    typeof(UIRoundedRect),
                    typeof(UIScrollablePanel),
                    typeof(UISpark),
                    typeof(UISprite),
                    typeof(UIVideo),
                    typeof(UIWindow),
                };

                ClassIconDictionary = new SortedList<int, ImageSource>(iconEmbeddedClasses.Length);
                ClassIconDictionary.Add(0, BitmapFrame.Create(GetEmbeddedResourceUri("Classes/Default.png")));

                foreach (var item in iconEmbeddedClasses)
                {
                    var uri = GetEmbeddedResourceUri(string.Format("Classes/{0}.png", item.Name));
                    ClassIconDictionary.Add(ClassIDAttribute.GetClassID(item), BitmapFrame.Create(uri));
                }
            }
        }

        static ImageSource GetClassIcon(Dictionary<string, object> o)
        {
            if (ClassIconDictionary == null)
                PreloadClassIcon();

            object classIDObject = null;
            if (o.TryGetValue("class", out classIDObject))
            {
                int classID = (int)classIDObject;
                ImageSource classIcon = null;
                if (ClassIconDictionary.TryGetValue(classID, out classIcon))
                    return classIcon;
            }

            return ClassIconDictionary[0];
        }

        static UIVisibility GetVisibility(Dictionary<string, object> o)
        {
            object valueObject = null;
            if (o.TryGetValue("visibility", out valueObject))
            {
                string value = (string)valueObject;
                switch (value[0])
                {
                    case 'V':
                        return UIVisibility.Visible;
                    case 'I':
                        return UIVisibility.Invisible;
                    case 'C':
                        return UIVisibility.Collapsed;
                    default:
                        return UIVisibility.Visible;
                }
            }
            else
                return UIVisibility.Visible;
        }

        static bool GetPickable(Dictionary<string, object> o)
        {
            object value = null;
            if (o.TryGetValue("pickable", out value))
                return (bool)value;
            else
                return true;
        }

        static List<object> GetChildren(Dictionary<string, object> o)
        {
            object childrenObject = null;
            if (o.TryGetValue("children", out childrenObject))
                return (List<object>)childrenObject;
            else
                return new List<object>();
        }

        protected override void OnClosed(EventArgs e)
        {
            Settings.Default.UIInspectorWindowX = Left;
            Settings.Default.UIInspectorWindowY = Top;
            Settings.Default.UIInspectorWindowWidth = Width;
            Settings.Default.UIInspectorWindowHeight = Height;
            Settings.Default.Save();
            App.Current.Shutdown();
            base.OnClosed(e);
        }

        private void Ready()
        {
            if (serverStream != null)
                serverStream.Dispose();

            serverStream = new NamedPipeServerStream("BibimRemoteDebugger",
                                                     PipeDirection.InOut,
                                                     NamedPipeServerStream.MaxAllowedServerInstances,
                                                     PipeTransmissionMode.Byte,
                                                     PipeOptions.Asynchronous);
            serverStreamReader = new BinaryReader(serverStream);
            serverStreamWriter = new BinaryWriter(serverStream);
            serverStream.BeginWaitForConnection(new AsyncCallback(OnConnected), null);
        }

        private void OnConnected(IAsyncResult result)
        {
            if (result.IsCompleted)
            {
                serverStream.EndWaitForConnection(result);
                serverStream.BeginRead(serverBuffer, 0, 4, new AsyncCallback(OnPacketReceived), null);
            }
            else
                Ready();
        }

        private void OnPacketReceived(IAsyncResult result)
        {
            if (result.IsCompleted == false)
            {
                Ready();
                return;
            }

            int readBytes = serverStream.EndRead(result);
            if (readBytes != 4)
            {
                Ready();
                return;
            }

            uint id = BitConverter.ToUInt32(serverBuffer, 0);
            Action postprocess = null;
            switch (id)
            {
                case UIDataPacketID:
                    string jsonString = serverStreamReader.ReadBibimString();

                    postprocess = new Action(() =>
                    {
                        var json = JsonSerializer.DeserializeData(jsonString);
                        Synchronize((Dictionary<string, object>)json);
                    });
                    break;
            }

            serverStreamWriter.Write(UIVisualSelectedPacketID);
            serverStreamWriter.Write(selectedVisualID);

            serverStream.BeginRead(serverBuffer, 0, 4, new AsyncCallback(OnPacketReceived), null);

            if (postprocess != null)
                Dispatcher.Invoke(postprocess);
        }

        private void OnTreeViewSelectedItemChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            if (e.NewValue != null)
            {
                var selectedTreeViewItem = (TreeViewItem)e.NewValue;
                if (selectedTreeViewItem != null)
                {
                    selectedVisualID = (long)selectedTreeViewItem.Tag;
                }
                //else
                //    selectedVisualID = 0;
            }
            //else
            //    selectedVisualID = 0;
        }

        private void textBoxFind_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (findingDispatcher == null)
            {
                findingDispatcher = new DispatcherTimer(TimeSpan.FromSeconds(0.5),
                                                        DispatcherPriority.Normal,
                                                        new EventHandler(findingDispatcher_Tick),
                                                        Dispatcher);
                findingDispatcher.Start();
            }
        }

        void findingDispatcher_Tick(object sender, EventArgs e)
        {
            Trace.Assert(object.ReferenceEquals(sender, findingDispatcher));
            var highlightingText = textBoxFind.Text;
            var lastHighlightingText = (string)findingDispatcher.Tag;

            if (highlightingText != lastHighlightingText)
            {
                HighlightTreeViewItemsByText(highlightingText);
                findingDispatcher.Tag = highlightingText;
            }
        }

        private void buttonFind_Click(object sender, RoutedEventArgs e)
        {
            SelectNextTreeViewItemByText(textBoxFind.Text);
            e.Handled = true;
        }

        private void textBoxFind_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                SelectNextTreeViewItemByText(textBoxFind.Text);
                e.Handled = true;
            }
        }

        private class AtValueConverter : IValueConverter
        {
            private int index;

            public AtValueConverter(int index)
            {
                this.index = index;
            }

            public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
            {
                return ((object[])value)[index];
            }

            public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
            {
                return null;
            }
        };
    }
}
