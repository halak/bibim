// lua_tinker.cpp
//
// LuaTinker - Simple and light C++ wrapper for Lua.
//
// Copyright (c) 2005-2007 Kwon-il Lee (zupet@hitel.net)
// 
// please check Licence.txt file for licence and legal issues. 

extern "C"
{
#   include <lua.h>
#   include <lauxlib.h>
#   include <lualib.h>
}

#include "lua_tinker.h"
#include <memory.h>
#include <Bibim/Numerics.h>


/*---------------------------------------------------------------------------*/ 
/* init                                                                      */ 
/*---------------------------------------------------------------------------*/ 
void lua_tinker::init(lua_State *L)
{
    init_s64(L);
    init_u64(L);
}

/*---------------------------------------------------------------------------*/ 
/* __s64                                                                     */ 
/*---------------------------------------------------------------------------*/ 
static int tostring_s64(lua_State *L)
{
    char temp[64];
    sprintf(temp, /*sizeof(temp), */"%I64d", *(long long*)lua_topointer(L, 1));
    lua_pushstring(L, temp);
    return 1;
}

/*---------------------------------------------------------------------------*/ 
static int eq_s64(lua_State *L)
{
    const long long a = lua_tinker::read<long long>(L, 1);
    const long long b = lua_tinker::read<long long>(L, 2);
    lua_pushboolean(L, a == b ? 1 : 0);
    return 1;
}

/*---------------------------------------------------------------------------*/ 
static int lt_s64(lua_State *L)
{
    const long long a = lua_tinker::read<long long>(L, 1);
    const long long b = lua_tinker::read<long long>(L, 2);
    lua_pushboolean(L, a < b ? 1 : 0);
    return 1;
}

/*---------------------------------------------------------------------------*/ 
static int le_s64(lua_State *L)
{
    const long long a = lua_tinker::read<long long>(L, 1);
    const long long b = lua_tinker::read<long long>(L, 2);
    lua_pushboolean(L, a <= b ? 1 : 0);
    return 1;
}

/*---------------------------------------------------------------------------*/ 
static int add_s64(lua_State *L)
{
    const long long a = lua_tinker::read<long long>(L, 1);
    const long long b = lua_tinker::read<long long>(L, 2);
    lua_tinker::push(L, a + b);
    return 1;
}

/*---------------------------------------------------------------------------*/
static int sub_s64(lua_State *L)
{
    const long long a = lua_tinker::read<long long>(L, 1);
    const long long b = lua_tinker::read<long long>(L, 2);
    lua_tinker::push(L, a - b);
    return 1;
}

/*---------------------------------------------------------------------------*/ 
static int mul_s64(lua_State *L)
{
    const long long a = lua_tinker::read<long long>(L, 1);
    const long long b = lua_tinker::read<long long>(L, 2);
    lua_tinker::push(L, a * b);
    return 1;
}

/*---------------------------------------------------------------------------*/
static int div_s64(lua_State *L)
{
    const long long a = lua_tinker::read<long long>(L, 1);
    const long long b = lua_tinker::read<long long>(L, 2);
    lua_tinker::push(L, a / b);
    return 1;
}

/*---------------------------------------------------------------------------*/ 
static int mod_s64(lua_State *L)
{
    const long long a = lua_tinker::read<long long>(L, 1);
    const long long b = lua_tinker::read<long long>(L, 2);
    lua_tinker::push(L, a % b);
    return 1;
}

/*---------------------------------------------------------------------------*/
static int unm_s64(lua_State *L)
{
    const long long a = lua_tinker::read<long long>(L, 1);
    lua_tinker::push(L, -a);
    return 1;
}


/*---------------------------------------------------------------------------*/ 
void lua_tinker::init_s64(lua_State *L)
{
    const char* name = "__s64";
    lua_newtable(L);

    lua_pushstring(L, "__name");
    lua_pushstring(L, name);
    lua_rawset(L, -3);

    lua_pushstring(L, "__tostring");
    lua_pushcclosure(L, tostring_s64, 0);
    lua_rawset(L, -3);

    lua_pushstring(L, "__eq");
    lua_pushcclosure(L, eq_s64, 0);
    lua_rawset(L, -3);    

    lua_pushstring(L, "__lt");
    lua_pushcclosure(L, lt_s64, 0);
    lua_rawset(L, -3);    

    lua_pushstring(L, "__le");
    lua_pushcclosure(L, le_s64, 0);
    lua_rawset(L, -3);    

    lua_pushstring(L, "__add");
    lua_pushcclosure(L, add_s64, 0);
    lua_rawset(L, -3);    

    lua_pushstring(L, "__sub");
    lua_pushcclosure(L, sub_s64, 0);
    lua_rawset(L, -3);

    lua_pushstring(L, "__mul");
    lua_pushcclosure(L, mul_s64, 0);
    lua_rawset(L, -3);

    lua_pushstring(L, "__div");
    lua_pushcclosure(L, div_s64, 0);
    lua_rawset(L, -3);

    lua_pushstring(L, "__mod");
    lua_pushcclosure(L, mod_s64, 0);
    lua_rawset(L, -3);

    lua_pushstring(L, "__unm");
    lua_pushcclosure(L, unm_s64, 0);
    lua_rawset(L, -3);

    lua_setglobal(L, name);
}

