using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Bibim.Asset.Pipeline.Recipes
{
    public sealed class FileToStream : CookingNode<Stream>
    {
        #region Properties
        public string Input1
        {
            get;
            set;
        }

        public string Input2
        {
            get;
            set;
        }

        public string Input3
        {
            get;
            set;
        }

        public string Input4
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        public FileToStream()
        {
        }

        public FileToStream(string input1 = null, string input2 = null, string input3 = null, string input4 = null)
        {
            Input1 = input1;
            Input2 = input2;
            Input3 = input3;
            Input4 = input4;
        }
        #endregion

        #region Methods
        public override Stream Cook(CookingContext context)
        {
            string[] paths = { Input1, Input2, Input3, Input4 };
            foreach (string item in paths)
            {
                string actualPath = Path.Combine(context.BaseDirectory, context.Directory, context.ExpandVariables(item));

                if (File.Exists(actualPath))
                {
                    context.AddDependency(actualPath);
                    return new FileStream(actualPath, FileMode.Open, FileAccess.Read);
                }
            }

            return null;
        }
        #endregion
    }
}
