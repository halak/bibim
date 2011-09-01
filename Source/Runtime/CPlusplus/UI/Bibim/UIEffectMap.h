#pragma once
#ifndef __BIBIM_UIEFFECTMAP_H__
#define __BIBIM_UIEFFECTMAP_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>

    namespace Bibim
    {
        class UIEffectMap : public SharedObject
        {
            public:
                UIEffectMap();
                virtual ~UIEffectMap();

            private:
        };
    }

#   include <Bibim/UIEffectMap.inl>

#endif