#pragma once
#ifndef __BIBIM_UIINVERSETRANSFORM_H__
#define __BIBIM_UIINVERSETRANSFORM_H__

#include <Bibim/FWD.h>
#include <Bibim/UITransform.h>

namespace Bibim
{
    class UIInverseTransform : public UITransform
    {
        BBComponentClass(UIInverseTransform, UITransform, 'U', 'T', 'M', 'I');
        public:
            UIInverseTransform();
            virtual ~UIInverseTransform();

            virtual const Matrix4& ComputeMatrix(UIVisualVisitor& context);
    };
}

#endif