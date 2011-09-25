using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using Halak.Bibim.UI;

namespace Halak.Bibim.Asset.Pipeline.Recipes
{
    public sealed class PhotoshopDocumentToUILayout : CookingNode<UILayout>
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
        public PhotoshopDocumentToUILayout()
        {
        }

        public PhotoshopDocumentToUILayout(CookingNode<PhotoshopDocument> input)
        {
            Input = input;
        }
        #endregion

        public override UILayout Cook(CookingContext context)
        {
            PhotoshopDocument photoshop = Input.Cook(context);

            throw new NotImplementedException();
        }
    }
}
