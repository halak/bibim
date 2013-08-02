#pragma once
#ifndef __BIBIM_MEMORY_H__
#define __BIBIM_MEMORY_H__

#   include <Bibim/Foundation.h>

    namespace Bibim
    {
        class Memory
        {
            BBThisIsStaticClass(Memory);
            public:
                static void* Alloc(int size);
                static void Free(void* pointer);
                static void Fill(void* destination, int destinationLength);
                static void Copy(void* destination, int destinationLength, const void* source, int sourceLength);
        };
    }

#endif