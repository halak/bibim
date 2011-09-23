using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Serialization;

namespace Halak.Bibim.Asset.Pipeline.Recipes
{
    public sealed class ReadRecipe : CookingNode<object>
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
        public ReadRecipe()
            : this(string.Empty)
        {
        }

        public ReadRecipe(string input)
        {
            Input = input;
        }
        #endregion

        #region Method
        public override object Cook(CookingContext context)
        {
            return context.Kitchen.Cook(Path.Combine(context.Directory, context.ExpandVariables(Input)), context);
        }
        #endregion
    }
}
