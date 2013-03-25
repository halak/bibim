#pragma once
#ifndef __BIBIM_PATH_H__
#define __BIBIM_PATH_H__

#   include <Bibim/FWD.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        class Path
        {
            BBThisIsStaticClass(Path);
            public:
                static String GetDirectory(const String& path);
                static bool IsAbsolutePath(const String& path);
        };
    }

#endif