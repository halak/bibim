using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Bibim.Asset.Pipeline
{
    public sealed class GameAssetRecipe
    {
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
    }
}
