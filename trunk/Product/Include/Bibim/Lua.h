#pragma once
#ifndef __BIBIM_LUA_H__
#define __BIBIM_LUA_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
extern "C"
{
#   include <lua.h>
#   include <lauxlib.h>
#   include <lualib.h>
}
#   pragma warning(push)
#   pragma warning(disable:4996)
#   pragma warning(disable:4100)
#   include <lua_tinker.h>
#   pragma warning(pop)

    namespace Bibim
    {
        class Lua : public GameModule
        {
            BBThisIsNoncopyableClass(Lua);
            BBModuleClass(Lua, Bibim::GameModule, 'L', 'U', 'A', '_');
            public:
                Lua();
                virtual ~Lua();

                void GC();

                virtual void DoFile(const String& path);

                int RegisterCallback(int index);
                void UnregisterCallback(int callbackIndex);

                inline lua_State* GetState() const;

            private:
                void LoadLibraries();
                void LoadClasses();

            private:
                lua_State* state;
                int lastCallbackIndex;

                struct Internal;
        };
    }

#   include <Bibim/Lua.inl>

#endif