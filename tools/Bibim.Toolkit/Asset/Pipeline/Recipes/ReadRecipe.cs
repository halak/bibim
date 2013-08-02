using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Bibim.Asset.Pipeline.Recipes
{
    public sealed class ReadRecipe : CookingNode<object>
    {
        #region Fields
        private string input;
        #endregion

        #region Properties
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
            return context.Kitchen.Cook(context, Path.Combine(context.Directory, context.ExpandVariables(Input)));
        }
        #endregion
    }
}
