using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;

namespace Bibim.UI.Effects
{
    [ClassID('U', 'F', 'X', 'M')]
    public sealed class UIEffectMap : UIElement
    {
        #region Fields
        private List<UIPixelEffect> pixelEffects;
        private ReadOnlyCollection<UIPixelEffect> readonlyPixelEffects;
        #endregion

        #region Properties
        public UIGeometryEffect GeometryEffect
        {
            get;
            set;
        }

        public IList<UIPixelEffect> PixelEffects
        {
            get { return readonlyPixelEffects; }
        }
        #endregion

        #region Constructors
        public UIEffectMap()
        {
            GeometryEffect = null;
            pixelEffects = new List<UIPixelEffect>();
            readonlyPixelEffects = new ReadOnlyCollection<UIPixelEffect>(pixelEffects);
        }
        #endregion

        #region Methods
        public void Insert(UIPixelEffect item)
        {
            if (pixelEffects.Count <= item.SlotIndex)
                pixelEffects.AddRange(new UIPixelEffect[item.SlotIndex - pixelEffects.Count + 1]);

            pixelEffects[item.SlotIndex] = item;
        }

        public bool Remove(UIPixelEffect item)
        {
            return pixelEffects.Remove(item);
        }

        public UIPixelEffect GetPixelEffect(int index)
        {
            if (0 <= index && index < pixelEffects.Count)
                return pixelEffects[index];
            else
                return null;
        }
        #endregion
    }
}
