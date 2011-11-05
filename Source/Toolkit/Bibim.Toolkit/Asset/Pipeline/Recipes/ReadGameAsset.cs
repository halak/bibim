using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using Bibim.Graphics;
using Microsoft.Xna.Framework;

namespace Bibim.Asset.Pipeline.Recipes
{
    public sealed class ReadGameAsset : CookingNode<GameAsset>
    {
        #region Properties
        [XmlElement]
        public GameAsset Input
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public ReadGameAsset()
        {
        }

        public ReadGameAsset(GameAsset input)
        {
            Input = input;
        }
        #endregion

        #region Method
        public override GameAsset Cook(CookingContext context)
        {
            return Input;
        }
        #endregion
    }
}
