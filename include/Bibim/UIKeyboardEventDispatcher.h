#pragma once
#ifndef __BIBIM_UIKEYBOARDEVENTDISPATCHER_H__
#define __BIBIM_UIKEYBOARDEVENTDISPATCHER_H__

#include <Bibim/FWD.h>
#include <Bibim/TimelineGameModule.h>
#include <Bibim/KeyboardState.h>

namespace Bibim
{
    class UIKeyboardEventDispatcher : public TimelineGameModule
    {
        BBModuleClass(UIKeyboardEventDispatcher, TimelineGameModule, 'U', 'I', 'K', 'B');
        public:
            UIKeyboardEventDispatcher();
            UIKeyboardEventDispatcher(UIDomain* domain, Keyboard* device);
            virtual ~UIKeyboardEventDispatcher();

            virtual void Update(float dt, int timestamp);

            inline UIDomain* GetDomain() const;
            void SetDomain(UIDomain* value);

            inline Keyboard* GetDevice() const;
            void SetDevice(Keyboard* value);

        private:
            UIDomain* domain;
            Keyboard* device;
            KeyboardState lastState;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    UIDomain* UIKeyboardEventDispatcher::GetDomain() const
    {
        return domain;
    }

    Keyboard* UIKeyboardEventDispatcher::GetDevice() const
    {
        return device;
    }
}

#endif