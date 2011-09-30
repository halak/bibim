using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using Halak.Bibim.Scripting;

namespace Halak.Bibim.Asset.Pipeline.Recipes
{
    public sealed class THPanicScriptToScript : CookingNode<Script>
    {
        #region Properties
        public CookingNode<Stream> Input
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public THPanicScriptToScript()
            : this(null)
        {
        }

        public THPanicScriptToScript(CookingNode<Stream> input)
        {
            Input = input;
        }
        #endregion

        public override Script Cook(CookingContext context)
        {
            StreamReader reader = new StreamReader(Input.Cook(context));

            while (reader.EndOfStream == false)
            {
                string line = reader.ReadLine();
            }

            reader.Close();

            return null;
        }
    }
}
