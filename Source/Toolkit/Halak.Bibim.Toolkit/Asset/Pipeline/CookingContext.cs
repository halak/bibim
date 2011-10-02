using System;
using System.Collections.Generic;
using System.Text;
using Halak.Bibim.Collections.Generic;

namespace Halak.Bibim.Asset.Pipeline
{
    public sealed class CookingContext
    {
        #region Fields
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

        public CookingContext Parent
        {
            get;
            private set;
        }

        public string Directory
        {
            get { return directory; }
            set
            {
                directory = value ?? string.Empty;
            }
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
        public CookingContext(GameAssetKitchen kitchen, CookingContext parent, string directory)
            : this(kitchen, parent, directory, null)
        {
        }

        public CookingContext(GameAssetKitchen kitchen, CookingContext parent, string directory, ICollection<KeyValuePair<string, string>> variables)
        {
            Kitchen = kitchen;
            Parent = parent;

            int variableCapacity = (variables != null) ? variables.Count : 0;

            this.directory = directory;
            this.variables = new Dictionary<string, string>(variableCapacity);
            this.expandableVariables = new Dictionary<string, string>(variableCapacity);

            if (variables != null)
            {
                foreach (KeyValuePair<string, string> item in variables)
                    SetVariable(item.Key, item.Value);
            }
            
            readonlyVariables = new ReadOnlyDictionary<string, string>(this.variables);
        }
        #endregion

        #region Methods
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
