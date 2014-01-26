using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.IO;
using System.Text;
using Bibim.Json.Serialization;

namespace Bibim.Asset.Pipeline
{
    [ClassID('A', 'S', 'K', 'C')]
    public sealed partial class GameAssetKitchen : GameModule
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
            LoadBuiltinRecipes();
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
            GameAssetRecipe recipe = null;
            string absolutePath = Path.Combine(baseDirectory, recipePath);
            if (File.Exists(absolutePath) == false)
                throw new FileNotFoundException("Recipe file not found.", absolutePath);

            recipe = JsonSerializer.Instance.Deserialize(absolutePath) as GameAssetRecipe;
            if (recipe != null && recipe.Cook != null)
                return recipe;

            using (var fs = new FileStream(absolutePath, FileMode.Open, FileAccess.Read))
            {
                var data = JsonSerializer.DeserializeData(fs) as Dictionary<string, object>;
                if (data != null)
                    recipe = CreateBuiltinRecipe(absolutePath, data);

                if (recipe != null)
                    return recipe;
            }

            recipe = FindBuiltinRecipe(absolutePath);
            if (recipe != null)
                return recipe;
            else
                throw new InvalidDataException(string.Format("couldn't guess recipe. ({0})", absolutePath));
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
