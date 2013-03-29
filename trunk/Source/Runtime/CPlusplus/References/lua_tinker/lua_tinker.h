// lua_tinker.h
//
// LuaTinker - Simple and light C++ wrapper for Lua.
//
// Copyright (c) 2005-2007 Kwon-il Lee (zupet@hitel.net)
// 
// please check Licence.txt file for licence and legal issues. 

#if !defined(_LUA_TINKER_H_)
#define _LUA_TINKER_H_

#include <new>
#include <Bibim/Color.h>
#include <Bibim/Point2.h>
#include <Bibim/Point3.h>
#include <Bibim/Point4.h>
#include <Bibim/Rect.h>
#include <Bibim/RectF.h>
#include <Bibim/SharedObject.h>
#include <Bibim/String.h>
#include <Bibim/Vector2.h>
#include <Bibim/Vector3.h>
#include <Bibim/Vector4.h>

namespace lua_tinker
{
    // init LuaTinker
    void    init(lua_State *L);

    void    init_s64(lua_State *L);
    void    init_u64(lua_State *L);

    // excution
    void    dofile(lua_State *L, const char *filename);
    void    dostring(lua_State *L, const char* buff);
    void    dostring(lua_State *L, const char* buff, const char* name);
    void    dobuffer(lua_State *L, const char* buff, size_t sz);
    void    dobuffer(lua_State *L, const char* buff, size_t sz, const char* name);

    // debug helpers
    void    enum_stack(lua_State *L);
    int     on_error(lua_State *L);
    void    print_error(lua_State *L, const char* fmt, ...);
    
    void push_meta(lua_State *L, const char* name);

    // dynamic type extention
    struct lua_value
    {
        virtual void to_lua(lua_State *L) = 0;
    };

    // type trait
    template<typename T> struct class_name;
    struct table;

    template<bool C, typename A, typename B> struct if_ {};
    template<typename A, typename B>        struct if_<true, A, B> { typedef A type; };
    template<typename A, typename B>        struct if_<false, A, B> { typedef B type; };

    template<typename A>
    struct is_ptr { static const bool value = false; };
    template<typename A>
    struct is_ptr<A*> { static const bool value = true; };

    template<typename A>
    struct is_ref { static const bool value = false; };
    template<typename A>
    struct is_ref<A&> { static const bool value = true; };

    template<typename A>
    struct remove_const { typedef A type; };
    template<typename A>
    struct remove_const<const A> { typedef A type; };

    template<typename A>
    struct base_type { typedef A type; };
    template<typename A>
    struct base_type<A*> { typedef A type; };
    template<typename A>
    struct base_type<A&> { typedef A type; };

    template<typename A>
    struct remove_ref { typedef A type; };
    template<typename A>
    struct remove_ref<A&> { typedef A type; };
    template<typename A>
    struct remove_ref<const A> { typedef A type; };
    template<typename A>
    struct remove_ref<const A&> { typedef A type; };

    template<typename A>
    struct class_type { typedef typename remove_const<typename base_type<A>::type>::type type; };
    
    /////////////////////////////////
    enum { no = 1, yes = 2 }; 
    typedef char (& no_type )[no]; 
    typedef char (& yes_type)[yes]; 

    struct int_conv_type { int_conv_type(int); }; 

    no_type int_conv_tester (...); 
    yes_type int_conv_tester (int_conv_type); 

    no_type vfnd_ptr_tester (const volatile char *); 
    no_type vfnd_ptr_tester (const volatile short *); 
    no_type vfnd_ptr_tester (const volatile int *); 
    no_type vfnd_ptr_tester (const volatile long *); 
    no_type vfnd_ptr_tester (const volatile double *); 
    no_type vfnd_ptr_tester (const volatile float *); 
    no_type vfnd_ptr_tester (const volatile bool *); 
    yes_type vfnd_ptr_tester (const volatile void *); 

    template <typename T> T* add_ptr(T&); 

    template <bool C> struct bool_to_yesno { typedef no_type type; }; 
    template <> struct bool_to_yesno<true> { typedef yes_type type; }; 

    template <typename T> 
    struct is_enum 
    { 
        static T arg; 
        static const bool value = ( (sizeof(int_conv_tester(arg)) == sizeof(yes_type)) && (sizeof(vfnd_ptr_tester(add_ptr(arg))) == sizeof(yes_type)) ); 
    }; 
    /////////////////////////////////

    // from lua
    template<typename T>
    struct void2val { static T invoke(void* input){ return *(T*)input; } };
    template<typename T>
    struct void2ptr { static T* invoke(void* input){ return (T*)input; } };
    template<typename T>
    struct void2ref { static T& invoke(void* input){ return *(T*)input; } };

	template<typename T>  
	struct void2type
	{
		static T invoke(void* ptr)
		{
			return	if_<is_ptr<T>::value
						,void2ptr<typename base_type<T>::type>
						,typename if_<is_ref<T>::value
							,void2ref<typename base_type<T>::type>
							,void2val<typename base_type<T>::type>
						>::type
					>::type::invoke(ptr);
		}
	};

    struct user
    {
        user(void* p) : m_p(p) {}
        virtual ~user() {}
        void* m_p;
    };

	template<typename T>  
	struct user2type { static T invoke(lua_State *L, int index) { return void2type<T>::invoke(lua_touserdata(L, index)); } };

