#pragma once
#ifndef __BIBIM_SCRIPTINGCONTEXT_H__
#define __BIBIM_SCRIPTINGCONTEXT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/ScriptObject.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        class ScriptingContext
        {
            BBThisIsNoncopyableClass(ScriptingContext);
            public:
                ScriptingContext(ScriptThread* thread, int numberOfArguments, int numberOfReturnValues);
                ~ScriptingContext();

                bool    GetBoolArg(int index) const;
                int     GetIntArg(int index) const;
                longint GetLongIntArg(int index) const;
                float   GetFloatArg(int index) const;
                Color   GetColorArg(int index) const;
                String  GetStringArg(int index) const;

                void Return();
                void Return(const ScriptObject& value);
                void Return(const ScriptObject& value1, const ScriptObject& value2);
                void Return(const ScriptObject& value1, const ScriptObject& value2, const ScriptObject& value3);
                void Return(const ScriptObject& value1, const ScriptObject& value2, const ScriptObject& value3, const ScriptObject& value4);
                void Return(const ScriptObject& value1, const ScriptObject& value2, const ScriptObject& value3, const ScriptObject& value4, const ScriptObject& value5);

                void YieldReturn();

                ScriptObject Call(const String& name);
                ScriptObject Call(const String& name, const ScriptObject& arg1);
                ScriptObject Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2);
                ScriptObject Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2, const ScriptObject& arg3);
                ScriptObject Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2, const ScriptObject& arg3, const ScriptObject& arg4);
                ScriptObject Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2, const ScriptObject& arg3, const ScriptObject& arg4, const ScriptObject& arg5);

                const ScriptObject& GetGlobal(int id) const;
                void SetGlobal(int id, const ScriptObject& value);

            private:
                ScriptThread* thread;
                int numberOfArguments;
                int numberOfReturnValues;
                bool returnCalled;
        };
    }

#endif