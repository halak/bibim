#pragma once
#ifndef __BIBIM_UIBOUNDSCONTEXT_H__
#define __BIBIM_UIBOUNDSCONTEXT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIVisualVisitor.h>
#   include <vector>

    namespace Bibim
    {
        class UIBoundsContext : public UIVisualVisitor
        {
            public:
                UIBoundsContext();
                virtual ~UIBoundsContext();

                RectF Compute(UIVisual* target);

            protected:
                virtual void OnVisit();

            private:
                RectF bounds;
                std::vector<UIVisual*> targets;
                int index;
        };
    }

#endif