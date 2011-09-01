#pragma once
#ifndef __BIBIM_UITRANSFORM_H__
#define __BIBIM_UITRANSFORM_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIElement.h>
#   include <Bibim/Matrix4.h>

    namespace Bibim
    {
        class UITransform : public UIElement
        {
            public:
                virtual ~UITransform();

                virtual const Matrix4& ComputeMatrix(UIVisualVisitor& visitor) = 0;

            protected:
                UITransform();
        };
    }

#   include <Bibim/UITransform.inl>

#endif