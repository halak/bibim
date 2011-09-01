#pragma once
#ifndef __BIBIM_LUARUNTIMEENVIRONMENT_H__
#define __BIBIM_LUARUNTIMEENVIRONMENT_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameComponent.h>
#   include <Bibim/Exception.h>
#   include <Bibim/String.h>
#   include <tuple>

    namespace Bibim
    {
        class LuaRuntimeEnvironment : public GameComponent
        {
            BBClassFOURCC('L', 'U', 'A', 'E');
            public:
                LuaRuntimeEnvironment();
                virtual ~LuaRuntimeEnvironment();

                void Load(const String& filename);

                template <typename Return>
                Return Call(const char* function);
                template <typename Return, typename Arg1>
                Return Call(const char* function, Arg1 arg1);
                template <typename Return, typename Arg1, typename Arg2>
                Return Call(const char* function, Arg1 arg1, Arg2 arg2);
                template <typename Return, typename Arg1, typename Arg2, typename Arg3>
                Return Call(const char* function, Arg1 arg1, Arg2 arg2, Arg3 arg3);
                template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
                Return Call(const char* function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4);
                template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
                Return Call(const char* function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5);
                template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
                Return Call(const char* function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6);
                template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
                Return Call(const char* function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7);
                template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
                Return Call(const char* function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7, Arg8 arg8);
                template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
                Return Call(const char* function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7, Arg8 arg8, Arg9 arg9);
                template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10>
                Return Call(const char* function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7, Arg8 arg8, Arg9 arg9, Arg10 arg10);

                template <typename Return>
                Return Call(const String& function);
                template <typename Return, typename Arg1>
                Return Call(const String& function, Arg1 arg1);
                template <typename Return, typename Arg1, typename Arg2>
                Return Call(const String& function, Arg1 arg1, Arg2 arg2);
                template <typename Return, typename Arg1, typename Arg2, typename Arg3>
                Return Call(const String& function, Arg1 arg1, Arg2 arg2, Arg3 arg3);
                template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
                Return Call(const String& function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4);
                template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
                Return Call(const String& function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5);
                template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
                Return Call(const String& function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6);
                template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
                Return Call(const String& function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7);
                template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
                Return Call(const String& function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7, Arg8 arg8);
                template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
                Return Call(const String& function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7, Arg8 arg8, Arg9 arg9);
                template <typename Return, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10>
                Return Call(const String& function, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7, Arg8 arg8, Arg9 arg9, Arg10 arg10);

            private:
                void Push(bool value);
                void Push(char value);
                void Push(uchar value);
                void Push(short value);
                void Push(ushort value);
                void Push(int value);
                void Push(uint value);
                void Push(long value);
                void Push(ulong value);
                void Push(int64 value);
                void Push(uint64 value);
                void Push(float value);
                void Push(double value);
                void Push(const char* value);
                void Push(const String& value);
                void PushAny(const Any& value);
                template <typename T>
                void Push(T value);
                void Get(int index, bool& outValue);
                void Get(int index, char& outValue);
                void Get(int index, uchar& outValue);
                void Get(int index, short& outValue);
                void Get(int index, ushort& outValue);
                void Get(int index, int& outValue);
                void Get(int index, uint& outValue);
                void Get(int index, long& outValue);
                void Get(int index, ulong& outValue);
                void Get(int index, int64& outValue);
                void Get(int index, uint64& outValue);
                void Get(int index, float& outValue);
                void Get(int index, double& outValue);
                void Get(int index, String& outValue);
                void Get(int index, Any& outValue);
                void Pop(int count);
                void BeginCall(const char* function);
                void CallActually(int numberOfArguments, int numberOfResults);

                template <typename Return> struct EndCall
                {
                    static const int NumberOfReturns = 1;
                    static Return Do(LuaRuntimeEnvironment* self)
                    {
                        Return result;
                        self->Get(-1, result);
                        self->Pop(NumberOfReturns + 1);
                        return result;
                    }
                };
                template <> struct EndCall<void>
                {
                    static const int NumberOfReturns = 0;
                    static void Do(LuaRuntimeEnvironment* /*self*/)
                    {
                    }
                };
                template <typename T1>
                struct EndCall<std::tr1::tuple<T1>>
                {
                    typedef typename std::tr1::tuple<T1> Return;
                    static const int NumberOfReturns = 1;
                    static Return Do(LuaRuntimeEnvironment* self)
                    {
                        T1 result1;
                        self->Get(-1, result1);
                        self->Pop(NumberOfReturns + 1);
                        return Return(result1);
                    }
                };
                template <typename T1, typename T2>
                struct EndCall<std::tr1::tuple<T1, T2>>
                {
                    typedef typename std::tr1::tuple<T1, T2> Return;
                    static const int NumberOfReturns = 2;
                    static Return Do(LuaRuntimeEnvironment* self)
                    {
                        T1 result1;
                        T2 result2;
                        self->Get(-2, result1);
                        self->Get(-1, result2);
                        self->Pop(NumberOfReturns + 1);
                        return Return(result1, result2);
                    }
                };
                template <typename T1, typename T2, typename T3>
                struct EndCall<std::tr1::tuple<T1, T2, T3>>
                {
                    typedef typename std::tr1::tuple<T1, T2, T3> Return;
                    static const int NumberOfReturns = 3;
                    static Return Do(LuaRuntimeEnvironment* self)
                    {
                        T1 result1;
                        T2 result2;
                        T3 result3;
                        self->Get(-3, result1);
                        self->Get(-2, result2);
                        self->Get(-1, result3);
                        self->Pop(NumberOfReturns + 1);
                        return Return(result1, result2, result3);
                    }
                };
                template <typename T1, typename T2, typename T3, typename T4>
                struct EndCall<std::tr1::tuple<T1, T2, T3, T4>>
                {
                    typedef typename std::tr1::tuple<T1, T2, T3, T4> Return;
                    static const int NumberOfReturns = 4;
                    static Return Do(LuaRuntimeEnvironment* self)
                    {
                        T1 result1;
                        T2 result2;
                        T3 result3;
                        T4 result4;
                        self->Get(-4, result1);
                        self->Get(-3, result2);
                        self->Get(-2, result3);
                        self->Get(-1, result4);
                        self->Pop(NumberOfReturns + 1);
                        return Return(result1, result2, result3, result4);
                    }
                };
                template <typename T1, typename T2, typename T3, typename T4, typename T5>
                struct EndCall<std::tr1::tuple<T1, T2, T3, T4, T5>>
                {
                    typedef typename std::tr1::tuple<T1, T2, T3, T4, T5> Return;
                    static const int NumberOfReturns = 5;
                    static Return Do(LuaRuntimeEnvironment* self)
                    {
                        T1 result1;
                        T2 result2;
                        T3 result3;
                        T4 result4;
                        T5 result5;
                        self->Get(-5, result1);
                        self->Get(-4, result2);
                        self->Get(-3, result3);
                        self->Get(-2, result4);
                        self->Get(-1, result5);
                        self->Pop(NumberOfReturns + 1);
                        return Return(result1, result2, result3, result4, result5);
                    }
                };
                template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
                struct EndCall<std::tr1::tuple<T1, T2, T3, T4, T5, T6>>
                {
                    typedef typename std::tr1::tuple<T1, T2, T3, T4, T5, T6> Return;
                    static const int NumberOfReturns = 6;
                    static Return Do(LuaRuntimeEnvironment* self)
                    {
                        T1 result1;
                        T2 result2;
                        T3 result3;
                        T4 result4;
                        T5 result5;
                        T6 result6;
                        self->Get(-6, result1);
                        self->Get(-5, result2);
                        self->Get(-4, result3);
                        self->Get(-3, result4);
                        self->Get(-2, result5);
                        self->Get(-1, result6);
                        self->Pop(NumberOfReturns + 1);
                        return Return(result1, result2, result3, result4, result5, result6);
                    }
                };
                template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
                struct EndCall<std::tr1::tuple<T1, T2, T3, T4, T5, T6, T7>>
                {
                    typedef typename std::tr1::tuple<T1, T2, T3, T4, T5, T6, T7> Return;
                    static const int NumberOfReturns = 7;
                    static Return Do(LuaRuntimeEnvironment* self)
                    {
                        T1 result1;
                        T2 result2;
                        T3 result3;
                        T4 result4;
                        T5 result5;
                        T6 result6;
                        T7 result7;
                        self->Get(-7, result1);
                        self->Get(-6, result2);
                        self->Get(-5, result3);
                        self->Get(-4, result4);
                        self->Get(-3, result5);
                        self->Get(-2, result6);
                        self->Get(-1, result7);
                        self->Pop(NumberOfReturns + 1);
                        return Return(result1, result2, result3, result4, result5, result6, result7);
                    }
                };
                template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
                struct EndCall<std::tr1::tuple<T1, T2, T3, T4, T5, T6, T7, T8>>
                {
                    typedef typename std::tr1::tuple<T1, T2, T3, T4, T5, T6, T7, T8> Return;
                    static const int NumberOfReturns = 8;
                    static Return Do(LuaRuntimeEnvironment* self)
                    {
                        T1 result1;
                        T2 result2;
                        T3 result3;
                        T4 result4;
                        T5 result5;
                        T6 result6;
                        T7 result7;
                        T8 result8;
                        self->Get(-8, result1);
                        self->Get(-7, result2);
                        self->Get(-6, result3);
                        self->Get(-5, result4);
                        self->Get(-4, result5);
                        self->Get(-3, result6);
                        self->Get(-2, result7);
                        self->Get(-1, result8);
                        self->Pop(NumberOfReturns + 1);
                        return Return(result1, result2, result3, result4, result5, result6, result7, result8);
                    }
                };
                template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
                struct EndCall<std::tr1::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9>>
                {
                    typedef typename std::tr1::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> Return;
                    static const int NumberOfReturns = 9;
                    static Return Do(LuaRuntimeEnvironment* self)
                    {
                        T1 result1;
                        T2 result2;
                        T3 result3;
                        T4 result4;
                        T5 result5;
                        T6 result6;
                        T7 result7;
                        T8 result8;
                        T9 result9;
                        self->Get(-9, result1);
                        self->Get(-8, result2);
                        self->Get(-7, result3);
                        self->Get(-6, result4);
                        self->Get(-5, result5);
                        self->Get(-4, result6);
                        self->Get(-3, result7);
                        self->Get(-2, result8);
                        self->Get(-1, result9);
                        self->Pop(NumberOfReturns + 1);
                        return Return(result1, result2, result3, result4, result5, result6, result7, result8, result9);
                    }
                };
                template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
                struct EndCall<std::tr1::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>>
                {
                    typedef typename std::tr1::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> Return;
                    static const int NumberOfReturns = 10;
                    static Return Do(LuaRuntimeEnvironment* self)
                    {
                        T1 result1;
                        T2 result2;
                        T3 result3;
                        T4 result4;
                        T5 result5;
                        T6 result6;
                        T7 result7;
                        T8 result8;
                        T9 result9;
                        T10 result10;
                        self->Get(-10, result1);
                        self->Get(-9, result2);
                        self->Get(-8, result3);
                        self->Get(-7, result4);
                        self->Get(-6, result5);
                        self->Get(-5, result6);
                        self->Get(-4, result7);
                        self->Get(-3 result8);
                        self->Get(-2, result9);
                        self->Get(-1, result10);
                        self->Pop(NumberOfReturns + 1);
                        return Return(result1, result2, result3, result4, result5, result6, result7, result8, result9, result10);
                    }
                };

            private:
                struct Fields;
                Fields* mPointer;
                Fields& m;
        };

        class LuaError : public Exception
        {
            public:
                const String Filename;
                const int Line;

            public:
                LuaError(const String& message, const String& filename, int line);
                LuaError(const LuaError& original);
                virtual ~LuaError();

            private:
                LuaError& operator = (const LuaError&);
        };
    }

#   include <Bibim/LuaRuntimeEnvironment.inl>

#endif