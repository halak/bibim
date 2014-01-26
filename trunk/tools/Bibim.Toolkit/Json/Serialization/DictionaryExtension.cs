using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using Bibim.Graphics;

namespace Bibim.Json.Serialization
{
    public static class DictionaryExtension
    {
        public static T Get<T>(this Dictionary<string, object> thiz, string key) where T : class
        {
            object valueObject = null;
            if (thiz.TryGetValue(key, out valueObject))
                return valueObject as T;
            else
                return null;
        }

        public static T Get<T>(this Dictionary<string, object> thiz, string key, T defaultValue = default(T)) where T : struct
        {
            object valueObject = null;
            if (thiz.TryGetValue(key, out valueObject))
                return (T)Convert.ChangeType(valueObject, typeof(T));
            else
                return defaultValue;
        }

        public static Size Get(this Dictionary<string, object> thiz, string key, Size defaultValue)
        {
            var sizeObject = thiz.Get<List<object>>(key);
            if (sizeObject != null)
            {
                System.Drawing.Size size = System.Drawing.Size.Empty;
                size.Width = (int)sizeObject[0];
                size.Height = (int)sizeObject[1];
                return size;
            }
            else
                return System.Drawing.Size.Empty;
        }

        public static BlendMode Get(this Dictionary<string, object> thiz, string key, BlendMode defaultValue)
        {
            var blendModeObject = thiz.Get<string>(key);
            BlendMode blendMode;
            if (Enum.TryParse<BlendMode>(blendModeObject, out blendMode))
                return blendMode;
            else
            {
                switch (blendModeObject.ToUpper())
                {
                    case "NORMAL": return BlendMode.Normal;
                    case "ADD": return BlendMode.Additive;
                    default: return defaultValue;
                }
            }
        }
    }
}
