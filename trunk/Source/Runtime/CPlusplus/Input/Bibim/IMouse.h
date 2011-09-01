#pragma once
#ifndef __BIBIM_MOUSE_INTERFACE_H__
#define __BIBIM_MOUSE_INTERFACE_H__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class IMouse
        {
            BBClassFOURCC('I', 'M', 'O', 'S');
            public:
                virtual ~IMouse() { }
        };
    }

#endif