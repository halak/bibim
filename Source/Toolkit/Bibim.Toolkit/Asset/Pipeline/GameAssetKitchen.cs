using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.IO;
using System.Text;

namespace Bibim.Asset.Pipeline
{
    [ClassID('A', 'S', 'K', 'C')]
    public sealed class GameAssetKitchen : GameModule
    {
        #region Fields
        #endregion

        #region Properties
        public GameAssetStorage Storage
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public GameAssetKitchen()
        {
        }

        public GameAssetKitchen(GameAssetStorage storage)
        {
            Storage = storage;
        }
        #endregion

        #region Methods
        public object Cook(string recipePath)
        {
            return Cook(string.Empty, recipePath);
        }

        public object Cook(string baseDirectory, string recipePath)
        {
            if (baseDirectory == null)
                throw new ArgumentNullException("baseDirectory");
            if (string.IsNullOrEmpty(recipePath))
                throw new ArgumentNullException("recipePath");

            GameAssetRecipe recipe = BeginCook(baseDirectory, recipePath);
            if (recipe != null)
            {
                CookingContext context = new CookingContext(this, baseDirectory, recipePath);
                context.SetVariable("AssetName", Path.GetFileNameWithoutExtension(recipePath));
                return recipe.Cook.CookObject(context);
            }
            else
                return null;
        }

        public object Cook(CookingContext parent, string recipePath)
        {
            if (parent == null)
                throw new ArgumentNullException("parent");
            if (string.IsNullOrEmpty(recipePath))
                throw new ArgumentNullException("recipePath");

            GameAssetRecipe recipe = BeginCook(parent.BaseDirectory, recipePath);
            if (recipe != null)
            {
                CookingContext context = new CookingContext(parent, recipePath);
                return recipe.Cook.CookObject(context);
            }
            else
                return null;
        }

        private GameAssetRecipe BeginCook(string baseDirectory, string recipePath)
        {
            string absolutePath = Path.Combine(baseDirectory, recipePath);
            if (File.Exists(absolutePath) == false)
                return null;

            FileStream fs = new FileStream(absolutePath, FileMode.Open, FileAccess.Read);
            GameAssetRecipe recipe = GameAssetRecipe.Deserialize(fs);
            fs.Close();

            if (recipe != null && recipe.Cook != null)
                return recipe;
            else
                return null;
        }
        #endregion
    }
}
