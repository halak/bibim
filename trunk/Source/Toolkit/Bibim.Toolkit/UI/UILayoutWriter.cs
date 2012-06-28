using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.Graphics;
using Bibim.IO;
using Bibim.UI.Effects;
using Bibim.UI.Events;
using Bibim.UI.Visuals;

namespace Bibim.UI
{
    [GameAssetWriter(typeof(UILayout))]
    public sealed class UILayoutWriter : GameAssetWriter<UILayout>
    {
        public override void Write(AssetStreamWriter writer, UILayout asset)
        {
            List<object> objectDictionary = new List<object>();

            writer.Write(asset.ClassID);
            WriteVisual(writer, asset.Root, objectDictionary);
        }

        #region Write
        private static bool WriteElement(AssetStreamWriter writer, UIElement o, List<object> objectDictionary)
        {
            if (o == null)
            {
                writer.Write(-1);
                return false;
            }

            int index = objectDictionary.IndexOf(o);
            if (index == -1)
            {
                objectDictionary.Add(o);
                writer.Write(objectDictionary.Count - 1);                
                return true;
            }
            else
            {
                writer.Write(index);
                return false;
            }
        }

        private static void WriteVisual(AssetStreamWriter writer, UIVisual o, List<object> objectDictionary)
        {
            if (WriteElement(writer, o, objectDictionary) == false)
                return;

            Type t = o.GetType();
            if (t == typeof(UIVisual))
                Write(writer, (UIVisual)o, objectDictionary);
            else if (t == typeof(UISprite))
                Write(writer, (UISprite)o, objectDictionary);
            else if (t == typeof(UILabel))
                Write(writer, (UILabel)o, objectDictionary);
            else if (t == typeof(UIPanel))
                Write(writer, (UIPanel)o, objectDictionary);
            else if (t == typeof(UIButton))
                Write(writer, (UIButton)o, objectDictionary);
            else if (t == typeof(UICheckBox))
                Write(writer, (UICheckBox)o, objectDictionary);
            else if (t == typeof(UIRadioButton))
                Write(writer, (UIRadioButton)o, objectDictionary);
            else if (t == typeof(UIWindow))
                Write(writer, (UIWindow)o, objectDictionary);
            else if (t == typeof(UIWindow3D))
                Write(writer, (UIWindow3D)o, objectDictionary);
            else
                throw new NotSupportedException(t.ToString());
        }

        private static void WriteEventMap(AssetStreamWriter writer, UIEventMap o, List<object> objectDictionary)
        {
            if (WriteElement(writer, o, objectDictionary) == false)
                return;

            throw new NotImplementedException();
        }

        private static void WriteEffectMap(AssetStreamWriter writer, UIEffectMap o, List<object> objectDictionary)
        {
            if (WriteElement(writer, o, objectDictionary) == false)
                return;

            Write(writer, (UIElement)o, objectDictionary);
            WriteGeometryEffect(writer, o.GeometryEffect, objectDictionary);
            writer.Write((short)o.PixelEffects.Count);
            foreach (var item in o.PixelEffects)
                WritePixelEffect(writer, item, objectDictionary);
        }

        private static void WriteGeometryEffect(AssetStreamWriter writer, UIGeometryEffect o, List<object> objectDictionary)
        {
            if (WriteElement(writer, o, objectDictionary) == false)
                return;

            Type t = o.GetType();
            throw new NotSupportedException(t.ToString());
        }

        private static void WritePixelEffect(AssetStreamWriter writer, UIPixelEffect o, List<object> objectDictionary)
        {
            if (WriteElement(writer, o, objectDictionary) == false)
                return;

            Type t = o.GetType();
            if (t == typeof(UIBlendingEffect))
                Write(writer, (UIBlendingEffect)o, objectDictionary);
            else
                throw new NotSupportedException(t.ToString());
        }
        #endregion

        #region WriteVisual
        private static void Write(AssetStreamWriter writer, UIElement o, List<object> objectDictionary)
        {
            writer.Write(o.ClassID);
            writer.Write(o.ID);
            writer.WriteBibimString(o.Name);
        }