	template<typename T>
	struct lua2enum { static T invoke(lua_State *L, int index) { return (T)(int)lua_tonumber(L, index); } };

    template<typename T>
    struct lua2object
    { 
        static T invoke(lua_State *L, int index) 
        { 
            if(lua_isnil(L,index))
                return void2type<T>::invoke(0); 
            else if(!lua_isuserdata(L,index))
            {
                lua_pushstring(L, "no class at first argument. (forgot ':' expression ?)");
                lua_error(L);
            }
            return void2type<T>::invoke(user2type<user*>::invoke(L,index)->m_p);
        } 
    };

    template<typename T>
    T lua2type(lua_State *L, int index)
    {
        return    if_<is_enum<T>::value
                    ,lua2enum<T>
                    ,lua2object<T> 
                >::type::invoke(L, index);
    }

    template<typename T>
    struct val2user : user
    {
        val2user() : user(new T)
        {
            ((Bibim::SharedObject*)m_p)->IncreaseReferenceCount();
        }

        template<typename T1>
        val2user(T1 t1) : user(new T(t1))
        {
            ((Bibim::SharedObject*)m_p)->IncreaseReferenceCount();
        }

        template<typename T1, typename T2>
        val2user(T1 t1, T2 t2) : user(new T(t1, t2))
        {
            ((Bibim::SharedObject*)m_p)->IncreaseReferenceCount();
        }

        template<typename T1, typename T2, typename T3>
        val2user(T1 t1, T2 t2, T3 t3) : user(new T(t1, t2, t3))
        {
            ((Bibim::SharedObject*)m_p)->IncreaseReferenceCount();
        }

        ~val2user()
        {
            ((Bibim::SharedObject*)m_p)->DecreaseReferenceCount();
        }
    };

    template<typename T>
    struct ptr2user : user
    {
        ptr2user(T* t) : user((void*)t) {}
    };

    template<typename T>
    struct ref2user : user
    {
        ref2user(T& t) : user(&t) {}
    };

    // to lua
    template<typename T>
    struct val2lua { static void invoke(lua_State *L, T& input){ new(lua_newuserdata(L, sizeof(val2user<T>))) val2user<T>(input); } };
    template<typename T>
    struct ptr2lua { static void invoke(lua_State *L, T* input){ if(input) new(lua_newuserdata(L, sizeof(ptr2user<T>))) ptr2user<T>(input); else lua_pushnil(L); } };
    template<typename T>
    struct ref2lua { static void invoke(lua_State *L, T& input){ new(lua_newuserdata(L, sizeof(ref2user<T>))) ref2user<T>(input); } };

    template<typename T>
    struct enum2lua { static void invoke(lua_State *L, T val) { lua_pushnumber(L, (int)val); } };

    template<typename T>
    struct object2lua 
    { 
        static void invoke(lua_State *L, T val) 
        { 
			if_<is_ptr<T>::value
				,ptr2lua<typename base_type<T>::type>
				,typename if_<is_ref<T>::value
					,ref2lua<typename base_type<T>::type>
					,val2lua<typename base_type<T>::type>
				>::type
			>::type::invoke(L, val);

            const char* name = class_name<typename class_type<T>::type>::name();
			push_meta(L, name);
			lua_setmetatable(L, -2);
        } 
    };

    template<typename T>
    void type2lua(lua_State *L, T val)
    {
        if_<is_enum<T>::value
            ,enum2lua<T>
            ,object2lua<T>
        >::type::invoke(L, val);
    }

    // get value from cclosure
    template<typename T>  
    T upvalue_(lua_State *L)
    {
        return user2type<T>::invoke(L, lua_upvalueindex(1));
    }

    // read a value from lua stack 
    template<typename T>
    T read(lua_State *L, int index)                { return lua2type<T>(L, index); }

    template<>    char*                read(lua_State *L, int index);
    template<>    const char*            read(lua_State *L, int index);
    template<>    char                read(lua_State *L, int index);
    template<>    unsigned char        read(lua_State *L, int index);
    template<>    short                read(lua_State *L, int index);
    template<>    unsigned short        read(lua_State *L, int index);
    template<>    long                read(lua_State *L, int index);
    template<>    unsigned long        read(lua_State *L, int index);
    template<>    int                    read(lua_State *L, int index);
    template<>    unsigned int        read(lua_State *L, int index);
    template<>    float                read(lua_State *L, int index);
    template<>    double                read(lua_State *L, int index);
    template<>    bool                read(lua_State *L, int index);
    template<>    void                read(lua_State *L, int index);
    template<>    long long                read(lua_State *L, int index);
    template<>    unsigned long long    read(lua_State *L, int index);
    template<>    table                read(lua_State *L, int index);
    template<>  Bibim::String       read(lua_State *L, int index);

    // push a value to lua stack 
    template<typename T>  
    void push(lua_State *L, T ret)                    { type2lua<T>(L, ret); }
    
