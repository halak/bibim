#pragma once
#ifndef __BIBIM_SCRIPTINGCONTEXT_H__
#define __BIBIM_SCRIPTINGCONTEXT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Any.h>
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
                void Return(const Any& value);
                void Return(const Any& value1, const Any& value2);
                void Return(const Any& value1, const Any& value2, const Any& value3);
                void Return(const Any& value1, const Any& value2, const Any& value3, const Any& value4);
                void Return(const Any& value1, const Any& value2, const Any& value3, const Any& value4, const Any& value5);

                void YieldReturn();

                Any Call(const String& name);
                Any Call(const String& name, const Any& arg1);
                Any Call(const String& name, const Any& arg1, const Any& arg2);
                Any Call(const String& name, const Any& arg1, const Any& arg2, const Any& arg3);
                Any Call(const String& name, const Any& arg1, const Any& arg2, const Any& arg3, const Any& arg4);
                Any Call(const String& name, const Any& arg1, const Any& arg2, const Any& arg3, const Any& arg4, const Any& arg5);

                const Any& GetGlobal(int id) const;
                void SetGlobal(int id, const Any& value);

            private:
                ScriptThread* thread;
                int numberOfArguments;
                int numberOfReturnValues;
                bool returnCalled;
        };
    }

#endif