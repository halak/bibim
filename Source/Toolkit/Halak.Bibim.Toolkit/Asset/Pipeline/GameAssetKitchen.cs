using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Asset.Pipeline
{
    [GameModule('A', 'S', 'K', 'C')]
    public sealed class GameAssetKitchen : GameModule
    {
        #region Fields
        #endregion

        #region Properties
        #endregion

        #region Constructors
        public GameAssetKitchen()
        {
        }
        #endregion

        #region Methods
        public object Cook(GameAssetRecipe recipe)
        {
            return Cook(recipe, null);
        }

        public object Cook(GameAssetRecipe recipe, ICollection<KeyValuePair<string, string>> variables)
        {
            if (recipe == null || recipe.Cook == null)
                return null;

            CookingContext context = new CookingContext(this, variables);
            return recipe.Cook.CookObject(context);
        }
        #endregion
    }
}
