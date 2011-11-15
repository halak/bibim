using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Diagnostics;
using System.ComponentModel;
using System.IO;
using System.Reflection;
using System.Runtime.Serialization;
using System.Text;
using Microsoft.Xna.Framework;
using Bibim.Reflection;
using LitJson;

namespace Bibim.Json.Serialization
{
    public sealed class JsonSerializer
    {
        #region Fields
        private static JsonSerializer instance;
        private static readonly string IDPropertyName = "$id";
        private static readonly string TypePropertyName = "$type";
        private static readonly string ItemsPropertyName = "$items";
        private static readonly BindingFlags memberFlags = BindingFlags.Public |
                                                           BindingFlags.Instance |
                                                           BindingFlags.GetProperty |
                                                           BindingFlags.SetProperty |
                                                           BindingFlags.GetField |
                                                           BindingFlags.SetField;
        private Dictionary<Type, TypeConverter> typeConverters = new Dictionary<Type, TypeConverter>();
        private Dictionary<string, Type> nameTypeDictionary = new Dictionary<string, Type>();
        #endregion

        #region Properties
        public static JsonSerializer Instance
        {
            get
            {
                if (instance == null)
                    instance = new JsonSerializer();

                return instance;
            }
        }
        #endregion

        #region Constructors
        public JsonSerializer()
        {
        }
        #endregion

        #region Methods
        #region Serialization
        public void Serialize(string path, object o)
        {
            if (string.IsNullOrEmpty(path))
                throw new ArgumentException(string.Empty, "path");

            using (var sw = new StreamWriter(path, false, Encoding.UTF8))
            {
                var writer = new JsonWriter(sw) { PrettyPrint = true };
                Serialize(writer, o);
            }
        }

        public void Serialize(Stream stream, object o)
        {
            if (stream == null)
                throw new ArgumentNullException("path");

            using (var sw = new StreamWriter(stream, Encoding.UTF8))
            {
                var writer = new JsonWriter(sw) { PrettyPrint = true };
                Serialize(writer, o);
            }
        }

        private void Serialize(JsonWriter writer, object o)
        {
            if (writer == null)
                throw new ArgumentNullException("writer");
            if (o == null)
                throw new ArgumentNullException("o");

            List<object> objectReferences = new List<object>();
            objectReferences.Add(null);
            Write(writer, o, objectReferences);
        }

        private void Write(JsonWriter writer, object o, List<object> objectReferences)
        {
            if (o == null)
            {
                writer.Write((string)null);
                return;
            }

            Type t = o.GetType();
            if (t.IsClass)
            {
                if (o is string)
                    writer.Write((string)o);
                else
                    WriteObject(writer, o, objectReferences);
            }
            else if (t.IsValueType)
            {
                if (t.IsPrimitive)
                {
                    if (t == typeof(bool))
                    {
                        writer.Write((bool)o);
                    }
                    else if (t == typeof(sbyte) ||
                             t == typeof(byte) ||
                             t == typeof(short) ||
                             t == typeof(ushort) ||
                             t == typeof(int))
                    {
                        writer.Write((int)Convert.ChangeType(o, typeof(int)));
                    }
                    else if (t == typeof(uint) ||
                             t == typeof(long))
                    {
                        writer.Write((long)Convert.ChangeType(o, typeof(long)));
                    }
                    else if (t == typeof(ulong))
                    {
                        writer.Write((ulong)o);
                    }
                    else if (t == typeof(float) ||
                             t == typeof(double))
                    {
                        writer.Write((double)Convert.ChangeType(o, typeof(double)));
                    }
                    else
                        throw new NotSupportedException(t.ToString());
                }
                else if (t.IsEnum)
                {
                    writer.Write(t.GetEnumName(o));
                }
                else
                {
                    var typeConverter = GetTypeConverter(t);
                    if (typeConverter != null)
                        writer.Write(typeConverter.ConvertToString(o));
                    else
                        WriteObject(writer, o, objectReferences);
                }
            }
            else
                throw new NotSupportedException(t.ToString());
        }

