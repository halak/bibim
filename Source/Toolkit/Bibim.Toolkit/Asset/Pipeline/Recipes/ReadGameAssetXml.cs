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
    public sealed class ReadGameAssetXml : CookingNode<GameAsset>
    {
        #region Fields
        private Type outputType;
        #endregion

        #region Properties
        [XmlElement]
        public CookingNode<Stream> Input
        {
            get;
            set;
        }

        [XmlElement]
        public Type OutputType
        {
            get { return outputType; }
            set
            {
                if (outputType != value)
                {
                    if (value != null && value.IsSubclassOf(typeof(GameAsset)) == false)
                        throw new ArgumentException("value is GameAsset == false", "value");

                    outputType = value;
                }
            }
        }
        #endregion

        #region Constructors
        public ReadGameAssetXml()
            : this(null, null)
        {
        }

        public ReadGameAssetXml(CookingNode<Stream> input)
            : this(input, null)
        {
        }

        public ReadGameAssetXml(CookingNode<Stream> input, Type outputType)
        {
            Input = input;
            OutputType = outputType;
        }
        #endregion

        #region Method
        public override GameAsset Cook(CookingContext context)
        {
            Stream input = Input.Cook(context);
            XmlSerializer serializer = new XmlSerializer(outputType);

            return (GameAsset)serializer.Deserialize(input);
        }
        #endregion
    }
}
