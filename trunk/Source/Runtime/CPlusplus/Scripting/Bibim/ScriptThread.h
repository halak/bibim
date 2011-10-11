#pragma once
#ifndef __BIBIM_ScriptThread_H__
#define __BIBIM_ScriptThread_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/MemoryStream.h>
#   include <Bibim/Script.h>
#   include <Bibim/ScriptObject.h>
#   include <Bibim/ScriptStack.h>

    namespace Bibim
    {
        class ScriptThread : public SharedObject
        {
            BBObjectClass(ScriptThread, SharedObject, 'S', 'C', 'P', 'S');
            public:
                ScriptThread(Script* script);
                ScriptThread(Script* script, int stackSize);
                virtual ~ScriptThread();

                void Resume();
                void Suspend();

                ScriptObject Call(const String& name);
                ScriptObject Call(const String& name, const ScriptObject& arg1);
                ScriptObject Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2);
                ScriptObject Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2, const ScriptObject& arg3);
                ScriptObject Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2, const ScriptObject& arg3, const ScriptObject& arg4);
                ScriptObject Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2, const ScriptObject& arg3, const ScriptObject& arg4, const ScriptObject& arg5);

                inline Script* GetScript() const;
                inline const ScriptStack& GetStack() const;

            private:
                const Script::Function* BeginCall(const String& name, int numberOfArguments);
                ScriptObject EndCall(const Script::Function* function);
                void PushArgument(ScriptObjectType type, const ScriptObject& value);

                void Process(BinaryReader& reader);

            private:
                ScriptPtr script;
                ScriptStack stack;
                MemoryStreamPtr stream;
        };
    }

#   include <Bibim/ScriptThread.inl>

#endif