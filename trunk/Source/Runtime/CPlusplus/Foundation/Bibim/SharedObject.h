#pragma once
#ifndef __BIBIM_SHAREDOBJECT_H__
#define __BIBIM_SHAREDOBJECT_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/Object.h>

    namespace lua_tinker { template<typename T> struct val2user; template<typename T> struct ptr2user; }

#   define BBBindLua(classname) \
        template<> inline void lua_tinker::push(lua_State* L, classname* value) \
        { \
            push(L, static_cast<lua_tinker::lua_value*>(value)); \
        } \
        \
        template<> inline void lua_tinker::push(lua_State* L, const classname* value) \
        { \
            push(L, const_cast<lua_tinker::lua_value*>(static_cast<const lua_tinker::lua_value*>(value))); \
        } \
        template<> inline int lua_tinker::push_for_return(lua_State* L, classname* value) \
        { \
            return push_for_return(L, static_cast<lua_tinker::lua_value*>(value)); \
        } \
        \
        template<> inline int lua_tinker::push_for_return(lua_State* L, const classname* value) \
        { \
            return push_for_return(L, const_cast<lua_tinker::lua_value*>(static_cast<const lua_tinker::lua_value*>(value))); \
        } \
	    template<> \
        struct lua_tinker::ptr2user<classname> : lua_tinker::user \
	    { \
		    ptr2user(classname* t) : lua_tinker::user((void*)t) \
            { \
                ((classname*)m_p)->IncreaseReferenceCount(); \
            } \
            \
		    ~ptr2user() \
            { \
                ((classname*)m_p)->DecreaseReferenceCount(); \
            } \
	    };

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
    }

#   include <Bibim/SharedObject.inl>

#endif