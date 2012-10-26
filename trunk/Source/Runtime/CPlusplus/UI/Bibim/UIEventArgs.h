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

BBBindLua(Bibim::UIEventArgs);