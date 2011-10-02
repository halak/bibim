using System;
using System.Collections.Generic;
using System.Text;
using System.Xml.Serialization;
using Halak.Bibim.UI;

namespace Halak.Bibim.Asset.Pipeline.Recipes
{
    public sealed class PhotoshopDocumentToUILayout1 : CookingNode<UILayout>
    {
        #region Properties
        [XmlElement]
        public CookingNode<PhotoshopDocument> Input
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public PhotoshopDocumentToUILayout1()
        {
        }

        public PhotoshopDocumentToUILayout1(CookingNode<PhotoshopDocument> input)
        {
            Input = input;
        }
        #endregion

        public override UILayout Cook(CookingContext context)
        {
            PhotoshopDocument input = Input.Cook(context);

            throw new NotImplementedException();
        }
    }
}
