#include <Bibim/PCH.h>
#include <Bibim/LuaRuntimeEnvironment.h>
#include <Bibim/Any.h>
#include <Bibim/Assert.h>
#include <Bibim/FileStream.h>
#include <vector>
extern "C"
{
#   include <lua.h>
#   include <lauxlib.h>
#   include <lualib.h>
}

namespace Bibim
{
    struct LuaRuntimeEnvironment::Fields
    {
        lua_State* state;
        String cachedCallStack;

        Fields()
            : state(nullptr)
        {
        }

        static int OnErrorOccured(lua_State* state);
    };

    LuaRuntimeEnvironment::LuaRuntimeEnvironment()
        : mPointer(new Fields()),
          m(*mPointer)
    {
        m.state = lua_open();
        lua_pushlightuserdata(m.state, this);
    }

    LuaRuntimeEnvironment::~LuaRuntimeEnvironment()
    {
        lua_pop(m.state, 1);
        lua_close(m.state);
        delete mPointer;
    }

    void LuaRuntimeEnvironment::Load(const String& filename)
    {
        FileStreamPtr stream(new FileStream(filename, FileAccess::Read, FileShare::Read));
        if (stream->CanRead() == false)
            return;

        std::vector<char> buffer;
        buffer.resize(stream->GetSize());
        stream->Read(&buffer[0], static_cast<int>(buffer.size()));

        lua_pushcclosure(m.state, &Fields::OnErrorOccured, 0);
        const int errorFunctionIndex = lua_gettop(m.state);

        const int loadResult = luaL_loadbuffer(m.state, &buffer[0], buffer.size(), filename.CStr());
        if (loadResult != 0)
        {
            const String errorMessage = lua_tostring(m.state, -1);
            lua_pop(m.state, 2);
            throw LuaError(errorMessage, filename, 0);
        }

        const int callResult = lua_pcall(m.state, 0, 0, errorFunctionIndex);
        if (callResult != 0)
        {
            const String errorMessage = lua_tostring(m.state, -1);
            lua_pop(m.state, 2);
            throw LuaError(errorMessage, filename, 0);
        }

        lua_pop(m.state, 1);
    }

    void LuaRuntimeEnvironment::Push(bool value)
    {
        lua_pushboolean(m.state, value ? 1 : 0);
    }

    void LuaRuntimeEnvironment::Push(char value)
    {
        lua_pushinteger(m.state, static_cast<lua_Integer>(value));
    }

    void LuaRuntimeEnvironment::Push(uchar value)
    {
        lua_pushinteger(m.state, static_cast<lua_Integer>(value));
    }

    void LuaRuntimeEnvironment::Push(short value)
    {
        lua_pushinteger(m.state, static_cast<lua_Integer>(value));
    }

    void LuaRuntimeEnvironment::Push(ushort value)
    {
        lua_pushinteger(m.state, static_cast<lua_Integer>(value));
    }

    void LuaRuntimeEnvironment::Push(int value)
    {
        lua_pushinteger(m.state, static_cast<lua_Integer>(value));
    }

    void LuaRuntimeEnvironment::Push(uint value)
    {
        lua_pushinteger(m.state, static_cast<lua_Integer>(value));
    }

    void LuaRuntimeEnvironment::Push(long value)
    {
        lua_pushinteger(m.state, static_cast<lua_Integer>(value));
    }

    void LuaRuntimeEnvironment::Push(ulong value)
    {
        lua_pushinteger(m.state, static_cast<lua_Integer>(value));
    }

    void LuaRuntimeEnvironment::Push(int64 value)
    {
        lua_pushinteger(m.state, static_cast<lua_Integer>(value));
    }

    void LuaRuntimeEnvironment::Push(uint64 value)
    {
        lua_pushinteger(m.state, static_cast<lua_Integer>(value));
    }

    void LuaRuntimeEnvironment::Push(float value)
    {
        lua_pushnumber(m.state, static_cast<lua_Number>(value));
    }

