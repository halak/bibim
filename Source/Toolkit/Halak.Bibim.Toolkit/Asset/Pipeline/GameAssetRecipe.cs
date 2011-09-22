using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Xml;
using System.Xml.Serialization;

namespace Halak.Bibim.Asset.Pipeline
{
    [XmlRoot("Halak.BibimAssetRecipe")]
    public sealed class GameAssetRecipe
    {
        #region Fields
        private string author;
        private string comment;
        #region Static Fields
        public static readonly Type[] RecipeTypes;
        #endregion
        #endregion

        #region Properties
        public ICookable<object> Cook
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
        #endregion

        #region Constructors
        public GameAssetRecipe()
            : this(null, string.Empty, string.Empty)
        {
        }

        public GameAssetRecipe(ICookable<object> cook)
            : this(null, string.Empty, string.Empty)
        {
        }

        public GameAssetRecipe(ICookable<object> cook, string author, string comment)
        {
            Cook = cook;
            Author = author;
            Comment = comment;
        }
        #endregion

        #region Static Constructor
        static GameAssetRecipe()
        {
            List<Type> result = new List<Type>();

            Assembly assembly = Assembly.GetCallingAssembly();
            foreach (Type item in assembly.GetTypes())
            {
                if (item.IsClass &&
                    item.IsAbstract == false &&
                    item.GetConstructor(new Type[]{}) != null &&
                    item.GetInterfaces().Contains(typeof(ICookable)))
                {
                    result.Add(item);
                }
            }

            RecipeTypes = new Type[result.Count];
            result.CopyTo(RecipeTypes);
        }
        #endregion

        #region Methods
        #endregion
    }
}
