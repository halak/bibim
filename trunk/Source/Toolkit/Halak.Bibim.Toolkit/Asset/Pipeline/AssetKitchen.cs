using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Asset.Pipeline
{
    [GameModule('A', 'S', 'K', 'C')]
    public sealed class AssetKitchen : GameModule
    {
        #region Fields
        #endregion

        #region Properties
        #endregion

        #region Constructors
        public AssetKitchen()
        {
        }
        #endregion

        #region Methods
        public object Cook(AssetRecipe recipe)
        {
            return Cook(recipe, null, null);
        }

        public object Cook(AssetRecipe recipe, IDictionary<string, object> ingredients)
        {
            return Cook(recipe, ingredients, null);
        }

        public object Cook(AssetRecipe recipe, IDictionary<string, object> ingredients, IDictionary<string, string> variables)
        {
            CookingContext context = new CookingContext(ingredients, variables);

            //foreach (CookingDirection item in recipe)
            //    item.Cook(context);

            return context.GetIngredient(recipe.Result);
        }
        #endregion
    }
}
