#pragma once
#ifndef __BIBIM_FILELOGGER_H__
#define __BIBIM_FILELOGGER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Logger.h>

    namespace Bibim
    {
        class FileLogger : public Logger
        {
            BBModuleClass(FileLogger, Logger, 'F', 'L', 'O', 'G');
            public:
                FileLogger();
                virtual ~FileLogger();
        };
    }

#   include <Bibim/FileLogger.inl>

#endif