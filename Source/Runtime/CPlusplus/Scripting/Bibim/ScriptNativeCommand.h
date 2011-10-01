#pragma once
#ifndef __BIBIM_SCRIPTNATIVECOMMAND_H__
#define __BIBIM_SCRIPTNATIVECOMMAND_H__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
#       define BBScriptNativeCommandClass(a, b, c, d)   public: \
                                                            static const uint32 ClassID = BBMakeFOURCC(a, b, c, d); \
                                                            virtual uint32 GetClassID() const { return ClassID; } \
                                                            \
                                                            static ScriptNativeCommand* Read(AssetStreamReader& reader, ScriptNativeCommand* existingInstance); \
                                                        private: \

        class ScriptNativeCommand
        {
            public:
                virtual ~ScriptNativeCommand() { }

                virtual void Call(ScriptingContext& context) = 0;

            protected:
                ScriptCallable();
        };
    }

#endif