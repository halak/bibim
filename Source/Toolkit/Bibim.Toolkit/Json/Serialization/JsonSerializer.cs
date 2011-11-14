using System;
using System.Collections.Generic;
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
        private static readonly string IDPropertyName = "$id";
        private static readonly string TypePropertyName = "$type";
        private static readonly BindingFlags memberFlags = BindingFlags.Public |
                                                           BindingFlags.Instance |
                                                           BindingFlags.GetProperty |
                                                           BindingFlags.SetProperty |
                                                           BindingFlags.GetField |
                                                           BindingFlags.SetField;
        private Dictionary<Type, TypeConverter> typeConverters = new Dictionary<Type, TypeConverter>();
        private Dictionary<string, Type> nameTypeDictionary = new Dictionary<string, Type>();
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
            WriteObjectAsElement(writer, o, objectReferences);
        }

        private void SerializeToElement(JsonWriter writer, object o, List<object> objectReferences)
        {
            if (o == null)
                return;

            Type t = o.GetType();
            foreach (var mi in t.GetMembers(memberFlags))
            {
                object v = null;
                Type declaredType = null;
                if (mi is PropertyInfo)
                {
                    var pi = (PropertyInfo)mi;

                    if (pi.GetGetMethod() == null || pi.GetGetMethod().IsPublic == false ||
                        pi.GetSetMethod() == null || pi.GetSetMethod().IsPublic == false)
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
                if (v != null)
                {
                    if (v.GetType().IsValueType)
                    {
                        if (v.GetType().IsPrimitive)
                        {
                            if (v.GetType() == typeof(bool))
                            {
                                writer.Write((bool)v);
                            }
                            else if (v.GetType() == typeof(sbyte) ||
                                     v.GetType() == typeof(byte) ||
                                     v.GetType() == typeof(short) ||
                                     v.GetType() == typeof(ushort) ||
                                     v.GetType() == typeof(int))
                            {
                                writer.Write((int)Convert.ChangeType(v, typeof(int)));
                            }
                            else if (v.GetType() == typeof(uint) ||
                                     v.GetType() == typeof(long) ||
                                     v.GetType() == typeof(ulong))
                            {
                                writer.Write((long)Convert.ChangeType(v, typeof(long)));
                            }
                            else if (v.GetType() == typeof(ulong))
                            {
                                writer.Write((ulong)v);
                            }
                            else if (v.GetType() == typeof(float) ||
                                     v.GetType() == typeof(double))
                            {
                                writer.Write((double)Convert.ChangeType(v, typeof(double)));
                            }
                            else
                                throw new NotSupportedException(v.GetType().ToString());
                        }
                        else if (v.GetType().IsEnum)
                            writer.Write(v.GetType().GetEnumName(v));
                        else
                        {
                            TypeConverter tc = GetTypeConverter(v.GetType());
                            if (tc != null)
                                writer.Write(tc.ConvertToString(v));
                            else
                                WriteObjectAsElement(writer, v, objectReferences);
                        }
                    }
                    else if (v.GetType().IsClass)
                    {
                        if (v.GetType() == typeof(string))
                            writer.Write((string)v);
                        else
                            WriteObjectAsElement(writer, v, objectReferences);
                    }
                    else
                        throw new NotSupportedException(v.GetType().ToString());
                }
                else
                    writer.Write((string)null);
            }
        }

        private void WriteObjectAsElement(JsonWriter writer, object o, List<object> objectReferences)
        {
            if (o == null)
            {
                writer.Write((string)null);
                return;
            }

            writer.WriteObjectStart();
            int index = objectReferences.IndexOf(o);
            if (index != -1)
            {
                writer.WritePropertyName(IDPropertyName);
                writer.Write(index);
            }
            else
            {
                objectReferences.Add(o);
                int id = objectReferences.Count - 1;
                writer.WritePropertyName(IDPropertyName);
                writer.Write(id);
                writer.WritePropertyName(TypePropertyName);
                writer.Write(o.GetType().FullName);
                SerializeToElement(writer, o, objectReferences);
            }
            writer.WriteObjectEnd();
        }
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
            return DeserializeFromElement(reader, objectReferences);
        }

        private object DeserializeFromElement(JsonReader reader, List<object> objectReferences)
        {
            if (reader.Read())
            {
                switch (reader.Token)
                {
                    case JsonToken.ObjectStart:
                        return ReadObject(reader, objectReferences);
                    case JsonToken.ArrayStart:
                        return ReadArray(reader, objectReferences);
                }
            }

            return null;
        }

        private List<object> ReadArray(JsonReader reader, List<object> objectReferences)
        {
            List<object> result = new List<object>();
            bool exit = false;
            while (exit == false && reader.Read())
            {
                switch (reader.Token)
                {
                    case JsonToken.None:
                        break;
                    case JsonToken.ObjectStart:
                        result.Add(ReadObject(reader, objectReferences));
                        break;
                    case JsonToken.PropertyName:
                        break;
                    case JsonToken.ObjectEnd:
                        break;
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

            int id = (int)properties[IDPropertyName];
            if (0 <= id && id < objectReferences.Count && objectReferences[id] != null)
                return objectReferences[id];

            Type type = FindType((string)properties[TypePropertyName]);
            object result = Activator.CreateInstance(type);

            properties.Remove(IDPropertyName);
            properties.Remove(TypePropertyName);
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