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
        public CookingReport Cook(string baseDirectory, string recipePath)
        {
            if (string.IsNullOrEmpty(baseDirectory))
                throw new ArgumentNullException("baseDirectory");
            if (string.IsNullOrEmpty(recipePath))
                throw new ArgumentNullException("recipePath");

            GameAssetRecipe recipe = BeginCook(baseDirectory, recipePath);
            if (recipe != null)
            {
                CookingContext context = new CookingContext(this, baseDirectory, recipePath, recipe);
                context.AddDependency(Path.Combine(baseDirectory, recipePath));
                context.SetVariable("AssetName", Path.GetFileNameWithoutExtension(recipePath));
                return new CookingReport(recipe.Cook.CookObject(context), context);
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
                CookingContext context = new CookingContext(parent, recipePath, recipe);
                context.AddDependency(Path.Combine(parent.BaseDirectory, recipePath));
                object asset = recipe.Cook.CookObject(context);
                parent.Reference(context);
                return asset;
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

        #region CookingReport (Nested Class)
        public class CookingReport
        {
            #region Properties
            public object Asset
            {
                get;
                private set;
            }

            public ICollection<string> Dependencies
            {
                get;
                private set;
            }

            public bool CanHotload
            {
                get;
                private set;
            }
            #endregion

            #region Constructor
            public CookingReport(object asset, CookingContext context)
            {
                Asset = asset;
                Dependencies = context.Dependencies;
                CanHotload = context.CanHotload;
            }
            #endregion
        }
        #endregion
    }
}