    void LuaRuntimeEnvironment::Push(double value)
    {
        lua_pushnumber(m.state, static_cast<lua_Number>(value));
    }

    void LuaRuntimeEnvironment::Push(const char* value)
    {
        if (value)
            lua_pushstring(m.state, value);
        else
            lua_pushnil(m.state);
    }

    void LuaRuntimeEnvironment::Push(const String& value)
    {
        lua_pushlstring(m.state, value.CStr(), value.GetLength());
    }

    void LuaRuntimeEnvironment::PushAny(const Any& value)
    {
        switch (value.GetType())
        {
            case Any::NullType:
            case Any::MissingType:
                lua_pushnil(m.state);
                break;
            case Any::BooleanType:
                lua_pushboolean(m.state, value.GetBoolean());
                break;
            case Any::CharType:
                lua_pushinteger(m.state, static_cast<lua_Integer>(value.GetChar()));
                break;
            case Any::UCharType:
                lua_pushinteger(m.state, static_cast<lua_Integer>(value.GetUChar()));
                break;
            case Any::ShortType:
                lua_pushinteger(m.state, static_cast<lua_Integer>(value.GetShort()));
                break;
            case Any::UShortType:
                lua_pushinteger(m.state, static_cast<lua_Integer>(value.GetUShort()));
                break;
            case Any::IntType:
                lua_pushinteger(m.state, static_cast<lua_Integer>(value.GetInt()));
                break;
            case Any::UIntType:
                lua_pushinteger(m.state, static_cast<lua_Integer>(value.GetUInt()));
                break;
            case Any::LongType:
                lua_pushinteger(m.state, static_cast<lua_Integer>(value.GetLong()));
                break;
            case Any::ULongType:
                lua_pushinteger(m.state, static_cast<lua_Integer>(value.GetULong()));
                break;
            case Any::Int64Type:
                lua_pushinteger(m.state, static_cast<lua_Integer>(value.GetInt64()));
                break;
            case Any::UInt64Type:
                lua_pushinteger(m.state, static_cast<lua_Integer>(value.GetUInt64()));
                break;
            case Any::FloatType:
                lua_pushnumber(m.state, static_cast<lua_Number>(value.GetFloat()));
                break;
            case Any::DoubleType:
                lua_pushnumber(m.state, static_cast<lua_Number>(value.GetDouble()));
                break;
            case Any::ColorType:
            case Any::Matrix4Type:
            case Any::PointType:
            case Any::QuaternionType:
            case Any::RectangleType:
            case Any::RectangleFType:
                throw;
            case Any::StringType:
                lua_pushstring(m.state, value.GetString().CStr());
                break;
            case Any::Vector2Type:
            case Any::Vector3Type:
            case Any::Vector4Type:
            case Any::ClassType:
                throw;
        }
    }

    void LuaRuntimeEnvironment::Get(int index, bool& outValue)
    {
        outValue = (lua_toboolean(m.state, index) != 0);
    }

    void LuaRuntimeEnvironment::Get(int index, char& outValue)
    {
        outValue = static_cast<char>(lua_tointeger(m.state, index));
    }

    void LuaRuntimeEnvironment::Get(int index, uchar& outValue)
    {
        outValue = static_cast<uchar>(lua_tointeger(m.state, index));
    }

    void LuaRuntimeEnvironment::Get(int index, short& outValue)
    {
        outValue = static_cast<short>(lua_tointeger(m.state, index));
    }

    void LuaRuntimeEnvironment::Get(int index, ushort& outValue)
    {
        outValue = static_cast<ushort>(lua_tointeger(m.state, index));
    }

    void LuaRuntimeEnvironment::Get(int index, int& outValue)
    {
        outValue = static_cast<int>(lua_tointeger(m.state, index));
    }

    void LuaRuntimeEnvironment::Get(int index, uint& outValue)
    {
        outValue = static_cast<uint>(lua_tointeger(m.state, index));
    }

