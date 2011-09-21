using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using System.Xml.Schema;

namespace Halak.Bibim.Asset.Pipeline.Cook
{
    public sealed class ImportBitmap : CookingDirection
    {
        #region Fields
        private string file;
        private string output;
        #endregion

        #region Properties
        [XmlAttribute]
        public string File
        {
            get { return file; }
            set
            {
                file = value ?? string.Empty;
            }
        }

        [XmlAttribute]
        public string Output
        {
            get { return output; }
            set
            {
                output = value ?? string.Empty;
            }
        }
        #endregion

        #region Constructors
        public ImportBitmap()
            : this(string.Empty, string.Empty)
        {
        }

        public ImportBitmap(string file, string output)
        {
            this.file = file ?? string.Empty;
            this.output = output ?? string.Empty;
        }
        #endregion

        #region Methods
        public override void Cook(CookingContext context)
        {
            string actualFile = context.ExpandVariables(File);
            string actualOutput = context.ExpandVariables(Output);

            try
            {
                Bitmap bitmap = new Bitmap(actualFile);
                context.SetIngredient(actualOutput, bitmap);
            }
            catch (Exception e)
            {
                context.SetIngredient(actualOutput, null);
            }
        }
        #endregion
    }
}
