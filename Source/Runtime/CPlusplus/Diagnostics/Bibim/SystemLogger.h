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

                virtual void Error(const char* category, const char* message);
                virtual void Warning(const char* category, const char* message);
                virtual void Information(const char* category, const char* message);

            private:
                inline void Write(const char* head, const char* category, const char* message);
        };
    }

#   include <Bibim/SystemLogger.inl>

#endif