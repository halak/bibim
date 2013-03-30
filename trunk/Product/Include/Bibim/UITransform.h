#pragma once
#ifndef __BIBIM_UITRANSFORM_H__
#define __BIBIM_UITRANSFORM_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIElement.h>

    namespace Bibim
    {
        class UITransform : public UIElement
        {
            BBAbstractComponentClass(UITransform, UIElement);
            public:
                virtual ~UITransform();
                
                virtual const Matrix4& ComputeMatrix(UIVisualVisitor& context) = 0;

            protected:
                UITransform();
        };
    }

    BBBindLua(Bibim::UITransform);

#endif