    template<>    void push(lua_State *L, char ret);
    template<>    void push(lua_State *L, unsigned char ret);
    template<>    void push(lua_State *L, short ret);
    template<>    void push(lua_State *L, unsigned short ret);
    template<>    void push(lua_State *L, long ret);
    template<>    void push(lua_State *L, unsigned long ret);
    template<>    void push(lua_State *L, int ret);
    template<>    void push(lua_State *L, unsigned int ret);
    template<>    void push(lua_State *L, float ret);
    template<>    void push(lua_State *L, double ret);
    template<>    void push(lua_State *L, char* ret);
    template<>    void push(lua_State *L, const char* ret);
    template<>    void push(lua_State *L, bool ret);
    template<>    void push(lua_State *L, lua_value* ret);
    template<>    void push(lua_State *L, long long ret);
    template<>    void push(lua_State *L, unsigned long long ret);
    template<>    void push(lua_State *L, table ret);
    template<>    void push(lua_State *L, const Bibim::String& ret);

    template<typename T>  
    int push_for_return(lua_State *L, T ret)                    { type2lua<T>(L, ret); return 1; }
    
    template<>    int push_for_return(lua_State *L, char ret);
    template<>    int push_for_return(lua_State *L, unsigned char ret);
    template<>    int push_for_return(lua_State *L, short ret);
    template<>    int push_for_return(lua_State *L, unsigned short ret);
    template<>    int push_for_return(lua_State *L, long ret);
    template<>    int push_for_return(lua_State *L, unsigned long ret);
    template<>    int push_for_return(lua_State *L, int ret);
    template<>    int push_for_return(lua_State *L, unsigned int ret);
    template<>    int push_for_return(lua_State *L, float ret);
    template<>    int push_for_return(lua_State *L, double ret);
    template<>    int push_for_return(lua_State *L, char* ret);
    template<>    int push_for_return(lua_State *L, const char* ret);
    template<>    int push_for_return(lua_State *L, bool ret);
    template<>    int push_for_return(lua_State *L, lua_value* ret);
    template<>    int push_for_return(lua_State *L, long long ret);
    template<>    int push_for_return(lua_State *L, unsigned long long ret);
    template<>    int push_for_return(lua_State *L, table ret);

    template<>  int push_for_return(lua_State *L, Bibim::Color ret);
    template<>  int push_for_return(lua_State *L, Bibim::Point2 ret);
    template<>  int push_for_return(lua_State *L, Bibim::Point3 ret);
    template<>  int push_for_return(lua_State *L, Bibim::Point4 ret);
    template<>  int push_for_return(lua_State *L, Bibim::Rect ret);
    template<>  int push_for_return(lua_State *L, Bibim::RectF ret);
    template<>  int push_for_return(lua_State *L, Bibim::Vector2 ret);
    template<>  int push_for_return(lua_State *L, Bibim::Vector3 ret);
    template<>  int push_for_return(lua_State *L, Bibim::Vector4 ret);
    template<>  int push_for_return(lua_State *L, const Bibim::String& ret);

    // pop a value from lua stack
    template<typename T>  
    T pop(lua_State *L) { T t = read<T>(L, -1); lua_pop(L, 1); return t; }
    
    template<>    void    pop(lua_State *L);
    template<>    table    pop(lua_State *L);

    // functor
    template<typename RVal, typename T1=void, typename T2=void, typename T3=void, typename T4=void, typename T5=void>
    struct functor
    {
        static int invoke(lua_State *L) { return push_for_return<RVal>(L,upvalue_<RVal(*)(T1,T2,T3,T4,T5)>(L)(read<typename remove_ref<T1>::type>(L,1),read<typename remove_ref<T2>::type>(L,2),read<typename remove_ref<T3>::type>(L,3),read<typename remove_ref<T4>::type>(L,4),read<typename remove_ref<T5>::type>(L,5))); }
    };

    template<typename RVal, typename T1, typename T2, typename T3, typename T4>
    struct functor<RVal, T1,T2,T3,T4> 
    {
        static int invoke(lua_State *L) { return push_for_return<RVal>(L,upvalue_<RVal(*)(T1,T2,T3,T4)>(L)(read<typename remove_ref<T1>::type>(L,1),read<typename remove_ref<T2>::type>(L,2),read<typename remove_ref<T3>::type>(L,3),read<typename remove_ref<T4>::type>(L,4))); }
    };

    template<typename RVal, typename T1, typename T2, typename T3>
    struct functor<RVal, T1,T2,T3> 
    {
        static int invoke(lua_State *L) { return push_for_return<RVal>(L,upvalue_<RVal(*)(T1,T2,T3)>(L)(read<typename remove_ref<T1>::type>(L,1),read<typename remove_ref<T2>::type>(L,2),read<typename remove_ref<T3>::type>(L,3))); }
    };

    template<typename RVal, typename T1, typename T2>
    struct functor<RVal, T1,T2> 
    {
        static int invoke(lua_State *L) { return push_for_return<RVal>(L,upvalue_<RVal(*)(T1,T2)>(L)(read<typename remove_ref<T1>::type>(L,1),read<typename remove_ref<T2>::type>(L,2))); }
    };

    template<typename RVal, typename T1>
    struct functor<RVal, T1> 
    {
        static int invoke(lua_State *L) { return push_for_return<RVal>(L,upvalue_<RVal(*)(T1)>(L)(read<typename remove_ref<T1>::type>(L,1))); }
    };

    template<typename RVal>
    struct functor<RVal>
    {
        static int invoke(lua_State *L) { return push_for_return<RVal>(L,upvalue_<RVal(*)()>(L)()); }
    };

