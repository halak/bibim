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
        #region Fields
        private string author;
        private string comment;

        #region Static Fields
        private static XmlSerializer serializer;
        private static XmlWriterSettings writerSettings;
        #endregion
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

        private static XmlSerializer Serializer
        {
            get
            {
                if (serializer == null)
                {
                    ICollection<Type> classes = AssemblyUtility.FindClasses(typeof(CookingNode), true, true);

                    Type[] recipeClasses = new Type[classes.Count];
                    classes.CopyTo(recipeClasses, 0);

                    serializer = new XmlSerializer(typeof(GameAssetRecipe), recipeClasses);
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
            Serializer.Serialize(writer, recipe);
            writer.Close();
        }

        public static void Serialize(XmlWriter writer, GameAssetRecipe recipe)
        {
            Serializer.Serialize(writer, recipe);
        }

        public static GameAssetRecipe Deserialize(string path)
        {
            using (var fs = new FileStream(path, FileMode.Open, FileAccess.Read))
                return Deserialize(fs) as GameAssetRecipe;
        }

        public static GameAssetRecipe Deserialize(Stream stream)
        {
            return Serializer.Deserialize(stream) as GameAssetRecipe;
        }

        public static GameAssetRecipe Deserialize(XmlReader reader)
        {
            return Serializer.Deserialize(reader) as GameAssetRecipe;
        }
        #endregion
    }
}
