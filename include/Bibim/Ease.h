#pragma once
#ifndef __BIBIM_EASE_H__
#define __BIBIM_EASE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Math.h>

    namespace Bibim
    {
        /// 고품격 수치 보간을 위한 Ease 함수들을 정의한 static class.
        class Ease
        {
            BBThisIsStaticClass(Ease);
            public:
                static inline float Linear(float t);
                static inline float InQuadratic(float t);
                static inline float OutQuadratic(float t);
                static inline float InOutQuadratic(float t);
                static inline float InCubic(float t);
                static inline float OutCubic(float t);
                static inline float InOutCubic(float t);
                static inline float InQuartic(float t);
                static inline float OutQuartic(float t);
                static inline float InOutQuartic(float t);
                static inline float InQuintic(float t);
                static inline float OutQuintic(float t);
                static inline float InOutQuintic(float t);
                static inline float InSinusoidal(float t);
                static inline float OutSinusoidal(float t);
                static inline float InOutSinusoidal(float t);
                static inline float InExponential(float t);
                static inline float OutExponential(float t);
                static inline float InOutExponential(float t);
                static inline float InCircular(float t);
                static inline float OutCircular(float t);
                static inline float InOutCircular(float t);
                static inline float InElastic(float t, float amplitude, float period);
                static inline float OutElastic(float t, float amplitude, float period);
                static inline float InOutElastic(float t, float amplitude, float period);
                static inline float InBack(float t);
                static inline float OutBack(float t);
                static inline float InOutBack(float t);
                static inline float InBack(float t, float overshoot);
                static inline float OutBack(float t, float overshoot);
                static inline float InOutBack(float t, float overshoot);

                static const float DefaultBackOvershoot; ///< using InBack, OutBack, InOutBack
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        float Ease::Linear(float t)
        {
            return t;
        }

        float Ease::InQuadratic(float t)
        {
            return t * t;
        }

        float Ease::OutQuadratic(float t)
        {
            return -1.0f * t * (t - 2.0f);
        }

        float Ease::InOutQuadratic(float t)
        {
            t *= 2.0f;
            if (t < 1.0f)
                return +0.5f * t * t;
            else
                return -0.5f * ((t - 1.0f) * (t - 3.0f) - 1.0f);
        }

        float Ease::InCubic(float t)
        {
            return t * t * t;
        }

        float Ease::OutCubic(float t)
        {
            t -= 1.0f;
            return t * t * t + 1.0f;
        }

        float Ease::InOutCubic(float t)
        {
            t *= 2.0f;
            if (t < 1.0f)
                return +0.5f * t * t * t;
            else
            {
                t -= 2.0f;
                return +0.5f * (t * t * t + 2.0f);
            }
        }

        float Ease::InQuartic(float t)
        {
            return t * t * t * t;
        }

        float Ease::OutQuartic(float t)
        {
            t -= 1.0f;
            return -1.0f * t * t * t * t - 1.0f;
        }

        float Ease::InOutQuartic(float t)
        {
            t *= 2.0f;
            if (t < 1.0f)
                return +0.5f * t * t * t * t;
            else
            {
                t -= 2.0f;
                return -0.5f * (t * t * t * t - 2.0f);
            }
        }

        float Ease::InQuintic(float t)
        {
            return t * t * t * t * t;
        }

        float Ease::OutQuintic(float t)
        {
            t -= 1.0f;
            return t * t * t * t * t + 1.0f;
        }

        float Ease::InOutQuintic(float t)
        {
            t *= 2.0f;
            if (t < 1.0f)
                return +0.5f * t * t * t * t * t;
            else
            {
                t -= 2.0f;
                return +0.5f * (t * t * t * t * t + 2.0f);
            }
        }

        float Ease::InSinusoidal(float t)
        {
            return -1.0f * Math::Cos(t * Math::PiOver2) + 1.0f;
        }

        float Ease::OutSinusoidal(float t)
        {
            return Math::Sin(t * Math::PiOver2);
        }

        float Ease::InOutSinusoidal(float t)
        {
            return -0.5f * (Math::Cos(t * Math::Pi) - 1.0f);
        }

        float Ease::InExponential(float t)
        {
            if (t > 0.0f)
                return Math::Pow(2.0f, 10.0f * (t - 1.0f));
            else
                return 0.0f;
        }

        float Ease::OutExponential(float t)
        {
            if (t < 1.0f)
                return -Math::Pow(2.0f, -10.0f * t) + 1.0f;
            else
                return 1.0f;
        }

        float Ease::InOutExponential(float t)
        {
            if (t == 0.0f)
                return 0.0f;
            if (t == 1.0f)
                return 1.0f;
            
            t *= 2.0f;
            if (t < 1.0f)
                return 0.5f * Math::Pow(2.0f, 10.0f * (t - 1.0f));
            else
                return 0.5f * (-Math::Pow(2.0f, -10.0f * (t - 1.0f)) + 2.0f);
        }

        float Ease::InCircular(float t)
        {
            return -1.0f * (Math::Sqrt(1.0f - t * t) - 1.0f);
        }

        float Ease::OutCircular(float t)
        {
            t -= 1.0f;
            return Math::Sqrt(1.0f - t * t);
        }

        float Ease::InOutCircular(float t)
        {
            t *= 2.0f;
            if (t < 1.0f)
                return -0.5f * (Math::Sqrt(1.0f - t * t) - 1.0f);
            else
            {
                t -= 2.0f;
                return +0.5f * (Math::Sqrt(1.0f - t * t) + 1.0f);
            }
        }

        float Ease::InElastic(float t, float amplitude, float period)
        {
            if (t == 0.0f)
                return 0.0f;
            if (t == 1.0f)
                return 1.0f;
            if (period == 0.0f)
                period = 0.3f;

            float s = 0.0f;
            if (amplitude < 1.0f)
            {
                amplitude = 1.0f;
                s = period * 0.25f;
            }
            else
                s = period / Math::TwoPi * Math::Asin(1.0f / amplitude);

            t -= 1.0f;
            return -(amplitude * Math::Pow(2.0f, 10.0f * t) * Math::Sin((t - s) * Math::TwoPi / period));
        }

        float Ease::OutElastic(float t, float amplitude, float period)
        {
            if (t == 0.0f)
                return 0.0f;
            if (t == 1.0f)
                return 1.0f;
            if (period == 0.0f)
                period = 0.3f;

            float s = 0.0f;
            if (amplitude < 1.0f)
            {
                amplitude = 1.0f;
                s = period * 0.25f;
            }
            else
                s = period / Math::TwoPi * Math::Asin(1.0f / amplitude);

            return amplitude * Math::Pow(2.0f, -10.0f * t) * Math::Sin((t - s) * Math::TwoPi / period) + 1.0f;
        }

        float Ease::InOutElastic(float t, float amplitude, float period)
        {
            if (t == 0.0f)
                return 0.0f;
            if (t == 1.0f)
                return 1.0f;
            if (period == 0.0f) 
                period = 0.3f * 1.5f;

            float s = 0.0f;
            if (amplitude < 1.0f)
            {
                amplitude = 1.0f;
                s = period * 0.25f;
            }
            else
                s = period / Math::TwoPi * Math::Asin(1.0f / amplitude);

            t *= 2.0f;

            if (t < 1.0f)
            {
                t -= 1.0f;
                return -0.5f * (amplitude * Math::Pow(2.0f, 10.0f * t) * Math::Sin((t - s) * Math::TwoPi / period));
            }
            else
            {
                t -= 1.0f;
                return amplitude * Math::Pow(2.0f, -10.0f * t) * Math::Sin((t - s) * Math::TwoPi / period) * 0.5f + 1.0f;
            }
        }

        float Ease::InBack(float t)
        {
            return InBack(t, DefaultBackOvershoot);
        }

        float Ease::OutBack(float t)
        {
            return OutBack(t, DefaultBackOvershoot);
        }

        float Ease::InOutBack(float t)
        {
            return InOutBack(t, DefaultBackOvershoot);
        }

        float Ease::InBack(float t, float overshoot)
        {
            return t * t * ((overshoot + 1.0f) * t - overshoot);
        }

        float Ease::OutBack(float t, float overshoot)
        {
            t -= 1.0f;
            return t * t * ((overshoot + 1.0f) * t + overshoot) + 1.0f;
        }

        float Ease::InOutBack(float t, float overshoot)
        {
            t *= 2.0f;
            overshoot *= 1.525f;
            if (t < 1.0f)
                return +0.5f * (t * t * ((overshoot + 1.0f) * t - overshoot));
            else
            {
                t -= 2.0f;
                return +0.5f * (t * t * ((overshoot + 1.0f) * t + overshoot) + 2.0f);
            }
        }
    }

#endif