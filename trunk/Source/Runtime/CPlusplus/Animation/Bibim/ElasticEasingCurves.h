#pragma once
#ifndef __BIBIM_ELASTICEASINGCURVES_H__
#define __BIBIM_ELASTICEASINGCURVES_H__

#   include <Bibim/EasingCurves.h>

    namespace Bibim
    {
        class ElasticEasingCurve : public EasingCurve
        {
            BBAbstractComponentClass(ElasticEasingCurve, EasingCurve);
            public:
                virtual ~ElasticEasingCurve();

                inline float GetAmplitude() const;
                void SetAmplitude(float value);
                inline float GetPeriod() const;
                void SetPeriod(float value);

            protected:
                ElasticEasingCurve();
                ElasticEasingCurve(float amplitude, float period);

            private:
                float amplitude;
                float period;
        };

        class EaseInElasticCurve : public ElasticEasingCurve
        {
            BBComponentClass(EaseInElasticCurve, ElasticEasingCurve, 'E', 'C', 'I', 'E');
            public:
                EaseInElasticCurve();
                EaseInElasticCurve(float amplitude, float period);
                virtual ~EaseInElasticCurve();

                virtual float Ease(float t) const { return Ease::InElastic(t, GetAmplitude(), GetPeriod()); }
        };

        class EaseOutElasticCurve : public ElasticEasingCurve
        {
            BBComponentClass(EaseOutElasticCurve, ElasticEasingCurve, 'E', 'C', 'O', 'E');
            public:
                EaseOutElasticCurve();
                EaseOutElasticCurve(float amplitude, float period);
                virtual ~EaseOutElasticCurve();

                virtual float Ease(float t) const { return Ease::OutElastic(t, GetAmplitude(), GetPeriod()); }
        };

        class EaseInOutElasticCurve : public ElasticEasingCurve
        {
            BBComponentClass(EaseInOutElasticCurve, ElasticEasingCurve, 'E', 'C', 'D', 'E');
            public:
                EaseInOutElasticCurve();
                EaseInOutElasticCurve(float amplitude, float period);
                virtual ~EaseInOutElasticCurve();

                virtual float Ease(float t) const { return Ease::InOutElastic(t, GetAmplitude(), GetPeriod()); }
        };
    }

#   include <Bibim/ElasticEasingCurves.inl>

#endif