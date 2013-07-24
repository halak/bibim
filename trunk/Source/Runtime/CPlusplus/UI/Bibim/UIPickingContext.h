#pragma once
#ifndef __BIBIM_UIPICKINGCONTEXT_H__
#define __BIBIM_UIPICKINGCONTEXT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIVisualVisitor.h>

    namespace Bibim
    {
        class UIPickingContext : public UIVisualVisitor
        {
            public:
                UIPickingContext(UIRenderer* renderer, Vector2 point);
                UIPickingContext(UIRenderer* renderer, Vector2 point, bool visibleOnly);
                virtual ~UIPickingContext();

                bool Pick(UIVisual* target);

                inline bool Contains(const RectF& bounds);

                inline Vector2 GetPoint() const;
                inline Vector2 GetCurrentPoint() const;

                inline UIVisual* GetResult() const;
                void SetResult(UIVisual* value);

            protected:
                inline bool PickChild(UIVisual* target);

                virtual void OnVisit();

            private:
                Vector2 point;
                Vector2 currentPoint;
                UIVisual* result;

                friend class UIPanel;
        };
    }

#endif