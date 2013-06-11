#pragma once
#ifndef __BIBIM_UISCROLLABLEPANEL_H__
#define __BIBIM_UISCROLLABLEPANEL_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIPanel.h>

    namespace Bibim
    {
        class UIScrollablePanel : public UIPanel
        {
            BBComponentClass(UIScrollablePanel, UIPanel, 'U', 'S', 'C', 'P');
            public:
                UIScrollablePanel();
                virtual ~UIScrollablePanel();

                inline UIVisual* GetContent() const;
                void SetContent(UIVisual* value);

            protected:
                virtual void OnDraw(UIDrawingContext& context);
                virtual void OnPick(UIPickingContext& context);

                virtual bool OnMouseMove(const UIMouseEventArgs& args);
                virtual bool OnMouseButtonDown(const UIMouseButtonEventArgs& args);
                virtual bool OnMouseButtonUp(const UIMouseButtonEventArgs& args);

            private:
                void RestrictContent(UIVisualVisitor& context);

            private:
                UIVisualPtr content;
                bool isScrolling;
                Point2 lastMousePosition;
                Point2 startMousePosition;
        };
    }

#   include <Bibim/UIScrollablePanel.inl>

#endif