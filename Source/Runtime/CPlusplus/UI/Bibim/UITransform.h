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

	template<> inline void lua_tinker::push(lua_State* L, Bibim::UITransform* value)
	{
        push(L, static_cast<lua_tinker::lua_value*>(value));
	}

	template<> inline void lua_tinker::push(lua_State* L, const Bibim::UITransform* value)
	{
        push(L, const_cast<lua_tinker::lua_value*>(static_cast<const lua_tinker::lua_value*>(value)));
	}

#endif