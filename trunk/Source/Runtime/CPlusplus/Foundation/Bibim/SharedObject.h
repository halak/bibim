#pragma once
#ifndef __BIBIM_SHAREDOBJECT_H__
#define __BIBIM_SHAREDOBJECT_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/Object.h>

    namespace lua_tinker { template<typename T> struct val2user; }

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

            private:
                SharedObject& operator = (const SharedObject&);
        };
    }

#   include <Bibim/SharedObject.inl>

#endif