﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Shapes;
using System.Windows.Threading;
using dragonz.actb.provider;
using Microsoft.Windows.Themes;

namespace dragonz.actb.core
{
    public class AutoCompleteManager
    {
        private const int WM_NCLBUTTONDOWN = 0x00A1;
        private const int WM_NCRBUTTONDOWN = 0x00A4;

        private const int POPUP_SHADOW_DEPTH = 5;

        /*+---------------------------------------------------------------------+
          |                                                                     |
          |                  Internal States                                    |
          |                                                                     |
          +---------------------------------------------------------------------*/

        private double _itemHeight;
        private double _downWidth;
        private double _downHeight;
        private double _downTop;
        private Point _ptDown;

        private bool _popupOnTop = true;
        private bool _manualResized;
        private string _textBeforeChangedByCode;
        private bool _textChangedByCode;

        private TextBox _textBox;
        private Popup _popup;
        private SystemDropShadowChrome _chrome;
        private ListBox _listBox;
        private ScrollBar _scrollBar;
        private ResizeGrip _resizeGrip;
        private ScrollViewer _scrollViewer;
        private Thread _asyncThread;

        private IAutoCompleteDataProvider _dataProvider;
        private bool _disabled;
        private bool _asynchronous;
        private bool _autoAppend;
        private bool _supressAutoAppend;

        /*+---------------------------------------------------------------------+
          |                                                                     |
          |                     Public interface                                |
          |                                                                     |
          +---------------------------------------------------------------------*/

        public IAutoCompleteDataProvider DataProvider
        {
            get { return _dataProvider; }
            set { _dataProvider = value; }
        }

        public bool Disabled
        {
            get { return _disabled; }
            set
            {
                _disabled = value;
                if (_disabled && _popup != null)
                {
                    _popup.IsOpen = false;
                }
            }
        }

        public bool AutoCompleting
        {
            get { return _popup.IsOpen; }
        }

        public bool Asynchronous
        {
            get { return _asynchronous; }
            set { _asynchronous = value; }
        }

        public bool AutoAppend
        {
            get { return _autoAppend; }
            set { _autoAppend = value; }
        }

        /*+---------------------------------------------------------------------+
          |                                                                     |
          |                       Initialier                                    |
          |                                                                     |
          +---------------------------------------------------------------------*/

        public AutoCompleteManager()
        {
            // default constructor
        }

        public AutoCompleteManager(TextBox textBox)
        {
            AttachTextBox(textBox);
        }

        public void AttachTextBox(TextBox textBox)
        {
            Debug.Assert(_textBox == null);
            if (Application.Current.Resources.FindName("AcTb_ListBoxStyle") == null)
            {
                var myResourceDictionary = new ResourceDictionary();
                var uri = new Uri("/dragonz.actb;component/resource/Resources.xaml", UriKind.Relative);
                myResourceDictionary.Source = uri;
                Application.Current.Resources.MergedDictionaries.Add(myResourceDictionary);
            }

            //
            _textBox = textBox;
            var ownerWindow = Window.GetWindow(_textBox);
            if (ownerWindow != null)
            {
                if (ownerWindow.IsLoaded)
                {
                    Initialize();
                }
                else
                {
                    ownerWindow.Loaded += OwnerWindow_Loaded;
                }
                ownerWindow.LocationChanged += OwnerWindow_LocationChanged;
            }

            //
            //_dataProvider = new FileSysDataProvider();
        }

        private void OwnerWindow_LocationChanged(object sender, EventArgs e)
        {
            _popup.IsOpen = false;
        }

        private void OwnerWindow_Loaded(object sender, RoutedEventArgs e)
        {
            Initialize();
        }

