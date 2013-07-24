#pragma once
#ifndef __BIBIM_UITRANSFORM2D_H__
#define __BIBIM_UITRANSFORM2D_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UITransform.h>

    namespace Bibim
    {
        class UITransform2D : public UITransform
        {
            BBComponentClass(UITransform2D, UITransform, 'U', 'T', 'M', '2');
            public:
                UITransform2D();
                virtual ~UITransform2D();

                virtual const Matrix4& ComputeMatrix(UIVisualVisitor& context);

                void Reset();
        };
    }

#endif