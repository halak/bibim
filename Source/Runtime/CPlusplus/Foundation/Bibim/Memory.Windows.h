#pragma once
#ifndef __BIBIM_MEMORY_WINDOWS_H__
#define __BIBIM_MEMORY_WINDOWS_H__

#   include <Bibim/FWD.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS))

        namespace Bibim
        {
            class Memory
            {
                BBThisIsStaticClass(Memory);
                public:
                    static void Fill(void* destination, int destinationLength);
                    static void Copy(void* destination, int destinationLength, const void* source, int sourceLength);
            };
        }

#   endif

#   endif