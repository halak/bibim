#pragma once
#ifndef __BIBIM_PROPERTYANIMATORS_H__
#define __BIBIM_PROPERTYANIMATORS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Animators.h>

    namespace Bibim
    {
        template <typename T, char a, char b, char c, char d>
        class PropertyAnimatorTemplate : public AnimatorTemplate<T>
        {
            BBComponentClass(PropertyAnimatorTemplate, AnimatorTemplate<T>, a, b, c, d);
            public:
                PropertyAnimatorTemplate();
                virtual ~PropertyAnimatorTemplate();
        };
    }

#endif