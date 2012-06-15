#pragma once

#include <Bibim/FWD.h>
#include <Bibim/SharedObject.h>

extern "C" 
{
#   include <lua.h>
}
#pragma warning(push)
#pragma warning(disable:4996)
#pragma warning(disable:4100)
#include <lua_tinker.h>
#pragma warning(pop)

namespace Bibim
{
    class UIEventArgs : public SharedObject, public lua_tinker::lua_value
    {
        protected: virtual void to_lua(lua_State *L) { type2lua(L, this); }
        public:
            UIEventArgs();
            UIEventArgs(UIVisual* target);
            UIEventArgs(const UIEventArgs& original);
            virtual ~UIEventArgs();

            virtual UIEventArgs* Clone() const;

            inline UIVisual* GetTarget() const;

        private:
            UIVisualPtr target;
    };
}

#include <Bibim/UIEventArgs.inl>

template<> inline void lua_tinker::push(lua_State* L, Bibim::UIEventArgs* value)
{
    push(L, static_cast<lua_tinker::lua_value*>(value));
}

template<> inline void lua_tinker::push(lua_State* L, const Bibim::UIEventArgs* value)
{
    push(L, const_cast<lua_tinker::lua_value*>(static_cast<const lua_tinker::lua_value*>(value)));
}