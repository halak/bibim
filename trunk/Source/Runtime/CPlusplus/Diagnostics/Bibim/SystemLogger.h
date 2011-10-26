#pragma once
#ifndef __BIBIM_SYSTEMLOGGER_H__
#define __BIBIM_SYSTEMLOGGER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Logger.h>

    namespace Bibim
    {
        class SystemLogger : public Logger
        {
            BBModuleClass(SystemLogger, Logger, 'S', 'L', 'O', 'G');
            public:
                SystemLogger();
                virtual ~SystemLogger();
        };
    }

#   include <Bibim/SystemLogger.inl>

#endif