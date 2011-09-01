namespace Bibim
{
    template <typename T>
    void LuaRuntimeEnvironment::Push(T value)
    {
        PushAny(Any(value));
    }

    template <typename Return>
    Return LuaRuntimeEnvironment::Call(const char* function)
    {
        BeginCall(function);
        CallActually(0, EndCall<Return>::NumberOfReturns);
        return EndCall<Return>::Do(this);
    }

    template <typename Return, typename Arg1>
    Return LuaRuntimeEnvironment::Call(const char* function, Arg1 arg1)
    {
        BeginCall(function);
        Push(arg1);
        CallActually(1, EndCall<Return>::NumberOfReturns);
        return EndCall<Return>::Do(this);
    }

    template <typename Return, typename Arg1, typename Arg2>
    Return LuaRuntimeEnvironment::Call(const char* function, Arg1 arg1, Arg2 arg2)
    {
        BeginCall(function);
        Push(arg1);
        Push(arg2);
        CallActually(2, EndCall<Return>::NumberOfReturns);
        return EndCall<Return>::Do(this);
    }

    template <typename Return, typename Arg1, typename Arg2, typename Arg3>
    Return LuaRuntimeEnvironment::Call(const char* function, Arg1 arg1, Arg2 arg2, Arg3 arg3)
    {
        BeginCall(function);
        Push(arg1);
        Push(arg2);
        Push(arg3);
        CallActually(3, EndCall<Return>::NumberOfReturns);
        return EndCall<Return>::Do(this);
    }

    template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
    Return LuaRuntimeEnvironment::Call(const char* function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
    {
        BeginCall(function);
        Push(arg1);
        Push(arg2);
        Push(arg3);
        Push(arg4);
        CallActually(4, EndCall<Return>::NumberOfReturns);
        return EndCall<Return>::Do(this);
    }

    template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    Return LuaRuntimeEnvironment::Call(const char* function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5)
    {
        BeginCall(function);
        Push(arg1);
        Push(arg2);
        Push(arg3);
        Push(arg4);
        Push(arg5);
        CallActually(5, EndCall<Return>::NumberOfReturns);
        return EndCall<Return>::Do(this);
    }

    template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
    Return LuaRuntimeEnvironment::Call(const char* function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6)
    {
        BeginCall(function);
        Push(arg1);
        Push(arg2);
        Push(arg3);
        Push(arg4);
        Push(arg5);
        Push(arg6);
        CallActually(6, EndCall<Return>::NumberOfReturns);
        return EndCall<Return>::Do(this);
    }

    template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
    Return LuaRuntimeEnvironment::Call(const char* function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7)
    {
        BeginCall(function);
        Push(arg1);
        Push(arg2);
        Push(arg3);
        Push(arg4);
        Push(arg5);
        Push(arg6);
        Push(arg7);
        CallActually(7, EndCall<Return>::NumberOfReturns);
        return EndCall<Return>::Do(this);
    }

    template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
    Return LuaRuntimeEnvironment::Call(const char* function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7, Arg8 arg8)
    {
        BeginCall(function);
        Push(arg1);
        Push(arg2);
        Push(arg3);
        Push(arg4);
        Push(arg5);
        Push(arg6);
        Push(arg7);
        Push(arg8);
        CallActually(8, EndCall<Return>::NumberOfReturns);
        return EndCall<Return>::Do(this);
    }

    template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
    Return LuaRuntimeEnvironment::Call(const char* function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7, Arg8 arg8, Arg9 arg9)
    {
        BeginCall(function);
        Push(arg1);
        Push(arg2);
        Push(arg3);
        Push(arg4);
        Push(arg5);
        Push(arg6);
        Push(arg7);
        Push(arg8);
        Push(arg9);
        CallActually(9, EndCall<Return>::NumberOfReturns);
        return EndCall<Return>::Do(this);
    }

    template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10>
    Return LuaRuntimeEnvironment::Call(const char* function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7, Arg8 arg8, Arg9 arg9, Arg10 arg10)
    {
        BeginCall(function);
        Push(arg1);
        Push(arg2);
        Push(arg3);
        Push(arg4);
        Push(arg5);
        Push(arg6);
        Push(arg7);
        Push(arg8);
        Push(arg9);
        Push(arg10);
        CallActually(10, EndCall<Return>::NumberOfReturns);
        return EndCall<Return>::Do(this);
    }

    template <typename Return>
    Return LuaRuntimeEnvironment::Call(const String& function)
    {
        return Call<Return>(function.CStr());
    }

    template <typename Return, typename Arg1>
    Return LuaRuntimeEnvironment::Call(const String& function, Arg1 arg1)
    {
        return Call<Return>(function.CStr(), arg1);
    }

    template <typename Return, typename Arg1, typename Arg2>
    Return LuaRuntimeEnvironment::Call(const String& function, Arg1 arg1, Arg2 arg2)
    {
        return Call<Return>(function.CStr(), arg1, arg2);
    }

    template <typename Return, typename Arg1, typename Arg2, typename Arg3>
    Return LuaRuntimeEnvironment::Call(const String& function, Arg1 arg1, Arg2 arg2, Arg3 arg3)
    {
        return Call<Return>(function.CStr(), arg1, arg2, arg3);
    }

    template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
    Return LuaRuntimeEnvironment::Call(const String& function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4)
    {
        return Call<Return>(function.CStr(), arg1, arg2, arg3, arg4);
    }

    template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
    Return LuaRuntimeEnvironment::Call(const String& function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5)
    {
        return Call<Return>(function.CStr(), arg1, arg2, arg3, arg4, arg5);
    }

    template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
    Return LuaRuntimeEnvironment::Call(const String& function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6)
    {
        return Call<Return>(function.CStr(), arg1, arg2, arg3, arg4, arg5, arg6);
    }

    template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
    Return LuaRuntimeEnvironment::Call(const String& function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7)
    {
        return Call<Return>(function.CStr(), arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
    Return LuaRuntimeEnvironment::Call(const String& function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7, Arg8 arg8)
    {
        return Call<Return>(function.CStr(), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
    }

    template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
    Return LuaRuntimeEnvironment::Call(const String& function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7, Arg8 arg8, Arg9 arg9)
    {
        return Call<Return>(function.CStr(), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
    }

    template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10>
    Return LuaRuntimeEnvironment::Call(const String& function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7, Arg8 arg8, Arg9 arg9, Arg10 arg10)
    {
        return Call<Return>(function.CStr(), arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
    }
}