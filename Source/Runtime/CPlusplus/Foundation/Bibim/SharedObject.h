#pragma once
#ifndef __BIBIM_SHAREDOBJECT_H__
#define __BIBIM_SHAREDOBJECT_H__

#   include <Bibim/Foundation.h>

    namespace Bibim
    {
        class SharedObject;
        class SharedObjectLife;
        template <typename T> class SharedPointer;
        template <typename T> class WeakPointer;

        class SharedObject
        {
            public:
                virtual ~SharedObject();

            protected:
                SharedObject();
                SharedObject(const SharedObject& original);

                template <typename To> SharedPointer<To> This();
                template <typename To, typename ThisType> SharedPointer<To> This(ThisType* thisInstance);

            private:
                SharedObjectLife* life;

                template <typename T> friend class SharedPointer;
                template <typename T> friend class WeakPointer;

            private:
                SharedObject& operator = (const SharedObject&);
        };
    }

#   include <Bibim/SharedObject.inl>

#endif