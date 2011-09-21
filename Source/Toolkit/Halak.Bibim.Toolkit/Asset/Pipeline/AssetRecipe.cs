using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Serialization;

namespace Halak.Bibim.Asset.Pipeline
{
    [XmlRoot("Halak.BibimRecipe")]
    public sealed class AssetRecipe// : IList<CookingDirection>
    {
        #region Fields
        private string result;
        
        private List<CookingDirection> directions;
        #endregion

        #region Properties
        [XmlAttribute]
        public string Result
        {
            get { return result; }
            set
            {
                result = value ?? string.Empty;
            }
        }
        [XmlArray]
        public List<CookingDirection> Directions
        {
            get { return directions; }
            set
            {
                directions = value;
            }
        }

        /*
        [XmlIgnore]
        public int Count
        {
            get { return directions.Count; }
        }

        [XmlIgnore]
        bool ICollection<CookingDirection>.IsReadOnly
        {
            get { return false; }
        }

        [XmlIgnore]
        public CookingDirection this[int index]
        {
            get { return directions[index]; }
            set
            {
                directions[index] = value;
            }
        }
         */
        #endregion

        #region Constructors
        public AssetRecipe()
        {
            directions = new List<CookingDirection>();
            result = string.Empty;
        }
        #endregion
        /*
        #region Methods
        public void Add(CookingDirection item)
        {
            directions.Add(item);
        }

        public void Clear()
        {
            directions.Clear();
        }

        public bool Contains(CookingDirection item)
        {
            return directions.Contains(item);
        }

        void ICollection<CookingDirection>.CopyTo(CookingDirection[] array, int arrayIndex)
        {
            directions.CopyTo(array, arrayIndex);
        }

        public bool Remove(CookingDirection item)
        {
            return directions.Remove(item);
        }
        
        public int IndexOf(CookingDirection item)
        {
            return directions.IndexOf(item);
        }
        
        public void Insert(int index, CookingDirection item)
        {
            directions.Insert(index, item);
        }
        
        public void RemoveAt(int index)
        {
            directions.RemoveAt(index);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return directions.GetEnumerator();
        }

        public IEnumerator<CookingDirection> GetEnumerator()
        {
            return directions.GetEnumerator();
        }
        #endregion*/
    }
}