	// functor (without return value)
	template<typename T1, typename T2, typename T3, typename T4, typename T5>
	struct functor<void, T1, T2, T3, T4, T5>
	{
		static int invoke(lua_State *L) { upvalue_<void(*)(T1,T2,T3,T4,T5)>(L)(read<typename remove_ref<T1>::type>(L,1),read<typename remove_ref<T2>::type>(L,2),read<typename remove_ref<T3>::type>(L,3),read<typename remove_ref<T4>::type>(L,4),read<typename remove_ref<T5>::type>(L,5)); return 0; }
	};

	template<typename T1, typename T2, typename T3, typename T4>
	struct functor<void, T1, T2, T3, T4>
	{
		static int invoke(lua_State *L) { upvalue_<void(*)(T1,T2,T3,T4)>(L)(read<typename remove_ref<T1>::type>(L,1),read<typename remove_ref<T2>::type>(L,2),read<typename remove_ref<T3>::type>(L,3),read<typename remove_ref<T4>::type>(L,4)); return 0; }
	};

	template<typename T1, typename T2, typename T3>
	struct functor<void, T1, T2, T3>
	{
		static int invoke(lua_State *L) { upvalue_<void(*)(T1,T2,T3)>(L)(read<typename remove_ref<T1>::type>(L,1),read<typename remove_ref<T2>::type>(L,2),read<typename remove_ref<T3>::type>(L,3)); return 0; }
	};

	template<typename T1, typename T2>
	struct functor<void, T1, T2>
	{
		static int invoke(lua_State *L) { upvalue_<void(*)(T1,T2)>(L)(read<typename remove_ref<T1>::type>(L,1),read<typename remove_ref<T2>::type>(L,2)); return 0; }
	};

	template<typename T1>
	struct functor<void, T1>
	{
		static int invoke(lua_State *L) { upvalue_<void(*)(T1)>(L)(read<typename remove_ref<T1>::type>(L,1)); return 0; }
	};

	template<>
	struct functor<void>
	{
		static int invoke(lua_State *L) { upvalue_<void(*)()>(L)(); return 0; }
	};

	// functor (non-managed)
	template<typename T1>
	struct functor<int, lua_State*, T1>
	{
		static int invoke(lua_State *L) { return upvalue_<int(*)(lua_State*,T1)>(L)(L,read<typename remove_ref<T1>::type>(L,1)); }
	};

	template<>
	struct functor<int,lua_State*>
	{
		static int invoke(lua_State *L) { return upvalue_<int(*)(lua_State*)>(L)(L); }
	};

    // push_functor
    template<typename RVal> 
    void push_functor(lua_State *L, RVal (*func)())
    {
        lua_pushcclosure(L, functor<RVal>::invoke, 1);
    }

    template<typename RVal, typename T1> 
    void push_functor(lua_State *L, RVal (*func)(T1))
    { 
        lua_pushcclosure(L, functor<RVal,T1>::invoke, 1);
    }

    template<typename RVal, typename T1, typename T2> 
    void push_functor(lua_State *L, RVal (*func)(T1,T2))
    { 
        lua_pushcclosure(L, functor<RVal,T1,T2>::invoke, 1);
    }

    template<typename RVal, typename T1, typename T2, typename T3> 
    void push_functor(lua_State *L, RVal (*func)(T1,T2,T3))
    { 
        lua_pushcclosure(L, functor<RVal,T1,T2,T3>::invoke, 1);
    }

    template<typename RVal, typename T1, typename T2, typename T3, typename T4> 
    void push_functor(lua_State *L, RVal (*func)(T1,T2,T3,T4))
    { 
        lua_pushcclosure(L, functor<RVal,T1,T2,T3,T4>::invoke, 1);
    }

    template<typename RVal, typename T1, typename T2, typename T3, typename T4, typename T5> 
    void push_functor(lua_State *L, RVal (*func)(T1,T2,T3,T4,T5))
    { 
        lua_pushcclosure(L, functor<RVal,T1,T2,T3,T4,T5>::invoke, 1);
    }

    // member variable
    struct var_base
    {
        virtual void get(lua_State *L) = 0;
        virtual void set(lua_State *L) = 0;
    };

    template<typename T, typename V>
    struct mem_var : var_base
    {
        V T::*_var;
        mem_var(V T::*val) : _var(val) {}
        void get(lua_State *L)    { push(L, read<T*>(L,1)->*(_var));        }
        void set(lua_State *L)    { read<T*>(L,1)->*(_var) = read<V>(L, 3);    }
    };

    // member function
    template<typename RVal, typename T, typename T1=void, typename T2=void, typename T3=void, typename T4=void, typename T5=void>
    struct mem_functor
    {
        static int invoke(lua_State *L) { return push_for_return<RVal>(L,(read<T*>(L,1)->*upvalue_<RVal(T::*)(T1,T2,T3,T4,T5)>(L))(read<typename remove_ref<T1>::type>(L,2),read<typename remove_ref<T2>::type>(L,3),read<typename remove_ref<T3>::type>(L,4),read<typename remove_ref<T4>::type>(L,5),read<typename remove_ref<T5>::type>(L,6))); }
    };

