using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Collections.Generic
{
    public sealed class ReadOnlyDictionary<TKey, TValue> : IDictionary<TKey, TValue>
    {
        #region Fields
        private IDictionary<TKey, TValue> reference;
        #endregion

        #region Properties
        public int Count
        {
            get { return reference.Count; }
        }

        public bool IsReadOnly
        {
            get { return true; }
        }

        public ICollection<TKey> Keys
        {
            get { return reference.Keys; }
        }

        public ICollection<TValue> Values
        {
            get { return reference.Values; }
        }

        public TValue this[TKey key]
        {
            get { return reference[key]; }
            set
            {
                throw new NotSupportedException();
            }
        }
        #endregion

        #region Constructors
        public ReadOnlyDictionary(IDictionary<TKey, TValue> dictionary)
        {
            reference = dictionary;
        }
        #endregion

        #region Methods
        public void Add(TKey key, TValue value)
        {
            throw new NotSupportedException();
        }

        public bool ContainsKey(TKey key)
        {
            return reference.ContainsKey(key);
        }

        public bool Remove(TKey key)
        {
            throw new NotSupportedException();
        }

        public void Clear()
        {
            throw new NotSupportedException();
        }

        public bool TryGetValue(TKey key, out TValue value)
        {
            return reference.TryGetValue(key, out value);
        }

        public void CopyTo(KeyValuePair<TKey, TValue>[] array, int arrayIndex)
        {
            reference.CopyTo(array, arrayIndex);
        }

        public IEnumerator<KeyValuePair<TKey, TValue>> GetEnumerator()
        {
            return reference.GetEnumerator();
        }
        
        #region Explicit-Interface Implements
        void ICollection<KeyValuePair<TKey, TValue>>.Add(KeyValuePair<TKey, TValue> item)
        {
            throw new NotSupportedException();
        }

        bool ICollection<KeyValuePair<TKey, TValue>>.Contains(KeyValuePair<TKey, TValue> item)
        {
            throw new NotSupportedException();
        }

        bool ICollection<KeyValuePair<TKey, TValue>>.Remove(KeyValuePair<TKey, TValue> item)
        {
            throw new NotSupportedException();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return reference.GetEnumerator();
        }
        #endregion
        #endregion
    }
}
