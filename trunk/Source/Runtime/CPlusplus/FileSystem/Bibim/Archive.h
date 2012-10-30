#pragma once
#ifndef __BIBIM_ARCHIVE_H__
#define __BIBIM_ARCHIVE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>

    namespace Bibim
    {
        class Archive : public GameModule
        {
            BBModuleClass(Archive, GameModule, 'A', 'R', 'C', 'H');
            public:
                Archive();
                virtual ~Archive();
        };
    }

#   include <Bibim/Archive.inl>

#endif