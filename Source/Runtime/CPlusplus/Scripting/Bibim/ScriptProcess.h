#pragma once
#ifndef __BIBIM_SCRIPTPROCESS_H__
#define __BIBIM_SCRIPTPROCESS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/Script.h>
#   include <Bibim/ScriptObject.h>
#   include <Bibim/ScriptStack.h>

    namespace Bibim
    {
        class ScriptProcess : public SharedObject
        {
            BBObjectClass(ScriptProcess, SharedObject, 'S', 'C', 'P', 'S');
            public:
                ScriptProcess(Script* script);
                ScriptProcess(Script* script, int stackSize);
                virtual ~ScriptProcess();

                void Resume();
                void Suspend();

                ScriptObject Call(const String& name);
                ScriptObject Call(const String& name, const ScriptObject& arg1);
                ScriptObject Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2);
                ScriptObject Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2, const ScriptObject& arg3);
                ScriptObject Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2, const ScriptObject& arg3, const ScriptObject& arg4);
                ScriptObject Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2, const ScriptObject& arg3, const ScriptObject& arg4, const ScriptObject& arg5);

            private:
                const Script::Function* BeginCall(const String& name, int numberOfArguments);
                ScriptObject EndCall(const Script::Function* function);
                void PushArgument(ScriptObjectType type, const ScriptObject& value);

                void Process(BinaryReader& reader);

            private:
                ScriptPtr script;
                ScriptStack stack;
                uint position;
        };
    }

#   include <Bibim/ScriptProcess.inl>

#endif