    template<typename RVal, typename T, typename T1, typename T2, typename T3, typename T4> 
    struct mem_functor<RVal,T,T1,T2,T3,T4>
    {
        static int invoke(lua_State *L) { return push_for_return<RVal>(L,(read<T*>(L,1)->*upvalue_<RVal(T::*)(T1,T2,T3,T4)>(L))(read<typename remove_ref<T1>::type>(L,2),read<typename remove_ref<T2>::type>(L,3),read<typename remove_ref<T3>::type>(L,4),read<typename remove_ref<T4>::type>(L,5))); }
    };

    template<typename RVal, typename T, typename T1, typename T2, typename T3> 
    struct mem_functor<RVal,T,T1,T2,T3>
    {
        static int invoke(lua_State *L) { return push_for_return<RVal>(L,(read<T*>(L,1)->*upvalue_<RVal(T::*)(T1,T2,T3)>(L))(read<typename remove_ref<T1>::type>(L,2),read<typename remove_ref<T2>::type>(L,3),read<typename remove_ref<T3>::type>(L,4))); }
    };

    template<typename RVal, typename T, typename T1, typename T2> 
    struct mem_functor<RVal,T,T1, T2>
    {
        static int invoke(lua_State *L) { return push_for_return<RVal>(L,(read<T*>(L,1)->*upvalue_<RVal(T::*)(T1,T2)>(L))(read<typename remove_ref<T1>::type>(L,2),read<typename remove_ref<T2>::type>(L,3))); }
    };

    template<typename RVal, typename T, typename T1> 
    struct mem_functor<RVal,T,T1>
    {
        static int invoke(lua_State *L) { return push_for_return<RVal>(L,(read<T*>(L,1)->*upvalue_<RVal(T::*)(T1)>(L))(read<typename remove_ref<T1>::type>(L,2))); }
    };

    template<typename RVal, typename T> 
    struct mem_functor<RVal,T>
    {
        static int invoke(lua_State *L) { return push_for_return<RVal>(L,(read<T*>(L,1)->*upvalue_<RVal(T::*)()>(L))()); }
    };


	// class member functor (without return value)
	template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5>
	struct mem_functor<void,T,T1,T2,T3,T4,T5>
	{
		static int invoke(lua_State *L)  { (read<T*>(L,1)->*upvalue_<void(T::*)(T1,T2,T3,T4,T5)>(L))(read<typename remove_ref<T1>::type>(L,2),read<typename remove_ref<T2>::type>(L,3),read<typename remove_ref<T3>::type>(L,4),read<typename remove_ref<T4>::type>(L,5),read<typename remove_ref<T5>::type>(L,6)); lua_pushvalue(L, 1); return 1; }
	};

	template<typename T, typename T1, typename T2, typename T3, typename T4>
	struct mem_functor<void,T,T1,T2,T3,T4>
	{
		static int invoke(lua_State *L)  { (read<T*>(L,1)->*upvalue_<void(T::*)(T1,T2,T3,T4)>(L))(read<typename remove_ref<T1>::type>(L,2),read<typename remove_ref<T2>::type>(L,3),read<typename remove_ref<T3>::type>(L,4),read<typename remove_ref<T4>::type>(L,5)); lua_pushvalue(L, 1); return 1; }
	};

	template<typename T, typename T1, typename T2, typename T3>
	struct mem_functor<void,T,T1,T2,T3>
	{
		static int invoke(lua_State *L)  { (read<T*>(L,1)->*upvalue_<void(T::*)(T1,T2,T3)>(L))(read<typename remove_ref<T1>::type>(L,2),read<typename remove_ref<T2>::type>(L,3),read<typename remove_ref<T3>::type>(L,4)); lua_pushvalue(L, 1); return 1; }
	};

	template<typename T, typename T1, typename T2>
	struct mem_functor<void,T,T1,T2>
	{
		static int invoke(lua_State *L)  { (read<T*>(L,1)->*upvalue_<void(T::*)(T1,T2)>(L))(read<typename remove_ref<T1>::type>(L,2),read<typename remove_ref<T2>::type>(L,3)); lua_pushvalue(L, 1); return 1; }
	};

	template<typename T, typename T1>
	struct mem_functor<void,T,T1>
	{
		static int invoke(lua_State *L)  { (read<T*>(L,1)->*upvalue_<void(T::*)(T1)>(L))(read<typename remove_ref<T1>::type>(L,2)); lua_pushvalue(L, 1); return 1; }
	};

	template<typename T>
	struct mem_functor<void,T>
	{
		static int invoke(lua_State *L)  { (read<T*>(L,1)->*upvalue_<void(T::*)()>(L))(); lua_pushvalue(L, 1); return 1; }
	};

	// class member functor (non-managed)
	template<typename T, typename T1> 
	struct mem_functor<int,T,lua_State*,T1>
	{
		static int invoke(lua_State *L) { return (read<T*>(L,1)->*upvalue_<int(T::*)(lua_State*,T1)>(L))(L, read<typename remove_ref<T1>::type>(L,2)); }
	};

	template<typename T> 
	struct mem_functor<int,T,lua_State*>
	{
		static int invoke(lua_State *L) { return (read<T*>(L,1)->*upvalue_<int(T::*)(lua_State*)>(L))(L); }
	};

    
    // push_functor
    template<typename RVal, typename T>
    void push_functor(lua_State *L, RVal (T::*func)()) 
    { 
        lua_pushcclosure(L, mem_functor<RVal,T>::invoke, 1); 
    }

