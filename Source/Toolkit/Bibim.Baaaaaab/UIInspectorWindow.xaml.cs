using System;
using System.Collections.Generic;
using System.Diagnostics;
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

        private readonly BitmapImage VISIBLE = new BitmapImage(new Uri("/Resources/VISIBLE.png", UriKind.Relative));
        private readonly BitmapImage INVISIBLE = new BitmapImage(new Uri("/Resources/INVISIBLE.png", UriKind.Relative));
        private readonly BitmapImage COLLAPSED = new BitmapImage(new Uri("/Resources/COLLAPSED.png", UriKind.Relative));
        private readonly BitmapImage PICKABLE = new BitmapImage(new Uri("/Resources/Pickable.png", UriKind.Relative));
        private readonly BitmapImage UNPICKABLE = new BitmapImage(new Uri("/Resources/Unpickable.png", UriKind.Relative));

        private NamedPipeServerStream serverStream;
        private BinaryReader serverStreamReader;
        private BinaryWriter serverStreamWriter;
        private byte[] serverBuffer;

        private long selectedVisualID;

        public UIInspectorWindow()
        {
            InitializeComponent();

            Ready();
            serverBuffer = new byte[16];
        }

        private void Synchronize(Dictionary<string, object> o)
        {
            Synchronize(treeView.Items, GetChildren(o));
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
                    subItem = new TreeViewItem();
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

                subItem.Tag = child;
                subItem.ToolTip = GenerateTooltip(child);

                if (subItem.Header == null)
                {
                    subItem.Header = new StackPanel()
                    {
                        Orientation = Orientation.Horizontal,
                        HorizontalAlignment = System.Windows.HorizontalAlignment.Center,
                        VerticalAlignment = System.Windows.VerticalAlignment.Center,
                    };
                }

                var stack = (StackPanel)subItem.Header;

                var classIcon = PrepareComponent<Image>(stack, "Class", 0);
                var nameLabel = PrepareComponent<TextBlock>(stack, "Name", 1);
                var visibilityIcon = PrepareComponent<Image>(stack, "Visibility", 2);
                var pickableIcon = PrepareComponent<Image>(stack, "Pickable", 3);

                if (classIcon.Source == null)
                {
                    string className = GetClassName(child);
                    if (string.IsNullOrEmpty(className))
                        className = "Default";

                    classIcon.Source = new BitmapImage(new Uri(string.Format("/Resources/Classes/{0}.png", className), UriKind.Relative));
                }

                nameLabel.Text = GetName(child);
                nameLabel.Margin = new Thickness(8, 0, 8, 0);
                nameLabel.HorizontalAlignment = System.Windows.HorizontalAlignment.Center;
                nameLabel.VerticalAlignment = System.Windows.VerticalAlignment.Center;

                var visibility = GetVisibility(child);
                switch (visibility)
                {
                    case UIVisibility.Visible:
                        visibilityIcon.Source = VISIBLE;
                        break;
                    case UIVisibility.Invisible:
                        nameLabel.Foreground = Brushes.Gray;
                        visibilityIcon.Source = INVISIBLE;
                        break;
                    case UIVisibility.Collapsed:
                        nameLabel.Foreground = Brushes.Gray;
                        visibilityIcon.Source = COLLAPSED;
                        break;
                }

                if (GetPickable(child))
                    pickableIcon.Source = PICKABLE;
                else
                    pickableIcon.Source = UNPICKABLE;

                changedItems.Add(subItem);

                Synchronize(subItem.Items, GetChildren(child));
            }

            for (int i = 0; i < subItems.Count; i++)
            {
                if (changedItems.Contains(subItems[i]) == false)
                    subItems.RemoveAt(i--);
            }
        }

        private static TreeViewItem FindTreeViewItem(ItemCollection items, long id, bool findAllItems = true)
        {
            foreach (TreeViewItem item in items)
            {
                var data = (Dictionary<string, object>)item.Tag;
                if (GetID(data) == id)
                    return item;

                if (findAllItems)
                {
                    var found = FindTreeViewItem(item.Items, id, true);
                    if (found != null)
                        return found;
                }
            }

            return null;
        }

        private static T PrepareComponent<T>(StackPanel header, string name, int index) where T : FrameworkElement, new()
        {
            foreach (FrameworkElement item in header.Children)
            {
                if (item.Name == name)
                    return (T)item;
            }

            var newItem = new T()
            {
                Name = name
            };
            header.Children.Insert(index, newItem);

            return newItem;
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

        static readonly Type[] IconEmbeddedClasses = 
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
        static Dictionary<int, string> ClassSimpleDictionary;
        static string GetClassName(Dictionary<string, object> o)
        {
            if (ClassSimpleDictionary == null)
            {
                ClassSimpleDictionary = new Dictionary<int,string>(IconEmbeddedClasses.Length);
                
                foreach (var item in IconEmbeddedClasses)
                    ClassSimpleDictionary.Add(ClassIDAttribute.GetClassID(item), item.Name);
            }

            object classIDObject = null;
            if (o.TryGetValue("class", out classIDObject))
            {
                int classID = Convert.ToInt32(classIDObject);

                string className = null;
                if (ClassSimpleDictionary.TryGetValue(classID, out className))
                    return className;
            }

            return string.Empty;
        }

        static UIVisibility GetVisibility(Dictionary<string, object> o)
        {
            object valueObject = null;
            if (o.TryGetValue("visibility", out valueObject))
            {
                string value = (string)valueObject;
                if (string.Compare(value, "VISIBLE", true) == 0)
                    return UIVisibility.Visible;
                else if (string.Compare(value, "INVISIBLE", true) == 0)
                    return UIVisibility.Invisible;
                else if (string.Compare(value, "COLLAPSED", true) == 0)
                    return UIVisibility.Collapsed;
                else
                    return UIVisibility.Visible;
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
                    var selectedVisual = (Dictionary<string, object>)selectedTreeViewItem.Tag;
                    selectedVisualID = Convert.ToInt64(selectedVisual["id"]);
                }
                //else
                //    selectedVisualID = 0;
            }
            //else
            //    selectedVisualID = 0;
        }
    }
}
