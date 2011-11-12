using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using Bibim.Reflection;

namespace Bibim.Asset.Pipeline
{
    [XmlRoot]
    public sealed class GameAssetRecipe
    {
        #region Static Fields
        private static XmlSerializer oldSerializer;
        private static DataContractSerializer serializer;
        private static XmlWriterSettings writerSettings;
        #endregion

        #region Fields
        private string author;
        private string comment;
        #endregion

        #region Properties
        [XmlElement]
        public CookingNode Cook
        {
            get;
            set;
        }

        [XmlAttribute]
        public string Author
        {
            get { return author; }
            set
            {
                author = value ?? string.Empty;
            }
        }

        [XmlAttribute]
        public string Comment
        {
            get { return comment; }
            set
            {
                comment = value ?? string.Empty;
            }
        }

        [XmlAttribute]
        public bool CanHotload
        {
            get;
            set;
        }

        private static XmlSerializer OldSerializer
        {
            get
            {
                if (oldSerializer == null)
                {
                    ICollection<Type> classes = AssemblyUtility.FindClasses(typeof(CookingNode), true, true);

                    Type[] recipeClasses = new Type[classes.Count];
                    classes.CopyTo(recipeClasses, 0);

                    oldSerializer = new XmlSerializer(typeof(GameAssetRecipe), recipeClasses);
                }

                return oldSerializer;
            }
        }

        private static DataContractSerializer Serializer
        {
            get
            {
                if (serializer == null)
                {
                    ICollection<Type> classes = AssemblyUtility.FindClasses(typeof(CookingNode), true, true);

                    serializer = new DataContractSerializer(typeof(GameAssetRecipe), null, "Bibim", classes, 65536, false, true, null);
                }

                return serializer;
            }
        }

        private static XmlWriterSettings WriterSettings
        {
            get
            {
                if (writerSettings == null)
                    writerSettings = new XmlWriterSettings() { Encoding = Encoding.UTF8, Indent = true, IndentChars = "\t" };

                return writerSettings;
            }
        }
        #endregion

        #region Constructors
        public GameAssetRecipe()
            : this(null, string.Empty, string.Empty, false)
        {
        }

        public GameAssetRecipe(CookingNode cook)
            : this(cook, string.Empty, string.Empty, false)
        {
        }

        public GameAssetRecipe(CookingNode cook, string author, string comment, bool canHotload)
        {
            Cook = cook;
            Author = author;
            Comment = comment;
            CanHotload = canHotload;
        }
        #endregion
        
        #region Methods
        #endregion

        #region Static Methods
        public static void Serialize(string path, GameAssetRecipe recipe)
        {
            using (var fs = new FileStream(path, FileMode.Create, FileAccess.Write))
                Serialize(fs, recipe);
        }

        public static void Serialize(Stream stream, GameAssetRecipe recipe)
        {
            var writer = XmlWriter.Create(stream, WriterSettings);
            OldSerializer.Serialize(writer, recipe);
            writer.Close();
        }

        public static void Serialize(XmlWriter writer, GameAssetRecipe recipe)
        {
            OldSerializer.Serialize(writer, recipe);
        }

        public static GameAssetRecipe Deserialize(string path)
        {
            using (var fs = new FileStream(path, FileMode.Open, FileAccess.Read))
            {
                try
                {
                    return Serializer.ReadObject(fs) as GameAssetRecipe;
                }
                catch (Exception)
                {
                    var result = OldSerializer.Deserialize(fs) as GameAssetRecipe;
                    if (result != null)
                    {
                        Serialize(path, result);
                        return result;
                    }
                    else
                        return null;
                }
            }
        }

        public static GameAssetRecipe Deserialize(Stream stream)
        {
            try
            {
                return Serializer.ReadObject(stream) as GameAssetRecipe;
            }
            catch (Exception)
            {
                return OldSerializer.Deserialize(stream) as GameAssetRecipe;
            }
        }

        public static GameAssetRecipe Deserialize(XmlReader reader)
        {
            try
            {
                return Serializer.ReadObject(reader) as GameAssetRecipe;
            }
            catch (Exception)
            {
                return OldSerializer.Deserialize(reader) as GameAssetRecipe;
            }
        }
        #endregion
    }
}
