#pragma once
#ifndef __BIBIM_SCRIPTCALLABLE_H__
#define __BIBIM_SCRIPTCALLABLE_H__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
#       define BBScriptCallableClass(a, b, c, d)    public: \
                                                        static const uint32 ClassID = BBMakeFOURCC(a, b, c, d); \
                                                        virtual uint32 GetClassID() const { return ClassID; } \
                                                        \
                                                        static ScriptCallable* Read(AssetStreamReader& reader, ScriptCallable* existingInstance); \
                                                    private: \

        class ScriptCallable
        {
            public:
                virtual ~ScriptCallable() { }

                virtual void Call(ScriptingContext& context) = 0;

            protected:
                ScriptCallable();
        };
    }

#endif