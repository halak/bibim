using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using Bibim.Reflection;
using Bibim.Json.Serialization;
using OldXmlSerializer = System.Xml.Serialization.XmlSerializer;

namespace Bibim.Asset.Pipeline
{
    [XmlRoot]
    public sealed class GameAssetRecipe
    {
        #region Static Fields
        private static OldXmlSerializer oldSerializer;
        private static JsonSerializer serializer;
        private static XmlWriterSettings writerSettings;
        #endregion

        #region Fields
        private string author;
        private string comment;
        #endregion

        #region Properties
        public CookingNode Cook
        {
            get;
            set;
        }

        public string Author
        {
            get { return author; }
            set
            {
                author = value ?? string.Empty;
            }
        }

        public string Comment
        {
            get { return comment; }
            set
            {
                comment = value ?? string.Empty;
            }
        }

        public bool CanHotload
        {
            get;
            set;
        }

        private static OldXmlSerializer OldSerializer
        {
            get
            {
                if (oldSerializer == null)
                {
                    ICollection<Type> classes = AssemblyUtility.FindClasses(typeof(CookingNode), true, true);

                    Type[] recipeClasses = new Type[classes.Count];
                    classes.CopyTo(recipeClasses, 0);

                    oldSerializer = new OldXmlSerializer(typeof(GameAssetRecipe), recipeClasses);
                }

                return oldSerializer;
            }
        }

        private static JsonSerializer Serializer
        {
            get
            {
                if (serializer == null)
                    serializer = new JsonSerializer();

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
            Serializer.Serialize(path, recipe);
        }

        public static void Serialize(Stream stream, GameAssetRecipe recipe)
        {
            Serializer.Serialize(stream, recipe);
        }

        //public static void Serialize(XmlWriter writer, GameAssetRecipe recipe)
        //{
        //    Serializer.Serialize(writer, recipe);
        //}

        public static GameAssetRecipe Deserialize(string path)
        {
            using (var fs = new FileStream(path, FileMode.Open, FileAccess.Read))
            {
                try
                {
                    var result = Serializer.Deserialize(fs) as GameAssetRecipe;
                    if (result != null)
                    {
                        fs.Close();
                        Serialize(path, result);
                    }

                    return result;
                }
                catch (Exception ex)
                {
                    using (var fs2 = new FileStream(path, FileMode.Open, FileAccess.Read))
                    {
                        var result = OldSerializer.Deserialize(fs2) as GameAssetRecipe;
                        if (result != null)
                        {
                            fs2.Close();
                            Serialize(path, result);
                            return result;
                        }
                        else
                            return null;
                    }
                }
            }
        }

        public static GameAssetRecipe Deserialize(Stream stream)
        {
            //try
            //{
            //    return Serializer.Deserialize(stream) as GameAssetRecipe;
            //}
            //catch (Exception)
            {
                return OldSerializer.Deserialize(stream) as GameAssetRecipe;
            }
        }

        public static GameAssetRecipe Deserialize(XmlReader reader)
        {
            //try
            //{
            //    return Serializer.Deserialize(reader) as GameAssetRecipe;
            //}
            //catch (Exception)
            {
                return OldSerializer.Deserialize(reader) as GameAssetRecipe;
            }
        }
        #endregion
    }
}
