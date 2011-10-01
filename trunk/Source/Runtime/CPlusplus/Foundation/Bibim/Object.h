#pragma once
#ifndef __BIBIM_OBJECT_H__
#define __BIBIM_OBJECT_H__

#   include <Bibim/Foundation.h>

    namespace Bibim
    {
#       define BBAbstractObjectClass(classname, parent) 
#       define BBObjectClass(classname, parent, a, b, c, d) public: \
                                                                static const uint32 ClassID = BBMakeFOURCC(a, b, c, d); \
                                                                virtual uint32 GetClassID() const { return ClassID; } \
                                                            private:

        class Object
        {
            public:
                virtual ~Object() { }

                virtual uint32 GetClassID() const { return 0; }

            protected:
                Object();
        };
    }

#   include <Bibim/Object.inl>

#endif