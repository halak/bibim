#pragma once
#ifndef __BIBIM_UIBUTTON_H__
#define __BIBIM_UIBUTTON_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIPanel.h>

    namespace Bibim
    {
        class UIButton : public UIPanel
        {
            BBComponentClass(UIButton, UIPanel, 'U', 'B', 'T', 'N');
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

                inline void Freeze();
                inline void Unfreeze();

                inline State GetCurrentState() const;
                inline UIVisual* GetNormal() const;
                void SetNormal(UIVisual* value);
                inline UIVisual* GetPushed() const;
                void SetPushed(UIVisual* value);
                inline UIVisual* GetHovering() const;
                void SetHovering(UIVisual* value);
                inline UIVisual* GetCurrent() const;

                inline bool GetHideInactives() const;
                void SetHideInactives(bool value);
                inline bool GetFocusVisible() const;
                void SetFocusVisible(bool value);
                inline bool GetFrozen() const;
                void SetFrozen(bool value);

            protected:
                void SetStateTemplate(UIVisualPtr& field, UIVisual* value);

                void UpdateLayout();
                virtual UIVisual* OnUpdateLayout();

                virtual void OnPick(UIPickingContext& context);

                virtual void OnFocused();
                virtual void OnBlured();

                virtual void OnMouseEnter(const UIMouseEventArgs& args);
                virtual void OnMouseLeave(const UIMouseEventArgs& args);
                virtual bool OnMouseButtonDown(const UIMouseButtonEventArgs& args);
                virtual bool OnMouseButtonUp(const UIMouseButtonEventArgs& args);
                virtual bool OnMouseClick(const UIMouseEventArgs& args);

            private:
                void SetCurrentState(State value);

            private:
                State currentState;
                UIVisualPtr normalVisual;
                UIVisualPtr pushedVisual;
                UIVisualPtr hoveringVisual;
                UIVisualPtr currentVisual;
                bool hideInactives;
                bool focusVisible;
                bool frozen;
        };
    }

#   include <Bibim/UIButton.inl>

#endif