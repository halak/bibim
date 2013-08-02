#pragma once
#ifndef __BIBIM_SCRIPTING_IO_H__
#define __BIBIM_SCRIPTING_IO_H__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        namespace ScriptLibrary
        {
            class IO
            {
                BBThisIsStaticClass(IO);
                public:
                    static const int  PrintID = BBMakeFOURCC('p', 'r', 'n', 't');
                    static       void Print(ScriptingContext& context);
            };
        }
    }

#endif