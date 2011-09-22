using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Serialization;

namespace Halak.Bibim.Asset.Pipeline.Recipes
{
    public sealed class CookAsset : CookingNode<object>
    {
        #region Fields
        private string input;
        #endregion

        #region Properties
        [XmlAttribute]
        public string Input
        {
            get { return input; }
            set
            {
                input = value ?? string.Empty;
            }
        }
        #endregion

        #region Constructors
        public CookAsset()
            : this(string.Empty)
        {
        }

        public CookAsset(string input)
        {
            Input = input;
        }
        #endregion

        public override object Cook(CookingContext context)
        {
            string path = context.ExpandVariables(Input);
            FileStream fs = new FileStream(path, FileMode.Open, FileAccess.Read);

            GameAssetRecipe recipe = GameAssetRecipe.Deserialize(fs);
            return context.Kitchen.Cook(recipe, context.Variables);
        }
    }
}