        private void WriteObject(JsonWriter writer, object o, List<object> objectReferences)
        {
            writer.WriteObjectStart();
            #region Write Header ($id, $type)
            if (o.GetType().IsClass)
            {
                int index = objectReferences.IndexOf(o);
                if (index != -1)
                {
                    writer.WritePropertyName(IDPropertyName);
                    writer.Write(index);
                    writer.WriteObjectEnd();
                    return;
                }
                else
                {
                    objectReferences.Add(o);
                    int id = objectReferences.Count - 1;
                    writer.WritePropertyName(IDPropertyName);
                    writer.Write(id);
                    writer.WritePropertyName(TypePropertyName);
                    writer.Write(o.GetType().FullName);
                }
            }
            else
            {
                writer.WritePropertyName(TypePropertyName);
                writer.Write(o.GetType().FullName);
            }
            #endregion

            if (o is IDictionary)
            {
                foreach (DictionaryEntry item in (IDictionary)o)
                {
                    writer.WritePropertyName(item.Key.ToString());
                    Write(writer, item.Value, objectReferences);
                }
            }
            else if (o is NameValueCollection)
            {
                var nvc = (NameValueCollection)o;
                for (int i = 0; i < nvc.Count; i++)
                {
                    writer.WritePropertyName(nvc.Keys[i].ToString());
                    Write(writer, nvc[i], objectReferences);
                }
            }
            else if (o is StringDictionary)
            {
                foreach (DictionaryEntry item in (StringDictionary)o)
                {
                    writer.WritePropertyName(item.Key.ToString());
                    writer.Write((string)item.Value);
                }
            }
            else if (o is HybridDictionary)
            {
                foreach (DictionaryEntry item in (HybridDictionary)o)
                {
                    writer.WritePropertyName(item.Key.ToString());
                    Write(writer, item.Value, objectReferences);
                }
            }
            else if (o is IList)
            {
                writer.WritePropertyName(ItemsPropertyName);
                writer.WriteArrayStart();
                foreach (object item in (IList)o)
                {
                    Write(writer, item, objectReferences);
                }
                writer.WriteArrayEnd();
            }
            else
            {
                Type t = o.GetType();
                foreach (var mi in t.FindMembers(MemberTypes.Field | MemberTypes.Property, memberFlags, (m, fc) => { return true; }, null))
                {
                    object v = null;
                    Type declaredType = null;
                    if (mi is PropertyInfo)
                    {
                        var pi = (PropertyInfo)mi;
                        if (pi.GetGetMethod() == null || pi.GetGetMethod().IsPublic == false ||
                            pi.GetSetMethod() == null || pi.GetSetMethod().IsPublic == false)
                            continue;
                        if (pi.GetIndexParameters() != null && pi.GetIndexParameters().Length > 0)
                            continue;

                        v = pi.GetValue(o, null);
                        declaredType = pi.PropertyType;
                    }
                    else if (mi is FieldInfo)
                    {
                        var fi = (FieldInfo)mi;
                        v = fi.GetValue(o);
                        declaredType = fi.FieldType;
                    }
                    else
                        continue;

                    if (mi.IsDefined(typeof(NonSerializedAttribute), true))
                        continue;

                    writer.WritePropertyName(mi.Name);
                    Write(writer, v, objectReferences);
                }
            }
            writer.WriteObjectEnd();
        }

        //private void SerializeToElement(JsonWriter writer, object o, List<object> objectReferences)
        //{
        //    if (o == null)
        //        return;

