using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using Bibim.Collections.Generic;

namespace Bibim.Asset.Pipeline
{
    public sealed class CookingContext
    {
        #region Fields
        private string baseDirectory;
        private string directory;
        private Dictionary<string, string> variables;
        private Dictionary<string, string> expandableVariables;
        private ReadOnlyDictionary<string, string> readonlyVariables;

        private SortedSet<string> dependencies;
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

        public ICollection<string> Dependencies
        {
            get { return dependencies; }
        }

        public bool CanHotload
        {
            get;
            private set;
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
        public CookingContext()
            : this(null, null, null, null, null, null)
        {
        }

        public CookingContext(GameAssetKitchen kitchen, string baseDirectory, string recipePath, GameAssetRecipe recipe)
            : this(kitchen, kitchen.Storage, null, baseDirectory, recipePath, recipe)
        {
        }

        public CookingContext(CookingContext parent, string recipePath, GameAssetRecipe recipe)
            : this(parent.Kitchen, parent.Storage, parent, parent.baseDirectory, recipePath, recipe)
        {
        }

        private CookingContext(GameAssetKitchen kitchen, GameAssetStorage storage, CookingContext parent, string baseDirectory, string recipePath, GameAssetRecipe recipe)
        {
            int variableCapacity = 4;
            string directory = Path.GetDirectoryName(recipePath);

            this.Kitchen = kitchen;
            this.Storage = storage;
            this.Parent = parent;
            this.baseDirectory = baseDirectory ?? string.Empty;
            this.directory = directory ?? string.Empty;
            this.variables = new Dictionary<string, string>(variableCapacity);
            this.expandableVariables = new Dictionary<string, string>(variableCapacity);
            this.readonlyVariables = new ReadOnlyDictionary<string, string>(this.variables);

            this.dependencies = new SortedSet<string>();
            this.CanHotload = recipe != null ? recipe.CanHotload : false;

            SetVariable("Directory", directory);
            SetVariable("Path", recipePath);
        }
        #endregion

        #region Methods
        public void AddDependency(string item)
        {
            dependencies.Add(item);
        }

        public void Store(string name, GameAsset asset)
        {
            Storage.Store(name, asset);
        }

        public void Reference(CookingContext context)
        {
            foreach (string item in context.Dependencies)
                dependencies.Add(item);

            if (context.CanHotload == false)
                CanHotload = false;
        }
        
        #region Variable Manipulation
        public string GetVariable(string name)
        {
            string result = null;
            if (variables.TryGetValue(name, out result))
                return result;
            else
            {
                if (Parent != null)
                    return Parent.GetVariable(name);
                else
                    return string.Empty;
            }
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
