#pragma once
#ifndef __BIBIM_CHECKEDRELEASE_H__
#define __BIBIM_CHECKEDRELEASE_H__

#   include <Bibim/Config.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS))

        namespace Bibim
        {
            template <typename T> void CheckedRelease(T*& comObject)
            {
                if (comObject)
                {
                    comObject->Release();
                    comObject = 0;
                }
            }
        }

#   endif

#endif