        private void Initialize()
        {
            _listBox = new ListBox();
            var tempItem = new ListBoxItem {Content = "TEMP_ITEM_FOR_MEASUREMENT"};
            _listBox.Items.Add(tempItem);
            _listBox.Focusable = false;
            _listBox.Style = (Style) Application.Current.Resources["AcTb_ListBoxStyle"];

            _chrome = new SystemDropShadowChrome();
            _chrome.Margin = new Thickness(0, 0, POPUP_SHADOW_DEPTH, POPUP_SHADOW_DEPTH);
            _chrome.Child = _listBox;

            _popup = new Popup();
            _popup.SnapsToDevicePixels = true;
            _popup.AllowsTransparency = true;
            _popup.MinHeight = SystemParameters.HorizontalScrollBarHeight + POPUP_SHADOW_DEPTH;
            _popup.MinWidth = SystemParameters.VerticalScrollBarWidth + POPUP_SHADOW_DEPTH;
            _popup.VerticalOffset = SystemParameters.PrimaryScreenHeight + 100;
            _popup.Child = _chrome;
            _popup.IsOpen = true;

            _itemHeight = tempItem.ActualHeight;
            _listBox.Items.Clear();

            //
            GetInnerElementReferences();
            UpdateGripVisual();
            SetupEventHandlers();
        }

        private void GetInnerElementReferences()
        {
            _scrollViewer = (_listBox.Template.FindName("Border", _listBox) as Border).Child as ScrollViewer;
            _resizeGrip = _scrollViewer.Template.FindName("ResizeGrip", _scrollViewer) as ResizeGrip;
            _scrollBar = _scrollViewer.Template.FindName("PART_VerticalScrollBar", _scrollViewer) as ScrollBar;
        }

        private void UpdateGripVisual()
        {
            var rectSize = SystemParameters.VerticalScrollBarWidth;
            var triangle = _resizeGrip.Template.FindName("RG_TRIANGLE", _resizeGrip) as Path;
            var pg = triangle.Data as PathGeometry;
            pg = pg.CloneCurrentValue();
            var figure = pg.Figures[0];
            var p = figure.StartPoint;
            p.X = rectSize;
            figure.StartPoint = p;
            var line = figure.Segments[0] as PolyLineSegment;
            p = line.Points[0];
            p.Y = rectSize;
            line.Points[0] = p;
            p = line.Points[1];
            p.X = p.Y = rectSize;
            line.Points[1] = p;
            triangle.Data = pg;
        }

        private void SetupEventHandlers()
        {
            var ownerWindow = Window.GetWindow(_textBox);
            ownerWindow.PreviewMouseDown += OwnerWindow_PreviewMouseDown;
            ownerWindow.Deactivated += OwnerWindow_Deactivated;

            var wih = new WindowInteropHelper(ownerWindow);
            var hwndSource = HwndSource.FromHwnd(wih.Handle);
            var hwndSourceHook = new HwndSourceHook(HookHandler);
            hwndSource.AddHook(hwndSourceHook);
            //hwndSource.RemoveHook();?

            _textBox.TextChanged += TextBox_TextChanged;
            _textBox.PreviewKeyDown += TextBox_PreviewKeyDown;

            _listBox.PreviewMouseLeftButtonDown += ListBox_PreviewMouseLeftButtonDown;
            _listBox.MouseLeftButtonUp += ListBox_MouseLeftButtonUp;
            _listBox.PreviewMouseMove += ListBox_PreviewMouseMove;

            _resizeGrip.PreviewMouseLeftButtonDown += ResizeGrip_PreviewMouseLeftButtonDown;
            _resizeGrip.PreviewMouseMove += ResizeGrip_PreviewMouseMove;
            _resizeGrip.PreviewMouseUp += ResizeGrip_PreviewMouseUp;
        }

