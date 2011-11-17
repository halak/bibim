#pragma once
#ifndef __BIBIM_ScriptThread_H__
#define __BIBIM_ScriptThread_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/MemoryStream.h>
#   include <Bibim/Script.h>
#   include <Bibim/Any.h>
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

                Any Call(const String& name);
                Any Call(const String& name, const Any& arg1);
                Any Call(const String& name, const Any& arg1, const Any& arg2);
                Any Call(const String& name, const Any& arg1, const Any& arg2, const Any& arg3);
                Any Call(const String& name, const Any& arg1, const Any& arg2, const Any& arg3, const Any& arg4);
                Any Call(const String& name, const Any& arg1, const Any& arg2, const Any& arg3, const Any& arg4, const Any& arg5);

                Any Resume();

                inline Script* GetScript() const;
                inline const ScriptStack& GetStack() const;
                inline State GetState() const;

                const Any& GetGlobal(int id) const;
                void SetGlobal(int id, const Any& value);

            private:
                const Script::Function* BeginCall(const String& name, int numberOfArguments);
                Any EndCall(const Script::Function* function);
                void PushArgument(AnyType type, const Any& value);

                Any Run(const Script::Function* function, int topIndex);
                void ProcessInstruction(BinaryReader& reader);

                inline void SetState(State value);
                inline int GetNativeFunctionDepth() const;

            private:
                ScriptPtr script;
                ScriptStack stack;
                MemoryStreamPtr stream;
                State state;
                int nativeFunctionDepth;
                std::map<int, Any> globalVariables;

                const Script::Function* suspendedFunction;
                int suspendedTopIndex;

                friend class ScriptingContext;
        };
    }

#   include <Bibim/ScriptThread.inl>

#endif