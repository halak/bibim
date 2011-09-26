#pragma once
#ifndef __BIBIM_UIBUTTON_H__
#define __BIBIM_UIBUTTON_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIPanel.h>

    namespace Bibim
    {
        class UIButton : public UIPanel
        {
            BBUIElementClass('U', 'B', 'T', 'N');
            public:
                enum State
                {
                    NormalState,
                    PushedState,
                    HoveringState,
                };

            public:
                UIButton();
                virtual ~UIButton();

                virtual Vector2 GetDesiredSize();

                inline State GetCurrentState() const;
                inline UIWindow* GetNormalWindow() const;
                inline UIWindow* GetPushedWindow() const;
                inline UIWindow* GetHoveringWindow() const;
                inline UIWindow* GetCurrentWindow() const;

                inline bool GetHideInactives() const;
                void SetHideInactives(bool value);

                inline bool GetStateSizeReferenced() const;
                inline void SetStateSizeReferenced(bool value);

            protected:
                void UpdateLayout();
                virtual UIWindow* OnUpdateLayout();

                virtual void OnMouseEnter(const UIMouseEventArgs& args);
                virtual void OnMouseLeave(const UIMouseEventArgs& args);
                virtual bool OnMouseButtonDown(const UIMouseButtonEventArgs& args);
                virtual bool OnMouseButtonUp(const UIMouseButtonEventArgs& args);

            private:
                void SetCurrentState(State value);

            private:
                State currentState;
                UIWindowPtr normalWindow;
                UIWindowPtr pushedWindow;
                UIWindowPtr hoveringWindow;
                UIWindowPtr currentWindow;
                bool hideInactives;
                bool stateSizeReferenced;
        };
    }

#   include <Bibim/UIButton.inl>

#endif