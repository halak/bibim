using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using Halak.Bibim.Collections.Generic;

namespace Halak.Bibim.Asset.Pipeline
{
    public sealed class CookingContext
    {
        #region Fields
        private string baseDirectory;
        private string directory;
        private Dictionary<string, string> variables;
        private Dictionary<string, string> expandableVariables;
        private ReadOnlyDictionary<string, string> readonlyVariables;
        #endregion

        #region Properties
        public GameAssetKitchen Kitchen
        {
            get;
            private set;
        }

        public GameAssetStorage Storage
        {
            get;
            private set;
        }

        public CookingContext Parent
        {
            get;
            private set;
        }

        public string BaseDirectory
        {
            get { return baseDirectory; }
        }

        public string Directory
        {
            get { return directory; }
        }

        public ReadOnlyDictionary<string, string> Variables
        {
            get { return readonlyVariables; }
        }

        private CookingContext Root
        {
            get
            {
                CookingContext current = this;

                while (current.Parent != null)
                    current = current.Parent;

                return current;
            }
        }
        #endregion

        #region Constructors
        public CookingContext(GameAssetKitchen kitchen, string baseDirectory, string recipePath)
            : this(kitchen, kitchen.Storage, null, baseDirectory, recipePath)
        {
        }

        public CookingContext(CookingContext parent, string recipePath)
            : this(parent.Kitchen, parent.Storage, parent, parent.baseDirectory, recipePath)
        {
        }

        private CookingContext(GameAssetKitchen kitchen, GameAssetStorage storage, CookingContext parent, string baseDirectory, string recipePath)
        {
            int variableCapacity = 4;
            string directory = Path.GetDirectoryName(recipePath);

            this.Kitchen = kitchen;
            this.Storage = storage;
            this.Parent = parent;
            this.baseDirectory = baseDirectory;
            this.directory = directory;
            this.variables = new Dictionary<string, string>(variableCapacity);
            this.expandableVariables = new Dictionary<string, string>(variableCapacity);
            this.readonlyVariables = new ReadOnlyDictionary<string, string>(this.variables);

            SetVariable("Directory", directory);
            SetVariable("Path", recipePath);
        }
        #endregion

        #region Methods
        public void Store(string name, GameAsset asset)
        {
            Storage.Store(name, asset);
        }
        
        #region Variable Manipulation
        public string GetVariable(string name)
        {
            string result = null;
            if (variables.TryGetValue(name, out result))
                return result;
            else
                return string.Empty;
        }

        public void SetVariable(string name, string value)
        {
            string newName = string.Format("$({0})", name);
            variables[name] = value;
            expandableVariables[newName] = value;
        }

        public string ExpandVariables(string value)
        {
            if (value == null)
                return string.Empty;

            foreach (KeyValuePair<string, string> item in expandableVariables)
                value = value.Replace(item.Key, item.Value);

            if (Parent != null && value.Contains("$("))
                return Parent.ExpandVariables(value);
            else
                return value;
        }
        #endregion
        #endregion
    }
}
