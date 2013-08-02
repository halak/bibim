#pragma once
#ifndef __BIBIM_EVALCONTEXT_H__
#define __BIBIM_EVALCONTEXT_H__

#include <Bibim/FWD.h>
#include <Bibim/Color.h>
#include <Bibim/Point2.h>
#include <Bibim/Point3.h>
#include <Bibim/Point4.h>
#include <Bibim/Rect.h>
#include <Bibim/RectF.h>
#include <Bibim/Vector2.h>
#include <Bibim/Vector3.h>
#include <Bibim/Vector4.h>

namespace Bibim
{
    class EvalContext
    {
        public:
            EvalContext();
            EvalContext(AnyStorage* variables);
            ~EvalContext();

            template <typename T>
            T GetValue(const String& name);

        private:
            AnyStoragePtr variables;
    };
}

#endif