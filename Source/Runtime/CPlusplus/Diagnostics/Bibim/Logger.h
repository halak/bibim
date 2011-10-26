#pragma once
#ifndef __BIBIM_LOGGER_H__
#define __BIBIM_LOGGER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/Log.h>

    namespace Bibim
    {
        class Logger : public GameModule, public Log::Listener
        {
            BBAbstractModuleClass(Logger, GameModule);
            public:
                Logger();
                virtual ~Logger();
        };
    }

#   include <Bibim/Logger.inl>

#endif