        private static void Write(AssetStreamWriter writer, UIVisual o, List<object> objectDictionary)
        {
            Write(writer, (UIElement)o, objectDictionary);
            writer.Write((byte)o.XMode);
            writer.Write((byte)o.YMode);
            writer.Write((byte)o.WidthMode);
            writer.Write((byte)o.HeightMode);
            writer.Write(o.X);
            writer.Write(o.Y);
            writer.Write(o.Width);
            writer.Write(o.Height);
            writer.Write((byte)o.Alignment);
            writer.Write((byte)(o.Opacity * 255.0f));
            writer.Write((byte)o.Visibility);
            writer.Write((byte)o.ZOrder);
            writer.Write(o.IsPickable);
            WriteEventMap(writer, o.EventMap, objectDictionary);
            WriteEffectMap(writer, o.EffectMap, objectDictionary);
        }

        private static void Write(AssetStreamWriter writer, UISprite o, List<object> objectDictionary)
        {
            Write(writer, (UIVisual)o, objectDictionary);
            writer.Write(o.Image);
            writer.Write(o.AutoResize);
            writer.Write(o.HorizontalFlip);
            writer.Write(o.VerticalFlip);
            writer.Write(o.Mask);
        }

        private static void Write(AssetStreamWriter writer, UILabel o, List<object> objectDictionary)
        {
            Write(writer, (UIVisual)o, objectDictionary);
            writer.Write(o.Font);
            writer.WriteBibimString(o.Text);
            writer.Write(o.AutoResize);
        }

        private static void Write(AssetStreamWriter writer, UIPanel o, List<object> objectDictionary)
        {
            Write(writer, (UIVisual)o, objectDictionary);
            writer.Write(o.Children.Count);
            foreach (UIVisual item in o.Children)
                WriteVisual(writer, item, objectDictionary);
        }

        private static void Write(AssetStreamWriter writer, UIButton o, List<object> objectDictionary)
        {
            Write(writer, (UIPanel)o, objectDictionary);
            WriteVisual(writer, o.Normal, objectDictionary);
            WriteVisual(writer, o.Pushed, objectDictionary);
            WriteVisual(writer, o.Hovering, objectDictionary);
            writer.Write(o.HideInactives);
            writer.Write(o.IsFrozen);
        }

        private static void Write(AssetStreamWriter writer, UICheckBox o, List<object> objectDictionary)
        {
            Write(writer, (UIButton)o, objectDictionary);
            WriteVisual(writer, o.CheckedNormal, objectDictionary);
            WriteVisual(writer, o.CheckedPushed, objectDictionary);
            WriteVisual(writer, o.CheckedHovering, objectDictionary);
            writer.Write(o.IsChecked);
        }

        private static void Write(AssetStreamWriter writer, UIRadioButton o, List<object> objectDictionary)
        {
            Write(writer, (UICheckBox)o, objectDictionary);
        }

        private static void Write(AssetStreamWriter writer, UIWindow o, List<object> objectDictionary)
        {
            Write(writer, (UIPanel)o, objectDictionary);
        }

        private static void Write(AssetStreamWriter writer, UIWindow3D o, List<object> objectDictionary)
        {
            Write(writer, (UIWindow)o, objectDictionary);
            writer.Write(o.LocalOffset);
            writer.Write(o.GlobalOffset);
            writer.Write(o.RotationCenter);
            writer.Write(o.Rotation);
            writer.Write(o.ScaleCenter);
            writer.Write(o.Scale);
        }
        #endregion

        #region WriteGeometryEffect
        private static void Write(AssetStreamWriter writer, UIGeometryEffect o, List<object> objectDictionary)
        {
            Write(writer, (UIElement)o, objectDictionary);
        }
        #endregion

        #region WritePixelEffect
        private static void Write(AssetStreamWriter writer, UIPixelEffect o, List<object> objectDictionary)
        {
            Write(writer, (UIElement)o, objectDictionary);
        }

        private static void Write(AssetStreamWriter writer, UIBlendingEffect o, List<object> objectDictionary)
        {
            Write(writer, (UIPixelEffect)o, objectDictionary);
            writer.Write((byte)o.Mode);
        }
        #endregion
    }
}
