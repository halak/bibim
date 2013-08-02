using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Animation
{
    public abstract class EasingCurve : GameComponent
    {
        protected EasingCurve()
        {
        }

        public abstract float Ease(float t);
    }

    #region Linear
    [ClassID('E', 'C', '0', '0')]
    public sealed class LinearCurve : EasingCurve
    {
        public static readonly LinearCurve Instance = new LinearCurve();
        private LinearCurve() { }
        public override float Ease(float t) { return Bibim.Animation.Ease.Linear(t); }
    }
    #endregion

    #region Quadratic
    [ClassID('E', 'C', 'I', '0')]
    public sealed class EaseInQuadraticCurve : EasingCurve
    {
        public static readonly EaseInQuadraticCurve Instance = new EaseInQuadraticCurve();
        private EaseInQuadraticCurve() { }
        public override float Ease(float t) { return Bibim.Animation.Ease.InQuadratic(t); }
    }

    [ClassID('E', 'C', 'O', '0')]
    public sealed class EaseOutQuadraticCurve : EasingCurve
    {
        public static readonly EaseOutQuadraticCurve Instance = new EaseOutQuadraticCurve();
        private EaseOutQuadraticCurve() { }
        public override float Ease(float t) { return Bibim.Animation.Ease.OutQuadratic(t); }
    }

    [ClassID('E', 'C', 'D', '0')]
    public sealed class EaseInOutQuadraticCurve : EasingCurve
    {
        public static readonly EaseInOutQuadraticCurve Instance = new EaseInOutQuadraticCurve();
        private EaseInOutQuadraticCurve() { }
        public override float Ease(float t) { return Bibim.Animation.Ease.InOutQuadratic(t); }
    }
    #endregion

    #region Cubic
    [ClassID('E', 'C', 'I', '1')]
    public sealed class EaseInCubicCurve : EasingCurve
    {
        public static readonly EaseInCubicCurve Instance = new EaseInCubicCurve();
        private EaseInCubicCurve() { }
        public override float Ease(float t) { return Bibim.Animation.Ease.InCubic(t); }
    }

    [ClassID('E', 'C', 'O', '1')]
    public sealed class EaseOutCubicCurve : EasingCurve
    {
        public static readonly EaseOutCubicCurve Instance = new EaseOutCubicCurve();
        private EaseOutCubicCurve() { }
        public override float Ease(float t) { return Bibim.Animation.Ease.OutCubic(t); }
    }

    [ClassID('E', 'C', 'D', '1')]
    public sealed class EaseInOutCubicCurve : EasingCurve
    {
        public static readonly EaseInOutCubicCurve Instance = new EaseInOutCubicCurve();
        private EaseInOutCubicCurve() { }
        public override float Ease(float t) { return Bibim.Animation.Ease.InOutCubic(t); }
    }
    #endregion

    #region Quartic
    [ClassID('E', 'C', 'I', '2')]
    public sealed class EaseInQuarticCurve : EasingCurve
    {
        public static readonly EaseInQuarticCurve Instance = new EaseInQuarticCurve();
        private EaseInQuarticCurve() { }
        public override float Ease(float t) { return Bibim.Animation.Ease.InQuartic(t); }
    }

    [ClassID('E', 'C', 'O', '2')]
    public sealed class EaseOutQuarticCurve : EasingCurve
    {
        public static readonly EaseOutQuarticCurve Instance = new EaseOutQuarticCurve();
        private EaseOutQuarticCurve() { }
        public override float Ease(float t) { return Bibim.Animation.Ease.OutQuartic(t); }
    }

    [ClassID('E', 'C', 'D', '2')]
    public sealed class EaseInOutQuarticCurve : EasingCurve
    {
        public static readonly EaseInOutQuarticCurve Instance = new EaseInOutQuarticCurve();
        private EaseInOutQuarticCurve() { }
        public override float Ease(float t) { return Bibim.Animation.Ease.InOutQuartic(t); }
    }
    #endregion

    #region Quintic
    [ClassID('E', 'C', 'I', '3')]
    public sealed class EaseInQuinticCurve : EasingCurve
    {
        public static readonly EaseInQuinticCurve Instance = new EaseInQuinticCurve();
        private EaseInQuinticCurve() { }
        public override float Ease(float t) { return Bibim.Animation.Ease.InQuintic(t); }
    }

    [ClassID('E', 'C', 'O', '3')]
    public sealed class EaseOutQuinticCurve : EasingCurve
    {
        public static readonly EaseOutQuinticCurve Instance = new EaseOutQuinticCurve();
        private EaseOutQuinticCurve() { }
        public override float Ease(float t) { return Bibim.Animation.Ease.OutQuintic(t); }
    }

    [ClassID('E', 'C', 'D', '3')]
    public sealed class EaseInOutQuinticCurve : EasingCurve
    {
        public static readonly EaseInOutQuinticCurve Instance = new EaseInOutQuinticCurve();
        private EaseInOutQuinticCurve() { }
        public override float Ease(float t) { return Bibim.Animation.Ease.InOutQuintic(t); }
    }
    #endregion

    #region Sinusoidal
    [ClassID('E', 'C', 'I', '4')]
    public sealed class EaseInSinusoidalCurve : EasingCurve
    {
        public static readonly EaseInSinusoidalCurve Instance = new EaseInSinusoidalCurve();
        private EaseInSinusoidalCurve() { }
        public override float Ease(float t) { return Bibim.Animation.Ease.InSinusoidal(t); }
    }

    [ClassID('E', 'C', 'O', '4')]
    public sealed class EaseOutSinusoidalCurve : EasingCurve
    {
        public static readonly EaseOutSinusoidalCurve Instance = new EaseOutSinusoidalCurve();
        private EaseOutSinusoidalCurve() { }
        public override float Ease(float t) { return Bibim.Animation.Ease.OutSinusoidal(t); }
    }

    [ClassID('E', 'C', 'D', '4')]
    public sealed class EaseInOutSinusoidalCurve : EasingCurve
    {
        public static readonly EaseInOutSinusoidalCurve Instance = new EaseInOutSinusoidalCurve();
        private EaseInOutSinusoidalCurve() { }
        public override float Ease(float t) { return Bibim.Animation.Ease.InOutSinusoidal(t); }
    }
    #endregion

    #region Exponential
    [ClassID('E', 'C', 'I', '5')]
    public sealed class EaseInExponentialCurve : EasingCurve
    {
        public static readonly EaseInExponentialCurve Instance = new EaseInExponentialCurve();
        private EaseInExponentialCurve() { }
        public override float Ease(float t) { return Bibim.Animation.Ease.InExponential(t); }
    }

    [ClassID('E', 'C', 'O', '5')]
    public sealed class EaseOutExponentialCurve : EasingCurve
    {
        public static readonly EaseOutExponentialCurve Instance = new EaseOutExponentialCurve();
        private EaseOutExponentialCurve() { }
        public override float Ease(float t) { return Bibim.Animation.Ease.OutExponential(t); }
    }

    [ClassID('E', 'C', 'D', '5')]
    public sealed class EaseInOutExponentialCurve : EasingCurve
    {
        public static readonly EaseInOutExponentialCurve Instance = new EaseInOutExponentialCurve();
        private EaseInOutExponentialCurve() { }
        public override float Ease(float t) { return Bibim.Animation.Ease.InOutExponential(t); }
    }
    #endregion

    #region Circular
    [ClassID('E', 'C', 'I', '6')]
    public sealed class EaseInCircularCurve : EasingCurve
    {
        public static readonly EaseInCircularCurve Instance = new EaseInCircularCurve();
        private EaseInCircularCurve() { }
        public override float Ease(float t) { return Bibim.Animation.Ease.InCircular(t); }
    }

    [ClassID('E', 'C', 'O', '6')]
    public sealed class EaseOutCircularCurve : EasingCurve
    {
        public static readonly EaseOutCircularCurve Instance = new EaseOutCircularCurve();
        private EaseOutCircularCurve() { }
        public override float Ease(float t) { return Bibim.Animation.Ease.OutCircular(t); }
    }

    [ClassID('E', 'C', 'D', '6')]
    public sealed class EaseInOutCircularCurve : EasingCurve
    {
        public static readonly EaseInOutCircularCurve Instance = new EaseInOutCircularCurve();
        private EaseInOutCircularCurve() { }
        public override float Ease(float t) { return Bibim.Animation.Ease.InOutCircular(t); }
    }
    #endregion
}
