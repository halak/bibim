using System;
using System.Collections.Generic;
using System.Text;
using Halak.Bibim.Asset;
using Halak.Bibim.IO;
using Halak.Bibim.UI.Frames;
using Halak.Bibim.UI.Visuals;

namespace Halak.Bibim.UI
{
    [GameAssetWriter(typeof(UILayout))]
    public sealed class UILayoutWriter : GameAssetWriter<UILayout>
    {
        public override void Write(AssetStreamWriter writer, UILayout asset)
        {
            writer.Write(asset.ClassID);
            WriteVisual(writer, asset.Root);
        }

        #region Write
        private static void WriteVisual(AssetStreamWriter writer, UIVisual o)
        {
            if (o == null)
            {
                writer.Write((uint)0);
                return;
            }

            Type t = o.GetType();
            if (t == typeof(UIVisual))
                Write(writer, (UIVisual)o);
            else if (t == typeof(UISprite))
                Write(writer, (UISprite)o);
            else if (t == typeof(UIPanel))
                Write(writer, (UIPanel)o);
            else if (t == typeof(UIButton))
                Write(writer, (UIButton)o);
            else if (t == typeof(UIWindow))
                Write(writer, (UIWindow)o);
            else
                throw new NotSupportedException(t.ToString());
        }

        private static void WriteFrame(AssetStreamWriter writer, UIFrame o)
        {
            if (o == null)
            {
                writer.Write((uint)0);
                return;
            }

            Type t = o.GetType();
            if (t == typeof(UIFixedFrame))
                Write(writer, (UIFixedFrame)o);
            else if (t == typeof(UIFittedFrame))
                Write(writer, (UIFittedFrame)o);
            else if (t == typeof(UIAlignedFrame))
                Write(writer, (UIAlignedFrame)o);
            else
                throw new NotSupportedException(t.ToString());
         }

        private static void WriteEvent()
        {
            throw new NotImplementedException();
        }

        private static void WriteEffect()
        {
            throw new NotImplementedException();
        }

        private static void WriteTransform()
        {
            throw new NotImplementedException();
        }

        private static void WriteImage(AssetStreamWriter writer, UIImage o)
        {
            writer.WriteBibimString(o.TextureURI);
            writer.Write(o.ClippingRectangle);
        }
        #endregion

        #region WriteVisual
        private static void Write(AssetStreamWriter writer, UIElement o)
        {
            writer.Write(o.ClassID);
            writer.Write(o.ID);
            writer.WriteBibimString(o.Name);
        }

        private static void Write(AssetStreamWriter writer, UIVisual o)
        {
            Write(writer, (UIElement)o);
            writer.Write(o.Opacity);
            writer.Write(o.Shown);
            writer.Write(o.Size);
            WriteFrame(writer, o.Frame);
            // writer.Write(o.EventMap);
            // writer.Write(o.Transform);
        }

        private static void Write(AssetStreamWriter writer, UISprite o)
        {
            Write(writer, (UIVisual)o);
            WriteImage(writer, o.Image);
            writer.Write(o.AutoResize);
            writer.Write(o.HorizontalFlip);
            writer.Write(o.VerticalFlip);
        }

        private static void Write(AssetStreamWriter writer, UIPanel o)
        {
            Write(writer, (UIVisual)o);
            writer.Write(o.Children.Count);
            foreach (UIVisual item in o.Children)
                WriteVisual(writer, item);
        }

        private static void Write(AssetStreamWriter writer, UIButton o)
        {
            Write(writer, (UIPanel)o);
            WriteVisual(writer, o.NormalWindow);
            WriteVisual(writer, o.PushedWindow);
            WriteVisual(writer, o.HoveringWindow);
            writer.Write(o.HideInactives);
        }

        private static void Write(AssetStreamWriter writer, UIWindow o)
        {
            Write(writer, (UIPanel)o);
        }
        #endregion

        #region WriteFrame
        private static void Write(AssetStreamWriter writer, UIFrame o)
        {
            Write(writer, (UIElement)o);
        }

        private static void Write(AssetStreamWriter writer, UIFixedFrame o)
        {
            Write(writer, (UIFrame)o);
            writer.Write(o.Rectangle);
        }

        private static void Write(AssetStreamWriter writer, UIFittedFrame o)
        {
            Write(writer, (UIFrame)o);
        }

        private static void Write(AssetStreamWriter writer, UIAlignedFrame o)
        {
            Write(writer, (UIFrame)o);
            writer.Write((byte)o.Align);
            writer.Write(o.Offset);
            writer.Write(o.Size);
        }
        #endregion
    }
}