        //    Action<string, object> writeValue = (key, value) =>
        //    {
        //        writer.WritePropertyName(key);
        //        if (value != null)
        //        {
        //            if (value.GetType().IsValueType)
        //            {
        //                if (value.GetType().IsPrimitive)
        //                {
        //                    if (value.GetType() == typeof(bool))
        //                    {
        //                        writer.Write((bool)value);
        //                    }
        //                    else if (value.GetType() == typeof(sbyte) ||
        //                             value.GetType() == typeof(byte) ||
        //                             value.GetType() == typeof(short) ||
        //                             value.GetType() == typeof(ushort) ||
        //                             value.GetType() == typeof(int))
        //                    {
        //                        writer.Write((int)Convert.ChangeType(value, typeof(int)));
        //                    }
        //                    else if (value.GetType() == typeof(uint) ||
        //                             value.GetType() == typeof(long))
        //                    {
        //                        writer.Write((long)Convert.ChangeType(value, typeof(long)));
        //                    }
        //                    else if (value.GetType() == typeof(ulong))
        //                    {
        //                        writer.Write((ulong)value);
        //                    }
        //                    else if (value.GetType() == typeof(float) ||
        //                             value.GetType() == typeof(double))
        //                    {
        //                        writer.Write((double)Convert.ChangeType(value, typeof(double)));
        //                    }
        //                    else
        //                        throw new NotSupportedException(value.GetType().ToString());
        //                }
        //                else if (value.GetType().IsEnum)
        //                    writer.Write(value.GetType().GetEnumName(value));
        //                else
        //                {
        //                    TypeConverter tc = GetTypeConverter(value.GetType());
        //                    if (tc != null)
        //                        writer.Write(tc.ConvertToString(value));
        //                    else
        //                        WriteObjectAsElement(writer, value, objectReferences);
        //                }
        //            }
        //            else if (value.GetType().IsClass)
        //            {
        //                if (value.GetType() == typeof(string))
        //                    writer.Write((string)value);
        //                else
        //                    WriteObjectAsElement(writer, value, objectReferences);
        //            }
        //            else
        //                throw new NotSupportedException(value.GetType().ToString());
        //        }
        //        else
        //            writer.Write((string)null);
        //    };

        //    if (o is IDictionary)
        //    {
        //        foreach (DictionaryEntry item in (IDictionary)o)
        //            writeValue(item.Key.ToString(), item.Value);
        //    }
        //    else if (o is NameValueCollection)
        //    {
        //        var nvc = (NameValueCollection)o;
        //        for (int i = 0; i < nvc.Count; i++)
        //            writeValue(nvc.Keys[i], nvc[i]);
        //    }
        //    else if (o is StringDictionary)
        //    {
        //        foreach (DictionaryEntry item in (StringDictionary)o)
        //            writeValue((string)item.Key, (string)item.Value);
        //    }
        //    else if (o is HybridDictionary)
        //    {
        //        foreach (DictionaryEntry item in (HybridDictionary)o)
        //            writeValue(item.Key.ToString(), item.Value);
        //    }
        //    else
        //    {
        //        Type t = o.GetType();
        //        foreach (var mi in t.FindMembers(MemberTypes.Field | MemberTypes.Property, memberFlags, (m, fc) => { return true; }, null))
        //        {
        //            object v = null;
        //            Type declaredType = null;
        //            if (mi is PropertyInfo)
        //            {
        //                var pi = (PropertyInfo)mi;
        //                if (pi.GetGetMethod() == null || pi.GetGetMethod().IsPublic == false ||
        //                    pi.GetSetMethod() == null || pi.GetSetMethod().IsPublic == false)
        //                    continue;
        //                if (pi.GetIndexParameters() != null && pi.GetIndexParameters().Length > 0)
        //                    continue;

        //                v = pi.GetValue(o, null);
        //                declaredType = pi.PropertyType;
        //            }
        //            else if (mi is FieldInfo)
        //            {
        //                var fi = (FieldInfo)mi;
        //                v = fi.GetValue(o);
        //                declaredType = fi.FieldType;
        //            }
        //            else
        //                continue;

        //            if (mi.IsDefined(typeof(NonSerializedAttribute), true))
        //                continue;

        //            writeValue(mi.Name, v);
        //        }
        //    }
        //}

        //private void WriteObjectAsElement(JsonWriter writer, object o, List<object> objectReferences)
        //{
        //    if (o == null)
        //    {
        //        writer.Write((string)null);
        //        return;
        //    }

        //    writer.WriteObjectStart();
        //    if (o.GetType().IsClass)
        //    {
        //        int index = objectReferences.IndexOf(o);
        //        if (index != -1)
        //        {
        //            writer.WritePropertyName(IDPropertyName);
        //            writer.Write(index);
        //        }
        //        else
        //        {
        //            objectReferences.Add(o);
        //            int id = objectReferences.Count - 1;
        //            writer.WritePropertyName(IDPropertyName);
        //            writer.Write(id);
        //            writer.WritePropertyName(TypePropertyName);
        //            writer.Write(o.GetType().FullName);
        //            SerializeToElement(writer, o, objectReferences);
        //        }
        //    }
        //    else
        //    {
        //        writer.WritePropertyName(TypePropertyName);
        //        writer.Write(o.GetType().FullName);
        //        SerializeToElement(writer, o, objectReferences);
        //    }
        //    writer.WriteObjectEnd();
        //}
        #endregion

