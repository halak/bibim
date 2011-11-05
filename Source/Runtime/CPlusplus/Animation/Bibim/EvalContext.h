#pragma once
#ifndef __BIBIM_EVALCONTEXT_H__
#define __BIBIM_EVALCONTEXT_H__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class EvalContext
        {
            public:
                EvalContext();
                ~EvalContext();

                template <typename T>
                T GetValue(const String& name);

            private:
        };
    }

#   include <Bibim/EvalContext.inl>

#endif