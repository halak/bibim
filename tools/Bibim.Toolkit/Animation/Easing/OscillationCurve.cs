using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    [ClassID('E', 'C', 'O', 'C')]
    public sealed class OscillationCurve : EasingCurve
    {
        #region Mode (Nested Enum)
        public enum OscillationMode
        {
            Still,
            Crescendo,
            Decrescendo,
            PitchAndRoll,
        }
        #endregion

        #region Fields
        private int frequency;
        private float strength;
        #endregion

        #region Properties
        public OscillationMode Mode
        {
            get;
            set;
        }

        public int Frequency
        {
            get { return frequency; }
            set
            {
                frequency = Math.Max(value, 0);
            }
        }

        public float Strength
        {
            get { return strength; }
            set
            {
                strength = value;
            }
        }
        #endregion

        #region Constructors
        public OscillationCurve()
            : this(OscillationMode.Still, 8, 0.0f)
        {
        }

        public OscillationCurve(OscillationMode mode, int frequency, float strength)
        {
            Mode = mode;
            Frequency = frequency;
            Strength = strength;
        }
        #endregion

        public override float Ease(float t)
        {
            throw new NotImplementedException();
        }
    }
}