        /*+---------------------------------------------------------------------+
          |                                                                     |
          |                   TextBox Event Handling                            |
          |                                                                     |
          +---------------------------------------------------------------------*/

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (_textChangedByCode || Disabled || _dataProvider == null)
            {
                return;
            }
            var text = _textBox.Text;
            if (string.IsNullOrEmpty(text))
            {
                _popup.IsOpen = false;
                return;
            }
            if (_asynchronous)
            {

                if (_asyncThread != null && _asyncThread.IsAlive)
                {
                    _asyncThread.Abort();
                }
                _asyncThread = new Thread(() => {
                    var items = _dataProvider.GetItems(text);
                    var dispatcher = Application.Current.Dispatcher;
                    var currentText = dispatcher.Invoke(new Func<string>(() => _textBox.Text)).ToString();
                    if (text != currentText)
                    {
                        return;
                    }
                    dispatcher.Invoke(new Action(() => PopulatePopupList(items)));
                });
                _asyncThread.Start();
            }
            else
            {
                var items = _dataProvider.GetItems(text);
                PopulatePopupList(items);
            }
        }

        private void TextBox_PreviewKeyDown(object sender, KeyEventArgs e)
        {
            _supressAutoAppend = e.Key == Key.Delete || e.Key == Key.Back;
            if (!_popup.IsOpen)
            {
                return;
            }
            if (e.Key == Key.Enter)
            {
                _popup.IsOpen = false;
                _textBox.SelectAll();
            }
            else if (e.Key == Key.Escape)
            {
                _popup.IsOpen = false;
                e.Handled = true;
            }
            if (!_popup.IsOpen)
            {
                return;
            }
            var index = _listBox.SelectedIndex;
            if (e.Key == Key.PageUp)
            {
                if (index == -1)
                {
                    index = _listBox.Items.Count - 1;
                }
                else if (index == 0)
                {
                    index = -1;
                }
                else if (index == _scrollBar.Value)
                {
                    index -= (int) _scrollBar.ViewportSize;
                    if (index < 0)
                    {
                        index = 0;
                    }
                }
                else
                {
                    index = (int) _scrollBar.Value;
                }
            }
            else if (e.Key == Key.PageDown)
            {
                if (index == -1)
                {
                    index = 0;
                }
                else if (index == _listBox.Items.Count - 1)
                {
                    index = -1;
                }
                else if (index == _scrollBar.Value + _scrollBar.ViewportSize - 1)
                {
                    index += (int) _scrollBar.ViewportSize - 1;
                    if (index > _listBox.Items.Count - 1)
                    {
                        index = _listBox.Items.Count - 1;
                    }
                }
                else
                {
                    index = (int) (_scrollBar.Value + _scrollBar.ViewportSize - 1);
                }
            }
            else if (e.Key == Key.Up)
            {
                if (index == -1)
                {
                    index = _listBox.Items.Count - 1;
                }
                else
                {
                    --index;
                }
            }
            else if (e.Key == Key.Down)
            {
                ++index;
            }

            if (index != _listBox.SelectedIndex)
            {
                string text;
                if (index < 0 || index > _listBox.Items.Count - 1)
                {
                    text = _textBeforeChangedByCode;
                    _listBox.SelectedIndex = -1;
                }
                else
                {
                    _listBox.SelectedIndex = index;
                    _listBox.ScrollIntoView(_listBox.SelectedItem);
                    text = _listBox.SelectedItem as string;
                }
                UpdateText(text, false);
                e.Handled = true;
            }
        }

        /*+---------------------------------------------------------------------+
          |                                                                     |
          |                     ListBox Event Handling                          |
          |                                                                     |
          +---------------------------------------------------------------------*/

