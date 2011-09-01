#pragma once
#ifndef __BIBIM_UITOUCHEVENTARGS_H__
#define __BIBIM_UITOUCHEVENTARGS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIEventArgs.h>

    namespace Bibim
    {
        class UITouchEventArgs : public UIEventArgs
        {
            public:
                UITouchEventArgs();
                virtual ~UITouchEventArgs();

            private:
        };
    }

#   include <Bibim/UITouchEventArgs.inl>

#endif