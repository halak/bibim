#pragma once
#ifndef __BIBIM_UIKEYBOARDEVENTDISPATCHER_H__
#define __BIBIM_UIKEYBOARDEVENTDISPATCHER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UpdateableGameComponent.h>
#   include <Bibim/KeyboardState.h>

    namespace Bibim
    {
        class UIKeyboardEventDispatcher : public UpdateableGameComponent
        {
            BBClassFOURCC('U', 'I', 'K', 'B');
            public:
                UIKeyboardEventDispatcher();
                virtual ~UIKeyboardEventDispatcher();

                virtual void Update(float dt, uint timestamp);

                inline UIDomain* GetDomain() const;
                void SetDomain(UIDomain* value);

                inline Keyboard* GetDevice() const;
                void SetDevice(Keyboard* value);

            private:
                UIDomain* domain;
                Keyboard* device;
                KeyboardState lastState;
        };
    }

#   include <Bibim/UIKeyboardEventDispatcher.inl>

#endif