#pragma once
#ifndef __BIBIM_SYSTEMLOGGER_H__
#define __BIBIM_SYSTEMLOGGER_H__

#include <Bibim/FWD.h>
#include <Bibim/Logger.h>
#include <Bibim/String.h>

namespace Bibim
{
    class SystemLogger : public Logger
    {
        BBModuleClass(SystemLogger, Logger, 'S', 'L', 'O', 'G');
        public:
            SystemLogger();
            SystemLogger(const String& name);
            virtual ~SystemLogger();

            virtual void Error(const char* category, const char* message);
            virtual void Warning(const char* category, const char* message);
            virtual void Information(const char* category, const char* message);

            inline const String& GetName() const;
            inline void SetName(const String& value);

        private:
            inline void Write(const char* head, const char* category, const char* message);

        private:
            String name;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const String& SystemLogger::GetName() const
    {
        return name;
    }

    void SystemLogger::SetName(const String& value)
    {
        name = value;   
    }
}

#endif