/*---------------------------------------------------------------------------*/ 
/* __u64                                                                     */ 
/*---------------------------------------------------------------------------*/ 
static int tostring_u64(lua_State *L)
{
    char temp[64];
    sprintf(temp, /*sizeof(temp), */"%I64u", *(unsigned long long*)lua_topointer(L, 1));
    lua_pushstring(L, temp);
    return 1;
}

/*---------------------------------------------------------------------------*/ 
static int eq_u64(lua_State *L)
{
    const unsigned long long a = lua_tinker::read<unsigned long long>(L, 1);
    const unsigned long long b = lua_tinker::read<unsigned long long>(L, 2);
    lua_pushboolean(L, a == b ? 1 : 0);
    return 1;
}

/*---------------------------------------------------------------------------*/ 
static int lt_u64(lua_State *L)
{
    const unsigned long long a = lua_tinker::read<unsigned long long>(L, 1);
    const unsigned long long b = lua_tinker::read<unsigned long long>(L, 2);
    lua_pushboolean(L, a < b ? 1 : 0);
    return 1;
}

/*---------------------------------------------------------------------------*/ 
static int le_u64(lua_State *L)
{
    const unsigned long long a = lua_tinker::read<unsigned long long>(L, 1);
    const unsigned long long b = lua_tinker::read<unsigned long long>(L, 2);
    lua_pushboolean(L, a <= b ? 1 : 0);
    return 1;
}

/*---------------------------------------------------------------------------*/ 
static int add_u64(lua_State *L)
{
    const unsigned long long a = lua_tinker::read<unsigned long long>(L, 1);
    const unsigned long long b = lua_tinker::read<unsigned long long>(L, 2);
    lua_tinker::push(L, a + b);
    return 1;
}

/*---------------------------------------------------------------------------*/
static int sub_u64(lua_State *L)
{
    const unsigned long long a = lua_tinker::read<unsigned long long>(L, 1);
    const unsigned long long b = lua_tinker::read<unsigned long long>(L, 2);
    lua_tinker::push(L, a - b);
    return 1;
}

/*---------------------------------------------------------------------------*/ 
static int mul_u64(lua_State *L)
{
    const unsigned long long a = lua_tinker::read<unsigned long long>(L, 1);
    const unsigned long long b = lua_tinker::read<unsigned long long>(L, 2);
    lua_tinker::push(L, a * b);
    return 1;
}

/*---------------------------------------------------------------------------*/
static int div_u64(lua_State *L)
{
    const unsigned long long a = lua_tinker::read<unsigned long long>(L, 1);
    const unsigned long long b = lua_tinker::read<unsigned long long>(L, 2);
    lua_tinker::push(L, a / b);
    return 1;
}

/*---------------------------------------------------------------------------*/ 
static int mod_u64(lua_State *L)
{
    const unsigned long long a = lua_tinker::read<unsigned long long>(L, 1);
    const unsigned long long b = lua_tinker::read<unsigned long long>(L, 2);
    lua_tinker::push(L, a % b);
    return 1;
}


/*---------------------------------------------------------------------------*/ 
void lua_tinker::init_u64(lua_State *L)
{
    const char* name = "__u64";
    lua_newtable(L);

    lua_pushstring(L, "__name");
    lua_pushstring(L, name);
    lua_rawset(L, -3);

    lua_pushstring(L, "__tostring");
    lua_pushcclosure(L, tostring_u64, 0);
    lua_rawset(L, -3);

    lua_pushstring(L, "__eq");
    lua_pushcclosure(L, eq_u64, 0);
    lua_rawset(L, -3);    

    lua_pushstring(L, "__lt");
    lua_pushcclosure(L, lt_u64, 0);
    lua_rawset(L, -3);    

    lua_pushstring(L, "__le");
    lua_pushcclosure(L, le_u64, 0);
    lua_rawset(L, -3);    

    lua_pushstring(L, "__add");
    lua_pushcclosure(L, add_u64, 0);
    lua_rawset(L, -3);    

    lua_pushstring(L, "__sub");
    lua_pushcclosure(L, sub_u64, 0);
    lua_rawset(L, -3);    

    lua_pushstring(L, "__mul");
    lua_pushcclosure(L, mul_u64, 0);
    lua_rawset(L, -3);    

    lua_pushstring(L, "__div");
    lua_pushcclosure(L, div_u64, 0);
    lua_rawset(L, -3);    

    lua_pushstring(L, "__mod");
    lua_pushcclosure(L, mod_u64, 0);
    lua_rawset(L, -3);    

    lua_setglobal(L, name);
}

