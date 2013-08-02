#pragma once
#ifndef __BIBIM_EASINGCURVES_H__
#define __BIBIM_EASINGCURVES_H__

#include <Bibim/FWD.h>
#include <Bibim/GameComponent.h>
#include <Bibim/Ease.h>

namespace Bibim
{
    /// @brief 수치 보간을 위한 보간 곡선을 나타내는 GameComponent
    /// 대부분의 보간 곡선은 Field를 필요로하지 않기 때문에 Singleton-object인 경우가 많습니다.
    class EasingCurve : public GameComponent
    {
        BBAbstractComponentClass(EasingCurve, GameComponent);
        public:
            virtual ~EasingCurve();

            virtual float Ease(float t) const = 0;

        protected:
            EasingCurve();
    };

#   define BBDeclareStandardEasingCurveClass(name, func, a, b, c, d) \
                                            class name : public EasingCurve \
                                            { \
                                                BBSingletonComponentClass(name, EasingCurve, a, b, c, d); \
                                                public: \
                                                    virtual ~name() { } \
                                                    virtual float Ease(float t) const { return func(t); } \
                                            };

    BBDeclareStandardEasingCurveClass(LinearCurve,               Ease::Linear,             'E', 'C', '0', '0');
    BBDeclareStandardEasingCurveClass(EaseInQuadraticCurve,      Ease::InQuadratic,        'E', 'C', 'I', '0');
    BBDeclareStandardEasingCurveClass(EaseOutQuadraticCurve,     Ease::OutQuadratic,       'E', 'C', 'O', '0');
    BBDeclareStandardEasingCurveClass(EaseInOutQuadraticCurve,   Ease::InOutQuadratic,     'E', 'C', 'D', '0');
    BBDeclareStandardEasingCurveClass(EaseInCubicCurve,          Ease::InCubic,            'E', 'C', 'I', '1');
    BBDeclareStandardEasingCurveClass(EaseOutCubicCurve,         Ease::OutCubic,           'E', 'C', 'O', '1');
    BBDeclareStandardEasingCurveClass(EaseInOutCubicCurve,       Ease::InOutCubic,         'E', 'C', 'D', '1');
    BBDeclareStandardEasingCurveClass(EaseInQuarticCurve,        Ease::InQuartic,          'E', 'C', 'I', '2');
    BBDeclareStandardEasingCurveClass(EaseOutQuarticCurve,       Ease::OutQuartic,         'E', 'C', 'O', '2');
    BBDeclareStandardEasingCurveClass(EaseInOutQuarticCurve,     Ease::InOutQuartic,       'E', 'C', 'D', '2');
    BBDeclareStandardEasingCurveClass(EaseInQuinticCurve,        Ease::InQuintic,          'E', 'C', 'I', '3');
    BBDeclareStandardEasingCurveClass(EaseOutQuinticCurve,       Ease::OutQuintic,         'E', 'C', 'O', '3');
    BBDeclareStandardEasingCurveClass(EaseInOutQuinticCurve,     Ease::InOutQuintic,       'E', 'C', 'D', '3');
    BBDeclareStandardEasingCurveClass(EaseInSinusoidalCurve,     Ease::InSinusoidal,       'E', 'C', 'I', '4');
    BBDeclareStandardEasingCurveClass(EaseOutSinusoidalCurve,    Ease::OutSinusoidal,      'E', 'C', 'O', '4');
    BBDeclareStandardEasingCurveClass(EaseInOutSinusoidalCurve,  Ease::InOutSinusoidal,    'E', 'C', 'D', '4');
    BBDeclareStandardEasingCurveClass(EaseInExponentialCurve,    Ease::InExponential,      'E', 'C', 'I', '5');
    BBDeclareStandardEasingCurveClass(EaseOutExponentialCurve,   Ease::OutExponential,     'E', 'C', 'O', '5');
    BBDeclareStandardEasingCurveClass(EaseInOutExponentialCurve, Ease::InOutExponential,   'E', 'C', 'D', '5');
    BBDeclareStandardEasingCurveClass(EaseInCircularCurve,       Ease::InCircular,         'E', 'C', 'I', '6');
    BBDeclareStandardEasingCurveClass(EaseOutCircularCurve,      Ease::OutCircular,        'E', 'C', 'O', '6');
    BBDeclareStandardEasingCurveClass(EaseInOutCircularCurve,    Ease::InOutCircular,      'E', 'C', 'D', '6');

    /// @class Bibim::LinearCurve
    /// @brief 선형 보간 곡선
    /// @see Ease::Linear(float)

#   undef BBDeclareStandardEasingCurveClass
}

#endif