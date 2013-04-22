#pragma once
#ifndef __BIBIM_SHAREDOBJECT_H__
#define __BIBIM_SHAREDOBJECT_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/Object.h>

    namespace lua_tinker
    {
        template<typename T> struct val2user;
        template<typename T> struct ptr2user;
        template<typename T> struct lua2enum;
        template<typename T> struct enum2lua;
    }

#   define BBBindLua(classname) \
        namespace lua_tinker \
        { \
            template<> inline void push(lua_State* L, classname* value) \
            { \
                push(L, static_cast<lua_value*>(value)); \
            } \
            \
            template<> inline void push(lua_State* L, const classname* value) \
            { \
                push(L, const_cast<lua_value*>(static_cast<const lua_value*>(value))); \
            } \
            template<> inline int push_for_return(lua_State* L, classname* value) \
            { \
                return push_for_return(L, static_cast<lua_value*>(value)); \
            } \
            \
            template<> inline int push_for_return(lua_State* L, const classname* value) \
            { \
                return push_for_return(L, const_cast<lua_value*>(static_cast<const lua_value*>(value))); \
            } \
            template<> \
            struct ptr2user<classname> : user \
            { \
                ptr2user(classname* t) : user((void*)t) \
                { \
                    ((classname*)m_p)->IncreaseReferenceCount(); \
                } \
                \
                ~ptr2user() \
                { \
                    ((classname*)m_p)->DecreaseReferenceCount(); \
                } \
            }; \
        }

#   define BBBindLuaEnum(enumname, toEnum, toString) \
        namespace lua_tinker \
        { \
            template<> \
            struct lua2enum<enumname> { static enumname invoke(lua_State *L, int index) { return toEnum(lua_tostring(L, index)); } }; \
            template<> \
            struct enum2lua<enumname> { static void invoke(lua_State *L, enumname val) { lua_pushstring(L, toString(val)); } }; \
        }

    namespace Bibim
    {
        class SharedObject;
        template <typename T> class SharedPointer;

        class SharedObject : public Object
        {
            public:
                virtual ~SharedObject();

            protected:
                SharedObject();
                SharedObject(const SharedObject& original);

                template <typename To> SharedPointer<To> This();
                template <typename To, typename ThisType> SharedPointer<To> This(ThisType* thisInstance);

            private:
                void IncreaseReferenceCount();
                void DecreaseReferenceCount();

            private:
                long referenceCount;

                template <typename T> friend class SharedPointer;
                template<typename T> friend struct lua_tinker::val2user;
                template<typename T> friend struct lua_tinker::ptr2user;

            private:
                SharedObject& operator = (const SharedObject&);
        };

        template <typename To> SharedPointer<To> SharedObject::This()
        {
            return SharedPointer<To>(static_cast<To*>(this));
        }

        template <typename To, typename ThisType> SharedPointer<To> SharedObject::This(ThisType* thisInstance)
        {
            return SharedPointer<To>(static_cast<To*>(thisInstance));
        }
    }

#endif