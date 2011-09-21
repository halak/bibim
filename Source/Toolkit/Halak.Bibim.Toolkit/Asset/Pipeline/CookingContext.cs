using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Halak.Bibim.Collections.Generic;

namespace Halak.Bibim.Asset.Pipeline
{
    public sealed class CookingContext
    {
        #region Fields
        private Dictionary<string, object> ingredients;
        private Dictionary<string, string> variables;
        private Dictionary<string, string> expandableVariables;

        private ReadOnlyDictionary<string, object> readonlyIngredients;
        private ReadOnlyDictionary<string, string> readonlyVariables;
        #endregion

        #region Properties
        public ReadOnlyDictionary<string, object> Ingredients
        {
            get { return readonlyIngredients; }
        }

        public ReadOnlyDictionary<string, string> Variables
        {
            get { return readonlyVariables; }
        }
        #endregion

        #region Constructors
        public CookingContext()
            : this(null, null)
        {
        }

        public CookingContext(IDictionary<string, object> ingredients, IDictionary<string, string> variables)
        {
            int ingredientCapacity = (ingredients != null) ? ingredients.Count : 0;
            int variableCapacity = (variables != null) ? variables.Count : 0;

            this.ingredients = new Dictionary<string, object>(ingredientCapacity);
            this.variables = new Dictionary<string, string>(variableCapacity);
            this.expandableVariables = new Dictionary<string, string>(variableCapacity);

            if (ingredients != null)
            {
                foreach (KeyValuePair<string, object> item in ingredients)
                    SetIngredient(item.Key, item.Value);
            }

            if (variables != null)
            {
                foreach (KeyValuePair<string, string> item in variables)
                    SetVariable(item.Key, item.Value);
            }
            
            readonlyIngredients = new ReadOnlyDictionary<string, object>(ingredients);
            readonlyVariables = new ReadOnlyDictionary<string, string>(variables);
        }
        #endregion

        #region Methods
        public object GetIngredient(string name)
        {
            object result = null;
            if (ingredients.TryGetValue(name, out result))
                return result;
            else
                return null;
        }

        public void SetIngredient(string name, object value)
        {
            ingredients[name] = value;
        }

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

            return value;
        }
        #endregion
    }
}