    void LuaRuntimeEnvironment::Get(int index, long& outValue)
    {
        outValue = static_cast<long>(lua_tointeger(m.state, index));
    }

    void LuaRuntimeEnvironment::Get(int index, ulong& outValue)
    {
        outValue = static_cast<ulong>(lua_tointeger(m.state, index));
    }

    void LuaRuntimeEnvironment::Get(int index, int64& outValue)
    {
        outValue = static_cast<int64>(lua_tointeger(m.state, index));
    }

    void LuaRuntimeEnvironment::Get(int index, uint64& outValue)
    {
        outValue = static_cast<uint64>(lua_tointeger(m.state, index));
    }

    void LuaRuntimeEnvironment::Get(int index, float& outValue)
    {
        outValue = static_cast<float>(lua_tonumber(m.state, index));
    }

    void LuaRuntimeEnvironment::Get(int index, double& outValue)
    {
        outValue = static_cast<double>(lua_tonumber(m.state, index));
    }

    void LuaRuntimeEnvironment::Get(int index, String& outValue)
    {
        outValue = lua_tostring(m.state, index);
    }

    void LuaRuntimeEnvironment::Get(int index, Any& outValue)
    {
        switch (lua_type(m.state, index))
        {
            case LUA_TNIL:
                outValue = Any::Null;
                break;
            case LUA_TBOOLEAN:
                outValue = (lua_toboolean(m.state, index) != 0);
                break;
            case LUA_TLIGHTUSERDATA:
                throw;
            case LUA_TNUMBER:
                outValue = lua_tonumber(m.state, index);
                break;
            case LUA_TSTRING:
                outValue = lua_tostring(m.state, index);
                break;
            case LUA_TTABLE:
                throw;
            case LUA_TFUNCTION:
                throw;
            case LUA_TUSERDATA:
                throw;
            case LUA_TTHREAD:
                throw;
            case LUA_TNONE:
                outValue = Any::Missing;
                break;
        }
    }

    void LuaRuntimeEnvironment::Pop(int count)
    {
        lua_pop(m.state, count);
    }

    void LuaRuntimeEnvironment::BeginCall(const char* function)
    {
        lua_pushcclosure(m.state, &Fields::OnErrorOccured, 0);

        lua_getglobal(m.state, function);
        BBAssertDebug(lua_isfunction(m.state, -1));
    }

    void LuaRuntimeEnvironment::CallActually(int numberOfArguments, int numberOfResults)
    {
        const int callResult = lua_pcall(m.state, numberOfArguments, numberOfResults, -numberOfArguments - 2);
        if (callResult != 0)
        {
            const String errorMessage = lua_tostring(m.state, -1);
            lua_pop(m.state, 2);
            throw LuaError(errorMessage, String::Empty, 0);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    int LuaRuntimeEnvironment::Fields::OnErrorOccured(lua_State* state)
    {
        LuaRuntimeEnvironment* environment = reinterpret_cast<LuaRuntimeEnvironment*>(lua_touserdata(state, 0));
        BBAssertDebug(environment);

        String callStack;
        lua_Debug debug;
        for (int i = 0;;i++)
        {
            if (lua_getstack(environment->m.state, i, &debug) ==  1)
            {
                lua_getinfo(environment->m.state, "nSlu", &debug);

                if (debug.name)
                {
                    callStack += debug.name;
                    callStack += " ";
                    callStack += debug.source;
                }
                else
                {
                    callStack += debug.name;
                    callStack += " ";
                    callStack += "Unknown";
                }
            }
            else
                break;
        }

        environment->m.cachedCallStack = callStack;

        return 0;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    LuaError::LuaError(const String& message, const String& filename, int line)
        : Exception(message.CStr()),
          Filename(filename),
          Line(line)
    {
    }

    LuaError::LuaError(const LuaError& original)
        : Exception(original),
          Filename(original.Filename),
          Line(original.Line)
    {
    }
    
    LuaError::~LuaError()
    {
    }
}