        #region Deserialization
        public object Deserialize(string path)
        {
            using (var se = new StreamReader(path, true))
                return Deserialize(new JsonReader(se));
        }

        public object Deserialize(Stream stream)
        {
            using (var se = new StreamReader(stream, true))
                return Deserialize(new JsonReader(se));
        }

        private object Deserialize(JsonReader reader)
        {
            if (reader == null)
                throw new ArgumentNullException("reader");

            List<object> objectReferences = new List<object>();
            objectReferences.Add(null);
            return Read(reader, objectReferences);
        }

        private object Read(JsonReader reader, List<object> objectReferences)
        {
            if (reader.Read())
            {
                switch (reader.Token)
                {
                    case JsonToken.None:
                        return null;
                    case JsonToken.ObjectStart:
                        return ReadObject(reader, objectReferences);
                    case JsonToken.PropertyName:
                        throw new InvalidDataException();
                    case JsonToken.ObjectEnd:
                        throw new InvalidDataException();
                    case JsonToken.ArrayStart:
                        return ReadArray(reader, objectReferences);
                    case JsonToken.ArrayEnd:
                        throw new InvalidDataException();
                    case JsonToken.Int:
                    case JsonToken.Long:
                    case JsonToken.Double:
                    case JsonToken.String:
                    case JsonToken.Boolean:
                        return reader.Value;
                    case JsonToken.Null:
                        return null;
                }
            }

            return null;
        }

        //private object DeserializeFromElement(JsonReader reader, List<object> objectReferences)
        //{
        //    if (reader.Read())
        //    {
        //        switch (reader.Token)
        //        {
        //            case JsonToken.ObjectStart:
        //                return ReadObject(reader, objectReferences);
        //            case JsonToken.ArrayStart:
        //                return ReadArray(reader, objectReferences);
        //        }
        //    }

        //    return null;
        //}

        private List<object> ReadArray(JsonReader reader, List<object> objectReferences)
        {
            List<object> result = new List<object>();
            bool exit = false;
            while (exit == false && reader.Read())
            {
                switch (reader.Token)
                {
                    case JsonToken.None:
                        throw new InvalidDataException();
                    case JsonToken.ObjectStart:
                        result.Add(ReadObject(reader, objectReferences));
                        break;
                    case JsonToken.PropertyName:
                        throw new InvalidDataException();
                    case JsonToken.ObjectEnd:
                        throw new InvalidDataException();
                    case JsonToken.ArrayStart:
                        result.Add(ReadArray(reader, objectReferences));
                        break;
                    case JsonToken.ArrayEnd:
                        exit = true;
                        break;
                    case JsonToken.Int:
                    case JsonToken.Long:
                    case JsonToken.Double:
                    case JsonToken.String:
                    case JsonToken.Boolean:
                    case JsonToken.Null:
                        result.Add(reader.Value);
                        break;
                }
            }

            return result;
        }

        private object ReadObject(JsonReader reader, List<object> objectReferences)
        {
            var properties = new Dictionary<string, object>();
            string propertyName = null;
            bool exit = false;
            while (exit == false && reader.Read())
            {
                switch (reader.Token)
                {
                    case JsonToken.None:
                        break;
                    case JsonToken.ObjectStart:
                        properties.Add(propertyName, ReadObject(reader, objectReferences));
                        break;
                    case JsonToken.PropertyName:
                        propertyName = (string)reader.Value;
                        break;
                    case JsonToken.ObjectEnd:
                        exit = true;
                        break;
                    case JsonToken.ArrayStart:
                        properties.Add(propertyName, ReadArray(reader, objectReferences));
                        break;
                    case JsonToken.ArrayEnd:
                        break;
                    case JsonToken.Int:
                    case JsonToken.Long:
                    case JsonToken.Double:
                    case JsonToken.String:
                    case JsonToken.Boolean:
                    case JsonToken.Null:
                        properties.Add(propertyName, reader.Value);
                        break;
                }
            }