    template<typename RVal, typename T>
    void push_functor(lua_State *L, RVal (T::*func)() const) 
    { 
        lua_pushcclosure(L, mem_functor<RVal,T>::invoke, 1); 
    }

    template<typename RVal, typename T, typename T1>
    void push_functor(lua_State *L, RVal (T::*func)(T1)) 
    { 
        lua_pushcclosure(L, mem_functor<RVal,T,T1>::invoke, 1); 
    }

    template<typename RVal, typename T, typename T1>
    void push_functor(lua_State *L, RVal (T::*func)(T1) const) 
    { 
        lua_pushcclosure(L, mem_functor<RVal,T,T1>::invoke, 1); 
    }

    template<typename RVal, typename T, typename T1, typename T2>
    void push_functor(lua_State *L, RVal (T::*func)(T1,T2)) 
    { 
        lua_pushcclosure(L, mem_functor<RVal,T,T1,T2>::invoke, 1); 
    }

    template<typename RVal, typename T, typename T1, typename T2>
    void push_functor(lua_State *L, RVal (T::*func)(T1,T2) const) 
    { 
        lua_pushcclosure(L, mem_functor<RVal,T,T1,T2>::invoke, 1); 
    }

    template<typename RVal, typename T, typename T1, typename T2, typename T3>
    void push_functor(lua_State *L, RVal (T::*func)(T1,T2,T3)) 
    { 
        lua_pushcclosure(L, mem_functor<RVal,T,T1,T2,T3>::invoke, 1); 
    }

    template<typename RVal, typename T, typename T1, typename T2, typename T3>
    void push_functor(lua_State *L, RVal (T::*func)(T1,T2,T3) const) 
    { 
        lua_pushcclosure(L, mem_functor<RVal,T,T1,T2,T3>::invoke, 1); 
    }

    template<typename RVal, typename T, typename T1, typename T2, typename T3, typename T4>
    void push_functor(lua_State *L, RVal (T::*func)(T1,T2,T3,T4)) 
    { 
        lua_pushcclosure(L, mem_functor<RVal,T,T1,T2,T3,T4>::invoke, 1); 
    }

    template<typename RVal, typename T, typename T1, typename T2, typename T3, typename T4>
    void push_functor(lua_State *L, RVal (T::*func)(T1,T2,T3,T4) const) 
    { 
        lua_pushcclosure(L, mem_functor<RVal,T,T1,T2,T3,T4>::invoke, 1); 
    }

    template<typename RVal, typename T, typename T1, typename T2, typename T3, typename T4, typename T5>
    void push_functor(lua_State *L, RVal (T::*func)(T1,T2,T3,T4,T5)) 
    { 
        lua_pushcclosure(L, mem_functor<RVal,T,T1,T2,T3,T4,T5>::invoke, 1); 
    }

    template<typename RVal, typename T, typename T1, typename T2, typename T3, typename T4, typename T5>
    void push_functor(lua_State *L, RVal (T::*func)(T1,T2,T3,T4,T5) const) 
    { 
        lua_pushcclosure(L, mem_functor<RVal,T,T1,T2,T3,T4,T5>::invoke, 1); 
    }

    // constructor
	template<typename T, typename T1, typename T2, typename T3, typename T4, typename T5>
	int constructor(lua_State *L) 
	{ 
		new(lua_newuserdata(L, sizeof(val2user<T>))) val2user<T>(read<typename remove_ref<T1>::type>(L,2),read<typename remove_ref<T2>::type>(L,3),read<typename remove_ref<T3>::type>(L,4),read<typename remove_ref<T4>::type>(L,5),read<typename remove_ref<T5>::type>(L,6));
		push_meta(L, class_name<typename class_type<T>::type>::name());
		lua_setmetatable(L, -2);

		return 1; 
	}

	template<typename T, typename T1, typename T2, typename T3, typename T4>
	int constructor(lua_State *L) 
	{ 
		new(lua_newuserdata(L, sizeof(val2user<T>))) val2user<T>(read<typename remove_ref<T1>::type>(L,2),read<typename remove_ref<T2>::type>(L,3),read<typename remove_ref<T3>::type>(L,4),read<typename remove_ref<T4>::type>(L,5));
		push_meta(L, class_name<typename class_type<T>::type>::name());
		lua_setmetatable(L, -2);

		return 1; 
	}

	template<typename T, typename T1, typename T2, typename T3>
	int constructor(lua_State *L) 
	{ 
		new(lua_newuserdata(L, sizeof(val2user<T>))) val2user<T>(read<typename remove_ref<T1>::type>(L,2),read<typename remove_ref<T2>::type>(L,3),read<typename remove_ref<T3>::type>(L,4));
		push_meta(L, class_name<typename class_type<T>::type>::name());
		lua_setmetatable(L, -2);

		return 1; 
	}

	template<typename T, typename T1, typename T2>
	int constructor(lua_State *L) 
	{ 
		new(lua_newuserdata(L, sizeof(val2user<T>))) val2user<T>(read<typename remove_ref<T1>::type>(L,2),read<typename remove_ref<T2>::type>(L,3));
		push_meta(L, class_name<typename class_type<T>::type>::name());
		lua_setmetatable(L, -2);

		return 1; 
	}