        private void ListBox_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            var pos = e.GetPosition(_listBox);
            var hitTestResult = VisualTreeHelper.HitTest(_listBox, pos);
            if (hitTestResult == null)
            {
                return;
            }
            var d = hitTestResult.VisualHit;
            while (d != null)
            {
                if (d is ListBoxItem)
                {
                    e.Handled = true;
                    break;
                }
                d = VisualTreeHelper.GetParent(d);
            }
        }

        private void ListBox_PreviewMouseMove(object sender, MouseEventArgs e)
        {
            if (Mouse.Captured != null)
            {
                return;
            }
            var pos = e.GetPosition(_listBox);
            var hitTestResult = VisualTreeHelper.HitTest(_listBox, pos);
            if (hitTestResult == null)
            {
                return;
            }
            var d = hitTestResult.VisualHit;
            while (d != null)
            {
                if (d is ListBoxItem)
                {
                    var item = (d as ListBoxItem);
                    item.IsSelected = true;
//                    _listBox.ScrollIntoView(item);
                    break;
                }
                d = VisualTreeHelper.GetParent(d);
            }
        }

        private void ListBox_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            ListBoxItem item = null;
            var d = e.OriginalSource as DependencyObject;
            while (d != null)
            {
                if (d is ListBoxItem)
                {
                    item = d as ListBoxItem;
                    break;
                }
                d = VisualTreeHelper.GetParent(d);
            }
            if (item != null)
            {
                _popup.IsOpen = false;
                UpdateText(item.Content as string, true);
            }
        }

        /*+---------------------------------------------------------------------+
          |                                                                     |
          |                 ResizeGrip Event Handling                           |
          |                                                                     |
          +---------------------------------------------------------------------*/

        private void ResizeGrip_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            _downWidth = _chrome.ActualWidth + POPUP_SHADOW_DEPTH;
            _downHeight = _chrome.ActualHeight + POPUP_SHADOW_DEPTH;
            _downTop = _popup.VerticalOffset;

            var p = e.GetPosition(_resizeGrip);
            p = _resizeGrip.PointToScreen(p);
            _ptDown = p;

            _resizeGrip.CaptureMouse();
        }

        private void ResizeGrip_PreviewMouseMove(object sender, MouseEventArgs e)
        {
            if (e.LeftButton != MouseButtonState.Pressed)
            {
                return;
            }
            var ptMove = e.GetPosition(_resizeGrip);
            ptMove = _resizeGrip.PointToScreen(ptMove);
            var dx = ptMove.X - _ptDown.X;
            var dy = ptMove.Y - _ptDown.Y;
            var newWidth = _downWidth + dx;

            if (newWidth != _popup.Width && newWidth > 0)
            {
                _popup.Width = newWidth;
            }
            if (PopupOnTop)
            {
                var bottom = _downTop + _downHeight;
                var newTop = _downTop + dy;
                if (newTop != _popup.VerticalOffset && newTop < bottom - _popup.MinHeight)
                {
                    _popup.VerticalOffset = newTop;
                    _popup.Height = bottom - newTop;
                }
            }
            else
            {
                var newHeight = _downHeight + dy;
                if (newHeight != _popup.Height && newHeight > 0)
                {
                    _popup.Height = newHeight;
                }
            }
        }

        private void ResizeGrip_PreviewMouseUp(object sender, MouseButtonEventArgs e)
        {
            _resizeGrip.ReleaseMouseCapture();
            if (_popup.Width != _downWidth || _popup.Height != _downHeight)
            {
                _manualResized = true;
            }
        }

        /*+---------------------------------------------------------------------+
          |                                                                     |
          |                    Window Event Handling                            |
          |                                                                     |
          +---------------------------------------------------------------------*/

        private void OwnerWindow_Deactivated(object sender, EventArgs e)
        {
            _popup.IsOpen = false;
        }

        private void OwnerWindow_PreviewMouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.Source != _textBox)
            {
                _popup.IsOpen = false;
            }
        }

        private IntPtr HookHandler(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            handled = false;

            switch (msg)
            {
                case WM_NCLBUTTONDOWN: // pass through
                case WM_NCRBUTTONDOWN:
                    _popup.IsOpen = false;
                    break;
            }
            return IntPtr.Zero;
        }

        /*+---------------------------------------------------------------------+
          |                                                                     |
          |                    AcTb State And Behaviors                         |
          |                                                                     |
          +---------------------------------------------------------------------*/

        private void PopulatePopupList(IEnumerable<string> items)
        {
            var text = _textBox.Text;
            
            _listBox.ItemsSource = items;
            if (_listBox.Items.Count == 0)
            {
                _popup.IsOpen = false;
                return;
            }
            var firstSuggestion = _listBox.Items[0] as string;
            if (_listBox.Items.Count == 1 && text.Equals(firstSuggestion, StringComparison.OrdinalIgnoreCase))
            {
                _popup.IsOpen = false;
            }
            else
            {
                _listBox.SelectedIndex = -1;
                _textBeforeChangedByCode = text;
                _scrollViewer.ScrollToHome();
                ShowPopup();

                //
                if (AutoAppend && !_supressAutoAppend && 
                     _textBox.SelectionLength == 0 && 
                     _textBox.SelectionStart == _textBox.Text.Length)
                {
                    _textChangedByCode = true;
                    try
                    {
                        string appendText;
                        var appendProvider = _dataProvider as IAutoAppendDataProvider;
                        if(appendProvider != null)
                        {
                            appendText = appendProvider.GetAppendText(text, firstSuggestion);
                        }
                        else
                        {
                            appendText = firstSuggestion.Substring(_textBox.Text.Length);
                        }
                        if(!string.IsNullOrEmpty(appendText))
                        {
                            _textBox.SelectedText = appendText;
                        }
                    }
                    finally
                    {
                        _textChangedByCode = false;
                    }
                }
            }
        }

        private bool PopupOnTop
        {
            get { return _popupOnTop; }
            set
            {
                if (_popupOnTop == value)
                {
                    return;
                }
                _popupOnTop = value;
                if (_popupOnTop)
                {
                    _resizeGrip.VerticalAlignment = VerticalAlignment.Top;
                    _scrollBar.Margin = new Thickness(0, SystemParameters.HorizontalScrollBarHeight, 0, 0);
                    _resizeGrip.LayoutTransform = new ScaleTransform(1, -1);
                    _resizeGrip.Cursor = Cursors.SizeNESW;
                }
                else
                {
                    _resizeGrip.VerticalAlignment = VerticalAlignment.Bottom;
                    _scrollBar.Margin = new Thickness(0, 0, 0, SystemParameters.HorizontalScrollBarHeight);
                    _resizeGrip.LayoutTransform = Transform.Identity;
                    _resizeGrip.Cursor = Cursors.SizeNWSE;
                }
            }
        }

        private void ShowPopup()
        {
            var popupOnTop = false;

            var p = new Point(0, _textBox.ActualHeight);
            p = _textBox.PointToScreen(p);
            var tbBottom = p.Y;

            p = new Point(0, 0);
            p = _textBox.PointToScreen(p);
            var tbTop = p.Y;

            _popup.HorizontalOffset = p.X;
            var popupTop = tbBottom;

            if (!_manualResized)
            {
                _popup.Width = _textBox.ActualWidth + POPUP_SHADOW_DEPTH;
            }

            double popupHeight;
            if (_manualResized)
            {
                popupHeight = _popup.Height;
            }
            else
            {
                var visibleCount = Math.Min(16, _listBox.Items.Count + 1);
                popupHeight = visibleCount*_itemHeight + POPUP_SHADOW_DEPTH;
            }
            var screenHeight = SystemParameters.PrimaryScreenHeight;
            if (popupTop + popupHeight > screenHeight)
            {
                if (screenHeight - tbBottom > tbTop)
                {
                    popupHeight = SystemParameters.PrimaryScreenHeight - popupTop;
                }
                else
                {
                    popupOnTop = true;
                    popupTop = tbTop - popupHeight + 4;
                    if (popupTop < 0)
                    {
                        popupTop = 0;
                        popupHeight = tbTop + 4;
                    }
                }
            }
            PopupOnTop = popupOnTop;
            _popup.Height = popupHeight;
            _popup.VerticalOffset = popupTop;

            _popup.IsOpen = true;
        }

        private void UpdateText(string text, bool selectAll)
        {
            text = text ?? string.Empty;
         
            _textChangedByCode = true;
            _textBox.Text = text;
            if (selectAll)
            {
                _textBox.SelectAll();
            }
            else
            {
                _textBox.SelectionStart = text.Length;
            }
            _textChangedByCode = false;
        }
    }
}