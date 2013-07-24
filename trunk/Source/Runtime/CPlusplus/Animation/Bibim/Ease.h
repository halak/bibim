#pragma once
#ifndef __BIBIM_EASE_H__
#define __BIBIM_EASE_H__

#   include <Bibim/FWD.h>

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
    }

#endif