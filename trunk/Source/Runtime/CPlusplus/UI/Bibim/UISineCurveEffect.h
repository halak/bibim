#pragma once
#ifndef __BIBIM_UISINECURVEEFFECT_H__
#define __BIBIM_UISINECURVDEFFECT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIGeometryEffect.h>

    namespace Bibim
    {
        class UISineCurveEffect : public UIGeometryEffect
        {
            BBComponentClass(UISineCurveEffect, UIGeometryEffect, 'U', 'S', 'I', 'F');
            public:
                UISineCurveEffect();
                virtual ~UISineCurveEffect();

            private:
        };
    }

#   include <Bibim/UISineCurveEffect.inl>

#endif