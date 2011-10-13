#pragma once
#ifndef __BIBIM_UIMOUSEEVENTDISPATCHER_H__
#define __BIBIM_UIMOUSEEVENTDISPATCHER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UpdateableGameModule.h>
#   include <Bibim/MouseState.h>
#   include <vector>

    namespace Bibim
    {
        class UIMouseEventDispatcher : public UpdateableGameModule
        {
            BBModuleClass(UIMouseEventDispatcher, UpdateableGameModule, 'U', 'I', 'M', 'S');
            public:
                UIMouseEventDispatcher();
                virtual ~UIMouseEventDispatcher();

                virtual void Update(float dt, uint timestamp);

                inline UIDomain* GetDomain() const;
                void SetDomain(UIDomain* value);

                inline Mouse* GetDevice() const;
                void SetDevice(Mouse* value);

                inline UIRenderer* GetRenderer() const;
                inline void SetRenderer(UIRenderer* value);

            private:
                UIDomain* domain;
                Mouse* device;
                UIRenderer* renderer;
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