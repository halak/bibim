#pragma once

#include <Bibim/FWD.h>
#include <Bibim/SharedObject.h>

namespace Bibim
{
    class UIEventArgs : public SharedObject
    {
        public:
            UIEventArgs();
            UIEventArgs(UIVisual* target);
            UIEventArgs(const UIEventArgs& original);
            virtual ~UIEventArgs();

            virtual UIEventArgs* Clone() const;

            inline UIVisual* GetTarget() const;

        private:
            UIVisualPtr target;
    };
}

#include <Bibim/UIEventArgs.inl>
