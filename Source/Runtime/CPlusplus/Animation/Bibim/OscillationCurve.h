#pragma once
#ifndef __BIBIM_OSCILLATIONCURVE_H__
#define __BIBIM_OSCILLATIONCURVE_H__

#   include <Bibim/EasingCurves.h>

    namespace Bibim
    {
        class OscillationCurve : public EasingCurve
        {
            BBComponentClass(OscillationCurve, EasingCurve, 'E', 'C', 'O', 'C');
            public:
                enum OscillationMode
                {
                    Still,
                    Crescendo,
                    Decrescendo,
                    PitchAndRoll,
                };

            public:
                OscillationCurve();
                OscillationCurve(OscillationMode mode, int frequency, float strength);
                virtual ~OscillationCurve();

                virtual float Ease(float t) const;

                inline OscillationMode GetMode() const;
                inline void SetMode(OscillationMode value);
                inline int GetFrequency() const;
                void SetFrequency(int value);
                inline float GetStrength() const;
                inline void SetStrength(float value);

            private:
                OscillationMode mode;
                int frequency;
                float frequencyFloat;
                float strength;
        };
    }

#endif