#pragma once
#ifndef __BIBIM_UIMOUSEEVENTDISPATCHER_H__
#define __BIBIM_UIMOUSEEVENTDISPATCHER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/TimelineGameModule.h>
#   include <Bibim/MouseState.h>
#   include <vector>

    namespace Bibim
    {
        class UIMouseEventDispatcher : public TimelineGameModule
        {
            BBModuleClass(UIMouseEventDispatcher, UpdateableGameModule, 'U', 'I', 'M', 'S');
            public:
                UIMouseEventDispatcher();
                UIMouseEventDispatcher(UIDomain* domain, Mouse* device, UIRenderer* renderer);
                UIMouseEventDispatcher(UIDomain* domain, Mouse* device, UIRenderer* renderer, bool focusWhenHover);
                virtual ~UIMouseEventDispatcher();

                void Reset();

                virtual void Update(float dt, int timestamp);

                inline UIDomain* GetDomain() const;
                void SetDomain(UIDomain* value);

                inline Mouse* GetDevice() const;
                void SetDevice(Mouse* value);

                inline UIRenderer* GetRenderer() const;
                inline void SetRenderer(UIRenderer* value);

                inline bool GetFocusWhenHover() const;
                inline void SetFocusWhenHover(bool value);

                inline UIVisual* GetCapture() const;
                void SetCapture(UIVisual* value);

                inline UIVisual* GetLastTarget() const;

            private:
                UIDomain* domain;
                Mouse* device;
                UIRenderer* renderer;
                bool focusWhenHover;

                UIVisualPtr capturedVisual;
                UIVisualPtr lastTargetVisual;
                MouseState  lastMouseState;

                typedef std::vector<UIVisual*> VisualVector;
                VisualVector cachedEnterVisuals;
                VisualVector cachedLeaveVisuals;
        };
    }

#   include <Bibim/UIMouseEventDispatcher.inl>

#endif