/*---------------------------------------------------------------------------*/ 
/* excution                                                                  */ 
/*---------------------------------------------------------------------------*/ 
void lua_tinker::dofile(lua_State *L, const char *filename)
{
    lua_pushcclosure(L, on_error, 0);
    int errfunc = lua_gettop(L);

    if(luaL_loadfile(L, filename) == 0)
    {
        if(lua_pcall(L, 0, 0, errfunc) != 0)
        {
            lua_pop(L, 1);
        }
    }
    else
    {
        print_error(L, "%s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }

    lua_pop(L, 1);
}

/*---------------------------------------------------------------------------*/ 
void lua_tinker::dostring(lua_State *L, const char* buff)
{
    lua_tinker::dobuffer(L, buff, strlen(buff), "lua_tinker::dostring()");
}

void lua_tinker::dostring(lua_State *L, const char* buff, const char* name)
{
    lua_tinker::dobuffer(L, buff, strlen(buff), name);
}

/*---------------------------------------------------------------------------*/ 
void lua_tinker::dobuffer(lua_State *L, const char* buff, size_t len)
{
    lua_tinker::dobuffer(L, buff, len, "lua_tinker::dobuffer()");
}

void lua_tinker::dobuffer(lua_State *L, const char* buff, size_t len, const char* name)
{
    lua_pushcclosure(L, on_error, 0);
    int errfunc = lua_gettop(L);

    if(luaL_loadbuffer(L, buff, len, name) == 0)
    {
        if(lua_pcall(L, 0, 0, errfunc) != 0)
        {
            lua_pop(L, 1);
        }
    }
    else
    {
        print_error(L, "%s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }

    lua_pop(L, 1);
}

/*---------------------------------------------------------------------------*/ 
/* debug helpers                                                             */ 
/*---------------------------------------------------------------------------*/ 
static void call_stack(lua_State* L, int n)
{
    lua_Debug ar;
    if(lua_getstack(L, n, &ar) == 1)
    {
        lua_getinfo(L, "nSlu", &ar);

        const char* indent;
        if(n == 0)
        {
            indent = "->\t";
            lua_tinker::print_error(L, "\t<call stack>");
        }
        else
        {
            indent = "\t";
        }

        if(ar.name)
            lua_tinker::print_error(L, "%s%s() : line %d [%s : line %d]", indent, ar.name, ar.currentline, ar.source, ar.linedefined);
        else
            lua_tinker::print_error(L, "%sunknown : line %d [%s : line %d]", indent, ar.currentline, ar.source, ar.linedefined);

        call_stack(L, n+1);
    }
}

/*---------------------------------------------------------------------------*/ 
int lua_tinker::on_error(lua_State *L)
{
    print_error(L, "%s", lua_tostring(L, -1));

    call_stack(L, 0);

    return 0;    
}

/*---------------------------------------------------------------------------*/ 
void lua_tinker::print_error(lua_State *L, const char* fmt, ...)
{
    char text[4096];

    va_list args;
    va_start(args, fmt);
    vsprintf(text, /*sizeof(text), */fmt, args);
    va_end(args);

    lua_getglobal(L, "_ALERT");
    if(lua_isfunction(L, -1))
    {
        lua_pushstring(L, text);
        lua_call(L, 1, 0);
    }
    else
    {
        printf("%s\n", text);
        lua_pop(L, 1);
    }
}

/*---------------------------------------------------------------------------*/ 
void lua_tinker::enum_stack(lua_State *L)
{
    int top = lua_gettop(L);
    print_error(L, "Type:%d", top);
    for(int i=1; i<=lua_gettop(L); ++i)
    {
        switch(lua_type(L, i))
        {
        case LUA_TNIL:
            print_error(L, "\t%s", lua_typename(L, lua_type(L, i)));
            break;
        case LUA_TBOOLEAN:
            print_error(L, "\t%s    %s", lua_typename(L, lua_type(L, i)), lua_toboolean(L, i)?"true":"false");
            break;
        case LUA_TLIGHTUSERDATA:
            print_error(L, "\t%s    0x%08p", lua_typename(L, lua_type(L, i)), lua_topointer(L, i));
            break;
        case LUA_TNUMBER:
            print_error(L, "\t%s    %f", lua_typename(L, lua_type(L, i)), lua_tonumber(L, i));
            break;
        case LUA_TSTRING:
            print_error(L, "\t%s    %s", lua_typename(L, lua_type(L, i)), lua_tostring(L, i));
            break;
        case LUA_TTABLE:
            print_error(L, "\t%s    0x%08p", lua_typename(L, lua_type(L, i)), lua_topointer(L, i));
            break;
        case LUA_TFUNCTION:
            print_error(L, "\t%s()    0x%08p", lua_typename(L, lua_type(L, i)), lua_topointer(L, i));
            break;
        case LUA_TUSERDATA:
            print_error(L, "\t%s    0x%08p", lua_typename(L, lua_type(L, i)), lua_topointer(L, i));
            break;
        case LUA_TTHREAD:
            print_error(L, "\t%s", lua_typename(L, lua_type(L, i)));
            break;
        }
    }
}
 
/*---------------------------------------------------------------------------*/ 
/* read                                                                      */ 
/*---------------------------------------------------------------------------*/ 
template<>
char* lua_tinker::read(lua_State *L, int index)
{
    return (char*)lua_tostring(L, index);
}

template<>
const char* lua_tinker::read(lua_State *L, int index)
{
    return (const char*)lua_tostring(L, index);        
}

template<>
char lua_tinker::read(lua_State *L, int index)
{
    return (char)lua_tonumber(L, index);                
}

template<>
unsigned char lua_tinker::read(lua_State *L, int index)
{
    return (unsigned char)lua_tonumber(L, index);        
}

template<>
short lua_tinker::read(lua_State *L, int index)
{
    return (short)lua_tonumber(L, index);                
}

template<>
unsigned short lua_tinker::read(lua_State *L, int index)
{
    return (unsigned short)lua_tonumber(L, index);    
}

template<>
long lua_tinker::read(lua_State *L, int index)
{
    return (long)lua_tonumber(L, index);                
}

template<>
unsigned long lua_tinker::read(lua_State *L, int index)
{
    return (unsigned long)lua_tonumber(L, index);        
}

template<>
int lua_tinker::read(lua_State *L, int index)
{
    return (int)lua_tonumber(L, index);                
}

template<>
unsigned int lua_tinker::read(lua_State *L, int index)
{
    return (unsigned int)lua_tonumber(L, index);        
}

template<>
float lua_tinker::read(lua_State *L, int index)
{
    return (float)lua_tonumber(L, index);                
}

template<>
double lua_tinker::read(lua_State *L, int index)
{
    return (double)lua_tonumber(L, index);            
}

template<>
bool lua_tinker::read(lua_State *L, int index)
{
    if(lua_isboolean(L, index))
        return lua_toboolean(L, index) != 0;                
    else
        return lua_tonumber(L, index) != 0;
}

template<>
void lua_tinker::read(lua_State */*L*/, int /*index*/)
{
    return;                                            
}

template<>
long long lua_tinker::read(lua_State *L, int index)
{
    if(lua_isnumber(L,index))
        return (long long)lua_tonumber(L, index);
    else
        return *(long long*)lua_touserdata(L, index);
}
template<>
unsigned long long lua_tinker::read(lua_State *L, int index)
{
    if(lua_isnumber(L,index))
        return (unsigned long long)lua_tonumber(L, index);
    else
        return *(unsigned long long*)lua_touserdata(L, index);
}

template<>
lua_tinker::table lua_tinker::read(lua_State *L, int index)
{
    return table(L, index);
}

template<>
Bibim::String lua_tinker::read(lua_State *L, int index)
{
    return Bibim::String(lua_tostring(L, index));
}

template<>
Bibim::Any lua_tinker::read(lua_State *L, int index)
{
    switch (lua_type(L, index))
    {
        case LUA_TNIL:
            return Bibim::Any::Void;
        case LUA_TBOOLEAN:
            return Bibim::Any(lua_toboolean(L, index) ? true : false);
        case LUA_TLIGHTUSERDATA:
            return Bibim::Any::Void;
        case LUA_TNUMBER:
            return Bibim::Any(static_cast<float>(lua_tonumber(L, index)));
        case LUA_TSTRING:
            return Bibim::Any(Bibim::String(lua_tostring(L, index)));
        case LUA_TTABLE:
            return Bibim::Any::Void;
        case LUA_TFUNCTION:
            return Bibim::Any::Void;
        case LUA_TUSERDATA:
            return Bibim::Any::Void;
        case LUA_TTHREAD:
            return Bibim::Any::Void; 
        default:
            return Bibim::Any::Void;
    }
}


/*---------------------------------------------------------------------------*/ 
/* push                                                                      */ 
/*---------------------------------------------------------------------------*/ 
template<>
void lua_tinker::push(lua_State *L, char ret)
{
    lua_pushnumber(L, ret);
}

template<>
void lua_tinker::push(lua_State *L, unsigned char ret)
{
    lua_pushnumber(L, ret);
}

template<>
void lua_tinker::push(lua_State *L, short ret)
{
    lua_pushnumber(L, ret);
}

template<>
void lua_tinker::push(lua_State *L, unsigned short ret)
{
    lua_pushnumber(L, ret);
}

template<>
void lua_tinker::push(lua_State *L, long ret)
{
    lua_pushnumber(L, ret);
}

template<>
void lua_tinker::push(lua_State *L, unsigned long ret)
{
    lua_pushnumber(L, ret);
}

template<>
void lua_tinker::push(lua_State *L, int ret)
{
    lua_pushnumber(L, ret);
}

template<>
void lua_tinker::push(lua_State *L, unsigned int ret)
{
    lua_pushnumber(L, ret);
}

template<>
void lua_tinker::push(lua_State *L, float ret)
{
    lua_pushnumber(L, ret);
}

template<>
void lua_tinker::push(lua_State *L, double ret)
{
    lua_pushnumber(L, ret);
}

template<>
void lua_tinker::push(lua_State *L, char* ret)
{
    lua_pushstring(L, ret);
}

template<>
void lua_tinker::push(lua_State *L, const char* ret)
{
    lua_pushstring(L, ret);
}

template<>
void lua_tinker::push(lua_State *L, bool ret)
{
    lua_pushboolean(L, ret);
}

template<>
void lua_tinker::push(lua_State *L, lua_value* ret)
{
    if(ret) ret->to_lua(L); else lua_pushnil(L);
}

template<>
void lua_tinker::push(lua_State *L, long long ret)
{ 
    *(long long*)lua_newuserdata(L, sizeof(long long)) = ret;
    lua_getglobal(L, "__s64");
    lua_setmetatable(L, -2);
}

template<>
void lua_tinker::push(lua_State *L, unsigned long long ret)
{
    *(unsigned long long*)lua_newuserdata(L, sizeof(unsigned long long)) = ret;
    lua_getglobal(L, "__u64");
    lua_setmetatable(L, -2);
}

template<>
void lua_tinker::push(lua_State *L, lua_tinker::table ret)
{
    lua_pushvalue(L, ret.m_obj->m_index);
}

template<>
void lua_tinker::push(lua_State *L, const Bibim::String& ret)
{
    lua_pushstring(L, ret.CStr());
}

template<>
void lua_tinker::push(lua_State *L, const Bibim::Any& ret)
{
    switch (ret.GetType())
    {
        case Bibim::Any::VoidType:
            lua_pushnil(L);
            break;
        case Bibim::Any::BoolType:
            push(L, ret.CastBool());
            break;
        case Bibim::Any::IntType:
            push(L, ret.CastInt());
            break;
        case Bibim::Any::LongIntType:
            push(L, ret.CastLongInt());
            break;
        case Bibim::Any::FloatType:
            push(L, ret.CastFloat());
            break;
        case Bibim::Any::ColorType:
        case Bibim::Any::Int2Type:
        case Bibim::Any::Int3Type:
        case Bibim::Any::Int4Type:
        case Bibim::Any::Float2Type:
        case Bibim::Any::Float3Type:
        case Bibim::Any::Float4Type:
            lua_pushnil(L);
            break;
        case Bibim::Any::StringType:
            push(L, ret.CastString());
            break;
        case Bibim::Any::SharedObjectType:
        case Bibim::Any::LightObjectType:
            lua_pushnil(L);
            break;
    }
}

template<>
int lua_tinker::push_for_return(lua_State *L, char ret)
{
    lua_pushnumber(L, ret);
    return 1;
}

template<>
int lua_tinker::push_for_return(lua_State *L, unsigned char ret)
{
    lua_pushnumber(L, ret);
    return 1;
}

template<>
int lua_tinker::push_for_return(lua_State *L, short ret)
{
    lua_pushnumber(L, ret);
    return 1;
}

template<>
int lua_tinker::push_for_return(lua_State *L, unsigned short ret)
{
    lua_pushnumber(L, ret);
    return 1;
}

template<>
int lua_tinker::push_for_return(lua_State *L, long ret)
{
    lua_pushnumber(L, ret);
    return 1;
}

template<>
int lua_tinker::push_for_return(lua_State *L, unsigned long ret)
{
    lua_pushnumber(L, ret);
    return 1;
}

template<>
int lua_tinker::push_for_return(lua_State *L, int ret)
{
    lua_pushnumber(L, ret);
    return 1;
}

template<>
int lua_tinker::push_for_return(lua_State *L, unsigned int ret)
{
    lua_pushnumber(L, ret);
    return 1;
}

template<>
int lua_tinker::push_for_return(lua_State *L, float ret)
{
    lua_pushnumber(L, ret);
    return 1;
}

template<>
int lua_tinker::push_for_return(lua_State *L, double ret)
{
    lua_pushnumber(L, ret);
    return 1;
}

template<>
int lua_tinker::push_for_return(lua_State *L, char* ret)
{
    lua_pushstring(L, ret);
    return 1;
}

template<>
int lua_tinker::push_for_return(lua_State *L, const char* ret)
{
    lua_pushstring(L, ret);
    return 1;
}

template<>
int lua_tinker::push_for_return(lua_State *L, bool ret)
{
    lua_pushboolean(L, ret);
    return 1;
}

template<>
int lua_tinker::push_for_return(lua_State *L, lua_value* ret)
{
    if(ret) ret->to_lua(L); else lua_pushnil(L);
    return 1;
}

template<>
int lua_tinker::push_for_return(lua_State *L, long long ret)
{ 
    *(long long*)lua_newuserdata(L, sizeof(long long)) = ret;
    lua_getglobal(L, "__s64");
    lua_setmetatable(L, -2);
    return 1;
}
template<>
int lua_tinker::push_for_return(lua_State *L, unsigned long long ret)
{
    *(unsigned long long*)lua_newuserdata(L, sizeof(unsigned long long)) = ret;
    lua_getglobal(L, "__u64");
    lua_setmetatable(L, -2);
    return 1;
}

template<>
int lua_tinker::push_for_return(lua_State *L, lua_tinker::table ret)
{
    lua_pushvalue(L, ret.m_obj->m_index);
    return 1;
}

template<>
int lua_tinker::push_for_return(lua_State *L, Bibim::Color ret)
{
    return push_for_return(L, ret.ToVector4());
}

template<>
int lua_tinker::push_for_return(lua_State *L, Bibim::Point2 ret)
{
    lua_pushinteger(L, ret.X);
    lua_pushinteger(L, ret.Y);
    return 2;
}

template<>
int lua_tinker::push_for_return(lua_State *L, Bibim::Point3 ret)
{
    lua_pushinteger(L, ret.X);
    lua_pushinteger(L, ret.Y);
    lua_pushinteger(L, ret.Z);
    return 3;
}

template<>
int lua_tinker::push_for_return(lua_State *L, Bibim::Point4 ret)
{
    lua_pushinteger(L, ret.X);
    lua_pushinteger(L, ret.Y);
    lua_pushinteger(L, ret.Z);
    lua_pushinteger(L, ret.W);
    return 4;
}

template<>
int lua_tinker::push_for_return(lua_State *L, Bibim::Rect ret)
{
    lua_pushinteger(L, ret.X);
    lua_pushinteger(L, ret.Y);
    lua_pushinteger(L, ret.Width);
    lua_pushinteger(L, ret.Height);
    return 4;
}

template<>
int lua_tinker::push_for_return(lua_State *L, Bibim::RectF ret)
{
    lua_pushnumber(L, ret.X);
    lua_pushnumber(L, ret.Y);
    lua_pushnumber(L, ret.Width);
    lua_pushnumber(L, ret.Height);
    return 4;
}

template<>
int lua_tinker::push_for_return(lua_State *L, Bibim::Vector2 ret)
{
    lua_pushnumber(L, ret.X);
    lua_pushnumber(L, ret.Y);
    return 2;
}

template<>
int lua_tinker::push_for_return(lua_State *L, Bibim::Vector3 ret)
{
    lua_pushnumber(L, ret.X);
    lua_pushnumber(L, ret.Y);
    lua_pushnumber(L, ret.Z);
    return 3;
}

template<>
int lua_tinker::push_for_return(lua_State *L, Bibim::Vector4 ret)
{
    lua_pushnumber(L, ret.X);
    lua_pushnumber(L, ret.Y);
    lua_pushnumber(L, ret.Z);
    lua_pushnumber(L, ret.W);
    return 4;
}

template<>
int lua_tinker::push_for_return(lua_State *L, const Bibim::String& ret)
{
    lua_pushstring(L, ret.CStr());
    return 1;
}

template<>
int lua_tinker::push_for_return(lua_State *L, const Bibim::Any& ret)
{
    switch (ret.GetType())
    {
        case Bibim::Any::VoidType:
            return 0;
        case Bibim::Any::BoolType:
            return push_for_return(L, ret.CastBool());
        case Bibim::Any::IntType:
            return push_for_return(L, ret.CastInt());
        case Bibim::Any::LongIntType:
            return push_for_return(L, ret.CastLongInt());
        case Bibim::Any::FloatType:
            return push_for_return(L, ret.CastFloat());
        case Bibim::Any::ColorType:
            return push_for_return(L, ret.CastColor());
        case Bibim::Any::Int2Type:
            return push_for_return(L, ret.CastPoint2());
        case Bibim::Any::Int3Type:
            return push_for_return(L, ret.CastPoint3());
        case Bibim::Any::Int4Type:
            return push_for_return(L, ret.CastPoint4());
        case Bibim::Any::Float2Type:
            return push_for_return(L, ret.CastVector2());
        case Bibim::Any::Float3Type:
            return push_for_return(L, ret.CastVector3());
        case Bibim::Any::Float4Type:
            return push_for_return(L, ret.CastVector4());
        case Bibim::Any::StringType:
            return push_for_return(L, ret.CastString());
        case Bibim::Any::SharedObjectType:
            return push_for_return(L, ret.CastSharedObject());
        default:
            return 0;
    }
}

/*---------------------------------------------------------------------------*/ 
/* pop                                                                       */ 
/*---------------------------------------------------------------------------*/ 
template<>
void lua_tinker::pop(lua_State *L)
{
    lua_pop(L, 1);
}

template<>    
lua_tinker::table lua_tinker::pop(lua_State *L)
{
    return table(L, lua_gettop(L));
}

/*---------------------------------------------------------------------------*/ 
/* Tinker Class Helper                                                       */ 
/*---------------------------------------------------------------------------*/ 
static void invoke_parent(lua_State *L)
{
    lua_pushstring(L, "__parent");
    lua_rawget(L, -2);
    if(lua_istable(L,-1))
    {
        lua_pushvalue(L,2);
        lua_rawget(L, -2);
        if(!lua_isnil(L,-1))
        {
            lua_remove(L,-2);
        }
        else
        {
            lua_remove(L, -1);
            invoke_parent(L);
            lua_remove(L,-2);
        }
    }
}

/*---------------------------------------------------------------------------*/ 
int lua_tinker::meta_get(lua_State *L)
{
    lua_getmetatable(L,1);
    lua_pushvalue(L,2);
    lua_rawget(L,-2);

    if(lua_isuserdata(L,-1))
    {
        user2type<var_base*>::invoke(L,-1)->get(L);
        lua_remove(L, -2);
    }
    else if(lua_isnil(L,-1))
    {
        lua_remove(L,-1);
        invoke_parent(L);
        if(lua_isnil(L,-1))
        {
            lua_pushfstring(L, "can't find '%s' class variable. (forgot registering class variable ?)", lua_tostring(L, 2));
            lua_error(L);
        }
    } 

    lua_remove(L,-2);

    return 1;
}

/*---------------------------------------------------------------------------*/ 
int lua_tinker::meta_set(lua_State *L)
{
    lua_getmetatable(L,1);
    lua_pushvalue(L,2);
    lua_rawget(L,-2);

    if(lua_isuserdata(L,-1))
    {
        user2type<var_base*>::invoke(L,-1)->set(L);
    }
    else if(lua_isnil(L, -1))
    {
        lua_pushvalue(L,2);
        lua_pushvalue(L,3);
        lua_rawset(L, -4);
    }
    lua_settop(L, 3);
    return 0;
}

/*---------------------------------------------------------------------------*/ 
void lua_tinker::push_meta(lua_State *L, const char* name)
{
    lua_getglobal(L, name);
}

/*---------------------------------------------------------------------------*/ 
int lua_tinker::is(lua_State *L)
{
#   if (defined(BIBIM_DEBUG))
        const int initialTop = lua_gettop(L);
#   endif

    luaL_checkstring(L, 2);

    const char* testName = lua_tostring(L, 2);

    lua_getmetatable(L, 1);

    for (int i = 0; ; i++)
    {
        if (lua_istable(L, -1) == false)
        {
            lua_pop(L, i + 1); // __parent(s) + initial metatable
            BBAssertDebug(initialTop == lua_gettop(L));
            lua_pushboolean(L, 0);
            return 1;
        }
        else
        {
            lua_pushstring(L, "__name");
            lua_rawget(L, -2);

            const char* className = lua_tostring(L, -1);
            if (strcmp(testName, className) == 0)
            {
                lua_pop(L, i + 1 + 1); // __parent(s) + class name + initial metatable
                BBAssertDebug(initialTop == lua_gettop(L));
                lua_pushboolean(L, 1);
                return 1;
            }
        }

        lua_pop(L, 1); // class name
        lua_pushstring(L, "__parent");
        lua_rawget(L, -2);
    }
}

int lua_tinker::eq(lua_State *L)
{
    BBAssert(lua_type(L, 1) == lua_type(L, 2));

    const Bibim::SharedObject* a = read<Bibim::SharedObject*>(L, 1);
    const Bibim::SharedObject* b = read<Bibim::SharedObject*>(L, 2);
    lua_pushboolean(L, a == b);

    return 1;
}

/*---------------------------------------------------------------------------*/ 
/* table object on stack                                                     */ 
/*---------------------------------------------------------------------------*/ 
lua_tinker::table_obj::table_obj(lua_State* L, int index)
    :m_L(L)
    ,m_index(index)
    ,m_ref(0)
{
    m_pointer = lua_topointer(m_L, m_index);
}

lua_tinker::table_obj::~table_obj()
{
    if(validate())
    {
        lua_remove(m_L, m_index);
    }
}

void lua_tinker::table_obj::inc_ref()
{
    ++m_ref;
}

void lua_tinker::table_obj::dec_ref()
{
    if(--m_ref == 0)
        delete this;
}

bool lua_tinker::table_obj::validate()
{
    if(m_pointer != NULL)
    {
        if(m_pointer == lua_topointer(m_L, m_index))
        {
            return true;
        }
        else
        {
            int top = lua_gettop(m_L);

            for(int i=1; i<=top; ++i)
            {
                if(m_pointer == lua_topointer(m_L, i))
                {
                    m_index = i;
                    return true;
                }
            }

            m_pointer = NULL;
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool lua_tinker::table_obj::has(const char* name)
{
    if(validate())
    {
        lua_pushstring(m_L, name);
        lua_gettable(m_L, m_index);
        const bool result = !lua_isnil(m_L, -1);
        lua_pop(m_L, 1);
        return result;
    }
    else
        return false;
}

bool lua_tinker::table_obj::has(int index)
{
    if(validate())
    {
        lua_pushinteger(m_L, index);
        lua_gettable(m_L, m_index);
        const bool result = !lua_isnil(m_L, -1);
        lua_pop(m_L, 1);
        return result;
    }
    else
        return false;
}

int lua_tinker::table_obj::type(const char* name)
{
    if(validate())
    {
        lua_pushstring(m_L, name);
        lua_gettable(m_L, m_index);
        const int result = lua_type(m_L, -1);
        lua_pop(m_L, 1);
        return result;
    }
    else
        return LUA_TNIL;
}

int lua_tinker::table_obj::type(int index)
{
    if(validate())
    {
        lua_pushinteger(m_L, index);
        lua_gettable(m_L, m_index);
        const int result = lua_type(m_L, -1);
        lua_pop(m_L, 1);
        return result;
    }
    else
        return LUA_TNIL;
}

int lua_tinker::table_obj::len()
{
    if (validate())
        return static_cast<int>(lua_rawlen(m_L, m_index));
    else
        return 0;
}


/*---------------------------------------------------------------------------*/ 
/* Table Object Holder                                                       */ 
/*---------------------------------------------------------------------------*/ 
lua_tinker::table::table(lua_State* L)
{
    lua_newtable(L);

    m_obj = new table_obj(L, lua_gettop(L));

    m_obj->inc_ref();
}

lua_tinker::table::table(lua_State* L, const char* name)
{
    enum_stack(L);

    lua_getglobal(L, name);

    if(lua_istable(L, -1) == 0)
    {
        lua_pop(L, 1);

        lua_newtable(L);
        lua_pushvalue(L, -1);
        lua_setglobal(L, name);
    }

    m_obj = new table_obj(L, lua_gettop(L));
}

lua_tinker::table::table(lua_State* L, int index)
{
    if(index < 0)
    {
        index = lua_gettop(L) + index + 1;
    }

    m_obj = new table_obj(L, index);

    m_obj->inc_ref();
}

lua_tinker::table::table(const table& input)
{
    m_obj = input.m_obj;

    m_obj->inc_ref();
}

lua_tinker::table::~table()
{
    m_obj->dec_ref();
}

lua_tinker::table::enumerator lua_tinker::table::enumerate()
{
    if (m_obj->validate())
    {
        lua_pushnil(m_obj->m_L);
        lua_pushnil(m_obj->m_L);
        return enumerator(this);
    }
    else
        return enumerator(0);
}

lua_tinker::table::enumerator::enumerator(table* t)
    : m_table(t)
{
}

bool lua_tinker::table::enumerator::next()
{
    if (m_table == 0)
        return false;

    lua_State* L = m_table->m_obj->m_L;

    lua_pop(L, 1);

    return lua_next(L, m_table->m_obj->m_index) != 0;
}

int lua_tinker::table::enumerator::key_type() const
{
    return lua_type(m_table->m_obj->m_L, -2);
}

int lua_tinker::table::enumerator::value_type() const
{
    return lua_type(m_table->m_obj->m_L, -1);
}

/*---------------------------------------------------------------------------*/ 
