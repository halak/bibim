﻿using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using System.Xml.Schema;

namespace Halak.Bibim.Asset.Pipeline.Recipes
{
    public sealed class ImportBitmap : CookableItem<Bitmap>
    {
        #region Properties
        [XmlElement]
        public ICookable<Stream> Input
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public ImportBitmap()
            : this(null)
        {
        }

        public ImportBitmap(ICookable<Stream> input)
        {
            Input = input;
        }
        #endregion

        #region Methods
        public override Bitmap Cook(CookingContext context)
        {
            return new Bitmap(Input.Cook(context));
        }
        #endregion
    }
}