	template<typename T, typename T1>
	int constructor(lua_State *L) 
	{ 
		new(lua_newuserdata(L, sizeof(val2user<T>))) val2user<T>(read<typename remove_ref<T1>::type>(L,2));
		push_meta(L, class_name<typename class_type<T>::type>::name());
		lua_setmetatable(L, -2);

		return 1; 
	}

	template<typename T>
	int constructor(lua_State *L) 
	{ 
		new(lua_newuserdata(L, sizeof(val2user<T>))) val2user<T>();
		push_meta(L, class_name<typename class_type<T>::type>::name());
		lua_setmetatable(L, -2);

		return 1; 
	}

    // destroyer
    template<typename T>
    int destroyer(lua_State *L) 
    { 
        ((user*)lua_touserdata(L, 1))->~user();
        return 0;
    }

    // global function
    template<typename F> 
    void def(lua_State* L, const char* name, F func)
    { 
        lua_pushstring(L, name);
        lua_pushlightuserdata(L, (void*)func);
        push_functor(L, func);
        lua_settable(L, LUA_GLOBALSINDEX);
    }

    // global variable
    template<typename T>
    void set(lua_State* L, const char* name, T object)
    {
        lua_pushstring(L, name);
        push(L, object);
        lua_settable(L, LUA_GLOBALSINDEX);
    }

    template<typename T>
    T get(lua_State* L, const char* name)
    {
        lua_pushstring(L, name);
        lua_gettable(L, LUA_GLOBALSINDEX);
        return pop<T>(L);
    }

    template<typename T>
    void decl(lua_State* L, const char* name, T object)
    {
        set(L, name, object);
    }

    // call
    template<typename RVal>
    RVal call(lua_State* L, const char* name)
    {
        lua_pushcclosure(L, on_error, 0);
        int errfunc = lua_gettop(L);

        lua_pushstring(L, name);
        lua_gettable(L, LUA_GLOBALSINDEX);
        if(lua_isfunction(L,-1))
        {
            if(lua_pcall(L, 0, 1, errfunc) != 0)
            {
                lua_pop(L, 1);
            }
        }
        else
        {
            print_error(L, "lua_tinker::call() attempt to call global `%s' (not a function)", name);
        }

        lua_remove(L, -2);
        return pop<RVal>(L);
    }

    template<typename RVal, typename T1>
    RVal call(lua_State* L, const char* name, T1 arg)
    {
        lua_pushcclosure(L, on_error, 0);
        int errfunc = lua_gettop(L);

        lua_pushstring(L, name);
        lua_gettable(L, LUA_GLOBALSINDEX);
        if(lua_isfunction(L,-1))
        {
            push(L, arg);
            if(lua_pcall(L, 1, 1, errfunc) != 0)
            {
                lua_pop(L, 1);
            }
        }
        else
        {
            print_error(L, "lua_tinker::call() attempt to call global `%s' (not a function)", name);
        }

        lua_remove(L, -2);
        return pop<RVal>(L);
    }

    template<typename RVal, typename T1, typename T2>
    RVal call(lua_State* L, const char* name, T1 arg1, T2 arg2)
    {
        lua_pushcclosure(L, on_error, 0);
        int errfunc = lua_gettop(L);

        lua_pushstring(L, name);
        lua_gettable(L, LUA_GLOBALSINDEX);
        if(lua_isfunction(L,-1))
        {
            push(L, arg1);
            push(L, arg2);
            if(lua_pcall(L, 2, 1, errfunc) != 0)
            {
                lua_pop(L, 1);
            }
        }
        else
        {
            print_error(L, "lua_tinker::call() attempt to call global `%s' (not a function)", name);
        }

        lua_remove(L, -2);
        return pop<RVal>(L);
    }

    template<typename RVal, typename T1, typename T2, typename T3>
    RVal call(lua_State* L, const char* name, T1 arg1, T2 arg2, T3 arg3)
    {
        lua_pushcclosure(L, on_error, 0);
        int errfunc = lua_gettop(L);

        lua_pushstring(L, name);
        lua_gettable(L, LUA_GLOBALSINDEX);
        if(lua_isfunction(L,-1))
        {
            push(L, arg1);
            push(L, arg2);
            push(L, arg3);
            if(lua_pcall(L, 3, 1, errfunc) != 0)
            {
                lua_pop(L, 1);
            }
        }
        else
        {
            print_error(L, "lua_tinker::call() attempt to call global `%s' (not a function)", name);
        }

        lua_remove(L, -2);
        return pop<RVal>(L);
    }

    // class helper
    int meta_get(lua_State *L);
    int meta_set(lua_State *L);
    int is(lua_State *L);
    int eq(lua_State *L);

