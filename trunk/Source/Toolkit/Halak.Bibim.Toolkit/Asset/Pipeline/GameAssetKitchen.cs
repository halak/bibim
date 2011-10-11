﻿using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.IO;
using System.Text;

namespace Halak.Bibim.Asset.Pipeline
{
    [ClassID('A', 'S', 'K', 'C')]
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
        public object Cook(string path)
        {
            return Cook(path, null);
        }

        public object Cook(string path, CookingContext parent)
        {
            if (File.Exists(path) == false)
                return null;

            string directory = Path.GetDirectoryName(path);
            string filename = Path.GetFileName(path);
            string assetName = Path.GetFileNameWithoutExtension(path);

            FileStream fs = new FileStream(path, FileMode.Open, FileAccess.Read);
            GameAssetRecipe recipe = GameAssetRecipe.Deserialize(fs);

            if (recipe != null && recipe.Cook != null)
            {
                CookingContext context = new CookingContext(this, parent, directory);
                context.SetVariable("Directory", directory);
                context.SetVariable("FileName", filename);
                if (parent == null)
                    context.SetVariable("AssetName", assetName);
                return recipe.Cook.CookObject(context);
            }
            else
                return null;
        }
        #endregion
    }
}
