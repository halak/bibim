#pragma once
#ifndef __BIBIM_OBJECT_H__
#define __BIBIM_OBJECT_H__

#include <Bibim/Foundation.h>
#include <Bibim/ClassInfo.h>

namespace Bibim
{
#   define BBAbstractObjectClass(classname, parent) private: \
                                                        typedef classname This; \
                                                        typedef parent Base; \
                                                    protected: \
                                                        virtual void to_lua(lua_State *L) { lua_tinker::type2lua(L, this); } \
                                                    private:
#   define BBObjectClass(classname, parent, a, b, c, d) BBAbstractObjectClass(classname, parent) \
                                                        public: \
                                                            static const int ClassID = BBMakeFOURCC(a, b, c, d); \
                                                            virtual int GetClassID() const { return ClassID; } \
                                                        private:

    class Object
    {
        public:
            static const ClassInfo Class;

        public:
            virtual ~Object() { }

            virtual const ClassInfo& GetClass() const;
            virtual int GetClassID() const;

            template <typename T> bool IsInstanceOf() const
            {
                return GetClassID() == T::ClassID;
            }

        protected:
            Object();
    };
}

#endif