            int id = -1;
            if (properties.ContainsKey(IDPropertyName))
            {
                id = (int)properties[IDPropertyName];
                if (0 <= id && id < objectReferences.Count && objectReferences[id] != null)
                    return objectReferences[id];
            }

            Type type = FindType((string)properties[TypePropertyName]);
            object result = Activator.CreateInstance(type, true);

            if (0 <= id)
            {
                if (objectReferences.Count <= id)
                    objectReferences.AddRange(new object[id - objectReferences.Count + 1]);

                objectReferences[id] = result;
            }

            properties.Remove(IDPropertyName);
            properties.Remove(TypePropertyName);

            if (result is IDictionary)
            {
                var dictionary = (IDictionary)result;
                foreach (var item in properties)
                    dictionary.Add(item.Key, item.Value);
            }
            else if (result is StringDictionary)
            {
                var dictionary = (StringDictionary)result;
                foreach (var item in properties)
                    dictionary.Add(item.Key, (string)item.Value);
            }
            else if (result is NameValueCollection)
            {
                var dictionary = (NameValueCollection)result;
                foreach (var item in properties)
                    dictionary.Add(item.Key, (string)item.Value);
            }
            else if (result is HybridDictionary)
            {
                var dictionary = (HybridDictionary)result;
                foreach (var item in properties)
                    dictionary.Add(item.Key, item.Value);
            }
            else if (result is IList)
            {
                var list = (IList)result;
                foreach (var item in (List<object>)properties[ItemsPropertyName])
                    list.Add(item);
            }
            else
            {
                foreach (var item in properties)
                {
                    MemberInfo[] members = type.GetMember(item.Key, memberFlags);
                    if (members == null || members.Length == 0)
                        continue;

                    Action<object> setValue = null;
                    Type declaredType = null;
                    if (members[0] is PropertyInfo)
                    {
                        var pi = (PropertyInfo)members[0];
                        setValue = (v) => { pi.SetValue(result, v, null); };
                        declaredType = pi.PropertyType;
                    }
                    else if (members[0] is FieldInfo)
                    {
                        var fi = (FieldInfo)members[0];
                        setValue = (v) => { fi.SetValue(result, v); };
                        declaredType = fi.FieldType;
                    }
                    else
                        continue;

                    if (item.Value == null)
                    {
                        setValue(null);
                        continue;
                    }

                    if (declaredType.IsValueType)
                    {
                        if (declaredType.IsPrimitive)
                            setValue(Convert.ChangeType(item.Value, declaredType));
                        else if (declaredType.IsEnum)
                            setValue(Enum.Parse(declaredType, (string)item.Value));
                        else
                        {
                            if (item.Value is string)
                            {
                                var tc = GetTypeConverter(declaredType);
                                setValue(tc.ConvertFromString((string)item.Value));
                            }
                            else
                                setValue(item.Value);
                        }
                    }
                    else
                        setValue(item.Value);
                }
            }

            return result;
        }
        #endregion

        private TypeConverter GetTypeConverter(Type type)
        {
            TypeConverter result = null;
            if (typeConverters.TryGetValue(type, out result))
                return result;
            else
            {
                var attribute = (TypeConverterAttribute)Attribute.GetCustomAttribute(type, typeof(TypeConverterAttribute));
                if (attribute == null)
                    return null;

                Type typeConverterType = FindType(attribute.ConverterTypeName);
                if (typeConverterType == null)
                    return null;

                result = (TypeConverter)Activator.CreateInstance(typeConverterType);
                if (result != null && result.CanConvertTo(typeof(string)) && result.CanConvertFrom(typeof(string)))
                {
                    typeConverters.Add(type, result);
                    return result;
                }
                else
                    return null;
            }
        }

        private Type FindType(string fullName)
        {
            Type result = null;
            if (nameTypeDictionary.TryGetValue(fullName, out result))
                return result;
            else
            {
                foreach (var item in AppDomain.CurrentDomain.GetAssemblies())
                {
                    foreach (var t in item.GetExportedTypes())
                    {
                        if (t.FullName == fullName || t.AssemblyQualifiedName == fullName)
                        {
                            nameTypeDictionary.Add(fullName, t);
                            return t;
                        }
                    }
                }
            }

            return null;
        }
        #endregion
    }
}