    // class init
    template<typename T>
    void class_add(lua_State* L, const char* name) 
    { 
        class_name<T>::name(name);

        lua_pushstring(L, name);
        lua_newtable(L);

        lua_pushstring(L, "__name");
        lua_pushstring(L, name);
        lua_rawset(L, -3);

        lua_pushstring(L, "__index");
        lua_pushcclosure(L, meta_get, 0);
        lua_rawset(L, -3);

        lua_pushstring(L, "__newindex");
        lua_pushcclosure(L, meta_set, 0);
        lua_rawset(L, -3);

        lua_pushstring(L, "__gc");
        lua_pushcclosure(L, destroyer<T>, 0);
        lua_rawset(L, -3);

        lua_pushstring(L, "__is__");
        lua_pushcclosure(L, is, 0);
        lua_rawset(L, -3);

        lua_pushstring(L, "__eq");
        lua_pushcclosure(L, eq, 0);
        lua_rawset(L, -3);

        lua_settable(L, LUA_GLOBALSINDEX);
    }

    // Tinker Class Inheritence
    template<typename T, typename P>
    void class_inh(lua_State* L)
    {
        push_meta(L, class_name<T>::name());
        if(lua_istable(L, -1))
        {
            lua_pushstring(L, "__parent");
            push_meta(L, class_name<P>::name());
            lua_rawset(L, -3);
        }
        lua_pop(L, 1);
    }

    // Tinker Class Constructor
	template<typename T, typename F>
	void class_con(lua_State* L,F func)
	{
		push_meta(L, class_name<T>::name());
		if(lua_istable(L, -1))
		{
			lua_newtable(L);
			lua_pushstring(L, "__call");
			lua_pushcclosure(L, func, 0);
			lua_rawset(L, -3);
			lua_setmetatable(L, -2);
		}
		lua_pop(L, 1);
	}

    // Tinker Class Functions
    template<typename T, typename F>
    void class_def(lua_State* L, const char* name, F func) 
    { 
        push_meta(L, class_name<T>::name());
        if(lua_istable(L, -1))
        {
            lua_pushstring(L, name);
            new(lua_newuserdata(L,sizeof(F))) F(func);
            push_functor(L, func);
            lua_rawset(L, -3);
        }
        lua_pop(L, 1);
    }

    // Tinker Class Variables
    template<typename T, typename BASE, typename VAR>
    void class_mem(lua_State* L, const char* name, VAR BASE::*val) 
    { 
        push_meta(L, class_name<T>::name());
        if(lua_istable(L, -1))
        {
            lua_pushstring(L, name);
            new(lua_newuserdata(L,sizeof(mem_var<BASE,VAR>))) mem_var<BASE,VAR>(val);
            lua_rawset(L, -3);
        }
        lua_pop(L, 1);
    }

    template<typename T>
    struct class_name
    {
        // global name
        static const char* name(const char* name = NULL)
        {
            static char temp[256] = "";
            if(name) strcpy(temp, name);
            return temp;
        }
    };

    // Table Object on Stack
    struct table_obj
    {
        table_obj(lua_State* L, int index);
        ~table_obj();

        void inc_ref();
        void dec_ref();

        bool validate();

        template<typename T>
        void set(const char* name, T object)
        {
            if(validate())
            {
                lua_pushstring(m_L, name);
                push(m_L, object);
                lua_settable(m_L, m_index);
            }
        }

        template<typename T>
        void set(int index, T object)
        {
            if(validate())
            {
                lua_pushinteger(m_L, index);
                push(m_L, object);
                lua_settable(m_L, m_index);
            }
        }

        template<typename T>
        T get(const char* name)
        {
            if(validate())
            {
                lua_pushstring(m_L, name);
                lua_gettable(m_L, m_index);
            }
            else
            {
                lua_pushnil(m_L);
            }

            return pop<T>(m_L);
        }

        template<typename T>
        T get(int index)
        {
            if(validate())
            {
                lua_pushinteger(m_L, index);
                lua_gettable(m_L, m_index);
            }
            else
            {
                lua_pushnil(m_L);
            }

            return pop<T>(m_L);
        }

        bool has(const char* name);
        bool has(int index);

        int type(const char* name);
        int type(int index);

        int len();

        lua_State*        m_L;
        int                m_index;
        const void*        m_pointer;
        int                m_ref;
    };

    // Table Object Holder
    struct table
    {
        struct enumerator
        {
            enumerator(table* t);

            bool next();

            int key_type() const;
            int value_type() const;

            template<typename T>
            T key()
            {
                return read<T>(m_table->m_obj->m_L, -2);
            }
            
            template<typename T>
            T value()
            {
                return read<T>(m_table->m_obj->m_L, -1);
            }

            table* m_table;
        };

        table(lua_State* L);
        table(lua_State* L, int index);
        table(lua_State* L, const char* name);
        table(const table& input);
        ~table();

        template<typename T>
        void set(const char* name, T object)
        {
            m_obj->set(name, object);
        }

        template<typename T>
        void set(int index, T object)
        {
            m_obj->set(index, object);
        }

        template<typename T>
        T get(const char* name)
        {
            return m_obj->get<T>(name);
        }

        template<typename T>
        T get(int index)
        {
            return m_obj->get<T>(index);
        }

        bool has(const char* name)
        {
            return m_obj->has(name);
        }

        bool has(int index)
        {
            return m_obj->has(index);
        }

        int type(const char* name)
        {
            return m_obj->type(name);
        }

        int type(int index)
        {
            return m_obj->type(index);
        }

        int len()
        {
            return m_obj->len();
        }

        enumerator enumerate();

        table_obj*        m_obj;
    };

} // namespace lua_tinker

#endif //_LUA_TINKER_H_