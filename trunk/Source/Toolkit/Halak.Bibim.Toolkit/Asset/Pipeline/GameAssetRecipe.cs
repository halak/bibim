﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using Halak.Bibim.Reflection;

namespace Halak.Bibim.Asset.Pipeline
{
    [XmlRoot("Halak.BibimAssetRecipe")]
    public sealed class GameAssetRecipe
    {
        #region Fields
        private string author;
        private string comment;

        #region Static Fields
        private static XmlSerializer serializer;
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
        #endregion

        #region Constructors
        public GameAssetRecipe()
            : this(null, string.Empty, string.Empty)
        {
        }

        public GameAssetRecipe(CookingNode cook)
            : this(cook, string.Empty, string.Empty)
        {
        }

        public GameAssetRecipe(CookingNode cook, string author, string comment)
        {
            Cook = cook;
            Author = author;
            Comment = comment;
        }
        #endregion
        
        #region Methods
        #endregion

        #region Static Methods
        public static void Serialize(Stream stream, GameAssetRecipe recipe)
        {
            Serializer.Serialize(stream, recipe);
        }

        public static void Serialize(XmlWriter writer, GameAssetRecipe recipe)
        {
            Serializer.Serialize(writer, recipe);
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