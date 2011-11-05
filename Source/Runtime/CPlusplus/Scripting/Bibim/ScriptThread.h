#pragma once
#ifndef __BIBIM_ScriptThread_H__
#define __BIBIM_ScriptThread_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/MemoryStream.h>
#   include <Bibim/Script.h>
#   include <Bibim/ScriptObject.h>
#   include <Bibim/ScriptStack.h>
#   include <map>

    namespace Bibim
    {
        class ScriptThread : public SharedObject
        {
            public:
                enum State
                {
                    Stopped,
                    Running,
                    Suspended,
                };

            public:
                ScriptThread(Script* script);
                ScriptThread(Script* script, int stackSize);
                virtual ~ScriptThread();

                ScriptObject Call(const String& name);
                ScriptObject Call(const String& name, const ScriptObject& arg1);
                ScriptObject Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2);
                ScriptObject Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2, const ScriptObject& arg3);
                ScriptObject Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2, const ScriptObject& arg3, const ScriptObject& arg4);
                ScriptObject Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2, const ScriptObject& arg3, const ScriptObject& arg4, const ScriptObject& arg5);

                ScriptObject Resume();

                inline Script* GetScript() const;
                inline const ScriptStack& GetStack() const;
                inline State GetState() const;

                const ScriptObject& GetGlobal(int id) const;
                void SetGlobal(int id, const ScriptObject& value);

            private:
                const Script::Function* BeginCall(const String& name, int numberOfArguments);
                ScriptObject EndCall(const Script::Function* function);
                void PushArgument(ScriptObjectType type, const ScriptObject& value);

                ScriptObject Run(const Script::Function* function, int topIndex);
                void ProcessInstruction(BinaryReader& reader);

                inline void SetState(State value);
                inline int GetNativeFunctionDepth() const;

            private:
                ScriptPtr script;
                ScriptStack stack;
                MemoryStreamPtr stream;
                State state;
                int nativeFunctionDepth;
                std::map<int, ScriptObject> globalVariables;

                const Script::Function* suspendedFunction;
                int suspendedTopIndex;

                friend class ScriptingContext;
        };
    }

#   include <Bibim/ScriptThread.inl>

#endif